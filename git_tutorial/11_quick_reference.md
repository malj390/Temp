[Previous (Merge Strategies)](10_merge_strategies.md) | [Back to Main](README.md) | [Next (Best Practices)](12_best_practices.md) | [Down](#aliases-add-to-gitconfig)

---
- [Quick Reference Cheatsheet](#quick-reference-cheatsheet)
	- [Daily Commands](#daily-commands)
	- [Undo Commands](#undo-commands)
	- [Branch Workflows](#branch-workflows)
	- [Troubleshooting](#troubleshooting)
	- [Aliases (Add to gitconfig)](#aliases-add-to-gitconfig)
---

# Quick Reference Cheatsheet

## Daily Commands

```bash
# Status
git status                     # Check current state
git status -s                  # Short format

# Adding
git add <file>                 # Stage file
git add .                      # Stage all
git add -p                     # Interactive

# Committing
git commit -m "msg"            # Commit
git commit -am "msg"           # Stage + commit
git commit --amend             # Fix last commit

# Branches
git branch                     # List branches
git branch <n>              # Create branch
git checkout -b <n>         # Create + switch
git switch <n>              # Switch branch
git branch -d <n>           # Delete branch

# Remote
git pull                       # Fetch + merge
git push                       # Push changes
git push -u origin <branch>    # Set upstream
git fetch                      # Download only

# Info
git log --oneline              # Commit history
git diff                       # Unstaged changes
git diff --staged              # Staged changes
```

---

## Undo Commands

```bash
# Working directory
git restore <file>             # Discard changes
git restore .                  # Discard all

# Staging
git restore --staged <file>    # Unstage

# Commits
git reset --soft HEAD~1        # Uncommit
git reset HEAD~1               # Uncommit + unstage
git reset --hard HEAD~1        # Uncommit + discard
git revert <commit>            # Safe undo (public)

# Recovery
git reflog                     # See all actions
```

---

## Branch Workflows

```bash
# Feature workflow
git checkout main
git pull
git checkout -b feature/name
# ... work ...
git commit -am "Add feature"
git push -u origin feature/name

# Merge workflow
git checkout main
git pull
git merge feature/name
git push
git branch -d feature/name
```

---

## Troubleshooting

```bash
# "I committed to wrong branch"
git branch feature-branch      # Create branch at current commit
git reset --hard HEAD~1        # Move current branch back

# "I need to undo a pushed commit"
git revert <commit>            # Create inverse commit
git push

# "I have merge conflicts"
# Edit conflicted files
git add <resolved-files>
git commit

# "I want to discard everything"
git reset --hard HEAD
git clean -fd
```

---

## Aliases (Add to gitconfig)

```ini
[alias]
    st = status -s
    co = checkout
    br = branch
    ci = commit
    unstage = restore --staged
    last = log -1 HEAD
    visual = log --graph --oneline --all
    amend = commit --amend --no-edit
```

---

---
[Previous (Merge Strategies)](10_merge_strategies.md) | [Back to Main](README.md) | [Next (Best Practices)](12_best_practices.md) | [Top](#11---quick-reference-cheatsheet)
