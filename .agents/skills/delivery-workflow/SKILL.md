---
name: "delivery-workflow"
description: "Correlate Artifact-Driven review units with delivery tickets and apply permitted ticket transitions"
---

Apply this skill when you create or transition a delivery ticket for an Artifact-Driven review unit.
For Phase 1, run dw draft --classification requirement with the title, one description paragraph, all Requirement artifacts, and one to ten eligible assignees.
For Phase 2, verify that the root Requirement is Accepted. Run dw handoff --requirement for each Specification and Decision ticket. Use the applicable classification and the same root Requirement.
For Phase 3, verify acceptance of the complete Phase 2 set. Run dw handoff --requirement with classification task for each Task ticket.
For phases 1-3, record each ticket URL in its artifacts under delivery.ticket front matter. Register the complete phase artifact set on one pull request. Assignment identifies GitHub work responsibility. It does not transfer artifact ownership or acceptance authority.
For Phase 4, start an accepted Ready Task without a new assignment prompt. It reuses its existing builder assignment. Register the implementation pull request with the Task Issue.
Verify the current pull request and ticket state before a transition. An accepted merge advances only the permitted ticket state. Archive phases 1-3 only after an explicit rejection. Keep an implementation ticket In Progress after rejection, close, or rework.

