# Invert Binary Tree (C++)

## Problem

Given the root of a binary tree, **invert the tree** and return its root.

**Invert means:**

- Swap left and right child **for every node**

---

## Core Idea (One Line)

> For every node:
> **swap(left, right)** → then do the same for its children

---

## Your Original Code (Correct)

```cpp
class Solution {
private:
    void invert(TreeNode* node) {
        if (!node) return;

        swap(node->left, node->right);
        invert(node->left);
        invert(node->right);
    }

public:
    TreeNode* invertTree(TreeNode* root) {
        invert(root);
        return root;
    }
};
```

---

## Your Doubt (Very Common, Very Valid)

> **“node->left and node->right nullptr hoga tab bhi swap hoga?
> Ye unnecessary nahi hai?”**

### Short Answer

❌ **No issue.
❌ Not unnecessary.
❌ Extra condition is NOT required.**

Let’s break it properly.

---

## What Happens When Both Are `nullptr`?

```cpp
swap(node->left, node->right);
```

Case:

```
node->left  = nullptr
node->right = nullptr
```

After swap:

```
node->left  = nullptr
node->right = nullptr
```

### Reality:

- **Nothing changes**
- **No crash**
- **O(1) operation**
- Completely safe

---

## Why Extra Condition Is Not Needed

Your second version:

```cpp
if (!node || (!node->left && !node->right))
    return;
```

### This condition means:

> “If this is a leaf node, don’t process it”

But look carefully:

### A leaf node:

```
left = nullptr
right = nullptr
```

Swapping does nothing.
Recursive calls immediately return.

So this condition:

- ❌ Does NOT improve correctness
- ❌ Does NOT improve complexity
- ❌ Adds unnecessary branching
- ❌ Makes code less clean

---

## Important Rule (DSA Discipline)

> **Base condition should stop recursion, not micro-optimize logic**

Correct base condition:

```cpp
if (!node) return;
```

That’s it.

---

## Dry Run

### Input Tree

```
      4
     / \
    2   7
   / \ / \
  1  3 6  9
```

---

### Step-by-Step

1. At node `4`

   - swap → `7` and `2`

2. Go left (`7`)

   - swap → `9` and `6`

3. Go right (`2`)

   - swap → `3` and `1`

4. Leaf nodes:

   - swap nullptr, nullptr → no effect

---

### Output Tree

```
      4
     / \
    7   2
   / \ / \
  9  6 3  1
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
O(H)
```

- Recursive call stack
- Worst case (skewed tree): `O(N)`
- Balanced tree: `O(log N)`

---

## Final Verdict (Straight Talk)

| Version           | Status       |
| ----------------- | ------------ |
| Only `if (!node)` | ✅ Best      |
| Extra leaf check  | ❌ Redundant |
| Swap on nullptr   | ✅ Safe      |

---

## Golden Rule (Lock This In)

> **Swapping two null pointers is harmless**
> Don’t overthink safe operations
