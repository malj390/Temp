[Previous (Quick Reference)](11_quick_reference.md) | [Back to Main](README.md) | [Down](#final-checklist)

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

---

[Previous (Quick Reference)](11_quick_reference.md) | [Back to Main](README.md) | [Top](#12---best-practices)
