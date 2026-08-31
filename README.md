# Snakex

Snakex is a simple 2D snake game for the console on Linux and Windows. The
project uses a polyrepo workspace layout and an artifact-driven documentation
model.

## Repository Layout

- [`apps/snake`](apps/snake/README.md) contains the game implementation in
  C++23.
- [`docs/`](docs/README.md) contains centralized project knowledge: feature
  scopes, the wiki, and the glossary.
- `deployment/` contains deployment concerns, including the delivery workflow
  configuration.
- `libs/` and `services/` are reserved repository categories with no content
  yet.

## Documentation

- [Project Knowledge](docs/README.md) indexes all documentation.
- [Console Snake Game](docs/features/console-snake-game/README.md) is the
  feature scope: requirement, specification, decision, tasks, and
  implementation plan.
- [Glossary](docs/glossary/README.md) defines the domain terms.
- [C++ Code Standard](docs/wiki/standards/cpp.md) defines how to write C++
  code.

## Development Environment

Enter the development shell with `devenv shell`. Inside the shell, run the
workspace scripts from `apps/snake`:

```sh
cpp-configure   # configure the CMake project
cpp-build       # build
cpp-test        # run the test suite
cpp-tidy        # run clang-tidy
```

Commit gates run as pre-commit hooks: clang-format, cmake-format,
markdownlint, and file hygiene checks.

Outside the shell, build with `make` or CMake directly. See the
[snake application README](apps/snake/README.md).

## How Work Flows

1. Read [Polyrepo Governance](docs/wiki/governance/polyrepo.md).
2. Read [Artifact-Driven Documentation Governance](docs/wiki/governance/documentation/artifact-driven/README.md).
3. Identify the cohesive change scope and the repository category that owns
   the implementation.

Define and maintain each change scope in `docs/features/<scope-id>/`. Keep
system-wide knowledge in `docs/wiki/`. Keep defined terms in
`docs/glossary/`. Implement the change in the applicable `apps/`, `services/`,
`libs/`, or `deployment/` repository, and keep implementation rules in that
repository.

The [Delivery Workflow](docs/wiki/governance/documentation/artifact-driven/delivery-workflow.md)
sequences the work in four phases: Requirement, then Specifications and
Decisions, then Tasks and Plan, then Implementation. Each phase is one review
unit: tickets, artifacts, and one pull request to `main`.
