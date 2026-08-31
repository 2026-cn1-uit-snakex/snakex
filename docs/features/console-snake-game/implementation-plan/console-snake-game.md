---
delivery:
    ticket: https://github.com/2026-cn1-uit-snakex/snakex/issues/9
---
# Implementation Plan: Console Snake Game

This document defines the change sequence, dependencies, risks, and
verification approach for the implementation of the
[Console Snake Game specification](../specifications/console-snake-game.md).
It links to its task definitions. It does not record execution-system status.

## Change Sequence

1. Implement the [Console Platform Layer](../tasks/console-platform-layer.md)
   task and the [Gameplay Core](../tasks/gameplay-core.md) task in parallel.
   The two tasks are independent.
2. Implement the [Game Shell](../tasks/game-shell.md) task after both tasks
   are complete.

## Dependencies

- The Game Shell task depends on the Console Platform Layer task and the
  Gameplay Core task.
- The Gameplay Core task has no platform dependency. Its logic and unit tests
  run without a real console.
- The Console Platform Layer task implements the specification
  [Platform Interface](../specifications/console-snake-game.md#platform-interface)
  exactly. A different interface shape breaks the Game Shell task.
- The Console Platform Layer task provides failure detection only. The Game
  Shell task owns the error message, the console restore on error, and the
  non-zero exit code.

## Risks

- Windows virtual-terminal support: an older Windows console does not support
  virtual-terminal sequences. The Windows implementation then needs a Console
  API fallback.
- Console restore: the game must restore the console on every exit path,
  including error paths. A missed path leaves the console unusable.
- Input coalescing: the last-valid-input rule and the reversal rule interact
  in one tick interval. An incorrect order of checks lets the snake reverse.

## Verification Approach

1. Build the project with CMake on Linux and on Windows.
2. Run the unit tests of the Gameplay Core task.
3. Run `clang-tidy` with no finding, as the
   [C++ Code Standard](../../../wiki/standards/cpp.md#validation) requires.
4. Run the checks in the specification
   [verification tables](../specifications/console-snake-game.md#verification)
   on Linux: criteria 1 to 8 and failure checks F1 and F2.
5. The Windows checks (criterion 2 and the Windows part of criterion 7) MUST
   run before the Game Shell task is reported complete, unless the validation
   report explicitly records them as not run with the reason, as the
   [C++ Code Standard](../../../wiki/standards/cpp.md#validation) requires.
