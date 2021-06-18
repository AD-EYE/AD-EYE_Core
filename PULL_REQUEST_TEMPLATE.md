# Pull Request Template

## Description

Please include a summary of the change and which issue is fixed. Please also include relevant motivation and context.


## Link to corresponding Trello card(s)


## Type of change

- [ ] Bug fix (fixes an issue)
- [ ] New feature (adds a functionality)
- [ ] Refactor (improves an existing functionality)


## How Has This Been Tested?

Please describe the tests that you ran to verify your changes. Provide instructions if needed so it can reproduced.
Also list any relevant details for your test configuration.


## Pull request Review Checklist:

#### Git
- [ ] Branch name: the name of the branch is descriptive
- [ ] Commit history: the history is clean and the commit have descriptive messages
- [ ] Authors: the commits have the proper author

#### General Pull Request steps
- [ ] Files: all the files modified are needed for the feature/bugfix
- [ ] Build: for C++ code, the code builds without error (`catkin_make`)
- [ ] Run: the feature runs without error and performs the intended task

#### Code specific steps
- [ ] Code conventions: the code follows the project conventions (https://gits-15.sys.kth.se/AD-EYE/AD-EYE_Core/wiki/Conventions)
- [ ] Variable names: the variables have descriptive names
- [ ] No magic numbers: there is no value in the code that is not assigned to a constant variable
- [ ] Doxygen tags: the code has tags for Doxygen as described on https://gits-15.sys.kth.se/AD-EYE/AD-EYE_Core/wiki/Code-Documentation (only for C++ and Python)
- [ ] Logic: the code logic performs the intended task and cannot be simplified
