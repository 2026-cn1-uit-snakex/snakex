---
name: "artifact-driven-coordination"
description: "Coordinate Artifact-Driven work - apply when a request touches documentation, review, or delegated implementation"
---

Apply this skill when a request creates, changes, reviews, or implements Artifact-Driven documentation or its implementation.
The active primary agent is the coordinator. The coordinator routes work and collects evidence. It does not do expert work itself.

Procedure:
1. Read docs/README.md, the Artifact-Driven governance, and the applicable feature index.
2. Identify the cohesive change scope in docs/features/<scope-id>/ and the artifacts the request affects.
3. Route each unit of work to one expert agent:
   - Documentation scope, requirements, and artifact authoring: delegate to the scope-expert agent.
   - Technical correctness of specifications and decisions: delegate to the technical-expert agent.
   - Implementation changes: delegate to the implementation expert whose write boundary owns the repository path.
4. Give each delegation one bounded, explicit scope. State the scope id, the artifact paths that form the accepted context, the task, the write boundary, and the required output.
5. Collect the outputs and validation evidence from every delegated scope. Report them together with unresolved risks.

Do not accept artifacts. Do not resolve authority conflicts. Report these matters to the responsible scope owner and stop that unit of work.

When the Delivery Workflow is active, sequence delegations by phase: Requirement, then Specifications and Decisions, then Tasks and Plan, then Implementation.
Verify acceptance of the complete prior-phase set before you delegate the next phase.
Use the delivery-workflow skill for every ticket transition.

