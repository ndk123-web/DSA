# Inorder Traversal of Binary Tree (C++)

## Problem

Given the root of a binary tree, return the **inorder traversal** of its nodes' values.

**Inorder Traversal rule (fixed, classical):**

```
Left → Root → Right
```

---

## Short Code Explanation

We use **recursion** to traverse the tree.

- Maintain a vector `res` to store the answer.
- Use a helper function `inorder()` to:

  1. Go to the left subtree
  2. Visit the current node
  3. Go to the right subtree

The recursion automatically uses the call stack to remember where to return.

---

## Code (Short Version)

```cpp
class Solution {
private:
    vector<int> res;

    void inorder(TreeNode* node) {
        if (!node) return;

        inorder(node->left);
        res.push_back(node->val);
        inorder(node->right);
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        inorder(root);
        return res;
    }
};
```

---

## Why This Works (Tell-it-like-it-is)

- Binary trees are **recursive by nature**
- Inorder traversal **must** visit left before root
- Recursion ensures correct order without manual stack handling
- This is the **standard textbook solution**, nothing fancy

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

1. `inorder(1)`

   - Go left → `nullptr` → return
   - Add `1`
   - Go right → `inorder(2)`

2. `inorder(2)`

   - Go left → `inorder(3)`

3. `inorder(3)`

   - Go left → `nullptr`
   - Add `3`
   - Go right → `nullptr`
   - return

4. Back to `2`

   - Add `2`
   - Go right → `nullptr`
   - return

### Final Output

```
res = [1, 3, 2]
```

---

## Time Complexity

```
O(N)
```

- Every node is visited **exactly once**
- `N` = number of nodes in the tree

---

## Space Complexity

```
O(N)
```

Worst case (skewed tree):

- Recursive call stack → `O(N)`
- Result vector → `O(N)`

Balanced tree:

- Call stack → `O(log N)`
- Result vector → `O(N)`

---

## Important Notes (Don’t Ignore)

- `res` is a **member variable**, not local
- On LeetCode this is fine because each test uses a new object
- In real projects, always **clear `res` before reuse**

---

## Key Concept Summary

| Concept   | Meaning                               |
| --------- | ------------------------------------- |
| Inorder   | Left → Root → Right                   |
| Recursion | Tree problems are naturally recursive |
| Base Case | `if (!node) return;`                  |
| Stack     | Managed automatically by recursion    |
