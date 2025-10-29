# Branch Management

## Overview

Branches are Git's way of allowing parallel development. Learn to create, switch, manage, and clean up branches effectively.

---

## Understanding Branches

**What is a branch?**
A branch is a movable pointer to a commit. It allows you to work on features, fixes, or experiments without affecting the main codebase.

```
main:       A---B---C
                 \
feature:          D---E
```

---

## Part 1: Creating Branches

### `git checkout -b <name> <start-point>` - Branch from Specific Commit

Create a branch from a specific commit, tag, or another branch.

**When to use:**
- Need to branch from older commit
- Creating hotfix from production
- Branching from another feature

**Example:**
```bash
# Branch from specific commit
git checkout -b hotfix/bug-123 a1b2c3d

# Branch from tag
git checkout -b release/v2.1 v2.0

# Branch from another branch
git checkout -b feature/sub-feature feature/main-feature

# Verify where you branched from
git log --oneline -5
```

---

## Part 2: Switching Between Branches

### `git checkout <branch>` - Switch Branch

**When to use:**
- Moving between existing branches
- Reviewing other people's work
- Testing different features

**Example:**
```bash
# Switch to existing branch
git checkout main

# Switch to feature branch
git checkout feature/user-profile

# Verify current branch
git branch
```

**Output:**
```
  main
* feature/user-profile
```

**⚠️ Important:** You cannot switch branches with uncommitted changes that would conflict. Either commit, stash, or discard them first.

---

### `git switch <branch>` - Modern Switch

Clearer alternative to `checkout` for switching branches.

**Example:**
```bash
# Switch to branch
git switch main

# Switch to feature
git switch feature/dashboard
```

