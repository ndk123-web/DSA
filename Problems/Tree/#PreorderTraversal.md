# Preorder Traversal of Binary Tree (C++)

## Problem

Given the root of a binary tree, return the **preorder traversal** of its nodes' values.

**Preorder Traversal rule (fixed):**

```
Root → Left → Right
```

---

## Short Code Explanation

- Maintain a vector `res` to store traversal result
- Use a recursive helper function `preorder()`
- Visit **root first**, then left subtree, then right subtree

---

## Code (Short Version)

```cpp
class Solution {
private:
    vector<int> res;

    void preorder(TreeNode* node) {
        if (!node) return;

        res.push_back(node->val);
        preorder(node->left);
        preorder(node->right);
    }

public:
    vector<int> preorderTraversal(TreeNode* root) {
        preorder(root);
        return res;
    }
};
```

---

## Why This Works (Straight Talk)

- Preorder traversal **always processes the root first**
- Recursive calls naturally maintain traversal order
- This is the **standard DFS preorder**
- No need for extra data structures

---

## Dry Run (Step-by-Step)

### Example Tree

```
       1
        \
         2
        /
       3
```

### Function Calls

1. `preorder(1)`

   - Add `1`
   - Go left → `nullptr`
   - Go right → `preorder(2)`

2. `preorder(2)`

   - Add `2`
   - Go left → `preorder(3)`

3. `preorder(3)`

   - Add `3`
   - Go left → `nullptr`
   - Go right → `nullptr`
   - return

### Final Output

```
res = [1, 2, 3]
```

---

## Time Complexity

```
O(N)
```

- Each node is visited exactly once

---

## Space Complexity

```
O(N)
```

- Result vector stores all nodes
- Recursion stack:

  - Skewed tree → `O(N)`
  - Balanced tree → `O(log N)`

---

## Important Notes (Classic Gotchas)

- `res` is a class-level variable
- Works fine in LeetCode because object is recreated per test
- In real code, **clear `res` before reuse**

---

## Key Concept Summary

| Concept   | Meaning                |
| --------- | ---------------------- |
| Preorder  | Root → Left → Right    |
| DFS       | Depth First Search     |
| Base Case | Stop at `nullptr`      |
| Stack     | Implicit via recursion |

---

## One-Line Memory Trick

> **Preorder = Print before going down**
