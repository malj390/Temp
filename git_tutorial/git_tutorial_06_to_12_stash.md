# Git Tutorials - Part 2 (Tutorials 06-12)

This file contains tutorials 06-12. Save each section as a separate markdown file.

---
---

# 06 - Stashing Changes

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

| Need | Solution |
|------|----------|
| Quick switch | Stash |
| Long-term WIP | Commit with "WIP:" |
| Parallel work | Worktree |
| Backup before risky | Branch |

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
---

# 07 - Undoing Changes

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

| Option | Commit | Staging | Working Dir |
|--------|--------|---------|-------------|
| `--soft` | ✓ Undo | Keep | Keep |
| `--mixed` | ✓ Undo | ✓ Unstage | Keep |
| `--hard` | ✓ Undo | ✓ Clear | ✓ Discard |

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

| Aspect | Revert | Reset |
|--------|--------|-------|
| **History** | Preserves | Rewrites |
| **Safety** | Safe for shared | Dangerous if pushed |
| **Method** | New commit | Move HEAD |
| **Use on** | Public branches | Local branches |

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
# Made commit
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

# 08 - Comparing Changes

## Overview

Learn to compare files, commits, and branches using git diff and log.

---

## Part 1: Basic Diff

### `git diff` - Unstaged Changes

```bash
# See all unstaged changes
git diff

# Specific file
git diff file.txt

# Specific directory
git diff src/
```

---

### `git diff --staged` - Staged Changes

```bash
# See what you're about to commit
git diff --staged

# Or
git diff --cached
```

---

### `git diff HEAD` - All Changes

```bash
# See staged + unstaged changes
git diff HEAD
```

---

## Part 2: Comparing Commits

### Between Two Commits

```bash
# Compare two commits
git diff abc123 def456

# Compare with HEAD
git diff abc123

# Previous commit
git diff HEAD~1

# Two commits ago
git diff HEAD~2
```

---

### Comparing Specific Files

```bash
# File between commits
git diff abc123 def456 -- file.txt

# File between branches
git diff main feature -- file.txt
```

---

## Part 3: Comparing Branches

### `git diff <branch1> <branch2>`

```bash
# See differences
git diff main feature

# Only file names
git diff --name-only main feature

# With status
git diff --name-status main feature
```

**Output:**
```
M    modified.txt
A    added.txt
D    deleted.txt
```

---

### What's in Branch but Not in Another

```bash
# Commits in feature not in main
git log main..feature

# Commits in main not in feature
git log feature..main

# Show divergence
git log --left-right main...feature
```

---

## Part 4: Viewing History

### `git log` Basics

```bash
# Standard log
git log

# One line per commit
git log --oneline

# With graph
git log --graph --oneline

# Last n commits
git log -n 5

# Since date
git log --since="2 weeks ago"
```

---

### Filtering Logs

```bash
# By author
git log --author="John"

# By message
git log --grep="fix"

# By file
git log -- file.txt

# Changes to file
git log -p file.txt
```

---

### Pretty Formats

```bash
# Custom format
git log --pretty=format:"%h - %an, %ar : %s"

# With dates
git log --pretty=format:"%h %ad | %s%d [%an]" --date=short

# Graph with details
git log --graph --pretty=format:"%h %s" --abbrev-commit
```

---

## Part 5: Showing Commits

### `git show <commit>`

```bash
# Show specific commit
git show abc123

# Show file at commit
git show abc123:path/to/file.txt

# Show last commit
git show HEAD

# Show parent
git show HEAD~1
```

---

## Part 6: Diffing Tools

### Word Diff

```bash
# Show word-by-word differences
git diff --word-diff

# Color words
git diff --color-words
```

---

### Statistics

```bash
# Show stats
git diff --stat

# Summary
git diff --shortstat

# Number only
git diff --numstat
```

---

## Quick Reference

```bash
# Working directory
git diff                       # Unstaged changes
git diff --staged              # Staged changes
git diff HEAD                  # All changes

# Commits
git diff <commit>              # Compare with commit
git diff <A> <B>               # Compare two commits
git diff HEAD~1                # Compare with parent

# Branches
git diff <branch1> <branch2>   # Compare branches
git diff --name-only <A> <B>   # File names only
git log <A>..<B>               # Commits in B not A

# Files
git diff -- <file>             # Specific file
git log -- <file>              # File history
git show <commit>:<file>       # File at commit

# Formatting
git diff --stat                # Statistics
git diff --word-diff           # Word level
git log --oneline              # Compact log
git log --graph                # With graph
```

---
---

# 09 - Remote Repository Management

## Overview

Manage connections to remote repositories and sync your work.

---

## Understanding Remotes

**Remote:** A URL pointing to another copy of your repository.

