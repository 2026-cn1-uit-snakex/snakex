---
delivery:
    ticket: https://github.com/2026-cn1-uit-snakex/snakex/issues/9
---
# Task: Console Platform Layer

## Goal

Implement the console interface that the
[specification](../specifications/console-snake-game.md#platform-interface)
defines. Provide all seven operations with one POSIX implementation and one
Windows implementation in the `apps/snake` repository. This task provides
failure detection only: the initialize operation reports a failure to the
caller when the console cannot enter the required mode, and the report-size
operation lets the caller check the console size. The specification operation
table is a minimum, so a failure signal on initialize does not contradict it.

## References

- [Specification: Platform Interface](../specifications/console-snake-game.md#platform-interface)
- [Specification: Console Presentation and Input](../specifications/console-snake-game.md#console-presentation-and-input)
- [Specification: Failure Conditions](../specifications/console-snake-game.md#failure-conditions)
- [Decision: Platform Console Abstraction](../decisions/platform-console-abstraction.md)
- [C++ Code Standard: Platform Code](../../../wiki/standards/cpp.md#platform-code)

## Scope

- Write boundary: the `apps/snake` repository.
- Platform console code only. This task does not implement gameplay rules.
- Failure detection only. The [Game Shell](game-shell.md) task owns the error
  message, the console restore on error, and the non-zero exit code.

## Done Criteria

- The project builds on Linux and on Windows.
- A small test or probe exercises the seven operations and observes the
  failure signal from initialize, for example with standard input that is not
  a terminal.
- The test suite passes.
- `clang-tidy` reports no finding for the changed files.
