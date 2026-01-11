# 📘 Remove Leaf Nodes With Given Target — README

## Problem Summary

You are given a **binary tree** and an integer `target`.

You must:

- Remove **all leaf nodes** whose value is equal to `target`
- After removing leaves, **new leaf nodes may appear**
- Those new leaves must also be checked and removed
- This process continues until no such leaf exists

Finally, return the **new root** of the tree.

---

## Key Insight (Very Important)

This problem is **not a one-pass deletion**.

> Removing a leaf can turn its parent into a new leaf.
> So the tree must be processed **bottom-up**.

This is why **postorder traversal** (left → right → node) is mandatory.

---

## Solution 1 — Return New Subtree (Cleanest & Recommended)

### Code

```cpp
class Solution {
private:
    TreeNode* dfs(TreeNode* root, int target) {
        if (!root) return nullptr;

        // Process children first (postorder)
        root->left = dfs(root->left, target);
        root->right = dfs(root->right, target);

        // If current node becomes a leaf and matches target → delete it
        if (root->val == target && !root->left && !root->right) {
            return nullptr;
        }

        return root; // keep node
    }

public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        return dfs(root, target);
    }
};
```

---

### Logic Explanation

- Each recursive call **returns the updated subtree**
- Parent directly reconnects to the returned subtree
- If a node becomes a leaf **after children are removed**, it is checked again
- This naturally handles **repeated pruning**

---

### Why This Works

- No parent tracking
- No pointer tricks
- No special handling for root
- Structure updates are explicit and safe

---

### Complexity

```
Time  : O(n)
Space : O(h)   // recursion stack
```

---

### When to Use This

✅ Best for interviews
✅ Best for readability
✅ Best for correctness

This is the **canonical solution**.

---

## Solution 2 — Parent Tracking + Pointer Reference

### Code

```cpp
class Solution {
private:
    void dfs(TreeNode*& root, int target, TreeNode* prev, bool isLeft) {
        if (!root) return;

        dfs(root->left, target, root, true);
        dfs(root->right, target, root, false);

        if (root->val == target && !root->left && !root->right) {
            if (prev) {
                if (isLeft)
                    prev->left = nullptr;
                else
                    prev->right = nullptr;
            } else {
                // root node deletion
                root = nullptr;
            }
        }
    }

public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        dfs(root, target, nullptr, true);
        return root;
    }
};
```

---

### Logic Explanation

- Uses **postorder traversal**
- Tracks:

  - `prev` → parent node
  - `isLeft` → whether current node is left or right child

- Uses `TreeNode*& root` so root deletion actually works
- Parent pointers are manually updated

---

### Why It Works

- `TreeNode*&` allows modifying the caller’s pointer
- `prev->left / prev->right` directly modifies real tree structure
- Postorder ensures children are removed before parent is checked

---

### Downsides / Doubts Explained

❌ Overcomplicated
❌ Manual parent tracking is error-prone
❌ Harder to reason about
❌ Easy to introduce bugs

This solution works **because of correct pointer semantics**, not because it is elegant.

---

### Complexity

```
Time  : O(n)
Space : O(h)
```

---

### When to Use This

⚠️ Only if you **want to practice pointer references**
⚠️ Not recommended for interviews

---

## Solution 3 — Pointer Reference Only (Simplified Version of #2)

### Code

```cpp
class Solution {
private:
    void dfs(TreeNode*& root, int target) {
        if (!root) return;

        dfs(root->left, target);
        dfs(root->right, target);

        if (root->val == target && !root->left && !root->right) {
            root = nullptr;
        }
    }

public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        dfs(root, target);
        return root;
    }
};
```

---

### Logic Explanation

- Uses `TreeNode*& root` (reference to pointer)
- Child pointers are modified directly
- No need for `prev` or `isLeft`
- Postorder ensures correctness

---

### Why This Works

- `root` is an **alias of the caller’s pointer**
- Setting `root = nullptr` removes the node from the tree
- Cleaner than solution 2, but still pointer-heavy

---

### Downsides / Doubts Explained

❌ Requires strong understanding of references
❌ Less intuitive than returning subtree
❌ Still lower-level than needed

---

### Complexity

```
Time  : O(n)
Space : O(h)
```

---

## Comparison of All Three Approaches

| Solution | Technique          | Cleanliness | Interview Friendly |
| -------- | ------------------ | ----------- | ------------------ |
| 1        | Return subtree     | ⭐⭐⭐⭐    | ⭐⭐⭐⭐           |
| 2        | Parent + reference | ⭐⭐        | ⭐                 |
| 3        | Reference only     | ⭐⭐⭐      | ⭐⭐               |

---

## Core Doubts Clarified

### ❓ Why postorder traversal?

Because:

- You must decide **after children are processed**
- A node may become a leaf **after deletion**

---

### ❓ Why returning `TreeNode*` is easier?

Because:

- Tree structure changes are explicit
- No parent tracking
- No pointer confusion

---

### ❓ Why references work?

Because:

- `TreeNode*&` allows changing the caller’s pointer
- Setting `root = nullptr` actually removes the node

---

## Final Mental Model (Lock This In)

> **Tree deletion problems are easiest when the DFS returns the new subtree.**

If:

- You find yourself tracking parent
- Using flags
- Or fixing edge cases manually

You’re probably fighting the problem instead of flowing with it.
