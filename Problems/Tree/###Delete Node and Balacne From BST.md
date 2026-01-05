# Delete Node in a Binary Search Tree (C++)

## Problem

Given the root of a **Binary Search Tree (BST)** and a key, delete the node with the given key and return the updated root.

**BST property (must remain valid):**

```
Left subtree  <  Root  <  Right subtree
```

All node values are **unique**.

---

## Core Idea (One Line)

> Search the node using BST rules, then delete it by handling one of **three cases**.

---

## Code (Final Correct Solution)

```cpp
class Solution {
private:
    TreeNode* deleteN(TreeNode* root, int key) {
        if (!root) return root;

        if (root->val > key) {
            root->left = deleteN(root->left, key);
        }
        else if (root->val < key) {
            root->right = deleteN(root->right, key);
        }
        else {
            // Case 1 & 2: zero or one child
            if (!root->left) return root->right;
            if (!root->right) return root->left;

            // Case 3: two children
            TreeNode* curr = root->right;
            while (curr->left) curr = curr->left;   // inorder successor

            root->val = curr->val;                  // replace value
            root->right = deleteN(root->right, root->val);
        }
        return root;
    }

public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        return deleteN(root, key);
    }
};
```

---

## Why This Works (Logic Breakdown)

Deletion in BST always falls into **three cases**.

### Case 1: Node has **no children** (leaf)

```
return nullptr
```

Handled implicitly by:

```cpp
if (!root->left) return root->right;
```

---

### Case 2: Node has **one child**

```
return the existing child
```

Handled by:

```cpp
if (!root->left) return root->right;
if (!root->right) return root->left;
```

---

### Case 3: Node has **two children**

Steps:

1. Find **inorder successor**
   → minimum node in right subtree (leftmost node)
2. Copy successor’s value to current node
3. Delete successor from right subtree

This guarantees:

- BST property remains intact
- Successor deletion becomes case 1 or 2 (easy)

---

## Dry Run (Step-by-Step)

### Example Tree

```
        5
       / \
      3   8
         /
        6
```

Delete key = `5`

---

### Execution

1. Found node `5`
2. Both children exist
3. Inorder successor = `6`
4. Replace `5 → 6`
5. Delete duplicate `6` from right subtree

---

### Final Tree

```
        6
       / \
      3   8
```

BST property preserved ✅

---

## Time Complexity

```
O(H)
```

Where `H` = height of BST

| Tree Type    | Time       |
| ------------ | ---------- |
| Balanced BST | `O(log N)` |
| Skewed BST   | `O(N)`     |

---

## Space Complexity

```
O(H)
```

- Due to recursion stack
- No extra data structures used

---

## Important Observations

- Recursive delete works cleanly because each call **returns new subtree root**
- Using inorder successor ensures:

  - Replacement value is valid
  - Deletion is simplified

- This is the **standard expected solution** in interviews

---

## Common Mistakes (You Avoided These)

❌ Ignoring return value of recursive delete
❌ Random subtree attachment
❌ Breaking BST ordering
❌ Special-casing root deletion incorrectly

---

## One-Line Memory Rule

> **BST delete = search + 3 cases + successor replacement**
