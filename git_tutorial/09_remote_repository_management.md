[Previous (Comparing Changes)](08_comparing_changes.md) | [Back to Main](README.md) | [Next (Merge Strategies)](10_merge_strategies.md) | [Down](#quick-reference)

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
| ------- | --------- | ------ | ---- |
| `fetch` | ✅         | ❌      | ✅    |
| `pull`  | ✅         | ✅      | ⚠️   |

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
[Previous (Comparing Changes)](08_comparing_changes.md) | [Back to Main](README.md) | [Next (Merge Strategies)](10_merge_strategies.md) | [Top](#09---remote-repository-management)
