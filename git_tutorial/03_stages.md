[Previous (Branch Management)](02_branch.md) | [Back to Main](README.md) | [Next (Staging Changes)](03_stages.md) | [Down](#best-practices)

# Working with Stages

## Overview

Master the staging area (index) - Git's preparation area between your working directory and repository. Learn to control exactly what goes into each commit.

---

## Understanding the Three Trees

```
Working Directory  →  Staging Area (Index)  →  Repository
   (your files)       (git add)                (git commit)
```

---

## Part 1: The Staging Area Concept

### What is Staging?

The staging area lets you **craft precise commits** by selecting exactly which changes to include.

**Why it matters:**

- Create atomic commits (one logical change per commit)
- Review changes before committing
- Exclude work-in-progress files
- Stage parts of files separately

---

## Part 2: Adding to Stage

### `git add <file>` - Stage Specific Files

**Example:**

```bash
# Modify multiple files
echo "fix" >> src/bug.c
echo "feature" >> src/feature.c
echo "docs" >> README.md

# Stage only the bug fix
git add src/bug.c

# Check what's staged
git status
```

**Output:**

```
Changes to be committed:
  modified:   src/bug.c

Changes not staged for commit:
  modified:   README.md
  modified:   src/feature.c
```

---

### `git add .` vs `git add -A` vs `git add -u`

| Command      | New Files | Modified | Deleted | Scope                  |
| ------------ | --------- | -------- | ------- | ---------------------- |
| `git add .`  | ✅         | ✅        | ✅       | Current directory down |
| `git add -A` | ✅         | ✅        | ✅       | Entire repository      |
| `git add -u` | ❌         | ✅        | ✅       | Entire repository      |

**Examples:**

```bash
# Stage all changes in current directory and subdirectories
git add .

# Stage all changes in entire repo (from any directory)
git add -A

# Stage only modified and deleted (skip new files)
git add -u
```

**Use cases:**

- `git add .` - Most common, stage everything here
- `git add -A` - Ensure you catch everything repo-wide
- `git add -u` - Update tracked files only, ignore new files

---

### `git add -p` - Interactive Patch Mode

**When to use:**

- File has multiple unrelated changes
- Want to split changes into separate commits
- Need surgical precision

**Example:**

```bash
# File with bug fix and new feature mixed
cat >> src/main.c << 'EOF'

// Bug fix for memory leak
void fix_leak() {
    free(buffer);
}

// New feature
void new_dashboard() {
    render_ui();
}
EOF

# Stage interactively
git add -p src/main.c
```

**Interactive prompts:**

```
Stage this hunk [y,n,q,a,d,s,e,?]?

y - yes, stage this hunk
n - no, don't stage
q - quit; don't stage this or remaining
a - stage this and all remaining
d - don't stage this or remaining
s - split into smaller hunks
e - manually edit the hunk
? - print help
```

**Workflow:**

```bash
git add -p src/main.c
# Select 'y' for bug fix hunk
# Select 'n' for feature hunk
git commit -m "fix: resolve memory leak"

# Now stage the feature
git add -p src/main.c
# Select 'y' for feature hunk
git commit -m "feat: add dashboard"
```

---

### `git add -i` - Interactive Mode

Full interactive menu for staging operations.

**Example:**

```bash
git add -i
```

**Menu:**

```
*** Commands ***
  1: status       2: update       3: revert       4: add untracked
  5: patch        6: diff         7: quit         8: help
What now>
```

- **status**: See what's staged
- **update**: Stage files
- **revert**: Unstage files
- **patch**: Patch mode (same as -p)
- **diff**: See staged changes

---

## Part 3: Inspecting Staged Changes

### `git status` - Overview

**Example:**

```bash
git status
```

**Output:**

```
On branch feature/new-ui
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   src/main.c
        new file:   src/feature.c

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
        modified:   src/utils.c

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        temp.txt
```

---

### `git diff` - Compare Working vs Staged

```bash
# See unstaged changes (working directory vs staging area)
git diff

# See what file changed
git diff src/main.c
```

---

### `git diff --staged` - Compare Staged vs Repository

**When to use:**

- Review what you're about to commit
- Double-check staged changes
- Before running `git commit`

```bash
# See staged changes (staging area vs last commit)
git diff --staged

# Or
git diff --cached

# For specific file
git diff --staged src/main.c
```

**Best practice workflow:**

```bash
# 1. Make changes
# ... edit files ...

# 2. Stage selectively
git add src/feature.c

# 3. Review what's staged
git diff --staged

# 4. If looks good, commit
git commit -m "feat: add new feature"
```

---

### `git status -s` - Short Status

Compact view of changes.

**Example:**

```bash
git status -s
```

**Output:**

```
M  src/main.c      # Modified and staged
 M src/utils.c     # Modified but not staged
A  src/new.c       # Added (new file staged)
?? temp.txt        # Untracked
MM src/complex.c   # Modified, staged, then modified again
```

**Legend:**

- First column: staging area status
- Second column: working directory status
- `M` = modified
- `A` = added
- `D` = deleted
- `??` = untracked
- `MM` = staged + more unstaged changes

---

## Part 4: Unstaging Changes

### `git restore --staged <file>` - Unstage File (Modern)

**When to use:**

- Staged wrong file
- Want to modify before committing
- Split into multiple commits

**Example:**

```bash
# Stage files
git add file1.c file2.c file3.c

# Oops, don't want file3.c in this commit
git restore --staged file3.c

# Check result
git status
```

**Output:**

```
Changes to be committed:
        modified:   file1.c
        modified:   file2.c

Changes not staged for commit:
        modified:   file3.c
```

---

### `git reset HEAD <file>` - Unstage File (Traditional)

Older syntax, still widely used.

**Example:**

```bash
# Unstage file
git reset HEAD src/main.c

# Unstage all
git reset HEAD
```

**Note:** `git restore --staged` is the modern, clearer alternative.

---

### Comparison: Unstaging Commands

| Command                       | Effect       | Notes                     |
| ----------------------------- | ------------ | ------------------------- |
| `git restore --staged <file>` | Unstage file | Modern, recommended       |
| `git reset HEAD <file>`       | Unstage file | Traditional, still common |
| `git reset`                   | Unstage all  | Shorthand for all files   |

---

## Part 5: Modifying Staged Content

### Scenario: Staged File, Then Made More Changes

**Example:**

```bash
# Modify and stage
echo "version 1" > file.txt
git add file.txt

# Make more changes
echo "version 2" > file.txt

# Check status
git status -s
```

**Output:**

```
MM file.txt
```

Two `M`s mean:

- First `M`: staged changes (version 1)
- Second `M`: unstaged changes (version 2)

**Options:**

#### Option 1: Stage the new changes too

```bash
git add file.txt  # Now both versions are staged
```

#### Option 2: Commit staged, keep working on unstaged

```bash
git commit -m "Add version 1"
# Continue working with version 2
```

#### Option 3: Unstage and restage everything

```bash
git restore --staged file.txt
git add file.txt  # Stage latest version
```

---

## Part 6: Staging Patterns

### Using Wildcards

```bash
# Stage all .c files
git add *.c

# Stage all files in directory
git add src/*.c

# Stage all .js files recursively
git add **/*.js
```

---

### Staging by Extension

```bash
# Stage all source files
git add src/*.c src/*.h

# Stage all documentation
git add docs/*.md

# Stage configuration files
git add *.json *.yml *.yaml
```

---

### Excluding Patterns

**Using .gitignore:**

```bash
# Create .gitignore
cat > .gitignore << 'EOF'
*.o
*.out
*.log
node_modules/
.env
EOF

# Stage .gitignore itself
git add .gitignore

# Now git add . will ignore these patterns
git add .
```

---

## Part 7: Advanced Staging Workflows

### Workflow 1: Atomic Commits

**Goal:** One logical change per commit

```bash
# Made changes to 5 files for 2 different features

# Commit feature A
git add file1.c file2.c
git commit -m "feat: add user authentication"

# Commit feature B
git add file3.c file4.c file5.c
git commit -m "feat: add data export"
```

---

### Workflow 2: Partial File Staging

**Goal:** Commit parts of a file separately

```bash
# File has bug fix + refactoring mixed

# Stage only bug fix
git add -p complex.c
# Select 'y' for bug fix hunks
# Select 'n' for refactoring hunks
git commit -m "fix: resolve null pointer"

# Stage refactoring
git add complex.c
git commit -m "refactor: simplify logic"
```

---

### Workflow 3: Review Before Commit

**Goal:** Always know what you're committing

```bash
# Stage files
git add .

# Review what's staged
git diff --staged

# If something's wrong
git restore --staged wrong-file.c

# Review again
git diff --staged

# Commit when confident
git commit -m "descriptive message"
```

---

### Workflow 4: Incremental Staging

**Goal:** Stage files as you complete them

```bash
# Complete file 1
# ... edit file1.c ...
git add file1.c

# Complete file 2
# ... edit file2.c ...
git add file2.c

# Review accumulated staging
git diff --staged

# Commit all staged
git commit -m "Complete feature implementation"
```

---

## Part 8: Common Staging Patterns

### Pattern 1: Fix and Feature Separation

```bash
# Working on feature, found bug

# Stage and commit bug fix first
git add src/bugfix.c
git commit -m "fix: resolve crash on null input"

# Continue with feature
git add src/feature.c src/feature.h
git commit -m "feat: add export functionality"
```

---

### Pattern 2: Code and Tests Separately

```bash
# Implement feature
git add src/feature.c includes/feature.h
git commit -m "feat: add data validation"

# Add tests
git add tests/test_validation.c
git commit -m "test: add validation tests"
```

---

### Pattern 3: Core and Documentation

```bash
# Stage implementation
git add src/*.c includes/*.h
git commit -m "feat: implement API endpoint"

# Stage documentation
git add docs/api.md README.md
git commit -m "docs: document new API endpoint"
```

---

## Part 9: Troubleshooting Staging

### Problem: Accidentally Staged Wrong Files

```bash
# Staged everything
git add .

# Oops, included debug files
git status

# Unstage specific files
git restore --staged debug.log temp.txt

# Or unstage everything and start over
git restore --staged .
```

---

### Problem: Can't Remember What's Staged

```bash
# Quick check
git status -s

# Detailed check
git status

# See actual changes
git diff --staged
```

---

### Problem: Staged Old Version of File

```bash
# Staged file
git add file.c

# Made more changes to same file
echo "update" >> file.c

# Want to stage latest version
git add file.c  # Stages the new version

# Or unstage and restage
git restore --staged file.c
git add file.c
```

---

### Problem: Want to Uncommit but Keep Staged

```bash
# Made a commit
git commit -m "message"

# Oops, want to modify it
git reset --soft HEAD~1

# Changes are now staged, can modify and recommit
git status  # Shows staged changes
```

---

## Practice Exercises

### Exercise 1: Selective Staging

```bash
# Create files with different purposes
echo "bug fix" > fix.c
echo "new feature" > feature.c
echo "documentation" > README.md

# Stage and commit separately
git add fix.c
git commit -m "fix: resolve bug"

git add feature.c
git commit -m "feat: add feature"

git add README.md
git commit -m "docs: update README"
```

---

### Exercise 2: Patch Mode Practice

```bash
# Create file with mixed changes
cat > test.c << 'EOF'
// Bug fix
void fix1() {}

// Feature
void feature1() {}

// Bug fix
void fix2() {}
EOF

# Stage interactively
git add -p test.c
# Stage only bug fixes, skip feature
```

---

### Exercise 3: Review Workflow

```bash
# Make changes
echo "change" >> file1.c
echo "change" >> file2.c

# Stage
git add .

# Review
git diff --staged

# Decide if looks good
# If yes: git commit
# If no: git restore --staged <file>
```

---

## Quick Reference

```bash
# Staging
git add <file>               # Stage specific file
git add .                    # Stage all in current dir
git add -A                   # Stage all in repo
git add -u                   # Stage modified/deleted only
git add -p                   # Interactive patch mode
git add -i                   # Interactive mode

# Inspecting
git status                   # Full status
git status -s                # Short status
git diff                     # Unstaged changes
git diff --staged            # Staged changes
git diff --cached            # Same as --staged

# Unstaging
git restore --staged <file>  # Unstage file (modern)
git reset HEAD <file>        # Unstage file (traditional)
git restore --staged .       # Unstage all

# Patterns
git add *.c                  # Stage by extension
git add src/                 # Stage directory
git add **/*.js              # Recursive pattern
```

---

## Best Practices

✅ **Do:**

- Review staged changes before committing (`git diff --staged`)
- Use `git status` frequently
- Stage related changes together
- Use patch mode for mixed changes
- Commit small, logical units

❌ **Don't:**

- Blindly `git add .` without checking
- Stage debug/temporary files
- Mix unrelated changes in one commit
- Forget to review what's staged
- Stage sensitive data (passwords, keys)

---

[Previous (Branch Management)](02_branch.md) | [Back to Main](README.md) | [Next (Cherry-pick)](04_cherry-pick.md) | [Top](#working-with-stages)
