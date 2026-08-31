# Console Snake Game

## Scope

This feature scope defines a simple 2D snake game. The game runs in a console
on Linux and Windows.

## Scope Owner

hieutran21198 owns this scope.

## Included Concerns

- Gameplay rules for a simple 2D snake game.
- Console presentation of the game.
- Keyboard control of the game.
- Support for Linux and Windows.

## Excluded Concerns

- Graphical user interfaces outside the console.
- Network or multiplayer play.
- Persistent storage of scores or settings.
- Sound.
- Mobile and web platforms.

## Documents

- [Requirements: Console Snake Game](requirements/console-snake-game.md)
  defines the intended outcome, constraints, and acceptance criteria.

## Related Knowledge

- The `apps/snake` repository owns the implementation. See
  [Polyrepo Governance](../../wiki/governance/polyrepo.md).
- The [C++ Code Standard](../../wiki/standards/cpp.md) applies to the
  implementation.
