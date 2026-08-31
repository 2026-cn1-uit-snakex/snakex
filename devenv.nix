{
  pkgs,
  lib,
  config,
  ...
}:
let
  # Single source of truth for the C++ revision this workspace targets.
  cxxStandard = "23";

  # Out-of-source build tree, relative to the repository you run a script in.
  buildDir = "build";

  onLinux = pkgs.stdenv.hostPlatform.isLinux;

  usableOn = pkg: lib.meta.availableOn pkgs.stdenv.hostPlatform pkg && !pkg.meta.broken;

  # Flags shared by every CMake configure step. The scripts run from the
  # repository that owns the CMake project, so the source directory is the CWD.
  configureFlags = lib.concatStringsSep " " (
    [
      "-S ."
      "-B ${buildDir}"
      # Named explicitly, not left to CXX. The stdenv compiler setup hook runs
      # after the environment below and puts g++ in CXX, which would give
      # clang-tidy and clangd a compilation database full of GCC-only flags.
      # The C compiler comes from CC instead: CMake only reads it when a project
      # enables C, so a C++-only project gets no unused-variable warning.
      "-DCMAKE_CXX_COMPILER=clang++"
      "-DCMAKE_CXX_STANDARD=${cxxStandard}"
      "-DCMAKE_CXX_STANDARD_REQUIRED=ON"
      "-DCMAKE_CXX_EXTENSIONS=OFF"
    ]
    # CMAKE_LINKER_TYPE needs CMake 3.29 or later.
    ++ lib.optional onLinux "-DCMAKE_LINKER_TYPE=MOLD"
  );

  # Gives a readable message instead of a CMake stack trace.
  requireProject = ''
    if [ ! -f CMakeLists.txt ]; then
      echo "cpp: no CMakeLists.txt in $PWD." >&2
      echo "cpp: run this from the repository that owns the CMake project." >&2
      exit 1
    fi
  '';

  requireBuildTree = ''
    if [ ! -f ${buildDir}/CMakeCache.txt ]; then
      echo "cpp: no configured build tree in $PWD/${buildDir}." >&2
      echo "cpp: run 'cpp-configure' first." >&2
      exit 1
    fi
  '';
