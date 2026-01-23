[Previous (Staging Changes)](03_stages.md) | [Back to Main](README.md) | [Next (Worktree)](05_worktree.md) | [Down](#quick-reference)

---
- [Overview](#Overview)
- [Understanding Cherry-Pick](#Understanding%20Cherry-Pick)
- [When to Use Cherry-Pick](#When%20to%20Use%20Cherry-Pick)
	- [✅ Good Use Cases](#%E2%9C%85%20Good%20Use%20Cases)
	- [❌ When NOT to Cherry-Pick](#%E2%9D%8C%20When%20NOT%20to%20Cherry-Pick)
- [Part 1: Basic Cherry-Pick](#Part%201:%20Basic%20Cherry-Pick)
	- [`git cherry-pick <commit>` - Apply Single Commit](#%60git%20cherry-pick%20%3Ccommit%3E%60%20-%20Apply%20Single%20Commit)
	- [Cherry-Pick Multiple Commits](#Cherry-Pick%20Multiple%20Commits)
- [Part 2: Handling Cherry-Pick Conflicts](#Part%202:%20Handling%20Cherry-Pick%20Conflicts)
	- [What Causes Conflicts?](#What%20Causes%20Conflicts?)
	- [Resolving Conflicts](#Resolving%20Conflicts)
		- [`git cherry-pick --abort`](#%60git%20cherry-pick%20--abort%60)
		- [`git cherry-pick --skip`](#%60git%20cherry-pick%20--skip%60)
- [Part 3: Cherry-Pick Options](#Part%203:%20Cherry-Pick%20Options)
	- [`git cherry-pick -n` - No Commit (Staging Only)](#%60git%20cherry-pick%20-n%60%20-%20No%20Commit%20(Staging%20Only))
	- [`git cherry-pick -x` - Record Source Commit](#%60git%20cherry-pick%20-x%60%20-%20Record%20Source%20Commit)
	- [`git cherry-pick --edit` - Edit Commit Message](#%60git%20cherry-pick%20--edit%60%20-%20Edit%20Commit%20Message)
	- [`git cherry-pick -m` - Cherry-Pick from Merge Commit](#%60git%20cherry-pick%20-m%60%20-%20Cherry-Pick%20from%20Merge%20Commit)
- [Part 4: Real-World Scenarios](#Part%204:%20Real-World%20Scenarios)
	- [Scenario 1: Bug Fix to Multiple Branches](#Scenario%201:%20Bug%20Fix%20to%20Multiple%20Branches)
	- [Scenario 2: Committed to Wrong Branch](#Scenario%202:%20Committed%20to%20Wrong%20Branch)
	- [Scenario 3: Extract Single Commit from Feature Branch](#Scenario%203:%20Extract%20Single%20Commit%20from%20Feature%20Branch)
	- [Scenario 4: Hotfix to Multiple Versions](#Scenario%204:%20Hotfix%20to%20Multiple%20Versions)
	- [Scenario 5: Undo an Accidental Revert](#Scenario%205:%20Undo%20an%20Accidental%20Revert)
- [Part 5: Testing Cherry-Picked Commits](#Part%205:%20Testing%20Cherry-Picked%20Commits)
	- [Your Original Scenario](#Your%20Original%20Scenario)
	- [Compare Different Commits](#Compare%20Different%20Commits)
- [Part 6: Advanced Cherry-Pick](#Part%206:%20Advanced%20Cherry-Pick)
	- [Cherry-Pick Range](#Cherry-Pick%20Range)
	- [Cherry-Pick with Strategy](#Cherry-Pick%20with%20Strategy)
	- [Interactive Cherry-Pick Selection](#Interactive%20Cherry-Pick%20Selection)
- [Part 7: Cherry-Pick vs Alternatives](#Part%207:%20Cherry-Pick%20vs%20Alternatives)
	- [Cherry-Pick vs Merge](#Cherry-Pick%20vs%20Merge)
	- [Cherry-Pick vs Rebase](#Cherry-Pick%20vs%20Rebase)
- [Practice Exercises](#Practice%20Exercises)
	- [Exercise 1: Basic Cherry-Pick](#Exercise%201:%20Basic%20Cherry-Pick)
	- [Exercise 2: Resolve Conflict](#Exercise%202:%20Resolve%20Conflict)
	- [Exercise 3: Selective Cherry-Pick](#Exercise%203:%20Selective%20Cherry-Pick)
- [Common Mistakes](#Common%20Mistakes)
	- [❌ Cherry-Picking Too Many Commits](#%E2%9D%8C%20Cherry-Picking%20Too%20Many%20Commits)
	- [✅ Use Merge Instead](#%E2%9C%85%20Use%20Merge%20Instead)
	- [❌ Not Recording Source](#%E2%9D%8C%20Not%20Recording%20Source)
	- [✅ Use -x Flag](#%E2%9C%85%20Use%20-x%20Flag)
	- [❌ Cherry-Picking on Shared Branches](#%E2%9D%8C%20Cherry-Picking%20on%20Shared%20Branches)
	- [✅ Cherry-Pick Only on Local/Personal Branches](#%E2%9C%85%20Cherry-Pick%20Only%20on%20Local/Personal%20Branches)
- [Quick Reference](#Quick%20Reference)

---

# Cherry-Pick Guide

## Overview

Cherry-pick lets you apply specific commits from one branch to another. It's like copying a commit to a different location.

---

## Understanding Cherry-Pick

```
Branch A:  A---B---C---D---E
                   ↓ cherry-pick C
Branch B:  X---Y---Z---C'
```

Cherry-pick creates a **new commit** (C') with the same changes as the original (C).

---

## When to Use Cherry-Pick

### ✅ Good Use Cases

1. **Apply a bug fix to multiple branches**
   
   ```
   Scenario: Fixed bug on main, need same fix on release branch
   ```

2. **Pull a specific feature from another branch**
   
   ```
   Scenario: Feature branch has 10 commits, only need commit #5
   ```

3. **Recover from wrong branch**
   
   ```
   Scenario: Committed on main instead of feature branch
   ```

4. **Apply hotfix to older releases**
   
   ```
   Scenario: Critical fix for v2.0 and v1.5
   ```

5. **Undo an accidental revert**
   
   ```
   Scenario: Revert was wrong, need to restore the commit
   ```

---

### ❌ When NOT to Cherry-Pick

1. **Many related commits** → Use merge or rebase instead
2. **Entire branch** → Use merge
3. **Maintaining history** → Cherry-pick obscures original context
4. **Shared branches** → Creates duplicate commits

---

## Part 1: Basic Cherry-Pick

### `git cherry-pick <commit>` - Apply Single Commit

**Example Setup:**

```bash
# On feature branch, make some commits
git checkout -b feature/api-v2
echo "commit 1" > file1.txt
git add file1.txt
git commit -m "Add feature A"

echo "commit 2" > file2.txt
git add file2.txt
git commit -m "Fix bug in parser"  # This is the one we want

echo "commit 3" > file3.txt
git add file3.txt
git commit -m "Add feature B"

# Get the bug fix commit hash
git log --oneline
```

**Output:**

```
a1b2c3d Add feature B
e4f5g6h Fix bug in parser    ← We want this one
i7j8k9l Add feature A
```

**Apply to main branch:**

```bash
# Switch to main
git checkout main

# Cherry-pick the bug fix
git cherry-pick e4f5g6h
```

**Output:**

```
[main m8n9o0p] Fix bug in parser
 Date: Sat Oct 25 10:30:00 2025
 1 file changed, 1 insertion(+)
 create mode 100644 file2.txt
```

**Verify:**

```bash
git log --oneline -3
```

```
m8n9o0p Fix bug in parser    ← New commit with same changes
p9q0r1s Previous commit
...
```

---

### Cherry-Pick Multiple Commits

```bash
# Cherry-pick commits in order
git cherry-pick abc123 def456 ghi789

# Or using range (exclusive start, inclusive end)
git cherry-pick abc123..ghi789

# Or using range (inclusive)
git cherry-pick abc123^..ghi789
```

**Example:**

```bash
# Apply commits C, D, and E
git cherry-pick C D E

# Or as range
git cherry-pick C^..E
```

---

## Part 2: Handling Cherry-Pick Conflicts

### What Causes Conflicts?

When the changes in the cherry-picked commit conflict with your current branch.

**Example:**

```bash
# feature branch changed line 5
# main branch also changed line 5 differently
# Cherry-pick will conflict
```

---

### Resolving Conflicts

**Example Scenario:**

```bash
# Try to cherry-pick
git cherry-pick abc123
```

**Output:**

```
error: could not apply abc123... Fix bug
hint: after resolving the conflicts, mark the corrected paths
hint: with 'git add <paths>' or 'git rm <paths>'
hint: and commit the result with 'git cherry-pick --continue'
```

**Resolution Steps:**

1. **Check conflict status**
   
   ```bash
   git status
   ```
   
   ```
   You are currently cherry-picking commit abc123.
   (fix conflicts and run "git cherry-pick --continue")
   (use "git cherry-pick --abort" to cancel)
   ```

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   src/main.c

```
2. **Open conflicted file**
```c
<<<<<<< HEAD
// Current branch version
void function() {
    printf("Version A
");
}
=======
// Cherry-picked version
void function() {
    printf("Version B
");
}
>>>>>>> abc123 (Fix bug)
```

3. **Resolve conflict manually**
   
   ```c
   // Choose one version or combine them
   void function() {
    printf("Combined Version
   ");
   }
   ```

4. **Mark as resolved and continue**
   
   ```bash
   # Stage resolved file
   git add src/main.c
   ```

# Continue cherry-pick

git cherry-pick --continue

```
5. **Edit commit message if needed**
```

Fix bug

(cherry picked from commit abc123)

# Conflicts resolved:

# - Combined changes from both versions

```
---

### Cherry-Pick Options During Conflicts

#### `git cherry-pick --continue`
After resolving conflicts, continue with the cherry-pick.

```bash
git add resolved-file.c
git cherry-pick --continue
```

---

#### `git cherry-pick --abort`

Cancel the cherry-pick, return to state before cherry-pick.

```bash
# Conflicts too complex, give up
git cherry-pick --abort
```

**When to abort:**

- Too many conflicts
- Wrong commit chosen
- Cherry-pick was a mistake

---

#### `git cherry-pick --skip`

Skip the current commit (when cherry-picking multiple).

```bash
# Cherry-picking A, B, C
# B has conflicts you want to skip
git cherry-pick --skip  # Skip B, continue with C
```

---

## Part 3: Cherry-Pick Options

### `git cherry-pick -n` - No Commit (Staging Only)

**When to use:**

- Want to modify changes before committing
- Combining multiple cherry-picks into one commit
- Need to review changes first

**Example:**

```bash
# Cherry-pick without committing
git cherry-pick -n abc123

# Changes are staged but not committed
git status
```

**Output:**

```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   src/main.c
```

**Use case - Combine multiple commits:**

```bash
# Cherry-pick two commits as one
git cherry-pick -n abc123
git cherry-pick -n def456

# Now commit them together
git commit -m "Combined fixes from commits abc123 and def456"
```

---

### `git cherry-pick -x` - Record Source Commit

**When to use:**

- Need traceability
- Corporate/open source requirements
- Backporting fixes

**Example:**

```bash
git cherry-pick -x abc123
```

**Resulting commit message:**

```
Fix critical bug

(cherry picked from commit abc123def456...)
```

This helps track where the change originally came from.

---

### `git cherry-pick --edit` - Edit Commit Message

**Example:**

```bash
# Cherry-pick and edit message
git cherry-pick --edit abc123

# Editor opens with original message
# Modify as needed
```

---

### `git cherry-pick -m` - Cherry-Pick from Merge Commit

**Context:** Merge commits have multiple parents.

```bash
# Merge commit has 2 parents
git show abc123
```

```
commit abc123 (merge commit)
Merge: parent1 parent2
```

**Specify which parent:**

```bash
# Use parent 1 as mainline
git cherry-pick -m 1 abc123

# Use parent 2 as mainline
git cherry-pick -m 2 abc123
```

Usually `-m 1` is what you want (the branch you merged into).

---

## Part 4: Real-World Scenarios

### Scenario 1: Bug Fix to Multiple Branches

**Setup:**

```
main:      A---B---C---D (bug fix)
                \
release-2.0:     E---F---G
```

**Goal:** Apply bug fix D to release-2.0

```bash
# On main, note the bug fix commit
git log --oneline -3
# d1e2f3g Fix critical security bug  ← This one

# Switch to release branch
git checkout release-2.0

# Cherry-pick the fix
git cherry-pick d1e2f3g -x

# Push to release
git push origin release-2.0
```

**Result:**

```
main:        A---B---C---D (original fix)
                  \
release-2.0:       E---F---G---D' (cherry-picked fix)
```

---

### Scenario 2: Committed to Wrong Branch

**Setup:**

```bash
# Oops, made commit on main instead of feature branch
git checkout main
# ... made changes ...
git commit -m "Add new feature"

git log --oneline -1
# a1b2c3d Add new feature  ← Need to move this
```

**Solution:**

```bash
# Note the commit hash
COMMIT_HASH=$(git rev-parse HEAD)

# Create feature branch at current commit
git branch feature/new-feature

# Move main back one commit (remove the commit from main)
git reset --hard HEAD~1

# Switch to feature branch
git checkout feature/new-feature

# Now the commit is only on feature branch
git log --oneline -1
```

**Alternative with cherry-pick:**

```bash
# Note commit hash first
COMMIT_HASH=a1b2c3d

# Reset main
git reset --hard HEAD~1

# Create and switch to feature branch
git checkout -b feature/new-feature

# Cherry-pick the commit
git cherry-pick $COMMIT_HASH
```

---

### Scenario 3: Extract Single Commit from Feature Branch

**Setup:**

```
feature/big-project:  A---B---C---D---E---F---G
                              ↑
                         Only want this one
```

**Goal:** Get commit C without A, B, D, E, F, G

```bash
# Create new branch from main
git checkout main
git checkout -b feature/specific-fix

# Cherry-pick only commit C
git cherry-pick <hash-of-C>

# Push
git push -u origin feature/specific-fix
```

---

### Scenario 4: Hotfix to Multiple Versions

**Setup:**

```
v1.0:  A---B---C
v2.0:  A---B---C---D---E---F
main:  A---B---C---D---E---F---G---H (hotfix here)
```

**Goal:** Apply hotfix H to v1.0 and v2.0

```bash
# Note hotfix commit
git checkout main
git log --oneline -1
# h1i2j3k Hotfix: resolve crash

# Apply to v2.0
git checkout v2.0
git cherry-pick h1i2j3k -x
git push origin v2.0

# Apply to v1.0 (might need conflict resolution)
git checkout v1.0
git cherry-pick h1i2j3k -x
# Resolve conflicts if any
git cherry-pick --continue
git push origin v1.0
```

---

### Scenario 5: Undo an Accidental Revert

**Setup:**

```bash
# Feature was merged
git log --oneline
# a1b2c3d Merge feature X

# Accidentally reverted
git revert a1b2c3d
# d4e5f6g Revert "Merge feature X"

# Oops, need feature X back!
```

**Solution:**

```bash
# Cherry-pick the original merge commit
git cherry-pick a1b2c3d -m 1

# Or revert the revert
git revert d4e5f6g
```

---

## Part 5: Testing Cherry-Picked Commits

### Your Original Scenario

**Goal:** Test a specific commit without merging

```bash
# From your current branch
git cherry-pick --abort  # If in middle of cherry-pick

# Create test branch from specific commit
git checkout -b test/commit-310 <commit-hash>

# Or create branch from current location
git checkout -b test/compare-approaches

# Cherry-pick to test
git cherry-pick <specific-commit>

# Test it
make
./program

# If good, you can merge later
# If bad, just delete the branch
git checkout main
git branch -D test/commit-310
```

---

### Compare Different Commits

```bash
# Test commit A
git checkout -b test/approach-a
git cherry-pick commit-A
# Test...

# Test commit B
git checkout main
git checkout -b test/approach-b
git cherry-pick commit-B
# Test...

# Compare
git diff test/approach-a test/approach-b
```

---

## Part 6: Advanced Cherry-Pick

### Cherry-Pick Range

```bash
# Cherry-pick commits from A to E (A is not included)
git cherry-pick A..E

# Cherry-pick commits from A to E (A is included)
git cherry-pick A^..E

# Example
git cherry-pick abc123^..def456
```

---

### Cherry-Pick with Strategy

```bash
# Use strategy for conflict resolution
git cherry-pick -X theirs abc123    # Favor their changes
git cherry-pick -X ours abc123      # Favor our changes
```

---

### Interactive Cherry-Pick Selection

```bash
# See commits on other branch
git log --oneline feature/other

# Pick specific ones interactively
git cherry-pick $(git log --oneline feature/other | fzf | cut -d' ' -f1)
```

---

## Part 7: Cherry-Pick vs Alternatives

### Cherry-Pick vs Merge

| Aspect       | Cherry-Pick                | Merge                    |
| ------------ | -------------------------- | ------------------------ |
| Use case     | Specific commits           | Entire branch            |
| History      | Creates new commits        | Preserves branch history |
| Traceability | Less clear origin          | Clear merge point        |
| Best for     | Bug fixes, single features | Complete features        |

**Example when to merge instead:**

```bash
# Bad: Cherry-pick 20 commits
git cherry-pick A B C D E F G H I J K L M N O P Q R S T

# Good: Merge the branch
git merge feature/complete-work
```

---

### Cherry-Pick vs Rebase

| Aspect    | Cherry-Pick             | Rebase                    |
| --------- | ----------------------- | ------------------------- |
| Direction | Pull commits to current | Replay current onto other |
| Use case  | Specific commits        | Entire branch update      |
| History   | Duplicates commits      | Rewrites history          |

**Example:**

```bash
# Cherry-pick: Pull specific commit from main to feature
git checkout feature/work
git cherry-pick abc123  # One commit from main

# Rebase: Move entire feature branch onto latest main
git checkout feature/work
git rebase main  # All feature commits onto main
```

---

## Practice Exercises

### Exercise 1: Basic Cherry-Pick

```bash
# Create two branches
git checkout -b branch-a
echo "fix" > fix.txt
git add fix.txt
git commit -m "Fix bug"
COMMIT=$(git rev-parse HEAD)

git checkout main
git checkout -b branch-b

# Cherry-pick the fix
git cherry-pick $COMMIT
```

---

### Exercise 2: Resolve Conflict

```bash
# Create conflict
git checkout -b branch-1
echo "version 1" > conflict.txt
git add conflict.txt
git commit -m "Version 1"
HASH=$(git rev-parse HEAD)

git checkout main
echo "version 2" > conflict.txt
git add conflict.txt
git commit -m "Version 2"

# Cherry-pick will conflict
git cherry-pick $HASH

# Resolve
# Edit conflict.txt
git add conflict.txt
git cherry-pick --continue
```

---

### Exercise 3: Selective Cherry-Pick

```bash
# Create branch with multiple commits
git checkout -b multi-commit
echo "a" > a.txt && git add a.txt && git commit -m "A"
echo "b" > b.txt && git add b.txt && git commit -m "B"
echo "c" > c.txt && git add c.txt && git commit -m "C"

# Get commit hashes
git log --oneline -3

# Cherry-pick only B
git checkout main
git cherry-pick <hash-of-B>
```

---

## Common Mistakes

### ❌ Cherry-Picking Too Many Commits

```bash
# Bad
git cherry-pick A B C D E F G H I J
```

### ✅ Use Merge Instead

```bash
# Good
git merge feature/branch
```

---

### ❌ Not Recording Source

```bash
# Bad (for important fixes)
git cherry-pick abc123
```

### ✅ Use -x Flag

```bash
# Good
git cherry-pick -x abc123
```

---

### ❌ Cherry-Picking on Shared Branches

Creates duplicate commits that confuse history.

### ✅ Cherry-Pick Only on Local/Personal Branches

---

## Quick Reference

```bash
# Basic cherry-pick
git cherry-pick <commit>            # Apply commit
git cherry-pick <A> <B> <C>         # Apply multiple
git cherry-pick A..C                # Apply range (A not included)
git cherry-pick A^..C               # Apply range (A included)

# Options
git cherry-pick -n <commit>         # Don't commit (stage only)
git cherry-pick -x <commit>         # Record source
git cherry-pick --edit <commit>     # Edit message
git cherry-pick -m 1 <commit>       # From merge (parent 1)

# Conflict handling
git cherry-pick --continue          # After resolving
git cherry-pick --abort             # Cancel
git cherry-pick --skip              # Skip this commit

# Strategies
git cherry-pick -X theirs <commit>  # Favor their changes
git cherry-pick -X ours <commit>    # Favor our changes
```

---

[Previous (Staging Changes)](03_stages.md) | [Back to Main](README.md) | [Next (Worktree)](05_worktree.md) | [Top](#cherry-pick-guide)