```
Local Repo ←→ Remote (origin)
               ↓
         GitHub/GitLab/Bitbucket
```

---

## Part 1: Viewing Remotes

### `git remote` - List Remotes

```bash
# List remotes
git remote
# origin

# With URLs
git remote -v
```

**Output:**
```
origin  https://github.com/user/repo.git (fetch)
origin  https://github.com/user/repo.git (push)
```

---

### `git remote show <name>`

```bash
git remote show origin
```

**Output:**
```
* remote origin
  Fetch URL: https://github.com/user/repo.git
  Push  URL: https://github.com/user/repo.git
  HEAD branch: main
  Remote branches:
    main    tracked
    develop tracked
  Local branch configured for 'git pull':
    main merges with remote main
  Local ref configured for 'git push':
    main pushes to main (up to date)
```

---

## Part 2: Adding Remotes

### `git remote add <name> <url>`

```bash
# Add origin
git remote add origin https://github.com/user/repo.git

# Add second remote
git remote add upstream https://github.com/original/repo.git
```

---

## Part 3: Removing/Renaming

### Remove Remote

```bash
git remote remove origin

# Or
git remote rm origin
```

---

### Rename Remote

```bash
git remote rename origin new-origin
```

---

## Part 4: Fetching and Pulling

### `git fetch` - Download Without Merging

```bash
# Fetch from origin
git fetch origin

# Fetch all remotes
git fetch --all

# Fetch and prune
git fetch --prune
```

---

### `git pull` - Fetch + Merge

```bash
# Pull current branch
git pull

# Pull specific branch
git pull origin main

# Pull with rebase
git pull --rebase
```

---

### Fetch vs Pull

| Command | Downloads | Merges | Safe |
|---------|-----------|--------|------|
| `fetch` | ✅ | ❌ | ✅ |
| `pull` | ✅ | ✅ | ⚠️ |

---

## Part 5: Pushing

### Basic Push

```bash
# Push current branch
git push

# Push specific branch
git push origin feature

# Set upstream
git push -u origin feature
```

---

### Force Push (Dangerous!)

```bash
# Overwrite remote (dangerous!)
git push --force

# Safer: only if no one else pushed
git push --force-with-lease
```

**⚠️ Never force push to shared branches!**

---

### Push All Branches

```bash
# Push all branches
git push --all

# Push tags
git push --tags

# Push everything
git push --all && git push --tags
```

---

## Part 6: Tracking Branches

### Set Upstream

```bash
# During push
git push -u origin feature

# After creation
git branch --set-upstream-to=origin/feature feature
```

---

### Check Tracking

```bash
# See tracking info
git branch -vv
```

**Output:**
```
* main    abc123 [origin/main] Latest
  feature def456 [origin/feature: ahead 2] Work
```

---

## Part 7: Handling Diverged Branches

### When Push Rejected

```
! [rejected]        main -> main (non-fast-forward)
```

**Options:**

#### Option 1: Pull then Push
```bash
git pull
git push
```

#### Option 2: Pull with Rebase
```bash
git pull --rebase
git push
```

#### Option 3: Force Push (if you're sure!)
```bash
git push --force-with-lease
```

---

## Quick Reference

```bash
# View
git remote                     # List remotes
git remote -v                  # With URLs
git remote show origin         # Detailed info

# Manage
git remote add <name> <url>    # Add remote
git remote remove <name>       # Remove
git remote rename <old> <new>  # Rename

# Sync
git fetch                      # Download
git fetch --prune              # Download + clean
git pull                       # Fetch + merge
git pull --rebase              # Fetch + rebase

# Push
git push                       # Push current
git push -u origin <branch>    # Set upstream
git push --force-with-lease    # Force (safer)
```

---
---

# 10 - Merge Strategies

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

| Aspect | Merge | Rebase |
|--------|-------|--------|
| **History** | Non-linear | Linear |
| **Commits** | Preserves all | Rewrites |
| **Safety** | Safe | Risky if shared |
| **Best for** | Shared branches | Local cleanup |

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

# 11 - Quick Reference Cheatsheet

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

## Aliases (Add to ~/.gitconfig)

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

# 12 - Best Practices

## Commit Messages

### Structure
```
<type>: <subject>

<body>

<footer>
```

### Types
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Formatting
- `refactor`: Code restructure
- `test`: Tests
- `chore`: Maintenance

### Examples
```
feat: add user authentication endpoint

fix: resolve null pointer in parser
- Added null check before dereferencing
- Added unit tests for edge case

docs: update API documentation for v2.0

refactor: simplify database connection logic

test: add integration tests for payment flow

chore: update dependencies to latest versions
```

---

## Branching Strategy

### GitFlow

