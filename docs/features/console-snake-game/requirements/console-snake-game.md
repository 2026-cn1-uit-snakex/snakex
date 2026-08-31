---
delivery:
  ticket: "https://github.com/2026-cn1-uit-snakex/snakex/issues/2"
---

# Requirements: Console Snake Game

This document defines the intended outcome, constraints, and acceptance
criteria for the [Console Snake Game](../README.md) feature scope. It does not
define a solution, an architecture, or a task sequence.

## Intended Outcome

A player can play a simple 2D snake game in a console on Linux and on Windows.

The game MUST provide this gameplay:

- The game presents a rectangular 2D play field with a visible boundary.
- One snake moves on the play field in one of four directions: up, down, left,
  or right.
- The snake moves continuously at a regular interval without player input.
- The player changes the direction of the snake with the keyboard.
- The snake cannot reverse into its own body in one input.
- The game places one food item at a free position on the play field.
- When the snake reaches the food, the snake grows by one segment, the score
  increases, and the game places new food at a free position.
- The game shows the current score during play.
- The game ends when the snake collides with the play field boundary or with
  its own body.
- When the game ends, the game shows the final score and the player can exit
  or start a new game.
- The player can quit the game at any time with a keyboard command.

## Constraints

- The game MUST present all output in a console (terminal). It MUST NOT
  require a graphical window system.
- The game MUST read all player input from the keyboard.
- The game MUST run on Linux and on Windows.
- The gameplay rules MUST be the same on Linux and on Windows.
- The game MUST restore the console to a usable state when it exits, also
  after a player quit.
- The `apps/snake` repository owns the implementation. The
  [C++ Code Standard](../../../wiki/standards/cpp.md) applies to the
  implementation.
- The game MUST NOT require a network connection.
- The game MUST NOT require elevated (administrator or root) permissions.

## Acceptance Criteria

1. A player starts the game in a Linux terminal and completes one full game:
   the snake moves, eats food, grows, and the game ends on a collision.
2. A player starts the game in a Windows console and completes one full game
   with the same gameplay rules as on Linux.
3. The snake changes direction directly after a valid keyboard input, and it
   ignores an input that reverses it into its own body.
4. The score is visible during play, increases when the snake eats food, and
   is shown as the final score when the game ends.
5. Food never appears on a position that the snake occupies.
6. After the game ends, the player can start a new game without a restart of
   the program.
7. The player quits with a keyboard command, and the console returns to a
   usable state on both platforms.
8. The game runs in a standard console without a graphical window system,
   without a network connection, and without elevated permissions.
