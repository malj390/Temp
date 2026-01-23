[Previous (Undoing Changes)](07_undoing_changes.md) | [Back to Main](README.md) | [Next (Remote Repository Management)](09_remote_repository_management.md) | [Down](#quick-reference)

---
- [Overview](#Overview)
- [Part 1: Basic Diff](#Part%201:%20Basic%20Diff)
	- [`git diff` - Unstaged Changes](#%60git%20diff%60%20-%20Unstaged%20Changes)
	- [`git diff --staged` - Staged Changes](#%60git%20diff%20--staged%60%20-%20Staged%20Changes)
	- [`git diff HEAD` - All Changes](#%60git%20diff%20HEAD%60%20-%20All%20Changes)
- [Part 2: Comparing Commits](#Part%202:%20Comparing%20Commits)
	- [Between Two Commits](#Between%20Two%20Commits)
	- [Comparing Specific Files](#Comparing%20Specific%20Files)
- [Part 3: Comparing Branches](#Part%203:%20Comparing%20Branches)
	- [`git diff <branch1> <branch2>`](#%60git%20diff%20%3Cbranch1%3E%20%3Cbranch2%3E%60)
	- [What's in Branch but Not in Another](#What's%20in%20Branch%20but%20Not%20in%20Another)
- [Part 4: Viewing History](#Part%204:%20Viewing%20History)
	- [`git log` Basics](#%60git%20log%60%20Basics)
	- [Filtering Logs](#Filtering%20Logs)
	- [Pretty Formats](#Pretty%20Formats)
- [Part 5: Showing Commits](#Part%205:%20Showing%20Commits)
	- [`git show <commit>`](#%60git%20show%20%3Ccommit%3E%60)
- [Part 6: Diffing Tools](#Part%206:%20Diffing%20Tools)
	- [Word Diff](#Word%20Diff)
	- [Statistics](#Statistics)
- [Quick Reference](#Quick%20Reference)

---

# Comparing Changes

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
