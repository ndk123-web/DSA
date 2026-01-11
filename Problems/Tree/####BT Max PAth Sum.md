# 📘 Binary Tree Maximum Path Sum — README

## Problem Summary

You are given a **binary tree**, where each node has an integer value (can be negative).

A **path** is defined as:

- Any sequence of nodes connected by parent–child edges
- You can start and end at **any node**
- You **cannot revisit** a node
- Path does **not** have to pass through the root

### Goal

Return the **maximum possible sum** of values along any valid path.

---

## Important Clarification (Most Confusion Comes From Here)

There are **two different concepts** in this problem:

1. **Maximum path sum anywhere in the tree**
   → This is the final answer (`res`)

2. **Maximum path sum that can be extended upward to the parent**
   → This is what `dfs()` returns

These are **not the same thing**.

---

## The Code

```cpp
class Solution {
private:
    int res;

    int dfs(TreeNode* root) {
        if (!root) return 0;

        int leftMax = max(dfs(root->left), 0);
        int rightMax = max(dfs(root->right), 0);

        res = max(res, root->val + leftMax + rightMax);

        return root->val + max(leftMax, rightMax);
    }

public:
    int maxPathSum(TreeNode* root) {
        res = root->val;
        dfs(root);
        return res;
    }
};
```

---

## Core Idea (One Sentence)

> At every node, decide:
>
> - **What is the best path that passes through this node?**
> - **What is the best path I can extend to my parent?**

---

## Why `max(dfs(child), 0)` ?

```cpp
int leftMax = max(dfs(root->left), 0);
int rightMax = max(dfs(root->right), 0);
```

### Reason

- A path is **optional**
- If a child contributes a **negative sum**, it is better to **not include it**

So:

- Negative contribution → ignore
- Positive contribution → include

This is the key trick.

---

## What `dfs()` Returns (Very Important)

```cpp
return root->val + max(leftMax, rightMax);
```

This means:

> “If I want to continue the path upward to my parent,
> I can only choose **one direction** (left OR right).”

You cannot take both, because a path going upward must be **linear**, not branching.

---

## Why `res` Uses Both Children

```cpp
res = max(res, root->val + leftMax + rightMax);
```

Here, we are calculating:

> “What if the **maximum path passes through this node**?”

This path:

- Comes from left child
- Goes through current node
- Goes to right child

This path **cannot be extended upward**, but it **might be the global maximum**, so we store it in `res`.

---

## Dry Run Example

Tree:

```
        -10
        /  \
       9   20
          /  \
         15   7
```

---

### Step-by-step

#### Node 15

```
left = 0, right = 0
res = max(-10, 15) = 15
return 15
```

#### Node 7

```
res = max(15, 7) = 15
return 7
```

#### Node 20

```
leftMax = 15
rightMax = 7

res = max(15, 20 + 15 + 7) = 42
return 20 + max(15,7) = 35
```

#### Node 9

```
res = max(42, 9) = 42
return 9
```

#### Node -10 (root)

```
leftMax = 9
rightMax = 35

res = max(42, -10 + 9 + 35) = 42
```

Final Answer:

```
42
```

---

## Why `res` Is Global

Because:

- The maximum path may exist **entirely in a subtree**
- It may not pass through the root
- Returning only one value upward would lose this information

So:

- `dfs()` handles **extendable paths**
- `res` stores **non-extendable global paths**

---

## Time & Space Complexity

```
Time  : O(n)   // each node visited once
Space : O(h)   // recursion stack (tree height)
```

---

## Common Doubts Explained

### ❓ Why not return `left + right + root`?

Because:

- A parent can only extend **one branch**
- Returning both would create a “forked path”, which is invalid

---

### ❓ Why initialize `res = root->val`?

Because:

- All values might be negative
- We must allow a single-node path as the answer

---

### ❓ Why `max(leftMax, 0)` instead of just `leftMax`?

Because:

- Path is optional
- Negative paths only reduce the sum

---

## Final Mental Model (Lock This In)

> **Tree DP often has two values:**
>
> - One for global answer
> - One for extendable result

Here:

- `res` → global maximum path
- `dfs()` return → best single-branch path

---

## Summary

- This is **postorder Tree DP**
- Each node decides:

  - Best path THROUGH itself
  - Best path TO parent

- Negative paths are ignored
- Global maximum is tracked separately
