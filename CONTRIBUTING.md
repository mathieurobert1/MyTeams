# Commitment standard

This project uses the Conventional Commits standard: https://www.conventionalcommits.org/en/v1.0.0/.
This standard automatically generates changelogs and determines the semantic version of the project.
The preferred language is English.

# Structure of a commit

A commit must follow the following structure:

<type>[optional scope]: <description>

[optional body]

[optional footer]

# Type

The type indicates the type of change made. The possible types are :

feat: New feature added
fix: Fix a bug
chore: Change not related to the code (documentation update, etc.)
docs: Documentation change
style: Change in code style
refactor: Refactoring the code
test: Addition or modification of a test
perf: Performance improvement
build: Change to the build system
ci: Change of continuous integration configuration
revert: Cancel a previous commit

# Scope

The scope is an optional string used to specify the area of the change.

# Description

The description is a brief description of the change. It must be clear and concise.

# Body

The body is an optional section which can contain additional information about the change.

# Footer

The footer is an optional section which may contain tracking information, such as the ticket number associated with the change.

# Examples

```
feat: Added a new feature
fix: Fixed a bug in the `foo` function
chore: Documentation update
docs: Addition of a tutorial
style: Correction of code formatting
refactor: Improved code structure
test: Added tests for the new functionality
perf: Improved performance of the `bar` function
build: Updated the build system
ci: Continuous integration configuration update
revert: Cancel the previous commit
```

By following these conventions, you make it easier to collaborate and maintain the project.
