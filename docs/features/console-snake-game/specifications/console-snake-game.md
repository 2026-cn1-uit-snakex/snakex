---
delivery:
    ticket: https://github.com/2026-cn1-uit-snakex/snakex/issues/6
---
# Specification: Console Snake Game

This document defines the behavior, interfaces, data, rules, failure
conditions, and verification of the [Console Snake Game](../README.md) feature
scope. It satisfies the
[Console Snake Game requirement](../requirements/console-snake-game.md). It
does not record change history, work status, tasks, or a solution narrative.

## Play Field

The play field is a bounded rectangle of playable cells.

- The play field MUST be 40 cells wide and 20 cells high.
- The game MUST draw a visible boundary around the play field.
- The boundary is not a playable cell. The snake and the food occupy only
  playable cells.

## Game Start

- A new game MUST start with a snake of 3 segments.
- The snake MUST spawn horizontally at the center of the play field.
- The initial direction MUST be right.
- The initial score MUST be 0.
- The `r` key on the end screen MUST start a new game from this same initial
  state.

Because the snake starts with 3 segments, the reversal rule in
[Snake Movement](#snake-movement) always has a body to protect at game start.

## Snake Movement

- The snake MUST move in one of four directions: up, down, left, or right.
- The direction keys MUST be `w` (up), `a` (left), `s` (down), and `d`
  (right).
- The game MUST advance the snake by one cell on each tick.
- The tick interval MUST be 150 milliseconds.
- A direction change from the keyboard MUST apply on the next tick.
- When the player enters more than one direction change in one tick interval,
  the game MUST apply the last valid input.
- The game MUST ignore an input that reverses the snake into its own body in
  one input. Example: the snake moves right and the body has more than one
  segment; the game ignores a left input.

## Food

- Exactly one food item MUST be on the play field during play.
- The game MUST place food only on a free cell. A free cell is a playable
  cell that the snake does not occupy.
- When the snake head reaches the food cell, the game MUST do all of these
  actions in one tick:
  1. Grow the snake by one segment.
  2. Increase the score by 10 points.
  3. Place new food on a free cell.
- When no free cell exists for new food, the game MUST end, because the snake
  fills the play field.

## Score

- The score starts at 0, as [Game Start](#game-start) defines.
- The game MUST show the current score during play.
- The game MUST show the final score on the end screen.

## Game End

The game ends when the snake head collides with the play field boundary or
with the snake body. A head move into a cell that the tail leaves on the same
tick is not a collision.

When the game ends, the game MUST show an end screen with:

- The final score.
- A keyboard command to start a new game without a restart of the program.
- A keyboard command to exit the program.

## Quit

- The `q` key MUST quit the game at any time during play.
- On the end screen, the `q` key MUST exit the program and the `r` key MUST
  start a new game.

## Console Presentation and Input

- The game MUST present all output in the console.
- The game MUST read all input from the keyboard, without a wait for the Enter
  key.
- The game MUST restore the console to a usable state on every exit path:
  normal game end, player quit, and error exit.

The [requirement constraints](../requirements/console-snake-game.md#constraints)
on network, permissions, and graphical window systems apply unchanged.

## Platform Interface

Gameplay logic MUST be platform-neutral. All platform-specific console calls
MUST stay behind one console interface, as the
[C++ Code Standard platform rule](../../../wiki/standards/cpp.md#platform-code)
defines. The interface MUST have one POSIX implementation and one Windows
implementation.

The console interface MUST provide these operations:

| Operation | Behavior |
| --- | --- |
| Initialize | Put the console into raw, non-echo, hidden-cursor mode. |
| Restore | Return the console to its previous usable mode. |
| Clear | Clear the console screen. |
| Move cursor | Position the cursor at a column and line. |
| Sleep | Wait a given number of milliseconds. |
| Report size | Return the console size in columns and lines. |
| Read key | Return one pressed key as one character, without a block when no key is pressed. |

Gameplay rules MUST be identical on Linux and on Windows. The key bindings
MUST be identical on both platforms. Only the console interface
implementations differ between the platforms.

## Failure Conditions

- When the console cannot enter the required mode, the game MUST report an
  error message, restore the console, and exit with a non-zero exit code.
- When the console is smaller than the play field plus the boundary and the
  score line, the game MUST report an error message that states the required
  size, restore the console, and exit with a non-zero exit code.

## Verification

Each check maps to one acceptance criterion of the
[requirement](../requirements/console-snake-game.md#acceptance-criteria).

| Criterion | Check |
| --- | --- |
| 1 | Play one full game in a Linux terminal: the snake moves, eats food, grows, and the game ends on a collision. |
| 2 | Play one full game in a Windows console and observe the same field size, tick interval, growth, and score rules as on Linux. |
| 3 | While the snake moves right, press `w` and observe the turn to up on the next tick; while the snake moves right, press `a` and observe no turn. |
| 4 | Observe the score during play, observe an increase of 10 after the snake eats food, and observe the same value as the final score on the end screen. |
| 5 | Eat food many times and observe that new food never appears on a cell that the snake occupies. |
| 6 | End a game, press `r` on the end screen, and observe a new game with score 0 without a program restart. |
| 7 | Press `q` during play on Linux and on Windows and observe a normal shell prompt with echo and a visible cursor. |
| 8 | Run the game in a standard console as a normal user without a network connection and observe a complete game. |

These checks verify the [failure conditions](#failure-conditions):

| Check | Procedure |
| --- | --- |
| F1 | Start the game where the console cannot enter the required mode, for example with standard input that is not a terminal. Observe an error message, a non-zero exit code, and a usable console. |
| F2 | Start the game in a console smaller than the required size. Observe an error message that states the required size, a non-zero exit code, and a usable console. |
