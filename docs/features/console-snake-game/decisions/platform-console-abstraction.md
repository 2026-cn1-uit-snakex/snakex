---
delivery:
    ticket: https://github.com/2026-cn1-uit-snakex/snakex/issues/7
---
# Decision: Platform Console Abstraction

This document defines one design decision for the Console Snake Game: how the
game accesses the console on Linux and on Windows. It does not duplicate the
[Console Snake Game specification](../specifications/console-snake-game.md).

## Context

The [Console Snake Game requirement](../requirements/console-snake-game.md)
requires the same gameplay on Linux and on Windows, all output in a console,
raw keyboard input, and a restored console on every exit path. Linux and
Windows expose these console operations through different system interfaces.
The [C++ Code Standard](../../../wiki/standards/cpp.md#platform-code) requires
platform-specific calls behind one interface with one implementation per
platform.

## Considered Options

1. Use an external TUI library, for example ncurses on POSIX and PDCurses on
   Windows.
2. Use a project-owned thin console layer behind one interface, with one POSIX
   implementation and one Windows implementation.
3. Build two separate game programs, one for each platform.

## Decision

Use option 2: a project-owned thin console layer behind one interface, with
one POSIX implementation and one Windows implementation.

## Rationale

- The game needs only a small console surface: raw key input, cursor moves,
  screen clear, sleep, and console mode restore. An external TUI library adds
  a dependency for functions the game does not use.
- A project-owned layer adds no external dependency to the build on either
  platform.
- One interface with one implementation per platform aligns directly with the
  C++ Code Standard platform rule.
- Two separate programs (option 3) duplicate the gameplay logic and make
  identical gameplay rules on both platforms hard to keep.

## Consequences

- The project maintains two platform implementations of the console
  interface.
- The console interface stays limited to the operations that gameplay needs.
  A new console operation requires a change to both implementations.
- Tests target the console interface. Gameplay logic tests run without a real
  console on any platform.
