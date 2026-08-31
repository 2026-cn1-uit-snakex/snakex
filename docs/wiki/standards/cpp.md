# C++ Code Standard

## Purpose

This standard defines how developers and AI agents write C++ code in this
system. It gives one consistent set of rules for every C++ repository.

## Why

A shared code standard removes repeated style discussions. It keeps code
readable when many people change it. It also lets automated tools accept or
reject a change without a human judgement.

## Scope

This standard applies to every C++ repository in `apps/`, `libs/`, and
`services/`. It applies to source files, header files, and build files.

This standard does not define application architecture. It does not define
the review or release process. The
[Delivery Workflow Governance](../governance/documentation/artifact-driven/delivery-workflow.md)
defines acceptance.

## Canonical Location

This document MUST be stored at `docs/wiki/standards/cpp.md`. This file is the
canonical C++ code standard.

Each repository holds the tool configuration that enforces this standard. A
repository MUST NOT state a different rule.

## Normative Terms

- `MUST` defines a mandatory rule.
- `MUST NOT` defines a prohibited rule.
- `SHOULD` defines a recommended rule.
- `SHOULD NOT` defines a discouraged rule.
- `MAY` defines an optional rule.

## Language

Code MUST use English. This rule applies to:

- Identifiers.
- Comments.
- Commit messages.
- Log and error messages.

Code MUST NOT use non-English identifiers. Code MUST NOT use abbreviations of
non-English words.

Replace a non-English identifier with the English term for the same concept.
Use the same English term for the same concept in all repositories.

## Language Revision

Code MUST target C++23.

The build MUST require the standard and MUST disable compiler extensions.

## Naming

| Element | Case | Example |
| --- | --- | --- |
| Namespace | `lower_case` | `snake` |
| Class, struct, enum, type alias | `PascalCase` | `Position` |
| Enum constant | `PascalCase` | `Direction::Right` |
| Function and method | `snake_case` | `move_cursor` |
| Variable and parameter | `snake_case` | `frame_delay` |
| Private and protected member | `snake_case` with a trailing underscore | `segments_` |
| Constant and `constexpr` variable | `PascalCase` | `FrameDelay` |
| Macro | `UPPER_CASE` | `SNAKE_VERSION` |

A name MUST state the purpose of the element. A name SHOULD NOT repeat the
type name.

The `.clang-tidy` file of each repository enforces these rules with the
`readability-identifier-naming` check.

## Formatting

The `.clang-format` file of each repository is authoritative for formatting.

Developers and AI agents MUST NOT format code by hand against this file. The
`clang-format` commit hook applies the format.

A repository MUST use the same `clang-format` version in the shell and in the
commit hook. Two versions can format the same file in two ways.

Build files MUST use the format of the `.cmake-format.yaml` file.

## Static Analysis

`clang-tidy` MUST report no finding for a changed file.

The `bugprone-*` checks are errors. A developer MUST correct the code. A
developer MUST NOT silence a `bugprone-*` finding with a comment.

For another check, a developer MAY add a `NOLINT` comment. The comment MUST
name the check and MUST state the reason.

## Types and Memory

Code MUST prefer a standard-library container to a raw array.

Code MUST prefer a standard-library algorithm to a manual loop when the
algorithm states the intent more clearly.

Code MUST NOT use `new` or `delete` directly. Use a container or a smart
pointer.

Code SHOULD use `[[nodiscard]]` for a function that returns a value and has no
other effect.

Code MUST use bounds-checked access when the index is not a constant.

## Errors

A function MUST report a failure it cannot handle. It MUST NOT hide the
failure.

`main` MUST NOT let an exception escape.

## Platform Code

Code MUST keep platform-specific calls behind one interface. Each supported
platform MUST have its own implementation of that interface.

Shared code MUST NOT contain a Windows-only or POSIX-only call.

A file that uses a platform interface MUST compile for every supported
platform.

## Validation

A developer or AI agent MUST run these checks before they report work as
complete:

1. Build the project.
2. Run the test suite.
3. Run `clang-tidy`.

The report MUST state the real result of each check. It MUST state a failure
as a failure. It MUST name each check that did not run.

A passing commit hook does not replace these checks.

## Expected Outcome

Every C++ repository uses the same language, names, format, and checks.
Automated tools enforce the rules. Reviewers read code instead of style.
