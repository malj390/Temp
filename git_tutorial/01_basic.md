[Previous (Setup Test Environment)](00_set_up.md) | [Back to Main](README.md) | [Next (Branch Management)](02_branch.md) | [Down](#quick-reference)

---


---

# Basic Git Operations

## Overview

Master the fundamental Git commands that you'll use daily. This tutorial covers staging, committing, and syncing with remotes.

---

## Understanding the Git Workflow

```
Working Directory → Staging Area → Local Repository → Remote Repository
     (modify)      git add      git commit         git push
```

---

## Part 1: Git Add - Staging Files

### The Purpose

`git add` moves changes from your working directory to the **staging area** (index). This allows you to carefully select what goes into your next commit.

### Command Variations

#### `git add .` - Stage All Changes

**When to use:**

- Starting a new feature and all changes are related
- Making consistent changes across multiple files
- Quick commits during active development

**Example:**

```bash
# Make changes to multiple files
echo "// New feature" >> src/main.c
echo "// Helper function" >> src/utils.c
echo "New user data" >> data/users.csv

# Check what changed
git status

# Stage everything
git add .

# Verify what's staged
git status
```

**Output:**

```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   data/users.csv
        modified:   src/main.c
        modified:   src/utils.c
```

---

#### `git add <file>` - Stage Specific Files

**When to use:**

- Changes belong to different logical commits
- Want to commit related changes separately
- Need to exclude certain modifications
- Following atomic commit principles

**Example Scenario: Separate Bug Fix from Feature**

```bash
# Make different types of changes
echo "// Bug fix" >> src/main.c
echo "// New feature" >> src/utils.c
echo "# Documentation update" >> docs/README.md

# Stage only the bug fix
git add src/main.c

# Check status
git status
```

**Output:**

```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   src/main.c

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
        modified:   docs/README.md
        modified:   src/utils.c
```

---

#### `git add <directory>/` - Stage Directory

**When to use:**

- Changes in one module/folder are related
- Refactoring a specific component
- Adding multiple new files in a directory

**Example:**

```bash
# Add multiple files to src directory
echo "// File 1" > src/module1.c
echo "// File 2" > src/module2.c

# Stage entire directory
git add src/

# Verify
git status
```

---

#### `git add -p` - Interactive Staging (Patch Mode)

**When to use:**

- File has multiple unrelated changes
- Want to commit parts of a file separately
- Need surgical precision in commits

**Example:**

```bash
# Make multiple changes to one file
cat >> src/main.c << 'EOF'

// Bug fix
void fix_bug() {}

// New feature
void new_feature() {}
EOF

# Stage interactively
git add -p src/main.c
```

**Interactive prompts:**

```
Stage this hunk [y,n,q,a,d,s,e,?]?
y - yes, stage this hunk
n - no, don't stage this hunk
s - split into smaller hunks
q - quit
```

---

### Comparison Table: git add Strategies

| Command          | Use Case              | Example Scenario                     |
| ---------------- | --------------------- | ------------------------------------ |
| `git add .`      | All related changes   | Implementing complete feature        |
| `git add file.c` | Specific file changes | Bug fix in one file                  |
| `git add src/`   | Directory changes     | Refactoring module                   |
| `git add -p`     | Partial file changes  | Mixed bug fix + feature in same file |
| `git add *.c`    | Pattern matching      | Stage all C files                    |

---

## Part 2: Git Commit - Saving Changes

### The Purpose

`git commit` saves your staged changes to the local repository with a descriptive message.

### Command Variations

#### `git commit -m "message"` - Quick Commit

**When to use:**

- Simple, straightforward changes
- Message fits in one line
- Quick iterations during development

**Example:**

```bash
# Stage changes
git add src/main.c

# Commit with inline message
git commit -m "Fix null pointer dereference in main"
```

**Best Practices for Messages:**

- Start with verb (Add, Fix, Update, Remove)
- Be specific and concise
- 50 characters or less
- Present tense

**Examples:**

```bash
git commit -m "Add user authentication module"
git commit -m "Fix memory leak in parser"
git commit -m "Update documentation for API endpoints"
git commit -m "Remove deprecated function calls"
```

---

#### `git commit` - Editor Commit (Multi-line)

**When to use:**

- Complex changes needing explanation
- Need to describe "why" not just "what"
- Following team commit conventions
- Changes affect multiple areas

**Example:**

```bash
# Stage changes
git add .

# Open editor for commit message
git commit
```

**Editor opens with template:**

```
Subject line (50 chars or less)

More detailed explanation if needed. Wrap at 72 characters.
Explain the problem this commit solves and why you chose
this particular solution.

- Bullet points are okay
- Use present tense ("Fix bug" not "Fixed bug")

Fixes #123
```

**Real Example:**

```
Add caching layer to database queries

The previous implementation was making redundant database calls
for frequently accessed data. This commit introduces a Redis
caching layer that reduces database load by 60%.

Implementation details:
- Cache expires after 5 minutes
- Cache invalidation on data updates
- Fallback to database if cache unavailable

Performance improvement: Average response time reduced from
450ms to 180ms.

Fixes #234
```

---

#### `git commit -a` - Auto-stage and Commit

**When to use:**

- Only modified tracked files (no new files)
- Quick commits during development
- Trust all changes are related

**⚠️ Warning:** Does NOT stage new (untracked) files!

**Example:**

```bash
# Modify existing files (don't create new ones)
echo "// Update" >> src/main.c
echo "// Update" >> src/utils.c

# Stage and commit in one step
git commit -a -m "Update error handling"

# Or combined short form
git commit -am "Update error handling"
```

**What it does:**

```bash
# Equivalent to:
git add -u  # stages modified tracked files only
git commit -m "message"
```

---

#### `git commit --amend` - Modify Last Commit

**When to use:**

- Forgot to include a file
- Typo in commit message
- Small fix to last commit
- **Before pushing to remote**

**Example:**

```bash
# Made a commit
git commit -m "Add feature"

# Oops, forgot a file!
git add forgotten-file.c

# Add it to the last commit
git commit --amend --no-edit

# Or change the message too
git commit --amend -m "Add feature with tests"
```

**⚠️ Important:** Never amend commits that have been pushed to shared branches!

---

### Commit Message Guidelines

#### Structure

```
<type>: <subject>

<body>

<footer>
```

#### Types

- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation only
- `style`: Formatting, missing semicolons, etc.
- `refactor`: Code restructuring
- `test`: Adding tests
- `chore`: Maintenance tasks

#### Examples

```bash
git commit -m "feat: add user login endpoint"
git commit -m "fix: resolve race condition in auth"
git commit -m "docs: update API documentation"
git commit -m "refactor: simplify database connection logic"
```

---

### Comparison: Commit Strategies

| Command                  | Stages New Files      | Use Case                           |
| ------------------------ | --------------------- | ---------------------------------- |
| `git commit -m "msg"`    | No (requires git add) | Controlled, explicit commits       |
| `git commit -a -m "msg"` | No                    | Quick commits, modified files only |
| `git commit`             | No (requires git add) | Detailed, multi-line messages      |
| `git commit --amend`     | N/A                   | Fix last commit                    |

---

## Part 3: Git Push - Syncing with Remote

### The Purpose

`git push` uploads your local commits to a remote repository (GitHub, GitLab, etc.).

### Command Variations

#### `git push` - Push Current Branch

**When to use:**

- Branch tracking is set up
- Regular sync during development
- After completing a feature

**Example:**

```bash
# Make commits locally
git commit -m "Add feature"

# Push to remote
git push
```

**Expected Output:**

```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Writing objects: 100% (3/3), 300 bytes | 300.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To github.com:user/repo.git
   a1b2c3d..e4f5g6h  main -> main
```

---

#### `git push origin <branch>` - Push Specific Branch

**When to use:**

- First time pushing a new branch
- Pushing to non-default branch
- Being explicit about destination

**Example:**

```bash
# Create and switch to new branch
git checkout -b feature/new-ui

# Make changes and commit
git add .
git commit -m "Design new UI"

# Push new branch to remote
git push origin feature/new-ui
```

---

#### `git push -u origin <branch>` - Set Upstream

**When to use:**

- First push of a new branch
- Want simple `git push` in future
- Setting up tracking relationship

**Example:**

```bash
# Create new branch
git checkout -b feature/api-v2

# Make commits
git commit -m "Start API v2"

# Push and set upstream tracking
git push -u origin feature/api-v2

# Now you can just use 'git push' in the future
```

**What -u does:**

- Creates remote branch if it doesn't exist
- Sets up tracking (local branch → remote branch)
- Enables simple `git push` and `git pull`

---

#### `git push --force` - Overwrite Remote (⚠️ Dangerous)

**When to use:**

- After rewriting history (rebase, amend)
- Only on branches you own
- **NEVER on shared/main branches**

**Example:**

```bash
# You amended a commit that was already pushed
git commit --amend -m "Better message"

# Remote refuses normal push
git push  # Error: updates were rejected

# Force push (use with caution!)
git push --force
# Or safer variant:
git push --force-with-lease
```

**⚠️ Warning:** `--force` can lose other people's work! Use `--force-with-lease` instead.

---

## Part 4: Git Pull - Getting Remote Changes

### The Purpose

`git pull` fetches changes from remote and merges them into your current branch.

### `git pull` = `git fetch` + `git merge`

---

#### `git pull` - Standard Pull

**When to use:**

- Getting latest changes from team
- Before starting new work
- Regular sync with main branch

**Example:**

```bash
# Pull latest changes
git pull

# Or be explicit
git pull origin main
```

**Output:**

```
remote: Enumerating objects: 5, done.
remote: Counting objects: 100% (5/5), done.
Updating a1b2c3d..e4f5g6h
Fast-forward
 src/main.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)
```

---

#### `git pull --rebase` - Pull with Rebase

**When to use:**

- Want clean, linear history
- Avoid merge commits
- Working on feature branch

**Example:**

```bash
# Pull and rebase your commits on top
git pull --rebase origin main
```

**Difference:**

```
# Regular git pull creates merge commit:
A---B---C (origin/main)
     \
      D---E---M (your branch, M is merge commit)

# git pull --rebase keeps linear history:
A---B---C---D'---E' (your commits rebased)
```

---

## Part 5: Git Fetch - Download Without Merging

### The Purpose

`git fetch` downloads changes from remote but doesn't modify your working files. Safer than `git pull`.

#### `git fetch` - Get Remote Changes

**When to use:**

- Want to see what changed before merging
- Checking for updates
- Safer than git pull

**Example:**

```bash
# Fetch all branches from remote
git fetch origin

# Check what changed
git log origin/main

# See differences
git diff main origin/main

# Merge when ready
git merge origin/main
```

---

### Git Pull vs Git Fetch

| Command     | Downloads | Merges | Safe | Use Case                  |
| ----------- | --------- | ------ | ---- | ------------------------- |
| `git fetch` | ✅         | ❌      | ✅    | Review before merging     |
| `git pull`  | ✅         | ✅      | ⚠️   | Quick sync, trust changes |

---

## Complete Workflow Summary

### Daily Development Workflow

```bash
# 1. Start of day - get latest
git checkout main
git pull

# 2. Create feature branch
git checkout -b feature/my-feature

# 3. Make changes
# ... edit files ...

# 4. Stage specific files
git add src/main.c src/utils.c

# 5. Commit with good message
git commit -m "feat: add user authentication"

# 6. Make more changes
# ... edit files ...

# 7. Quick commit
git commit -am "fix: resolve edge case in auth"

# 8. Push to remote (first time)
git push -u origin feature/my-feature

# 9. Continue working...
# ... more commits ...

# 10. Push updates
git push

# 11. Keep branch updated with main
git checkout main
git pull
git checkout feature/my-feature
git merge main

# 12. Final push
git push
```

---

### Atomic Commit Workflow

**Scenario:** You fixed a bug and added a feature

```bash
# Stage and commit bug fix separately
git add src/bugfix.c
git commit -m "fix: null pointer in parser"

# Stage and commit feature separately
git add src/feature.c includes/feature.h
git commit -m "feat: add export functionality"

# Push both commits
git push
```

---

### Collaborative Workflow

```bash
# Morning: sync with team
git checkout main
git pull

# Create your branch
git checkout -b feature/my-work

# Before lunch: push work in progress
git add .
git commit -m "WIP: partial implementation"
git push -u origin feature/my-work

# After lunch: get teammate's changes
git checkout main
git pull
git checkout feature/my-work
git merge main  # or git rebase main

# Continue working...
git commit -am "Complete implementation"
git push

# End of day: final sync
git push
```

---

## Practice Exercises

### Exercise 1: Selective Staging

```bash
# Make changes to 3 files
echo "change1" >> src/main.c
echo "change2" >> src/utils.c
echo "change3" >> docs/README.md

# Commit them separately with different messages
git add src/main.c
git commit -m "Update main logic"

git add src/utils.c
git commit -m "Add utility function"

git add docs/README.md
git commit -m "Update documentation"
```

### Exercise 2: Amend Practice

```bash
# Make a commit
git add file1.c
git commit -m "Add feature"

# Oops! Forgot a file
git add file2.c
git commit --amend --no-edit

# Check the result
git show
```

### Exercise 3: Pull vs Fetch

```bash
# Fetch to see what's new
git fetch origin

# Review changes
git log origin/main

# Merge when ready
git merge origin/main
```

---

## Common Pitfalls

### ❌ Using `git add .` Without Checking

```bash
# Bad
git add .
git commit -m "Update"
```

### ✅ Always Check First

```bash
# Good
git status
git diff
git add .
git status  # verify
git commit -m "descriptive message"
```

---

### ❌ Vague Commit Messages

```bash
git commit -m "fix"
git commit -m "updates"
git commit -m "changes"
```

### ✅ Descriptive Messages

```bash
git commit -m "fix: resolve memory leak in parser"
git commit -m "feat: add user profile page"
git commit -m "docs: update installation guide"
```

---

## Quick Reference

```bash
# Staging
git add .                    # Stage all changes
git add file.c              # Stage specific file
git add src/                # Stage directory
git add -p                  # Interactive staging

# Committing
git commit -m "message"     # Quick commit
git commit                  # Editor commit
git commit -am "message"    # Stage + commit modified files
git commit --amend          # Fix last commit

# Remote sync
git push                    # Push current branch
git push -u origin branch   # Push and set upstream
git pull                    # Fetch and merge
git pull --rebase           # Fetch and rebase
git fetch                   # Download without merging
```

---

[Previous (Setup Test Environment)](00_set_up.md) | [Back to Main](README.md) | [Next (Branch Management)](02_branch.md) | [Top](#basic-git-operations)