```
main          Production-ready code
develop       Integration branch
feature/*     New features
hotfix/*      Production fixes
release/*     Release preparation
```

### GitHub Flow (Simpler)

```
main          Always deployable
feature/*     All development branches
```

### Trunk-Based

```
main          Single source of truth
              Short-lived feature branches (1-2 days)
```

---

## Commit Best Practices

✅ **Do:**
- Commit often, push less often
- Write clear commit messages
- One logical change per commit
- Review before committing (`git diff --staged`)
- Use present tense ("Add feature" not "Added")

❌ **Don't:**
- Commit broken code
- Mix unrelated changes
- Use vague messages ("fix", "update")
- Commit sensitive data (passwords, keys)
- Commit generated files (unless necessary)

---

## Branch Best Practices

✅ **Do:**
- Use descriptive names (`feature/user-auth`)
- Keep branches short-lived
- Delete merged branches
- Update from main regularly
- Use prefixes (feature/, bugfix/, hotfix/)

❌ **Don't:**
- Work directly on main
- Keep stale branches
- Use unclear names ("test", "fix")
- Let branches diverge too much

---

## Remote Best Practices

✅ **Do:**
- Pull before starting work
- Push at end of day
- Use `--force-with-lease` not `--force`
- Communicate before force pushing
- Fetch regularly to stay updated

❌ **Don't:**
- Force push to shared branches
- Push untested code to main
- Commit directly to main
- Leave unpushed work overnight

---

## Security Best Practices

### Never Commit

- Passwords
- API keys
- Private keys
- Tokens
- Database credentials
- Environment files (.env)

### Use .gitignore

```
# Environment
.env
.env.local

# Credentials
secrets.json
credentials.yml

# Keys
*.pem
*.key

# IDE
.vscode/
.idea/

# Dependencies
node_modules/
vendor/

# Build
dist/
build/
*.o
*.out
```

---

### Remove Committed Secrets

```bash
# If you accidentally committed secrets
git rm --cached .env
git commit -m "Remove .env file"

# Update .gitignore
echo ".env" >> .gitignore
git add .gitignore
git commit -m "Add .env to gitignore"

# Force push if already pushed (coordinate with team!)
git push --force-with-lease
```

**Better:** Use tools like `git-secrets` or GitHub secret scanning.

---

## Code Review Best Practices

### Before Pull Request

```bash
# Update with main
git checkout main
git pull
git checkout feature/branch
git merge main

# Clean up commits
git rebase -i main

# Run tests
npm test  # or your test command

# Push
git push
```

### PR Description Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
How to test these changes

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Tests added/updated
- [ ] Documentation updated
```

---

## Performance Best Practices

### Large Repositories

```bash
# Shallow clone (faster)
git clone --depth 1 <url>

# Sparse checkout (only specific paths)
git sparse-checkout set src/

# Fetch only one branch
git clone --single-branch --branch main <url>
```

### Clean Up

```bash
# Remove unused branches
git fetch --prune

# Compress repository
git gc --aggressive

# Remove large files from history
git filter-branch --tree-filter 'rm -f large-file.zip' HEAD
```

---

## Team Collaboration

### Communication

✅ **Do:**
- Announce before force pushing
- Coordinate on shared branches
- Use descriptive PR titles
- Respond to review comments
- Keep team updated on blockers

❌ **Don't:**
- Surprise force push
- Work in isolation too long
- Ignore review feedback
- Merge without approval

---

### Code Review Etiquette

**As Reviewer:**
- Be constructive and kind
- Explain the "why"
- Approve quickly if minor issues
- Test the changes locally

**As Author:**
- Keep PRs small and focused
- Respond to all comments
- Don't take feedback personally
- Update PR description as needed

---

## Git Hygiene

### Regular Maintenance

```bash
# Weekly: Update main and clean up
git checkout main
git pull
git branch --merged | grep -v "\*" | xargs -n 1 git branch -d

# Monthly: Repository cleanup
git fetch --prune
git gc
```

---

### Before Leaving Project

```bash
# Push all work
git push --all

# Clean up local branches
git branch -d feature/completed

# Document WIP
git commit -am "WIP: document current state"
```

---

## Common Patterns

### Hotfix Pattern

```bash
# 1. Branch from main
git checkout main
git pull
git checkout -b hotfix/critical-bug

# 2. Fix and commit
git commit -am "fix: resolve critical bug"

# 3. Merge to main
git checkout main
git merge hotfix/critical-bug
git push

# 4. Merge to develop (if using GitFlow)
git checkout develop
git merge hotfix/critical-bug
git push

# 5. Cleanup
git branch -d hotfix/critical-bug
```

---

### Feature Pattern

```bash
# 1. Create feature branch
git checkout main
git pull
git checkout -b feature/new-feature

