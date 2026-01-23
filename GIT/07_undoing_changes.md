[Previous (Stashing Changes)](06_stashing_changes.md) | [Back to Main](README.md) | [Next (Comparing Changes)](08_comparing_changes.md) | [Down](#quick-reference)

---
- [Undoing Changes](#undoing-changes)
	- [Overview](#overview)
	- [Understanding Undo Operations](#understanding-undo-operations)
	- [Part 1: Undoing Working Directory Changes](#part-1-undoing-working-directory-changes)
		- [`git restore <file>` - Discard Changes](#git-restore-file---discard-changes)
		- [`git checkout -- <file>` - Old Syntax](#git-checkout----file---old-syntax)
	- [Part 2: Unstaging Changes](#part-2-unstaging-changes)
		- [`git restore --staged <file>` - Unstage](#git-restore---staged-file---unstage)
		- [`git reset HEAD <file>` - Old Unstage](#git-reset-head-file---old-unstage)
	- [Part 3: Undoing Commits](#part-3-undoing-commits)
		- [`git reset --soft HEAD~1` - Uncommit, Keep Staged](#git-reset---soft-head1---uncommit-keep-staged)
		- [`git reset --mixed HEAD~1` - Uncommit, Unstage](#git-reset---mixed-head1---uncommit-unstage)
		- [`git reset --hard HEAD~1` - Completely Remove](#git-reset---hard-head1---completely-remove)
		- [Reset Comparison](#reset-comparison)
		- [Undoing Multiple Commits](#undoing-multiple-commits)
	- [Part 4: Reverting Commits](#part-4-reverting-commits)
		- [`git revert <commit>` - Create Inverse Commit](#git-revert-commit---create-inverse-commit)
		- [Revert vs Reset](#revert-vs-reset)
		- [Revert Multiple Commits](#revert-multiple-commits)
	- [Part 5: Recovering Lost Commits](#part-5-recovering-lost-commits)
		- [`git reflog` - See All HEAD Movements](#git-reflog---see-all-head-movements)
		- [Recovering After Hard Reset](#recovering-after-hard-reset)
	- [Part 6: Practical Scenarios](#part-6-practical-scenarios)
		- [Scenario 1: Fix Last Commit Message](#scenario-1-fix-last-commit-message)
		- [Scenario 2: Add Forgotten File to Last Commit](#scenario-2-add-forgotten-file-to-last-commit)
		- [Scenario 3: Undo Pushed Commit Safely](#scenario-3-undo-pushed-commit-safely)
		- [Scenario 4: Completely Undo Uncommitted Work](#scenario-4-completely-undo-uncommitted-work)
	- [Part 7: Clean Command](#part-7-clean-command)
		- [`git clean` - Remove Untracked Files](#git-clean---remove-untracked-files)
	- [Quick Reference](#quick-reference)

---

# Undoing Changes

## Overview

Learn to safely undo changes at various stages using reset, revert, and restore.

---

## Understanding Undo Operations

```
Working Dir → Staging → Repository → Remote
   restore    restore    reset       revert
             --staged
```

---

## Part 1: Undoing Working Directory Changes

### `git restore <file>` - Discard Changes

```bash
# Modified file, want to discard changes
echo "bad change" >> file.txt

# Restore to last commit
git restore file.txt

# Restore all files
git restore .
```

**⚠️ Warning:** Changes are permanently lost!

---

### `git checkout -- <file>` - Old Syntax

```bash
# Old way (still works)
git checkout -- file.txt

# Modern way (preferred)
git restore file.txt
```

---

## Part 2: Unstaging Changes

### `git restore --staged <file>` - Unstage

```bash
# Staged file
git add file.txt

# Unstage it
git restore --staged file.txt

# File still modified, just not staged
```

---

### `git reset HEAD <file>` - Old Unstage

```bash
# Old way
git reset HEAD file.txt

# Modern way
git restore --staged file.txt
```

---

## Part 3: Undoing Commits

### `git reset --soft HEAD~1` - Uncommit, Keep Staged

```bash
# Undo last commit, keep changes staged
git reset --soft HEAD~1

# Changes are staged, ready to recommit
git status  # Changes to be committed
```

**Use when:** Wrong commit message, forgot files

---

### `git reset --mixed HEAD~1` - Uncommit, Unstage

Default `git reset` behavior.

```bash
# Undo last commit, unstage changes
git reset HEAD~1

# Or explicitly
git reset --mixed HEAD~1

# Changes are in working directory, not staged
```

**Use when:** Want to modify changes before recommitting

---

### `git reset --hard HEAD~1` - Completely Remove

```bash
# Undo last commit, discard all changes
git reset --hard HEAD~1
```

**⚠️ DANGER:** Changes are permanently lost!

**Use when:** Commit was completely wrong

---

### Reset Comparison

| Option    | Commit | Staging   | Working Dir |
| --------- | ------ | --------- | ----------- |
| `--soft`  | ✓ Undo | Keep      | Keep        |
| `--mixed` | ✓ Undo | ✓ Unstage | Keep        |
| `--hard`  | ✓ Undo | ✓ Clear   | ✓ Discard   |

---

### Undoing Multiple Commits

```bash
# Undo last 3 commits
git reset --soft HEAD~3

# Undo to specific commit
git reset --soft abc123
```

---

## Part 4: Reverting Commits

### `git revert <commit>` - Create Inverse Commit

**When to use:**

- Commit already pushed to shared branch
- Want to keep history
- Safe undo for public commits

```bash
# Create new commit that undoes abc123
git revert abc123
```

**Example:**

```
Before:  A---B---C (C is bad)
After:   A---B---C---C' (C' undoes C)
```

---

### Revert vs Reset

| Aspect      | Revert          | Reset               |
| ----------- | --------------- | ------------------- |
| **History** | Preserves       | Rewrites            |
| **Safety**  | Safe for shared | Dangerous if pushed |
| **Method**  | New commit      | Move HEAD           |
| **Use on**  | Public branches | Local branches      |

---

### Revert Multiple Commits

```bash
# Revert range
git revert abc123..def456

# Revert without committing each
git revert -n abc123
git revert -n def456
git commit -m "Revert bad changes"
```

---

## Part 5: Recovering Lost Commits

### `git reflog` - See All HEAD Movements

```bash
git reflog
```

**Output:**

```
abc123 HEAD@{0}: reset: moving to HEAD~1
def456 HEAD@{1}: commit: Add feature
ghi789 HEAD@{2}: commit: Fix bug
```

---

### Recovering After Hard Reset

```bash
# Accidentally did hard reset
git reset --hard HEAD~3  # Oops!

# Find the lost commit
git reflog

# Restore it
git reset --hard HEAD@{1}
# or
git reset --hard abc123
```

---

## Part 6: Practical Scenarios

### Scenario 1: Fix Last Commit Message

```bash
git commit --amend -m "Correct message"
```

---

### Scenario 2: Add Forgotten File to Last Commit

```bash
# Made a commit
git commit -m "Add feature"

# Forgot a file!
git add forgotten.txt
git commit --amend --no-edit
```

---

### Scenario 3: Undo Pushed Commit Safely

```bash
# Commit was pushed
git log --oneline
# abc123 Bad commit
# def456 Good commit

# Use revert (safe for shared branch)
git revert abc123
git push
```

---

### Scenario 4: Completely Undo Uncommitted Work

```bash
# Discard all uncommitted changes
git restore .

# Also remove untracked files
git clean -fd
```

---

## Part 7: Clean Command

### `git clean` - Remove Untracked Files

```bash
# See what would be removed (dry run)
git clean -n

# Remove untracked files
git clean -f

# Remove untracked files and directories
git clean -fd

# Remove ignored files too
git clean -fdx
```

**⚠️ Warning:** Files are permanently deleted!

---

## Quick Reference

```bash
# Working directory
git restore <file>             # Discard changes
git restore .                  # Discard all

# Staging
git restore --staged <file>    # Unstage
git reset HEAD <file>          # Unstage (old)

# Commits (local only)
git reset --soft HEAD~1        # Uncommit, keep staged
git reset HEAD~1               # Uncommit, unstage
git reset --hard HEAD~1        # Uncommit, discard

# Commits (safe for shared)
git revert <commit>            # Inverse commit
git commit --amend             # Fix last commit

# Recovery
git reflog                     # See history
git reset --hard HEAD@{1}      # Restore from reflog

# Clean
git clean -n                   # Preview
git clean -fd                  # Remove untracked
```

---

---
[Previous (Stashing Changes)](06_stashing_changes.md) | [Back to Main](README.md) | [Next (Comparing Changes)](08_comparing_changes.md) | [Top](#07---undoing-changes)
