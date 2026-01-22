[Previous (Undoing Changes)](07_undoing_changes.md) | [Back to Main](README.md) | [Next (Remote Repository Management)](09_remote_repository_management.md) | [Down](#formatting)

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
[Previous (Undoing Changes)](07_undoing_changes.md) | [Back to Main](README.md) | [Next (Remote Repository Management)](09_remote_repository_management.md) | [Top](#08---comparing-changes)
