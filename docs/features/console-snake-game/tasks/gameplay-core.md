---
delivery:
    ticket: https://github.com/2026-cn1-uit-snakex/snakex/issues/10
---
# Task: Gameplay Core

## Goal

Implement the platform-neutral gameplay rules of the
[specification](../specifications/console-snake-game.md) as pure logic with
unit tests in the `apps/snake` repository. Cover the play field model, the
game start state, movement, direction change with the reversal rule and
last-input coalescing, food placement and growth, score, collision with the
tail-chase exception, and the game end when the play field is full. The code
has no dependency on the console interface.

## References

- [Specification: Play Field](../specifications/console-snake-game.md#play-field)
- [Specification: Game Start](../specifications/console-snake-game.md#game-start)
- [Specification: Snake Movement](../specifications/console-snake-game.md#snake-movement)
- [Specification: Food](../specifications/console-snake-game.md#food)
- [Specification: Score](../specifications/console-snake-game.md#score)
- [Specification: Game End](../specifications/console-snake-game.md#game-end)

## Scope

- Write boundary: the `apps/snake` repository.
- Gameplay logic and its unit tests only. This task does not use the console
  interface or other platform code.

## Done Criteria

- Unit tests cover each state and rule in the specification sections Play
  Field, Game Start, Snake Movement, Food, Score, and Game End, except the
  presentation rules that the [Game Shell](game-shell.md) task owns: show the
  score during play and show the end screen.
- The Play Field tests cover the field model, the 40 by 20 dimensions, and
  the rule that the boundary is not a playable cell. The Game Shell task owns
  the drawing of the boundary.
- The project builds and the test suite passes.
- `clang-tidy` reports no finding for the changed files.
