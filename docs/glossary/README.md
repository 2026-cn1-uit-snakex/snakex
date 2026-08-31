# Glossary

This glossary defines the shared terms of the project. Each entry defines one
term in one or two sentences. The linked canonical documents define the rules
that use the term. The
[Console Snake Game specification](../features/console-snake-game/specifications/console-snake-game.md)
is the authority for the game behavior behind these terms.

## Boundary

The visible frame around the play field. The boundary is not a playable cell.
See
[Play Field](../features/console-snake-game/specifications/console-snake-game.md#play-field).

## Console Interface

The project-owned interface that holds all platform-specific console
operations, with one POSIX implementation and one Windows implementation. See
[Platform Interface](../features/console-snake-game/specifications/console-snake-game.md#platform-interface).

## Direction

The heading of the snake: up, down, left, or right. See
[Snake Movement](../features/console-snake-game/specifications/console-snake-game.md#snake-movement).

## End Screen

The screen that the game shows when the game ends. See
[Game End](../features/console-snake-game/specifications/console-snake-game.md#game-end).

## Food

The one item on the play field that the snake eats to grow. See
[Food](../features/console-snake-game/specifications/console-snake-game.md#food).

## Free Cell

A playable cell that the snake does not occupy. See
[Food](../features/console-snake-game/specifications/console-snake-game.md#food).

## Game Start

The initial state of a new game. See
[Game Start](../features/console-snake-game/specifications/console-snake-game.md#game-start).

## Play Field

The bounded rectangle of playable cells where the game takes place. See
[Play Field](../features/console-snake-game/specifications/console-snake-game.md#play-field).

## Playable Cell

One cell of the play field that the snake or the food can occupy. See
[Play Field](../features/console-snake-game/specifications/console-snake-game.md#play-field).

## Raw Mode

A console mode that gives each key press to the game immediately, without echo
and without a wait for the Enter key. See
[Platform Interface](../features/console-snake-game/specifications/console-snake-game.md#platform-interface).

## Score

The point total that the player collects in one game. See
[Score](../features/console-snake-game/specifications/console-snake-game.md#score).

## Segment

One cell-sized part of the snake body. See
[Game Start](../features/console-snake-game/specifications/console-snake-game.md#game-start).

## Snake Head

The first segment of the snake in its direction of movement. See
[Game End](../features/console-snake-game/specifications/console-snake-game.md#game-end).

## Snake Tail

The last segment of the snake. See
[Game End](../features/console-snake-game/specifications/console-snake-game.md#game-end).

## Tick

One fixed time step of the game. See
[Snake Movement](../features/console-snake-game/specifications/console-snake-game.md#snake-movement).
