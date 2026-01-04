`# Lowest Common Ancestor in a Binary Search Tree (C++)

## Problem

Given a **Binary Search Tree (BST)** and two nodes `p` and `q`, find their **Lowest Common Ancestor (LCA)**.

**Lowest Common Ancestor (LCA)**:

- The **lowest (deepest)** node in the tree
- That has **both `p` and `q` as descendants**
- A node **can be an ancestor of itself**

---

## Key BST Property Used

In a BST:

```
Left subtree  <  Root  <  Right subtree
```

All values are **unique**.

This ordering allows us to decide **direction** (left or right) using values only.

---

## Core Logic (One Line)

> If `p` and `q` are on the **same side** of `root`, move to that side.
> Otherwise, `root` itself is the **LCA**.

---

## Code (Your Solution – Correct)

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return nullptr;

        if (max(p->val, q->val) < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
        else if (min(p->val, q->val) > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        }
        else {
            return root;
        }
    }
};
```

---

## Condition Breakdown (Very Important)

### 1️⃣ Both nodes on LEFT side

```cpp
max(p->val, q->val) < root->val
```

Meaning:

- Even the **larger** value is smaller than `root`
- So **both `p` and `q` lie in left subtree**

👉 LCA cannot be `root`, go left.

---

### 2️⃣ Both nodes on RIGHT side

```cpp
min(p->val, q->val) > root->val
```

Meaning:

- Even the **smaller** value is greater than `root`
- So **both lie in right subtree**

👉 LCA cannot be `root`, go right.

---

### 3️⃣ Else case (Split point)

```cpp
return root;
```

This covers:

- One node on left, one on right
- OR one node equals `root`

👉 This is exactly where paths **split** → LCA found.

---

## Dry Run (Step-by-Step)

### Example BST

```
        6
       / \
      2   8
     / \
    0   4
```

---

### Case 1: `p = 0`, `q = 4`

**At root = 6**

```
max(0,4) < 6  → true
→ move left
```

**At root = 2**

```
max(0,4) < 2  → false
min(0,4) > 2  → false
→ else → return 2
```

✅ **LCA = 2**

---

### Case 2: `p = 2`, `q = 8`

**At root = 6**

```
max(2,8) < 6 → false
min(2,8) > 6 → false
→ else → return 6
```

✅ **LCA = 6**

---

### Case 3: One node is ancestor of other

`p = 2`, `q = 4`

**At root = 6**

```
max(2,4) < 6 → true
→ left
```

**At root = 2**

```
max(2,4) < 2 → false
min(2,4) > 2 → false
→ return 2
```

✅ **LCA = 2**
(Ancestor allowed to be itself)

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

## Why This Is Efficient

- You **never visit unnecessary branches**
- You follow **only one path** from root to LCA
- This is faster than normal binary tree LCA (`O(N)`)

---

## One-Line Memory Rule

> **BST LCA = first node where p and q go in different directions**
