[Previous (Worktree)](05_worktree.md) | [Back to Main](README.md) | [Next (Undoing Changes)](07_undoing_changes.md) | [Down](#quick-reference)

---
- [Stashing Changes](#stashing-changes)
	- [Overview](#overview)
	- [When to Use Stash](#when-to-use-stash)
	- [Basic Stashing](#basic-stashing)
		- [`git stash` - Save Changes](#git-stash---save-changes)
		- [`git stash save "message"` - Stash with Description](#git-stash-save-message---stash-with-description)
		- [`git stash list` - View Stashes](#git-stash-list---view-stashes)
		- [`git stash pop` - Apply and Remove](#git-stash-pop---apply-and-remove)
		- [`git stash apply` - Apply but Keep](#git-stash-apply---apply-but-keep)
		- [`git stash drop` - Delete Stash](#git-stash-drop---delete-stash)
	- [Advanced Stashing](#advanced-stashing)
		- [`git stash -u` - Include Untracked Files](#git-stash--u---include-untracked-files)
		- [`git stash -a` - Include All (Even Ignored)](#git-stash--a---include-all-even-ignored)
		- [`git stash -p` - Partial Stash](#git-stash--p---partial-stash)
		- [`git stash branch <name>` - Create Branch from Stash](#git-stash-branch-name---create-branch-from-stash)
	- [Real-World Scenarios](#real-world-scenarios)
		- [Scenario 1: Quick Bug Fix](#scenario-1-quick-bug-fix)
		- [Scenario 2: Pull with Conflicts](#scenario-2-pull-with-conflicts)
		- [Scenario 3: Experiment Without Committing](#scenario-3-experiment-without-committing)
	- [Stash vs Alternatives](#stash-vs-alternatives)
	- [Quick Reference](#quick-reference)

---

# Stashing Changes

## Overview

Temporarily save uncommitted changes without committing them. Perfect for quick context switches.

---

## When to Use Stash

✅ **Use stash when:**

- Quick branch switch needed
- Pull requires clean working directory
- Experiment with something else temporarily
- Not ready to commit but need clean state

❌ **Don't stash when:**

- Changes are ready to commit (just commit!)
- Long-term storage needed (use branches)
- Multiple parallel tasks (use worktrees)

---

## Basic Stashing

### `git stash` - Save Changes

```bash
# Make changes
echo "work in progress" >> file.txt

# Stash them
git stash

# Working directory is now clean
git status  # clean
```

---

### `git stash save "message"` - Stash with Description

```bash
git stash save "WIP: implementing login feature"

# Or modern syntax
git stash push -m "WIP: implementing login feature"
```

---

### `git stash list` - View Stashes

```bash
git stash list
```

**Output:**

```
stash@{0}: WIP on feature: implementing login
stash@{1}: WIP on main: bug fix
stash@{2}: WIP on develop: refactoring
```

---

### `git stash pop` - Apply and Remove

```bash
# Apply most recent stash and remove it
git stash pop

# Apply specific stash
git stash pop stash@{1}
```

---

### `git stash apply` - Apply but Keep

```bash
# Apply stash but keep it in list
git stash apply

# Apply specific stash
git stash apply stash@{2}
```

**Difference:**

- `pop`: apply + delete
- `apply`: apply + keep

---

### `git stash drop` - Delete Stash

```bash
# Delete most recent
git stash drop

# Delete specific
git stash drop stash@{1}

# Delete all
git stash clear
```

---

## Advanced Stashing

### `git stash -u` - Include Untracked Files

```bash
# Stash tracked and untracked files
git stash -u

# Or
git stash --include-untracked
```

---

### `git stash -a` - Include All (Even Ignored)

```bash
# Stash everything including .gitignore files
git stash -a

# Or
git stash --all
```

---

### `git stash -p` - Partial Stash

```bash
# Stash interactively
git stash -p
# Select which hunks to stash
```

---

### `git stash branch <name>` - Create Branch from Stash

```bash
# Create branch with stashed changes
git stash branch feature/new-work

# Useful when stash has conflicts with current branch
```

---

## Real-World Scenarios

### Scenario 1: Quick Bug Fix

```bash
# Working on feature
# ... coding ...

# Urgent bug reported on main!
git stash save "WIP: feature work"
git checkout main
git checkout -b hotfix/urgent

# Fix bug
git commit -am "Fix urgent bug"
git checkout main
git merge hotfix/urgent

# Back to feature
git checkout feature/work
git stash pop
# Continue working
```

---

### Scenario 2: Pull with Conflicts

```bash
# Try to pull
git pull
# error: Your local changes would be overwritten

# Stash changes
git stash
git pull
git stash pop

# Resolve any conflicts
```

---

### Scenario 3: Experiment Without Committing

```bash
# Stash current work
git stash

# Try different approach
# ... experiment ...

# Doesn't work, restore original
git stash pop
```

---

## Stash vs Alternatives

| Need                | Solution           |
| ------------------- | ------------------ |
| Quick switch        | Stash              |
| Long-term WIP       | Commit with "WIP:" |
| Parallel work       | Worktree           |
| Backup before risky | Branch             |

---

## Quick Reference

```bash
git stash                      # Stash changes
git stash save "msg"           # Stash with message
git stash -u                   # Include untracked
git stash -a                   # Include all (even ignored)
git stash -p                   # Interactive stash

git stash list                 # List stashes
git stash show                 # Show stash diff
git stash show -p              # Show full diff

git stash pop                  # Apply and remove
git stash apply                # Apply and keep
git stash drop                 # Delete stash
git stash clear                # Delete all stashes

git stash branch <name>        # Branch from stash
```

---
[Previous (Worktree)](05_worktree.md) | [Back to Main](README.md) | [Next (Undoing Changes)](07_undoing_changes.md) | [Top](#06---stashing-changes)
