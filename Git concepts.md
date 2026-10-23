# Git Concepts — Practical Revision Notes

> A practical, beginner-friendly guide to Git for development and interviews. Examples use a fictional project with `main`, `feature/rbac`, and `release` branches.

## Table of Contents

- [1. Git's basic workflow](#1-gits-basic-workflow)
- [2. Local vs. remote repositories](#2-local-vs-remote-repositories)
- [3. Fetch vs. pull](#3-fetch-vs-pull)
- [4. Merge vs. rebase](#4-merge-vs-rebase)
- [5. Cherry-pick](#5-cherry-pick)
- [6. Revert](#6-revert)
- [7. Reset: soft, mixed, and hard](#7-reset-soft-mixed-and-hard)
- [8. Merge and rebase conflicts](#8-merge-and-rebase-conflicts)
- [9. Stash](#9-stash)
- [10. Amend and interactive rebase](#10-amend-and-interactive-rebase)
- [11. Branch and pull-request workflow](#11-branch-and-pull-request-workflow)
- [12. HEAD, diff, log, and reflog](#12-head-diff-log-and-reflog)
- [13. Quick comparison table](#13-quick-comparison-table)
- [14. Interview questions and answers](#14-interview-questions-and-answers)
- [15. Official references](#15-official-references)

---

## 1. Git's basic workflow

Think of Git as a system that records snapshots of your code. You edit files, select which changes should go into the next snapshot, create a commit, and optionally send it to GitHub.

```text
Working directory
      |
      | git add
      v
Staging area (index)
      |
      | git commit
      v
Local repository
      |
      | git push
      v
Remote repository (for example, GitHub)
```

- **Working directory:** the files you are currently editing.
- **Staging area/index:** the changes selected for the next commit.
- **Local repository:** commits stored on your computer.
- **Remote repository:** a copy hosted elsewhere, commonly on GitHub.

Example:

```bash
git status
git add middleware/rbac.go
git diff --staged
git commit -m "Add RBAC middleware"
git push origin feature/rbac
```

Important: `git add` does not upload to GitHub. `git commit` also stays local. `git push` sends local commits to the remote branch.

To inspect changes:
- `git diff`: unstaged changes.
- `git diff --staged`: staged changes.
- `git status`: current branch and working-tree/staging status.

## 2. Local vs. remote repositories

A **local branch** lives in your local repository. A **remote branch** is a branch on the server, such as GitHub. A remote-tracking branch such as `origin/main` is your local record of the last known state of the remote `main` branch; it is not the live remote itself.

Example:

```text
Your computer                         GitHub
Local main: A -- B                    Remote main: A -- B -- C
```

If a teammate pushes commit `C` to GitHub, your local `main` does not magically change. After `git fetch origin`, your local remote-tracking reference `origin/main` can point to `C`, while local `main` still points to `B`.

Commands:
```bash
git branch                 # local branches
git branch -r              # remote-tracking branches
git branch -a              # local and remote-tracking branches
git remote -v              # configured remotes
```

The key rule: **local operations generally affect your local repository first; `push` updates a remote, and `fetch` downloads remote information.**

## 3. Fetch vs. pull

Imagine a teammate pushed a new commit `C` to GitHub.

Before fetching:
```text
Local main:  A -- B
GitHub main: A -- B -- C
```

### `git fetch origin`

```bash
git fetch origin
```

Fetch downloads new commits and updates remote-tracking references such as `origin/main`. It does **not** integrate those commits into your current local branch.

```text
Local main:          A -- B
origin/main:         A -- B -- C
```

### `git pull origin main`

```bash
git pull origin main
```

Pull fetches and then integrates the fetched changes into the current branch, using the configured strategy (commonly merge, or rebase if configured/requested).

Simple analogy:
- **Fetch:** the latest parcel has arrived; you have not combined its contents with your current work.
- **Pull:** fetch the parcel and integrate its changes into the current branch.

Use fetch when you want to inspect incoming changes before integrating them.

## 4. Merge vs. rebase

Suppose `main` and your feature branch diverged after commit `A`.

Initial history:
```text
main:           A -- B -- C
                       (main advances)
feature/rbac:   A -- D -- E
```

Here, `B` and `C` are commits on `main`; `D` and `E` are your feature commits.

### Merge

Merge combines the histories. If the branches diverged, Git commonly creates a merge commit with both histories as parents.

```bash
git switch feature/rbac
git merge main
```

Conceptual result:
```text
A -- B -- C ------- M   feature/rbac
 \                   /
  -- D -- E --------
```

The exact drawing depends on the graph; the important point is that merge preserves the original commits and records the integration. It does not rewrite the existing feature commits.

Use merge when you want to integrate branches and preserve the branching history.

### Rebase

Rebase replays your feature commits on top of a new base.

```bash
git switch feature/rbac
git fetch origin
git rebase origin/main
```

Conceptual result:
```text
Before:
main:           A -- B -- C
feature/rbac:   A -- D -- E

After rebasing feature/rbac onto main:
main:           A -- B -- C
feature/rbac:               \-- D' -- E'
```

The feature branch now has a linear-looking history: `A -- B -- C -- D' -- E'`. The new commits `D'` and `E'` replay the changes from `D` and `E`, and normally have different hashes because their parent/history changed.

**Rebase changes only the branch you rebase.** It does not automatically change your teammate's local branch or the GitHub remote branch. Pushing a rebased branch that already exists remotely may require a coordinated history update; avoid rewriting shared branches. If appropriate, `git push --force-with-lease` is safer than plain `--force`, but still changes remote history and must be used carefully.

Simple distinction:
- **Merge:** combine histories; often adds a merge commit.
- **Rebase:** replay commits onto a new base; produces a linear history and changes replayed commit IDs.

## 5. Cherry-pick

Cherry-pick applies the changes introduced by a **specific commit** to your current branch, creating a new commit there. It does not move or remove the original commit from its original branch.

Scenario: the `main` branch contains a bug fix you need in `release`, but you do not want to bring every other `main` commit into the release branch.

Before:
```text
main:       A -- B -- C -- D
                  login  bug fix  dashboard

release:   A -- R
                release configuration
```

Here, `R` is an existing commit already on the release branch. Cherry-pick did not create `R`.

Commands:
```bash
git switch release
git cherry-pick <C-commit-hash>
```

After:
```text
main:       A -- B -- C -- D      (unchanged)
release:   A -- R -- C'
```

- `R` is the release branch's existing commit.
- `C'` is a new commit on `release` that applies the changes introduced by `C`.
- `main` remains unchanged by the cherry-pick.
- The change reaches GitHub's remote `release` branch only after you push it.

Use cherry-pick when you need one particular fix or feature commit without merging an entire branch.

## 6. Revert

Revert undoes the effect of an existing commit by creating a **new commit**. It does not erase the original commit from history.

Suppose a buggy commit `C` has already been pushed to a shared GitHub branch.

Before:
```text
GitHub main: A -- B -- C (bug)
```

Commands:
```bash
git switch main
git pull origin main
git revert <C-commit-hash>
git push origin main
```

After the revert commit is created locally:
```text
Local main: A -- B -- C -- R
```

After the push succeeds:
```text
GitHub main: A -- B -- C -- R
```

`R` is a new commit that reverses the changes introduced by `C`. Commit `C` remains in history. The remote changes only after the push.

Prefer revert for undoing a change on shared/published history because it does not rewrite earlier commits. Reverting a complex commit can cause conflicts; reverting a merge commit requires choosing a mainline parent.

## 7. Reset: soft, mixed, and hard

Reset moves the current branch pointer (`HEAD`) to another commit and, depending on the mode, changes the staging area and working files. It affects your **local current branch**; it does not directly move a GitHub branch.

Suppose your local branch is:
```text
A -- B -- C   (HEAD)
```

Run `git reset <mode> HEAD~1` to move the local branch back one commit to `B`.

### Soft reset

```bash
git reset --soft HEAD~1
```

- Moves local `HEAD` back to `B`.
- Keeps the changes from `C` staged.
- Useful if you want to redo the commit, perhaps with a different message.

### Mixed reset (default)

```bash
git reset --mixed HEAD~1
# Equivalent to: git reset HEAD~1
```

- Moves local `HEAD` back to `B`.
- Keeps the changes in the working directory but unstaged.
- You can edit them and stage the desired changes again.

### Hard reset

```bash
git reset --hard HEAD~1
```

- Moves local `HEAD` back to `B`.
- Resets the index and tracked working files to match the target commit.
- Uncommitted tracked changes can be lost. Use only when you are certain.

Summary:
| Mode | Commit pointer | Staging area | Working files |
|---|---|---|---|
| `--soft` | Moves back | Keeps changes staged | Keeps changes |
| `--mixed` | Moves back | Resets staging | Keeps changes unstaged |
| `--hard` | Moves back | Resets staging | Resets tracked files; local edits may be lost |

If commit `C` was already pushed, resetting your local branch does not remove it from GitHub. Avoid force-pushing a reset over shared history. For a published change, `git revert` is usually safer.

## 8. Merge and rebase conflicts

A conflict happens when Git cannot safely combine changes automatically, often because two branches changed the same lines differently.

Your version:
```go
message := "Access denied"
```

Teammate's version:
```go
message := "Permission denied"
```

Git may mark the file like this:
```text
<<<<<<< HEAD
message := "Access denied"
=======
message := "Permission denied"
>>>>>>> main
```

Choose the correct final code, edit the file, and remove all conflict markers.

For a merge:
```bash
git status
# Resolve the file manually
git add path/to/file
git commit
```

For a rebase:
```bash
git status
# Resolve the file manually
git add path/to/file
git rebase --continue
```

To cancel the operation:
```bash
git rebase --abort
# or, during an in-progress merge:
git merge --abort
```

Do not just delete markers without understanding the code. Resolve the logic correctly, then run tests.

## 9. Stash

Stash temporarily stores eligible uncommitted changes so you can switch context without making a commit.

Scenario: you are midway through RBAC work, but need to switch branches to investigate an urgent bug.

```bash
git stash push -m "WIP RBAC"
git stash list
git switch main
# handle the urgent task
git switch feature/rbac
git stash pop
```

- `git stash push`: stores the current eligible changes and cleans them from the working tree.
- `git stash list`: lists stash entries.
- `git stash pop`: applies the selected stash and removes the entry if application succeeds.
- `git stash apply`: applies changes but keeps the stash entry.
- `git stash -u`: also includes untracked files.

Stash is local; it does not upload the changes to GitHub. Applying a stash can cause conflicts.

## 10. Amend and interactive rebase

### Amend the last commit

If you want to fix the last commit message:
```bash
git commit --amend -m "Add RBAC middleware"
```

If you forgot to include a file:
```bash
git add middleware_test.go
git commit --amend --no-edit
```

Amend replaces the last commit with a new commit, so its hash changes. Avoid amending commits already shared with others unless you coordinate the history update.

### Interactive rebase

Interactive rebase lets you edit, reorder, squash, or reword recent commits.

```bash
git rebase -i HEAD~3
```

Example todo list:
```text
pick   a111 Add RBAC
squash b222 Fix typo
fixup  c333 Fix another typo
```

- `pick`: keep the commit.
- `squash`: combine with the previous commit and allow commit-message editing.
- `fixup`: combine with the previous commit and discard this commit's message.
- `reword`: keep the commit's changes but edit its message.

Interactive rebase is commonly used to clean up a feature branch before opening a pull request. Do not casually rewrite shared history.

## 11. Branch and pull-request workflow

A safe team workflow keeps `main` stable and develops each feature on a separate branch.

```bash
git switch main
git pull origin main
git switch -c feature/rbac

# Make changes and test them
git add .
git commit -m "Add RBAC middleware"
git push -u origin feature/rbac
```

Then open a pull request (PR) on GitHub. Teammates review the code and automated checks run. After approval, the PR can be merged according to repository policy.

- `git switch -c feature/rbac`: creates and switches to a new local branch.
- `git push -u origin feature/rbac`: pushes the branch and sets its upstream tracking branch.
- A PR is a review/integration request; opening one does not automatically merge it.

## 12. HEAD, diff, log, and reflog

- **HEAD:** normally identifies the current checkout position, usually the latest commit on the current branch.
- **Detached HEAD:** HEAD points directly to a commit rather than a local branch. Create/switch to a branch if you want to preserve new commits easily.
- **`git log --oneline --graph --all`:** compact commit history with branch graph.
- **`git diff`:** unstaged differences.
- **`git diff --staged`:** staged differences.
- **`git reflog`:** local record of recent movements of HEAD and branch references; can help find commits after an accidental reset or rebase, as long as the commit is still recoverable.

Useful commands:
```bash
git status
git log --oneline --graph --all
git diff
git diff --staged
git reflog
```

## 13. Quick comparison table

| Command | What it means | Typical use | First affects |
|---|---|---|---|
| `fetch` | Downloads remote updates without integrating into current branch | Inspect incoming work | Local remote-tracking refs and object database |
| `pull` | Fetches, then integrates | Update current branch | Local repository/current branch |
| `merge` | Combines branch histories | Integrate a branch | Current local branch |
| `rebase` | Replays commits on a new base | Linearize feature history | Current local branch |
| `cherry-pick` | Applies one commit's changes as a new commit | Take one fix from another branch | Current local branch |
| `revert` | Creates a commit that reverses another commit | Undo published/shared change | Local branch first; remote after push |
| `reset` | Moves current branch pointer and adjusts index/files by mode | Redo or discard local commits | Current local branch |
| `stash` | Temporarily stores eligible uncommitted changes | Switch tasks without committing | Local repository |
| `commit --amend` | Replaces the latest commit | Fix message or add forgotten changes | Local repository |
| `push` | Sends local commits to a remote | Publish changes | Remote branch |

### The four commands to never confuse

- **Rebase:** replay my commits on a new base.
- **Cherry-pick:** apply one chosen commit's changes to my current branch.
- **Revert:** create a new commit that undoes an earlier commit.
- **Reset:** move my current local branch pointer to another commit.

## 14. Interview questions and answers

### Q1. What is the difference between fetch and pull?
Fetch downloads remote updates without integrating them into the current branch. Pull fetches and then integrates the updates, commonly through merge or rebase depending on configuration.

### Q2. What is the difference between merge and rebase?
Merge combines histories and often creates a merge commit. Rebase replays commits onto a new base, making history linear but changing the replayed commits' hashes.

### Q3. How would you safely undo a commit already pushed to a shared branch?
Usually use `git revert <commit-hash>`, then push the new revert commit. This preserves the earlier commit in history rather than rewriting it.

### Q4. When would you use cherry-pick?
When I need one specific commit's changes on another branch without merging the entire source branch—for example, bringing a critical bug fix into a release branch.

### Q5. What is the difference between reset soft, mixed, and hard?
Soft keeps changes staged; mixed keeps changes in the working tree but unstaged; hard resets tracked files to the target and may discard uncommitted changes.

### Q6. How do you resolve a rebase conflict?
Inspect `git status`, resolve the files, stage them with `git add`, and run `git rebase --continue`. To cancel, run `git rebase --abort`.

### Q7. Does rebasing a local branch change GitHub immediately?
No. Rebase changes the local branch. A push is needed to update the remote, and rewriting an existing remote branch may require coordinated force-pushing.

### Q8. What does R mean in the cherry-pick diagram `A -- R -- C'`?
`R` is an existing commit on the release branch (for example, a release configuration change). Cherry-pick does not create R; it applies commit C's changes as a new commit C' on top of R.

## 15. Official references

These are the official Git documentation pages for further reading:

- [Git Reference](https://git-scm.com/docs)
- [Git Book: Git Basics — Recording Changes](https://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository)
- [Git Book: Branching and Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging)
- [Git Book: Rebasing](https://git-scm.com/book/en/v2/Git-Branching-Rebasing)
- [git fetch](https://git-scm.com/docs/git-fetch)
- [git pull](https://git-scm.com/docs/git-pull)
- [git merge](https://git-scm.com/docs/git-merge)
- [git rebase](https://git-scm.com/docs/git-rebase)
- [git cherry-pick](https://git-scm.com/docs/git-cherry-pick)
- [git revert](https://git-scm.com/docs/git-revert)
- [git reset](https://git-scm.com/docs/git-reset)
- [git stash](https://git-scm.com/docs/git-stash)
- [git reflog](https://git-scm.com/docs/git-reflog)
- [GitHub Docs: About branches](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-branches)
- [GitHub Docs: About pull requests](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests)
