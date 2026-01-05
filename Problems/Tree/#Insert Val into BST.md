# Insert into a Binary Search Tree (C++)

## Problem

Given the root of a **Binary Search Tree (BST)** and a value `val`, insert `val` into the BST and return the root of the tree.

**BST rules (must always hold):**

```
Left subtree  <  root->val
Right subtree >  root->val
```

All values are **unique** (no duplicates).

---

## Core Idea (One Line)

> Starting from the root, keep going **left or right** until you find an empty spot, then insert the node there.

---

## Code (Your Solution)

```cpp
class Solution {
private:
    void push(TreeNode* root, int val) {
        if (root->val > val) {
            if (root->left == nullptr) {
                root->left = new TreeNode(val);
                return;
            }
            push(root->left, val);
        }
        else {
            if (root->right == nullptr) {
                root->right = new TreeNode(val);
                return;
            }
            push(root->right, val);
        }
    }

public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root)
            return new TreeNode(val);

        push(root, val);
        return root;
    }
};
```

---

## Why This Works (Logic Breakdown)

At **each node**, you ask only one question:

> Is `val` smaller or greater than current node’s value?

### Case 1: `val` is smaller

```cpp
if (root->val > val)
```

- BST rule says smaller values go **left**
- If left child is empty → insert here
- Otherwise → keep going left

---

### Case 2: `val` is greater

```cpp
else
```

- Greater values go **right**
- If right child is empty → insert here
- Otherwise → keep going right

---

## Dry Run (Step-by-Step)

### Initial BST

```
        4
       / \
      2   7
     / \
    1   3
```

Insert `val = 5`

---

### Execution Flow

1. `insertIntoBST(4, 5)`

   - root exists → call `push(4, 5)`

2. At node `4`

   ```
   4 < 5 → go right
   ```

3. At node `7`

   ```
   7 > 5 → go left
   ```

4. `7->left` is `nullptr`

   ```
   Insert new TreeNode(5)
   ```

---

### Final Tree

```
        4
       / \
      2   7
     / \  /
    1   3 5
```

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
- No extra data structures

---

## Important Observations

- This is **DFS**
- You modify tree **in-place**
- Stops recursion immediately after insertion
- Clean separation of logic (`push`) and API (`insertIntoBST`)

---

## Common Mistakes (You Avoided These)

❌ Inserting without respecting BST rule
❌ Creating new tree instead of modifying existing one
❌ Forgetting base case when root is `nullptr`

---

## One-Line Memory Rule

> **BST insert = follow the rule until null**