**Advantages over `checkout`:**
- Only for switching branches (not files)
- Clearer intent
- Safer (won't accidentally checkout files)

---

### Switching with Uncommitted Changes

**Scenario:** You have uncommitted work and need to switch branches.

#### Option 1: Commit the changes
```bash
git add .
git commit -m "WIP: work in progress"
git switch other-branch
```

#### Option 2: Stash the changes (recommended for temporary switch)
```bash
# Save changes temporarily
git stash

# Switch branch
git switch other-branch

# Later, return and restore
git switch original-branch
git stash pop
```

#### Option 3: Carry changes (if no conflicts)
```bash
# Git will bring your changes along
git switch other-branch
# Your uncommitted changes come with you
```

---

## Part 3: Viewing Branches

### `git branch` - List Local Branches

**Example:**
```bash
git branch
```

**Output:**
```
  feature/api-v2
  feature/dashboard
* main
```

The `*` indicates your current branch.

---

### `git branch -a` - List All Branches (Local + Remote)

**When to use:**
- See what branches exist remotely
- Check if your branch is pushed
- Review team's branches

**Example:**
```bash
git branch -a
```

**Output:**
```
* main
  feature/dashboard
  remotes/origin/main
  remotes/origin/feature/api-v2
  remotes/origin/feature/user-auth
```

---

### `git branch -r` - List Remote Branches Only

**Example:**
```bash
git branch -r
```

**Output:**
```
  origin/main
  origin/feature/api-v2
  origin/feature/dashboard
```

---

### `git branch -v` - List with Last Commit

**When to use:**
- See what's on each branch
- Quick status check
- Compare branch progress

**Example:**
```bash
git branch -v
```

**Output:**
```
  feature/api-v2    a1b2c3d Add API endpoints
  feature/dashboard e4f5g6h Update UI components
* main              h7i8j9k Merge pull request #45
```

---

### `git branch -vv` - Show Tracking Information

**When to use:**
- Check which remote branch is tracked
- See if branch is ahead/behind
- Verify upstream configuration

**Example:**
```bash
git branch -vv
```

**Output:**
```
* main              h7i8j9k [origin/main] Merge pull request
  feature/api-v2    a1b2c3d [origin/feature/api-v2: ahead 2] Add endpoints
  feature/dashboard e4f5g6h Update UI components
```

Interpretation:
- `[origin/main]` - tracking origin/main, in sync
- `[origin/feature/api-v2: ahead 2]` - 2 commits ahead of remote
- No brackets - not tracking any remote branch

---

## Part 4: Deleting Branches

### `git branch -d <branch>` - Safe Delete (Merged Only)

**When to use:**
- Branch has been merged
- Feature is complete and integrated
- Cleaning up after pull request merge

**Example:**
```bash
# Switch away from the branch first
git checkout main

# Delete merged branch
git branch -d feature/completed-feature
```

**Output:**
```
Deleted branch feature/completed-feature (was a1b2c3d).
```

**Safety:** Git will prevent deletion if branch isn't merged:
```bash
git branch -d feature/unmerged-work
```
```
error: The branch 'feature/unmerged-work' is not fully merged.
If you are sure you want to delete it, run 'git branch -D feature/unmerged-work'.
```

---

### `git branch -D <branch>` - Force Delete

**When to use:**
- Experimental branch you don't need
- Failed approach you're abandoning
- Branch you know you don't want to merge

**⚠️ Warning:** This will delete the branch even if not merged. Make sure you really want to lose that work!

**Example:**
```bash
# Force delete unmerged branch
git branch -D experiment/failed-approach
```

**Output:**
```
Deleted branch experiment/failed-approach (was e4f5g6h).
```

---

### Deleting Remote Branches

#### `git push origin --delete <branch>` - Delete Remote Branch

**When to use:**
- Feature merged via pull request
- Cleaning up old branches on GitHub/GitLab
- Branch no longer needed by team

**Example:**
```bash
# Delete remote branch
git push origin --delete feature/old-feature

# Alternative syntax
git push origin :feature/old-feature
```

**Output:**
```
To github.com:user/repo.git
 - [deleted]         feature/old-feature
```

**Complete cleanup workflow:**
```bash
# 1. Delete local branch
git branch -d feature/completed

# 2. Delete remote branch
git push origin --delete feature/completed
```

---

### Pruning Stale Remote References

When branches are deleted on remote but still show locally:

```bash
# See stale references
git branch -a

# Clean up stale remote references
git fetch --prune

# Or set to always prune
git config --global fetch.prune true
```

**Example:**
```bash
# Before prune
git branch -r
```
```
  origin/main
  origin/feature/deleted-remotely  ← stale reference
```

```bash
# After prune
git fetch --prune
git branch -r
```
```
  origin/main
```

---

## Part 5: Renaming Branches

### `git branch -m <new-name>` - Rename Current Branch

**Example:**
```bash
# While on the branch to rename
git checkout feature/old-name
git branch -m feature/new-name

# Verify
git branch
```

---

### `git branch -m <old> <new>` - Rename Any Branch

**Example:**
```bash
# Rename without switching to it
git branch -m feature/typo feature/correct-name
```

---

### Renaming and Updating Remote

**Complete workflow:**
```bash
# 1. Rename local branch
git branch -m old-name new-name

# 2. Delete old remote branch
git push origin --delete old-name

# 3. Push new branch and set upstream
git push -u origin new-name
```

---

## Part 6: Local vs Remote Branches

### Understanding the Relationship

**Local branch:** Exists only on your computer
**Remote branch:** Exists on remote server (GitHub, GitLab)
**Tracking branch:** Local branch that follows a remote branch

```
Local:          main    feature/api
                 |           |
Remote:    origin/main  origin/feature/api
```

---

### Setting Up Tracking

#### Automatic (when pushing with -u)
```bash
git push -u origin feature/new-feature
```

#### Manual tracking setup
```bash
# Set existing branch to track remote
git branch --set-upstream-to=origin/feature/api feature/api

# Or shorter
git branch -u origin/feature/api feature/api
```

---

### Checking Tracking Status

```bash
# See tracking relationships
git branch -vv
```

**Output:**
```
* main              a1b2c3d [origin/main] Latest commit
  feature/api       e4f5g6h [origin/feature/api: ahead 3] Add endpoints
  experiment/test   h7i8j9k No tracking info
```

Interpretation:
- `main` - in sync with `origin/main`
- `feature/api` - 3 commits ahead of `origin/feature/api`
- `experiment/test` - not tracking any remote branch

---

### Fetching Remote Branches

**Scenario:** Teammate created a branch on remote, you want to work on it.

```bash
# 1. Fetch all remote branches
git fetch origin

# 2. See available remote branches
git branch -r

# 3. Create local tracking branch
git checkout -b feature/teammate-work origin/feature/teammate-work

# Or with newer syntax
git switch -c feature/teammate-work origin/feature/teammate-work

# Or even simpler (Git will figure it out)
git switch feature/teammate-work
```

---

### Comparing Local and Remote

```bash
# See commits on local but not remote
git log origin/main..main

# See commits on remote but not local
git log main..origin/main

# See divergence
git log --left-right --oneline main...origin/main
```

---

## Part 7: Branch Naming Conventions

### Common Patterns

#### By Type
```
feature/user-authentication
feature/payment-integration

bugfix/login-crash
bugfix/memory-leak

hotfix/critical-security-issue
hotfix/production-crash

experiment/new-architecture
experiment/performance-test

release/v2.0.0
release/v2.1.0
```

#### By Developer
```
dev/john/api-refactor
dev/sarah/ui-update
```

#### By Issue/Ticket
```
issue-123/fix-login
GH-456/add-feature
JIRA-789/update-docs
```

---

### Best Practices

✅ **Do:**
- Use lowercase
- Use hyphens, not spaces or underscores
- Be descriptive
- Include type prefix
- Keep reasonably short

❌ **Don't:**
- Use spaces: `feature new ui` ❌
- Be vague: `fix` or `update` ❌
- Use special characters: `feature/new@ui` ❌
- Make too long: `feature/add-the-new-user-authentication-system-with-oauth` ❌

**Good Examples:**
```
feature/oauth-integration
bugfix/null-pointer-login
hotfix/security-patch-cve-2024
refactor/database-layer
docs/api-endpoints
test/unit-coverage
```

---

## Part 8: Branch Workflows

### Feature Branch Workflow

```bash
# 1. Update main
git checkout main
git pull

# 2. Create feature branch
git checkout -b feature/new-dashboard

# 3. Work and commit
git add .
git commit -m "feat: add dashboard layout"

# 4. Push feature branch
git push -u origin feature/new-dashboard

# 5. Keep feature updated with main
git checkout main
git pull
git checkout feature/new-dashboard
git merge main

# 6. After PR merged, cleanup
git checkout main
git pull
git branch -d feature/new-dashboard
git push origin --delete feature/new-dashboard
```

---

### Hotfix Workflow

```bash
# 1. Branch from production/main
git checkout main
git pull
git checkout -b hotfix/critical-bug

# 2. Fix and commit
git add .
git commit -m "hotfix: resolve critical authentication bug"

# 3. Push hotfix
git push -u origin hotfix/critical-bug

# 4. After merge, cleanup
git checkout main
git pull
git branch -d hotfix/critical-bug
```

---

### Experiment Workflow

```bash
# 1. Create experiment branch
git checkout -b experiment/new-approach

# 2. Try things out
# ... make changes ...
git commit -am "Try new algorithm"

# 3. Decision time:
#    Keep it: merge to main
#    Discard it: force delete

# If keeping:
git checkout main
git merge experiment/new-approach

# If discarding:
git checkout main
git branch -D experiment/new-approach
```

---

## Practice Exercises

### Exercise 1: Complete Branch Lifecycle
```bash
# Create feature branch
git checkout -b feature/user-settings

# Make changes
echo "Settings page" > settings.html
git add settings.html
git commit -m "feat: add settings page"

# Push to remote
git push -u origin feature/user-settings

# Merge to main
git checkout main
git merge feature/user-settings

# Cleanup
git branch -d feature/user-settings
git push origin --delete feature/user-settings
```

---

### Exercise 2: Working with Remote Branches
```bash
# Fetch all remote branches
git fetch origin

# List all branches
git branch -a

# Create local tracking branch
git checkout -b feature/team-work origin/feature/team-work

# Make contribution
git commit -am "Add my changes"
git push
```

---

### Exercise 3: Branch Comparison
```bash
# Create two branches
git checkout -b version-a
echo "Version A" > file.txt
git add file.txt
git commit -m "Version A"

git checkout main
git checkout -b version-b
echo "Version B" > file.txt
git add file.txt
git commit -m "Version B"

# Compare them
git diff version-a version-b
git log version-a..version-b
```

---

## Common Scenarios

### Scenario 1: "I'm on the wrong branch!"

```bash
# You made changes on main but should be on feature branch
git status  # see uncommitted changes

# Create branch with changes
git checkout -b feature/correct-branch

# Commit them
git add .
git commit -m "feat: add feature (on correct branch now)"
```

---

### Scenario 2: "I want to switch branches but have uncommitted work"

```bash
# Option 1: Stash changes
git stash
git checkout other-branch
# Later:
git checkout original-branch
git stash pop

# Option 2: Commit as WIP
git commit -am "WIP: work in progress"
git checkout other-branch
# Later:
git checkout original-branch
# Continue working or git reset --soft HEAD~1 to uncommit
```

---

### Scenario 3: "Remote branch was deleted but I still see it"

```bash
# Clean up stale references
git fetch --prune

# Or delete specific remote reference
git branch -dr origin/deleted-branch
```

---

## Quick Reference

```bash
# Creating
git branch <name>               # Create (don't switch)
git checkout -b <name>          # Create and switch
git switch -c <name>            # Create and switch (modern)

# Switching
git checkout <name>             # Switch to branch
git switch <name>               # Switch to branch (modern)

# Viewing
git branch                      # List local
git branch -a                   # List all (local + remote)
git branch -r                   # List remote only
git branch -v                   # With last commit
git branch -vv                  # With tracking info

# Deleting
git branch -d <name>            # Safe delete (merged only)
git branch -D <name>            # Force delete
git push origin --delete <name> # Delete remote

# Renaming
git branch -m <new-name>        # Rename current
git branch -m <old> <new>       # Rename specific

# Tracking
git push -u origin <name>       # Push and set upstream
git branch -u origin/<name>     # Set upstream manually

# Cleanup
git fetch --prune               # Remove stale references
```

---

**Next:** [Working with Stages](./03-working-with-stages.md) `git branch <name>` - Create Branch

Creates a new branch but **doesn't switch to it**.

**When to use:**
- Want to create branch for later
- Planning multiple branches
- Creating backup branch

**Example:**
```bash
# Create new branch
git branch feature/new-login

# Verify it was created
git branch

# Note: you're still on current branch
git status
```

**Output:**
```
  feature/new-login
* main
```

---

### `git checkout -b <name>` - Create and Switch

Creates a new branch **and switches to it** immediately.

**When to use:**
- Most common scenario
- Starting new feature right away
- Quick branch creation

**Example:**
```bash
# Create and switch in one command
git checkout -b feature/user-profile

# Verify
git branch
```

**Output:**
```
* feature/user-profile
  main
```

---

### `git switch -c <name>` - Modern Create and Switch

Newer, clearer syntax introduced in Git 2.23.

**When to use:**
- Prefer modern, explicit commands
- Avoiding confusion with `checkout`
- Same as `checkout -b` but clearer

**Example:**
```bash
# Modern syntax
git switch -c feature/dashboard

# Verify
git branch
```

---

###