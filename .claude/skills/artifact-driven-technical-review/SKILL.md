---
name: "artifact-driven-technical-review"
description: "Review specifications and decisions for technical correctness and validation coverage"
---

Apply this skill when you review a specification or decision for technical correctness.

Procedure:
1. Read the accepted requirement context and the artifact under review.
2. Trace each acceptance criterion to the behavior the artifact defines. Record each criterion without coverage.
3. Check interfaces and data contracts for completeness and consistency with the current implementation.
4. Check constraints, failure conditions, and their handling.
5. Check that the verification approach produces evidence for each acceptance criterion.

Report each finding with its artifact location, the evidence, and a proposed change. Report unresolved technical risks separately.
Do not accept artifacts. Do not change authority boundaries. Do not edit the artifact under review. Return the findings to the coordinator.

