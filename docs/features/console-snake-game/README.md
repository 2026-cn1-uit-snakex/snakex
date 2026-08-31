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
- [Specification: Console Snake Game](specifications/console-snake-game.md)
  defines the behavior, interfaces, data, rules, failure conditions, and
  verification.
- [Decision: Platform Console Abstraction](decisions/platform-console-abstraction.md)
  defines the choice of a project-owned console interface with one POSIX and
  one Windows implementation.
- [Task: Console Platform Layer](tasks/console-platform-layer.md) defines the
  work to implement the console interface on POSIX and on Windows.
- [Task: Gameplay Core](tasks/gameplay-core.md) defines the work to implement
  the platform-neutral gameplay rules with unit tests.
- [Task: Game Shell](tasks/game-shell.md) defines the work to implement the
  game loop and the console presentation.
- [Implementation Plan: Console Snake Game](implementation-plan/console-snake-game.md)
  defines the change sequence, dependencies, risks, and verification approach.

## Related Knowledge

- The `apps/snake` repository owns the implementation. See
  [Polyrepo Governance](../../wiki/governance/polyrepo.md).
- The [C++ Code Standard](../../wiki/standards/cpp.md) applies to the
  implementation.
