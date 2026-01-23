[Previous (Remote Repository Management)](09_remote_repository_management.md) | [Back to Main](README.md) | [Next (Quick Reference)](11_quick_reference.md) | [Down](#quick-reference)

---
- [Overview](#Overview)
- [Types of Merges](#Types%20of%20Merges)
	- [Fast-Forward Merge](#Fast-Forward%20Merge)
	- [Three-Way Merge](#Three-Way%20Merge)
- [Part 1: Basic Merging](#Part%201:%20Basic%20Merging)
	- [`git merge <branch>`](#%60git%20merge%20%3Cbranch%3E%60)
	- [No Fast-Forward](#No%20Fast-Forward)
- [Part 2: Merge Conflicts](#Part%202:%20Merge%20Conflicts)
	- [What Causes Conflicts?](#What%20Causes%20Conflicts?)
	- [Resolving Conflicts](#Resolving%20Conflicts)
	- [Abort Merge](#Abort%20Merge)
- [Part 3: Rebase](#Part%203:%20Rebase)
	- [What is Rebase?](#What%20is%20Rebase?)
	- [Merge vs Rebase](#Merge%20vs%20Rebase)
	- [Interactive Rebase](#Interactive%20Rebase)
- [Part 4: Merge Strategies](#Part%204:%20Merge%20Strategies)
	- [Recursive (Default)](#Recursive%20(Default))
	- [Ours/Theirs](#Ours/Theirs)
- [Quick Reference](#Quick%20Reference)

---

# Merge Strategies

## Overview

Learn different ways to integrate changes from one branch to another.

---

## Types of Merges

### Fast-Forward Merge

When target branch hasn't diverged:

```
Before:  main:    A---B
                       \
         feature:       C---D

After:   main:    A---B---C---D
```

```bash
git checkout main
git merge feature  # Fast-forward
```

---

### Three-Way Merge

When branches have diverged:

```
Before:  main:    A---B---C
                       \
         feature:       D---E

After:   main:    A---B---C---M
                       \     /
         feature:       D---E
```

```bash
git checkout main
git merge feature  # Creates merge commit M
```

---

## Part 1: Basic Merging

### `git merge <branch>`

```bash
# Merge feature into current branch
git checkout main
git merge feature
```

---

### No Fast-Forward

Force creation of merge commit:

```bash
git merge --no-ff feature
```

**When to use:** Want explicit merge commit even if fast-forward possible.

---

## Part 2: Merge Conflicts

### What Causes Conflicts?

Same lines modified in both branches.

```bash
# Attempt merge
git merge feature
```

**Output:**

```
Auto-merging file.txt
CONFLICT (content): Merge conflict in file.txt
Automatic merge failed; fix conflicts and then commit the result.
```

---

### Resolving Conflicts

1. **Check status**
   
   ```bash
   git status
   ```

2. **Open conflicted file**
   
   ```c
   <<<<<<< HEAD
   // Your version
   =======
   // Their version
   >>>>>>> feature
   ```

3. **Resolve manually**
   
   ```c
   // Combined version
   ```

4. **Mark as resolved**
   
   ```bash
   git add file.txt
   git commit  # Complete the merge
   ```

---

### Abort Merge

```bash
# Cancel merge
git merge --abort
```

---

## Part 3: Rebase

### What is Rebase?

Move commits to new base.

```
Before:  main:    A---B---C
                       \
         feature:       D---E

After:   main:    A---B---C
                           \
         feature:           D'---E'
```

```bash
git checkout feature
git rebase main
```

---

### Merge vs Rebase

| Aspect       | Merge           | Rebase          |
| ------------ | --------------- | --------------- |
| **History**  | Non-linear      | Linear          |
| **Commits**  | Preserves all   | Rewrites        |
| **Safety**   | Safe            | Risky if shared |
| **Best for** | Shared branches | Local cleanup   |

---

### Interactive Rebase

```bash
# Rebase and edit last 3 commits
git rebase -i HEAD~3
```

**Options:**

```
pick abc123 First commit
reword def456 Second commit  # Change message
edit ghi789 Third commit     # Pause to modify
squash jkl012 Fourth commit  # Combine with previous
```

---

## Part 4: Merge Strategies

### Recursive (Default)

```bash
git merge feature
# Uses recursive strategy automatically
```

---

### Ours/Theirs

```bash
# Prefer our changes
git merge -X ours feature

# Prefer their changes
git merge -X theirs feature
```

---

## Quick Reference

```bash
# Merge
git merge <branch>             # Merge branch
git merge --no-ff <branch>     # Force merge commit
git merge --squash <branch>    # Squash into one commit
git merge --abort              # Cancel merge

# Rebase
git rebase <branch>            # Rebase onto branch
git rebase -i HEAD~n           # Interactive rebase
git rebase --continue          # After resolving
git rebase --abort             # Cancel rebase

# Conflict resolution
git status                     # Check conflicts
git add <file>                 # Mark resolved
git merge --continue           # Continue merge
```

---

---
[Previous (Remote Repository Management)](09_remote_repository_management.md) | [Back to Main](README.md) | [Next (Quick Reference)](11_quick_reference.md) | [Top](#10---merge-strategies)
