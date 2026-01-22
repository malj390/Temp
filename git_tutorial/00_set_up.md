[Back to Main](README.md) | [Next (Basic Git Commands)](01_basic.md) | [Down](#tips-for-using-this-environment)

# Setup Test Environment

## Purpose

Create a safe, isolated Git repository where you can practice all Git commands without fear of breaking anything important. This environment includes dummy files and realistic scenarios.

---

## Step 1: Create Test Repository

```bash
# Navigate to where you want to create your test repo
cd ~\/Desktop  # or any location you prefer

# Create and enter the test directory
mkdir git-practice
cd git-practice

# Initialize Git repository
git init

# Configure user (if not done globally)
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

**Expected Output:**

```
Initialized empty Git repository in /Users/yourname/Desktop/git-practice/.git/
```

---

## Step 2: Create Dummy File Structure

Create a realistic project structure to practice with:

```bash
# Create directories
mkdir src includes data docs

# Create dummy source files
cat > src\/main.c << 'EOF'
#include <stdio.h>

int main(void) {
    printf("Hello, Git!
");
    return 0;
}
EOF

cat > src\/utils.c << 'EOF'
#include "utils.h"

void print_message(char *msg) {
    printf("%s
", msg);
}
EOF

# Create header files
cat > includes\/utils.h << 'EOF'
#ifndef UTILS_H
#define UTILS_H

void print_message(char *msg);

#endif
EOF

# Create data files
echo "user1,active,2024-01-15" > data\/users.csv
echo "user2,inactive,2024-02-20" >> data\/users.csv

# Create documentation
cat > docs\/README.md << 'EOF'
# Project Documentation

This is a test project for learning Git.

## Features
- Feature A
- Feature B
EOF

# Create configuration file
cat > config.txt << 'EOF'
debug=true
log_level=info
EOF

# Create .gitignore
cat > .gitignore << 'EOF'
*.o
*.out
.DS_Store
node_modules/
EOF
```

---

## Step 3: Verify Structure

```bash
# Check the directory structure
tree .
# or if tree is not installed:
find . -type f | grep -v ".git"
```

**Expected Structure:**

```
.
├── .gitignore
├── config.txt
├── data
│   └── users.csv
├── docs
│   └── README.md
├── includes
│   └── utils.h
└── src
    ├── main.c
    └── utils.c
```

---

## Step 4: Initial Commit

```bash
# Check status
git status

# Add all files
git add .

# Create initial commit
git commit -m "Initial commit: project structure"

# View commit history
git log --oneline
```

**Expected Output:**

```
[main (root-commit) a1b2c3d] Initial commit: project structure
 7 files changed, 35 insertions(+)
```

---

## Step 5: Create Remote Repository (Optional)

If you want to practice remote operations:

### Option A: GitHub

1. Go to GitHub.com
2. Click "New Repository"
3. Name it `git-practice`
4. Don't initialize with README
5. Copy the repository URL

```bash
# Add remote
git remote add origin https:\/\/github.com\/yourusername\/git-practice.git

# Push to remote
git push -u origin main
```

### Option B: Local "Remote" (for offline practice)

```bash
# Create a bare repository to simulate a remote
cd ~\/Desktop
git init --bare git-practice-remote.git

# Add as remote in your working repository
cd ~\/Desktop\/git-practice
git remote add origin ~\/Desktop\/git-practice-remote.git

# Push to "remote"
git push -u origin main
```

---

## Step 6: Create Additional Dummy Content

Add more files for practicing different scenarios:

```bash
# Create a feature branch with some files
git checkout -b feature\/add-logging

# Add a log file
cat > src\/logger.c << 'EOF'
#include <stdio.h>
#include <time.h>

void log_message(char *msg) {
    time_t now = time(NULL);
    printf("[%s] %s
", ctime(&now), msg);
}
EOF

# Commit this
git add src\/logger.c
git commit -m "Add logger functionality"

# Go back to main
git checkout main

# Create another branch
git checkout -b feature\/add-tests

# Add test file
cat > src\/test.c << 'EOF'
#include <assert.h>

void test_utils() {
    assert(1 == 1);
    printf("Tests passed!
");
}
EOF

git add src\/test.c
git commit -m "Add test suite"

# Return to main
git checkout main
```

---

## Step 7: Verify Setup

```bash
# Check all branches
git branch -a

# Check remotes (if configured)
git remote -v

# View full log
git log --all --graph --oneline --decorate
```

**Expected Output:**

```
* a1b2c3d (HEAD -> main) Initial commit: project structure
| * b2c3d4e (feature/add-tests) Add test suite
|/
| * c3d4e5f (feature/add-logging) Add logger functionality
|/
```

---

## Quick Reset (If You Need to Start Over)

```bash
# From within git-practice directory
cd ..
rm -rf git-practice
rm -rf git-practice-remote.git  # if you created it

# Then repeat Step 1
```

---

## What You Now Have

✅ A complete Git repository with realistic file structure  
✅ Multiple branches to practice with  
✅ Initial commit history  
✅ Optional remote repository  
✅ Diverse file types (code, data, docs, config)  
✅ A .gitignore file  

---

## Ready to Practice!

You're now ready to proceed with the tutorials:

**Next Steps:**

- [Basic Git Operations](./01-basic-git-operations.md) - Learn fundamental commands
- [Branch Management](./02-branch-management.md) - Work with branches
- [Working with Stages](./03-working-with-stages.md) - Master the staging area

**Quick Practice Ideas:**

1. Modify a file and practice staging
2. Create new branches
3. Switch between branches
4. View differences between files

---

## Tips for Using This Environment

- **Don't worry about breaking things** - it's a test environment!
- **Experiment freely** - try commands you're unsure about
- **Use `git status` often** - it's your best friend
- **Check `git log`** regularly to see your history
- **Create snapshots** - commit your state before trying risky operations

Happy learning! 🎓
[Back to Main](README.md) | [Next (Basic Git Commands)](01_basic.md) | [Top](#setup-test-environment)