# 2. Develop with regular commits
git commit -am "feat: add basic structure"
git commit -am "feat: implement logic"
git commit -am "test: add unit tests"

# 3. Keep updated with main
git checkout main
git pull
git checkout feature/new-feature
git merge main

# 4. Push and create PR
git push -u origin feature/new-feature

# 5. After PR merged, cleanup
git checkout main
git pull
git branch -d feature/new-feature
```

---

### Release Pattern

```bash
# 1. Create release branch
git checkout -b release/v2.0.0 develop

# 2. Prepare release
# Update version numbers
# Final testing
git commit -am "chore: prepare v2.0.0"

# 3. Merge to main
git checkout main
git merge release/v2.0.0
git tag -a v2.0.0 -m "Release version 2.0.0"
git push origin main --tags

# 4. Merge back to develop
git checkout develop
git merge release/v2.0.0
git push

# 5. Cleanup
git branch -d release/v2.0.0
```

---

## Anti-Patterns to Avoid

❌ **Commit Everything**
```bash
git add .
git commit -m "updates"
```

✅ **Be Selective**
```bash
git add src/feature.c
git commit -m "feat: implement user authentication"
```

---

❌ **Long-Lived Feature Branches**
```
feature/big-project (30 days old, 200 commits behind main)
```

✅ **Short, Focused Branches**
```
feature/add-login (2 days old, merged)
feature/add-logout (created after login merged)
```

---

❌ **Vague Messages**
```bash
git commit -m "fix"
git commit -m "changes"
git commit -m "asdf"
```

✅ **Clear Messages**
```bash
git commit -m "fix: resolve memory leak in parser"
git commit -m "feat: add password reset functionality"
```

---

❌ **Working on Main**
```bash
git checkout main
# ... make changes ...
git commit -am "changes"
```

✅ **Use Feature Branches**
```bash
git checkout -b feature/changes
# ... make changes ...
git commit -am "feat: add new feature"
```

---

## Tools and Integration

### Useful Git Tools

- **Git GUI**: GitKraken, SourceTree, GitHub Desktop
- **IDE Integration**: VSCode, IntelliJ, Vim plugins
- **CLI Enhancement**: tig, lazygit, git-delta
- **Hooks**: husky (pre-commit, pre-push)

### Git Hooks Example

```bash
# .git/hooks/pre-commit
#!/bin/bash

# Run linter
npm run lint
if [ $? -ne 0 ]; then
    echo "Linting failed. Commit aborted."
    exit 1
fi

# Run tests
npm test
if [ $? -ne 0 ]; then
    echo "Tests failed. Commit aborted."
    exit 1
fi
```

---

## Learning Resources

### Practice
- Try commands in test repository first
- Use `--dry-run` flags when available
- Keep backups before risky operations

### Documentation
- `git help <command>`
- https://git-scm.com/doc
- https://learngitbranching.js.org/

### Community
- Stack Overflow
- GitHub Community
- Git Discord servers

---

## Final Checklist

**Before Every Commit:**
- [ ] Code works and is tested
- [ ] Follows project style guide
- [ ] Commit message is clear
- [ ] No sensitive data included
- [ ] Only related changes included

**Before Every Push:**
- [ ] Pulled latest changes
- [ ] Resolved any conflicts
- [ ] Tests pass
- [ ] Build succeeds
- [ ] Code reviewed (self or peer)

**Before Every Merge:**
- [ ] Branch is up to date with target
- [ ] All checks pass
- [ ] Code reviewed and approved
- [ ] Documentation updated
- [ ] Ready for production (if merging to main)

---

## Key Principles

1. **Commit Often, Push Regularly**
   - Commits are cheap, use them liberally
   - Push at least daily

2. **Keep History Clean**
   - Use meaningful commits
   - Rebase before merging (if appropriate)
   - Squash WIP commits

3. **Communicate**
   - Write for future you and teammates
   - Document decisions in commit messages
   - Use PR descriptions effectively

4. **Stay Updated**
   - Pull from main regularly
   - Resolve conflicts early
   - Don't let branches diverge

5. **Test Before Sharing**
   - Never push broken code
   - Run tests locally
   - Review your own changes first

---

**End of Tutorial System**

---

## How to Save These Files

Save each section (delimited by `# NN - Title`) as a separate file:

```
00-setup-test-environment.md
01-basic-git-operations.md
02-branch-management.md
03-working-with-stages.md
04-cherry-pick-guide.md
05-git-worktree.md
06-stashing-changes.md
07-undoing-changes.md
08-comparing-changes.md
09-remote-management.md
10-merge-strategies.md
11-quick-reference.md
12-best-practices.md
```

All files reference each other with relative paths, so keep them in the same directory!