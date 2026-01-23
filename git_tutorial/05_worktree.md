[Previous (Cherry-Pick)](04_cherry-pick.md) | [Back to Main](README.md) | [Next (Stashing Changes)](06_stashing_changes.md) | [Down](#key-takeaways)

---

- [Git Worktree](#git-worktree)
  - [Overview](#overview)
  - [The Problem Worktrees Solve](#the-problem-worktrees-solve)
  - [Part 1: Creating Worktrees](#part-1-creating-worktrees)
    - [`git worktree add <path> <branch>` - Create Worktree](#git-worktree-add-path-branch---create-worktree)
    - [Create Worktree with New Branch](#create-worktree-with-new-branch)
    - [Create Worktree from Specific Commit](#create-worktree-from-specific-commit)
  - [Part 2: Viewing Worktrees](#part-2-viewing-worktrees)
    - [`git worktree list` - Show All Worktrees](#git-worktree-list---show-all-worktrees)
    - [`git worktree list --porcelain` - Detailed Info](#git-worktree-list---porcelain---detailed-info)
  - [Part 3: Removing Worktrees](#part-3-removing-worktrees)
    - [`git worktree remove <path>` - Remove Worktree](#git-worktree-remove-path---remove-worktree)
    - [Cleanup Workflow](#cleanup-workflow)
    - [`git worktree prune` - Clean Up Stale References](#git-worktree-prune---clean-up-stale-references)
  - [Part 4: Real-World Scenarios](#part-4-real-world-scenarios)
    - [Scenario 1: Feature Development + Urgent Hotfix](#scenario-1-feature-development--urgent-hotfix)
    - [Scenario 2: Multiple Features in Parallel](#scenario-2-multiple-features-in-parallel)
    - [Scenario 3: Code Review Different Branches](#scenario-3-code-review-different-branches)
    - [Scenario 4: Testing Different Versions](#scenario-4-testing-different-versions)
    - [Scenario 5: Building Multiple Configurations](#scenario-5-building-multiple-configurations)
  - [Part 5: Worktree Best Practices](#part-5-worktree-best-practices)
    - [Directory Naming Conventions](#directory-naming-conventions)
    - [When to Use Worktrees](#when-to-use-worktrees)
    - [Workflow Pattern](#workflow-pattern)
  - [Part 6: Worktree Limitations](#part-6-worktree-limitations)
    - [Can't Check Out Same Branch Twice](#cant-check-out-same-branch-twice)
    - [Shared Git Directory](#shared-git-directory)
    - [Disk Space](#disk-space)
  - [Part 7: Advanced Worktree Usage](#part-7-advanced-worktree-usage)
    - [Detached HEAD Worktree](#detached-head-worktree)
    - [Worktree with Sparse Checkout](#worktree-with-sparse-checkout)
    - [Moving Worktrees](#moving-worktrees)
  - [Part 8: Troubleshooting](#part-8-troubleshooting)
    - [Problem: Worktree Directory Deleted Manually](#problem-worktree-directory-deleted-manually)
    - [Problem: Can't Create Worktree - Branch Exists](#problem-cant-create-worktree---branch-exists)
    - [Problem: Lost Track of Worktrees](#problem-lost-track-of-worktrees)
  - [Practice Exercises](#practice-exercises)
    - [Exercise 1: Basic Worktree Workflow](#exercise-1-basic-worktree-workflow)
    - [Exercise 2: Parallel Development](#exercise-2-parallel-development)
    - [Exercise 3: Hotfix Interrupt](#exercise-3-hotfix-interrupt)
  - [Comparison: Worktree vs Alternatives](#comparison-worktree-vs-alternatives)
    - [Worktree vs Stash](#worktree-vs-stash)
    - [Worktree vs Clone](#worktree-vs-clone)
    - [Worktree vs Branch Switch](#worktree-vs-branch-switch)
  - [Quick Reference](#quick-reference)
  - [Key Takeaways](#key-takeaways)

---

# Git Worktree

## Overview

Worktrees let you check out multiple branches simultaneously in different directories. Work on multiple features/fixes without constant branch switching.

---

## The Problem Worktrees Solve

**Traditional workflow:**

```bash
# Working on feature
git checkout feature/api
# ... coding ...

# Urgent hotfix needed!
git stash                    # Save current work
git checkout main
git checkout -b hotfix/critical
# ... fix bug ...
git checkout feature/api
git stash pop                # Restore work
```

**With worktrees:**

```
project/                     ← main worktree (main branch)
project-feature-api/         ← worktree (feature/api branch)
project-hotfix/              ← worktree (hotfix/critical branch)
```

Work in all three simultaneously! No stashing, no switching.

---

## Part 1: Creating Worktrees

### `git worktree add <path> <branch>` - Create Worktree

**Example:**

```bash
# Currently in main repo
cd ~/projects/myapp

# Create worktree for feature branch
git worktree add ../myapp-feature feature/new-ui

# Directory structure now:
# ~/projects/myapp/              (main branch)
# ~/projects/myapp-feature/      (feature/new-ui branch)
```

**Work in both:**

```bash
# Terminal 1
cd ~/projects/myapp
# Work on main

# Terminal 2
cd ~/projects/myapp-feature
# Work on feature
```

---

### Create Worktree with New Branch

```bash
# Create new branch and worktree
git worktree add -b feature/dashboard ../myapp-dashboard

# Or explicit branch creation
git worktree add ../myapp-dashboard -b feature/dashboard main
```

---

### Create Worktree from Specific Commit

```bash
# Create worktree from commit
git worktree add ../myapp-hotfix abc123

# Create worktree from tag
git worktree add ../myapp-v2.0 v2.0.0
```

---

## Part 2: Viewing Worktrees

### `git worktree list` - Show All Worktrees

**Example:**

```bash
git worktree list
```

**Output:**

```
/Users/dev/projects/myapp              abc123 [main]
/Users/dev/projects/myapp-feature      def456 [feature/new-ui]
/Users/dev/projects/myapp-hotfix       ghi789 [hotfix/critical]
```

---

### `git worktree list --porcelain` - Detailed Info

```bash
git worktree list --porcelain
```

**Output:**

```
worktree /Users/dev/projects/myapp
HEAD abc123def456...
branch refs/heads/main

worktree /Users/dev/projects/myapp-feature
HEAD def456ghi789...
branch refs/heads/feature/new-ui

worktree /Users/dev/projects/myapp-hotfix
HEAD ghi789jkl012...
branch refs/heads/hotfix/critical
```

---

## Part 3: Removing Worktrees

### `git worktree remove <path>` - Remove Worktree

**Example:**

```bash
# Remove worktree
git worktree remove ../myapp-feature

# Or if already deleted the directory
git worktree prune
```

---

### Cleanup Workflow

```bash
# 1. Finish work in worktree
cd ../myapp-feature
git add .
git commit -m "Complete feature"
git push

# 2. Merge to main (from main worktree)
cd ../myapp
git checkout main
git merge feature/new-ui

# 3. Remove worktree
git worktree remove ../myapp-feature

# 4. Delete branch if done
git branch -d feature/new-ui
```

---

### `git worktree prune` - Clean Up Stale References

```bash
# If you manually deleted worktree directories
rm -rf ../myapp-feature

# Clean up Git's records
git worktree prune

# Check what will be pruned (dry run)
git worktree prune --dry-run
```

---

## Part 4: Real-World Scenarios

### Scenario 1: Feature Development + Urgent Hotfix

**Setup:**

```bash
# Main project
cd ~/projects/myapp

# Start feature (worktree)
git worktree add ../myapp-feature -b feature/dashboard

# Work on feature
cd ../myapp-feature
# ... hours of work ...
```

**Urgent bug reported!**

```bash
# Create hotfix worktree (from original repo)
cd ~/projects/myapp
git worktree add ../myapp-hotfix -b hotfix/crash-fix

# Fix bug
cd ../myapp-hotfix
# ... fix bug ...
git commit -am "fix: resolve crash on startup"
git push

# Merge hotfix
cd ~/projects/myapp
git merge hotfix/crash-fix
git push

# Remove hotfix worktree
git worktree remove ../myapp-hotfix

# Continue feature work
cd ../myapp-feature
# ... continue where you left off ...
```

**No stashing required!**

---

### Scenario 2: Multiple Features in Parallel

```bash
# Create worktrees for different features
git worktree add ../myapp-auth -b feature/auth
git worktree add ../myapp-ui -b feature/ui-redesign
git worktree add ../myapp-api -b feature/api-v2

# Work on all in parallel
# Terminal 1: cd ../myapp-auth
# Terminal 2: cd ../myapp-ui
# Terminal 3: cd ../myapp-api

# When done, merge them one by one
cd ~/projects/myapp
git merge feature/auth
git merge feature/ui-redesign
git merge feature/api-v2

# Cleanup
git worktree remove ../myapp-auth
git worktree remove ../myapp-ui
git worktree remove ../myapp-api
```

---

### Scenario 3: Code Review Different Branches

```bash
# Reviewer workflow
git worktree add ../review-pr-123 origin/feature/pr-123
cd ../review-pr-123
# ... review code ...
# ... test ...

# While reviewing, work continues on main
cd ~/projects/myapp
# ... continue your work ...

# Done reviewing
git worktree remove ../review-pr-123
```

---

### Scenario 4: Testing Different Versions

```bash
# Test v1.0 and v2.0 simultaneously
git worktree add ../myapp-v1 v1.0.0
git worktree add ../myapp-v2 v2.0.0

# Terminal 1
cd ../myapp-v1
make && ./app

# Terminal 2
cd ../myapp-v2
make && ./app

# Compare behavior
```

---

### Scenario 5: Building Multiple Configurations

**Your specific case:**

```bash
# Main development
cd ~/projects/philosophers

# Create worktree to test specific commit
git worktree add ../philo-test-310 abc123

# Work in main
cd ~/projects/philosophers
# ... normal development ...

# Test specific commit
cd ../philo-test-310
make
./philo 5 800 200 200

# Clean code, no conflicts!
# Both environments independent

# When done testing
cd ~/projects/philosophers
git worktree remove ../philo-test-310
```

---

## Part 5: Worktree Best Practices

### Directory Naming Conventions

```bash
# Good: Descriptive names
project/                    # Main
project-feature-auth/       # Feature
project-hotfix-123/         # Hotfix
project-review-pr-45/       # Review

# Bad: Confusing names
project/
project2/
project-new/
project-copy/
```

---

### When to Use Worktrees

✅ **Use worktrees for:**

- Urgent interruptions (hotfixes while coding)
- Parallel feature development
- Code reviews
- Testing different branches
- Building multiple versions
- Comparing implementations

❌ **Don't use worktrees for:**

- Simple branch switches (use `git checkout`)
- Short-lived changes (use `git stash`)
- Single task focus

---

### Workflow Pattern

```bash
# 1. Create worktree for task
git worktree add <path> -b <branch>

# 2. Work in worktree
cd <path>
# ... code ...
git commit

# 3. Push and merge
git push
cd <main-repo>
git merge <branch>

# 4. Cleanup
git worktree remove <path>
git branch -d <branch>
```

---

## Part 6: Worktree Limitations

### Can't Check Out Same Branch Twice

```bash
# This fails:
git worktree add ../copy1 main
git worktree add ../copy2 main  # ERROR!
```

**Error:**

```
fatal: 'main' is already checked out at '/path/to/myapp'
```

**Solution:** Use different branches or create from commit:

```bash
git worktree add ../copy2 -b temp-main main
```

---

### Shared Git Directory

All worktrees share the same `.git` directory (in main worktree).

**Implications:**

- Commits in any worktree affect the same repository
- Branches are shared across all worktrees
- Config is shared
- Remotes are shared

---

### Disk Space

Each worktree is a full working directory.

```bash
# Main: 500MB
# Worktree 1: 500MB
# Worktree 2: 500MB
# Total: 1.5GB
```

More disk space than stashing, but worth it for the flexibility.

---

## Part 7: Advanced Worktree Usage

### Detached HEAD Worktree

```bash
# Create worktree at specific commit (detached HEAD)
git worktree add ../test-commit abc123

cd ../test-commit
git status
# HEAD detached at abc123
```

**Use case:** Testing without affecting branches.

---

### Worktree with Sparse Checkout

For large repos, check out only specific paths:

```bash
# Create worktree
git worktree add ../myapp-docs

# Configure sparse checkout
cd ../myapp-docs
git sparse-checkout init
git sparse-checkout set docs/
# Now only docs/ directory is checked out
```

---

### Moving Worktrees

```bash
# Move worktree to new location
mv ../myapp-feature ../new-location/myapp-feature

# Update Git's records
git worktree repair ../new-location/myapp-feature
```

---

## Part 8: Troubleshooting

### Problem: Worktree Directory Deleted Manually

```bash
# Oops, deleted without git worktree remove
rm -rf ../myapp-feature

# Git still thinks it exists
git worktree list  # Shows deleted path

# Clean up
git worktree prune
```

---

### Problem: Can't Create Worktree - Branch Exists

```bash
git worktree add ../new -b feature/exists
# fatal: 'feature/exists' is already checked out
```

**Solutions:**

```bash
# Solution 1: Use different branch name
git worktree add ../new -b feature/exists-2

# Solution 2: Remove other worktree first
git worktree remove <path-with-that-branch>

# Solution 3: Check out at commit without branch
git worktree add ../new <commit-hash>
```

---

### Problem: Lost Track of Worktrees

```bash
# List all worktrees
git worktree list

# Remove stale ones
git worktree prune

# Force remove if needed
git worktree remove --force <path>
```

---

## Practice Exercises

### Exercise 1: Basic Worktree Workflow

```bash
# Create worktree
git worktree add ../myapp-feature -b feature/test

# Work in it
cd ../myapp-feature
echo "feature" > feature.txt
git add feature.txt
git commit -m "Add feature"

# Merge back
cd -
git merge feature/test

# Cleanup
git worktree remove ../myapp-feature
git branch -d feature/test
```

---

### Exercise 2: Parallel Development

```bash
# Create two worktrees
git worktree add ../app-feature1 -b feature/one
git worktree add ../app-feature2 -b feature/two

# Terminal 1
cd ../app-feature1
echo "Feature 1" > f1.txt
git add f1.txt
git commit -m "Feature 1"

# Terminal 2
cd ../app-feature2
echo "Feature 2" > f2.txt
git add f2.txt
git commit -m "Feature 2"

# Merge both
cd <original-repo>
git merge feature/one
git merge feature/two

# Cleanup
git worktree remove ../app-feature1
git worktree remove ../app-feature2
```

---

### Exercise 3: Hotfix Interrupt

```bash
# Start feature work
git worktree add ../app-feature -b feature/work
cd ../app-feature
# ... working ...

# Urgent bug! Create hotfix from main repo
cd <original-repo>
git worktree add ../app-hotfix -b hotfix/urgent

cd ../app-hotfix
echo "fix" > fix.txt
git add fix.txt
git commit -m "Hotfix"

# Merge hotfix
cd <original-repo>
git merge hotfix/urgent

# Continue feature work
cd ../app-feature
# ... continue seamlessly ...
```

---

## Comparison: Worktree vs Alternatives

### Worktree vs Stash

| Aspect         | Worktree      | Stash          |
| -------------- | ------------- | -------------- |
| **Duration**   | Long-term     | Temporary      |
| **Disk Space** | More          | Less           |
| **Complexity** | Multiple dirs | Single dir     |
| **Best For**   | Parallel work | Quick switches |

---

### Worktree vs Clone

| Aspect         | Worktree           | Clone              |
| -------------- | ------------------ | ------------------ |
| **Repository** | Shared             | Separate           |
| **Disk Space** | 1x .git + n dirs   | n full repos       |
| **Branches**   | Shared             | Independent        |
| **Best For**   | Same project tasks | Different purposes |

---

### Worktree vs Branch Switch

| Aspect         | Worktree       | Branch Switch    |
| -------------- | -------------- | ---------------- |
| **Speed**      | Instant access | Switch time      |
| **Context**    | Preserved      | Lost             |
| **Disk Space** | More           | Less             |
| **Best For**   | Parallel tasks | Sequential tasks |

---

## Quick Reference

```bash
# Create worktree
git worktree add <path> <branch>              # Existing branch
git worktree add <path> -b <new-branch>       # New branch
git worktree add <path> <commit>              # Detached HEAD

# View worktrees
git worktree list                              # Simple list
git worktree list --porcelain                  # Detailed info

# Remove worktree
git worktree remove <path>                     # Remove
git worktree remove --force <path>             # Force remove
git worktree prune                             # Clean stale refs

# Maintenance
git worktree repair <path>                     # Fix after move
git worktree lock <path>                       # Prevent removal
git worktree unlock <path>                     # Allow removal
```

---

## Key Takeaways

✅ **Worktrees are perfect for:**

- Working on multiple branches simultaneously
- Urgent interruptions without losing context
- Code reviews while continuing development
- Testing different implementations
- Building multiple versions

⚠️ **Remember:**

- Each worktree needs its own directory
- All worktrees share the same Git repository
- Can't check out the same branch twice
- Always clean up when done

---

[Previous (Cherry-pick)](04_cherry-pick.md) | [Back to Main](README.md) | [Next (Stashing Changes)](06_stashing_changes.md) | [Top](#git-worktree)
