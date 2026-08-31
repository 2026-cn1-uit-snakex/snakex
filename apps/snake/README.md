# Snake

A terminal snake game. The snake is an array of points on an Oxy grid.

Supported platforms: Linux and Windows.

## Build

With `cmake` and a C++ compiler on `PATH`:

```sh
make          # or: cmake -S . -B build && cmake --build build
make run
```

Windows has no `make`. Use the `cmake` commands directly, or open this directory
in Visual Studio.

Inside the devenv shell, use `cpp-configure`, `cpp-build`, and `cpp-tidy`.

## Layout

- `src/domain/` holds the game model.
- `src/platform/` holds the console interface and one implementation for each
  platform. CMake selects the implementation.

The workspace [C++ Code Standard](../../docs/wiki/standards/cpp.md) applies.
