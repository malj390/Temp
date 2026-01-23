[Previous (Worktree)](05_worktree.md) | [Back to Main](README.md) | [Next (Undoing Changes)](07_undoing_changes.md) | [Down](#quick-reference)

---
- [Overview](#Overview)
- [When to Use Stash](#When%20to%20Use%20Stash)
- [Basic Stashing](#Basic%20Stashing)
	- [`git stash` - Save Changes](#%60git%20stash%60%20-%20Save%20Changes)
	- [`git stash save "message"` - Stash with Description](#%60git%20stash%20save%20%22message%22%60%20-%20Stash%20with%20Description)
	- [`git stash list` - View Stashes](#%60git%20stash%20list%60%20-%20View%20Stashes)
	- [`git stash pop` - Apply and Remove](#%60git%20stash%20pop%60%20-%20Apply%20and%20Remove)
	- [`git stash apply` - Apply but Keep](#%60git%20stash%20apply%60%20-%20Apply%20but%20Keep)
	- [`git stash drop` - Delete Stash](#%60git%20stash%20drop%60%20-%20Delete%20Stash)
- [Advanced Stashing](#Advanced%20Stashing)
	- [`git stash -u` - Include Untracked Files](#%60git%20stash%20-u%60%20-%20Include%20Untracked%20Files)
	- [`git stash -a` - Include All (Even Ignored)](#%60git%20stash%20-a%60%20-%20Include%20All%20(Even%20Ignored))
	- [`git stash -p` - Partial Stash](#%60git%20stash%20-p%60%20-%20Partial%20Stash)
	- [`git stash branch <name>` - Create Branch from Stash](#%60git%20stash%20branch%20%3Cname%3E%60%20-%20Create%20Branch%20from%20Stash)
- [Real-World Scenarios](#Real-World%20Scenarios)
	- [Scenario 1: Quick Bug Fix](#Scenario%201:%20Quick%20Bug%20Fix)
	- [Scenario 2: Pull with Conflicts](#Scenario%202:%20Pull%20with%20Conflicts)
	- [Scenario 3: Experiment Without Committing](#Scenario%203:%20Experiment%20Without%20Committing)
- [Stash vs Alternatives](#Stash%20vs%20Alternatives)
- [Quick Reference](#Quick%20Reference)

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
