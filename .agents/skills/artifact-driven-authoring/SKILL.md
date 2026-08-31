---
name: "artifact-driven-authoring"
description: "Author Artifact-Driven documentation - apply before you create or change files under docs/"
---

Apply this skill before you create or change a file under docs/.

Procedure:
1. Read docs/README.md, the Artifact-Driven governance, and the feature README.md of the target scope.
2. Resolve the scope id. Reuse the docs/features/<scope-id>/ directory that owns the topic. Create a new directory only for a new cohesive scope. Use lowercase ASCII letters, digits, and hyphens. Do not use an execution-system identifier.
3. Write each artifact in its own document boundary:
   - Requirements define the intended outcome, constraints, and acceptance criteria. They do not define a solution.
   - Specifications define current behavior, interfaces, data, rules, failure conditions, and verification. They do not record history or work status.
   - Decisions define one significant design choice with its context, options, decision, rationale, and consequences.
   - Tasks define actionable work that implementation status does not represent yet.
   - Implementation plans define the change sequence, dependencies, risks, and verification approach. They link to their tasks.
4. Create only the document areas the scope needs. Do not create empty template areas.
5. Link directly related artifacts with descriptive relative links: requirement and specification to each other, decision to its motivating requirement or specification, plan to its tasks.
6. Update the feature README.md scope, owner, concerns, and document links. Update docs/README.md when you add a feature scope.
7. Keep shared policy in docs/wiki/ and shared terms in docs/glossary/. Link to the canonical shared page. Do not duplicate its normative content.
8. Before completion, confirm one canonical document per topic and no duplicated normative content.

When the Delivery Workflow is active, record the owning ticket URL in delivery.ticket front matter. Do not add provider configuration, ticket state, or commands to the artifact.

