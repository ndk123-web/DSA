# Postorder Traversal of Binary Tree (C++)

## Problem

Given the root of a binary tree, return the **postorder traversal** of its nodes' values.

**Postorder Traversal rule (fixed, classical):**

```
Left → Right → Root
```

---

## Short Code Explanation

- Use a vector `res` to store the traversal result
- Use a recursive helper function `postorder()`
- Traverse:

  1. Left subtree
  2. Right subtree
  3. Then process the current node

---

## Code (Short Version)

```cpp
class Solution {
private:
    vector<int> res;

    void postorder(TreeNode* node) {
        if (!node) return;

        postorder(node->left);
        postorder(node->right);
        res.push_back(node->val);
    }

public:
    vector<int> postorderTraversal(TreeNode* root) {
        postorder(root);
        return res;
    }
};
```

---

## Why This Works (No Sugarcoating)

- Postorder means **node is processed after its children**
- Recursion naturally delays `res.push_back()` until both subtrees finish
- This is why postorder is heavily used in:

  - Tree deletion
  - Expression tree evaluation
  - Dependency resolution

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

---

### Function Calls

1. `postorder(1)`

   - Go left → `nullptr`
   - Go right → `postorder(2)`

2. `postorder(2)`

   - Go left → `postorder(3)`

3. `postorder(3)`

   - Go left → `nullptr`
   - Go right → `nullptr`
   - Add `3`
   - return

4. Back to `2`

   - Go right → `nullptr`
   - Add `2`
   - return

5. Back to `1`

   - Add `1`

---

### Final Output

```
res = [3, 2, 1]
```

---

## Time Complexity

```
O(N)
```

- Every node is visited exactly once

---

## Space Complexity

```
O(N)
```

- Result vector → `O(N)`
- Recursion stack:

  - Skewed tree → `O(N)`
  - Balanced tree → `O(log N)`

---

## Important Notes (Classic Reality Check)

- `res` is a **member variable**
- On platforms like LeetCode, this is safe
- In production code, always reset shared state

---

## Key Concept Summary

| Concept   | Meaning               |
| --------- | --------------------- |
| Postorder | Left → Right → Root   |
| DFS       | Depth-first traversal |
| Base Case | Stop at `nullptr`     |
| Stack     | Handled by recursion  |

---

## One-Line Memory Trick

> **Postorder = Print while coming back**

---

## Final Big Picture (Lock This In)

| Traversal | Order               |
| --------- | ------------------- |
| Preorder  | Root → Left → Right |
| Inorder   | Left → Root → Right |
| Postorder | Left → Right → Root |
