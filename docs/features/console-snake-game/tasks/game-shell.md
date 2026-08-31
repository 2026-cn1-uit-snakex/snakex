---
delivery:
    ticket: https://github.com/2026-cn1-uit-snakex/snakex/issues/11
---
# Task: Game Shell

## Goal

Implement the game loop and the console presentation in the `apps/snake`
repository. Draw the boundary, the snake, the food, and the score line during
play. Show the end screen with the final score, start a new game on `r`, exit
on `q`, and quit on `q` during play. This task exclusively owns the
failure-condition handling: on a failure signal from the console interface,
report the error message, restore the console, and exit with a non-zero exit
code. Keep gameplay identical on Linux and on Windows.

This task depends on the
[Console Platform Layer](console-platform-layer.md) task and the
[Gameplay Core](gameplay-core.md) task.

## References

- [Specification: Console Presentation and Input](../specifications/console-snake-game.md#console-presentation-and-input)
- [Specification: Quit](../specifications/console-snake-game.md#quit)
- [Specification: Game End](../specifications/console-snake-game.md#game-end)
- [Specification: Failure Conditions](../specifications/console-snake-game.md#failure-conditions)
- [Specification: Verification](../specifications/console-snake-game.md#verification)

## Scope

- Write boundary: the `apps/snake` repository.
- Game loop, presentation, and program wiring. This task does not change the
  console interface operations or the gameplay rules.
- All drawing uses standard output after a Move cursor call. The console
  interface stays at the seven specified operations; this task does not add a
  write operation.

## Done Criteria

- Checks 1 to 8 and checks F1 and F2 from the specification
  [verification](../specifications/console-snake-game.md#verification) pass in
  a manual run on Linux.
- The Windows checks (criterion 2 and the Windows part of criterion 7) follow
  the verification rule in the
  [implementation plan](../implementation-plan/console-snake-game.md#verification-approach).
- The project builds and the test suite passes.
- `clang-tidy` reports no finding for the changed files.
