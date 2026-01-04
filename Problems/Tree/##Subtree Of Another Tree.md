# Subtree of Another Tree (C++)

## Problem

Given two binary trees `root` and `subRoot`, determine whether `subRoot` is a **subtree** of `root`.

A subtree means:

- There exists **some node** in `root`
- Such that the subtree rooted at that node is **exactly identical** to `subRoot`
- Both **structure and values** must match

---

## Core Idea (One Line)

> Try every node in `root` as a possible subtree root and compare trees using DFS.

---

## Code (Correct & Standard)

```cpp
class Solution {
private:
    bool same(TreeNode* a, TreeNode* b) {
        if (!a && !b)
            return true;
        if (!a || !b)
            return false;

        if (a->val != b->val)
            return false;

        return same(a->left, b->left) &&
               same(a->right, b->right);
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root)
            return false;

        if (same(root, subRoot))
            return true;

        return isSubtree(root->left, subRoot) ||
               isSubtree(root->right, subRoot);
    }
};
```

---

## Why This Works (Straight Logic)

There are **two recursive layers**, each with a clear responsibility.

### 1️⃣ `same(a, b)`

Checks whether **two trees are identical**:

- Both null → same
- One null → not same
- Values differ → not same
- Otherwise → check left and right

### 2️⃣ `isSubtree(root, subRoot)`

- At each node in `root`, ask:

  > “Can `subRoot` start here?”

- If yes → return `true`
- Otherwise → try left and right subtrees

---

## Dry Run (Step-by-Step)

### Example

```
root:
       3
      / \
     4   5
    / \
   1   2

subRoot:
     4
    / \
   1   2
```

---

### Execution Flow

1. `isSubtree(3, 4)`

   - `same(3,4)` → ❌
   - Check left & right

2. `isSubtree(4, 4)`

   - `same(4,4)` → ✅

     - `same(1,1)` → ✅
     - `same(2,2)` → ✅

3. Return `true`

---

### Final Answer

```
true
```

---

## Edge Case (Duplicate Values)

```
root:      subRoot:
   1          1
  /
 1
```

- First `1` fails structure match
- Second `1` succeeds
- Algorithm correctly finds it

✅ This is why we **don’t stop at first value match**

---

## Time Complexity

```
O(N × M)
```

Where:

- `N` = number of nodes in `root`
- `M` = number of nodes in `subRoot`

Worst case:

- Every node in `root` is compared with `subRoot`

---

## Space Complexity

```
O(H)
```

- Recursion stack depth
- `H` = height of `root`

| Tree Type | Space      |
| --------- | ---------- |
| Skewed    | `O(N)`     |
| Balanced  | `O(log N)` |

---

## Important Observations

- This is **DFS**
- Early exit when match is found
- No extra data structures used
- Handles:

  - Duplicate values
  - Partial matches
  - Deep trees

---

## Common Mistakes (Avoid These)

❌ Matching only values
❌ Picking first matching node and stopping
❌ Comparing inorder traversals only
❌ Ignoring structure

---

## One-Line Memory Rule

> **Subtree = Same tree starting at some node**