in
{
  workspace = {
    composition = {
      use = "artifact-polyrepo-workspace";
      agent = {
        enable = true;
        clients = {
          claude.enable = true;
          opencode.enable = true;
        };
        implementationBoundary.mode = "required";
      };

      deliveryWorkflow = import ./deployment/ci-cd/delivery-workflow.nix {
        inherit pkgs lib config;
      };
    };
  };

  # Toolchain -----------------------------------------------------------------

  languages.cplusplus = {
    enable = true;
    # clang-tools already provides clangd. ccls would only duplicate it.
    lsp.enable = false;
  };

  packages =
    with pkgs;
    [
      # Build drivers
      ninja
      pkg-config
      ccache

      # llvm-cov, llvm-profdata, and llvm-symbolizer for coverage and for
      # symbolized sanitizer stack traces. Same LLVM release as clang-tools.
      llvmPackages.llvm

      # Static analysis and formatting
      cppcheck
      include-what-you-use
      cmake-format

      # Coverage reporting
      gcovr

      # Test frameworks, found through CMAKE_PREFIX_PATH
      gtest
      catch2_3
    ]
    ++ lib.optionals onLinux [
      mold # fast linker, selected by CMAKE_LINKER_TYPE
      gdb
    ]
    ++ lib.optional (!onLinux) lldb
    ++ lib.optional (usableOn valgrind) valgrind;

  # Defaults every CMake invocation reads from the environment ----------------

  env = {
    CMAKE_GENERATOR = "Ninja";
    CMAKE_EXPORT_COMPILE_COMMANDS = "ON";
    CMAKE_COLOR_DIAGNOSTICS = "ON";

    # Makes find_package see the test frameworks and libraries in this profile.
    CMAKE_PREFIX_PATH = config.devenv.profile;

    # Compiler cache, kept in the devenv state so 'devenv gc' can reclaim it.
    CCACHE_DIR = "${config.devenv.state}/ccache";
    CMAKE_C_COMPILER_LAUNCHER = "ccache";
    CMAKE_CXX_COMPILER_LAUNCHER = "ccache";

    # Sanitizer defaults. llvm-symbolizer is on PATH, so traces are symbolized.
    ASAN_OPTIONS = "detect_leaks=1:detect_stack_use_after_return=1:strict_string_checks=1:abort_on_error=1";
    UBSAN_OPTIONS = "print_stacktrace=1:halt_on_error=1";
  };

  # Tool configuration, seeded once and then owned by the repository ----------

  files = {
    ".clang-format" = {
      copyMode = "seed";
      text = ''
        # Seeded by devenv. Edit freely; devenv keeps your changes.
        ---
        BasedOnStyle: LLVM
        Standard: Latest
        ColumnLimit: 100
        IndentWidth: 2
        AccessModifierOffset: -2
        PointerAlignment: Left
        ReferenceAlignment: Left
        QualifierAlignment: Left
        BreakTemplateDeclarations: Yes
        BreakConstructorInitializers: BeforeColon
        PackConstructorInitializers: NextLine
        SeparateDefinitionBlocks: Always
        FixNamespaceComments: true
        IncludeBlocks: Regroup
        SortIncludes: CaseSensitive
        SortUsingDeclarations: true
        AllowShortFunctionsOnASingleLine: Empty
        AllowShortIfStatementsOnASingleLine: Never
        AllowShortLoopsOnASingleLine: false
        InsertBraces: true
        InsertNewlineAtEOF: true
        RemoveSemicolon: true
        SpaceAfterTemplateKeyword: false
      '';
    };

    ".clang-tidy" = {
      copyMode = "seed";
      text = ''
        # Seeded by devenv. Edit freely; devenv keeps your changes.
        ---
        Checks: >
          -*,
          bugprone-*,
          concurrency-*,
          cppcoreguidelines-*,
          misc-*,
          modernize-*,
          performance-*,
          portability-*,
          readability-*,
          -bugprone-easily-swappable-parameters,
          -cppcoreguidelines-avoid-magic-numbers,
          -misc-non-private-member-variables-in-classes,
          -modernize-use-trailing-return-type,
          -readability-magic-numbers
        WarningsAsErrors: 'bugprone-*'
        HeaderFilterRegex: '.*'
        FormatStyle: file
      '';
    };

    ".cmake-format.yaml" = {
      copyMode = "seed";
      text = ''
        # Seeded by devenv. Edit freely; devenv keeps your changes.
        ---
        format:
          line_width: 100
          tab_size: 2
          dangle_parens: true
          command_case: lower
          keyword_case: upper
        markup:
          enable_markup: false
      '';
    };
  };

  # Workflow. Run these from the repository that owns the CMake project. ------
  # Each one forwards extra arguments to the underlying tool.

  scripts = {
    cpp-configure = {
      description = "Configure the CMake project in the current directory";
      exec = ''
        set -euo pipefail
        ${requireProject}
        cmake ${configureFlags} "$@"
        ln -sfn ${buildDir}/compile_commands.json compile_commands.json
      '';
    };

    cpp-build = {
      description = "Build the configured CMake project";
      exec = ''
        set -euo pipefail
        ${requireBuildTree}
        cmake --build ${buildDir} "$@"
      '';
    };

    cpp-test = {
      description = "Run the CTest suite";
      exec = ''
        set -euo pipefail
        ${requireBuildTree}
        ctest --test-dir ${buildDir} --output-on-failure "$@"
      '';
    };

    cpp-tidy = {
      description = "Run clang-tidy over the compilation database";
      exec = ''
        set -euo pipefail
        ${requireBuildTree}
        run-clang-tidy -p ${buildDir} -quiet "$@"
      '';
    };

    cpp-iwyu = {
      description = "Report unused and missing includes";
      exec = ''
        set -euo pipefail
        ${requireBuildTree}
        iwyu_tool.py -p ${buildDir} "$@"
      '';
    };

    cpp-coverage = {
      description = "Report line coverage of an instrumented build tree";
      exec = ''
        set -euo pipefail
        ${requireBuildTree}
        gcovr --gcov-executable "llvm-cov gcov" \
          --root . --exclude '${buildDir}/' --print-summary "$@"
      '';
    };

    cpp-clean = {
      description = "Remove the build tree of the current directory";
      exec = ''
        set -euo pipefail
        rm -rf ${buildDir} compile_commands.json
      '';
    };
  };

  # Commit gates --------------------------------------------------------------

  git-hooks.hooks = {
    clang-format = {
      enable = true;
      # git-hooks.nix pins its own nixpkgs. Without this the hook would enforce
      # a different clang-format release than clangd and the shell use, and the
      # two would fight over the same files.
      package = pkgs.clang-tools;
      # The default also claims JSON and JavaScript files. Keep it to C and C++.
      types_or = lib.mkForce [
        "c"
        "c++"
      ];
    };

    cmake-format = {
      enable = true;
      package = pkgs.cmake-format;
      settings.inPlace = true;
    };
  };

  # 'devenv test' configures, builds, and runs the suite of the repository it
  # is invoked in, and stays quiet where there is no CMake project.
  # The stdenv compiler setup hook sets CC and CXX to gcc while it initializes
  # the shell. Point them back at clang once it has finished, so tools outside
  # CMake agree with the compilation database.
  enterShell = ''
    export CC=clang
    export CXX=clang++
  '';

  enterTest = ''
    if [ -f CMakeLists.txt ]; then
      cpp-configure
      cpp-build
      cpp-test
    fi
  '';
}
