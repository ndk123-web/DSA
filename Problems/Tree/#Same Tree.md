# Same Tree

## Problem

Given the roots of two binary trees `p` and `q`, determine if they are **structurally identical** and have the **same node values**.

Two trees are the same if:

1. Both are empty, or
2. Roots have the same value **and**
3. Left subtrees are the same **and**
4. Right subtrees are the same

---

## Core Idea (One Line)

> Compare both trees **node by node** using recursion.

---

## Code (Your Solution – Correct)

```cpp
class Solution {
private:
    bool same(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;

        if (!p || !q)
            return false;

        if (p->val != q->val)
            return false;

        return same(p->left, q->left) && same(p->right, q->right);
    }

public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return same(p, q);
    }
};
```

---

## Why This Works (Straight Logic)

At every step, we check **three things**:

1. **Both null?**
   → Trees match at this position.

2. **One null, one not?**
   → Structure mismatch → return `false`.

3. **Values different?**
   → Data mismatch → return `false`.

Only if all above pass:

- Recursively compare **left subtrees**
- Recursively compare **right subtrees**

---

## Dry Run (Step-by-Step)

### Example 1: Same Trees

```
Tree p:        Tree q:
     1              1
    / \            / \
   2   3          2   3
```

### Calls

```
same(1,1)
 ├─ same(2,2)
 │   ├─ same(null,null) → true
 │   └─ same(null,null) → true
 └─ same(3,3)
     ├─ same(null,null) → true
     └─ same(null,null) → true
```

### Final Result

```
true
```

---

### Example 2: Different Structure

```
Tree p:        Tree q:
     1              1
    /                \
   2                  2
```

### Key Call

```
same(2, null) → false
```

### Final Result

```
false
```

---

### Example 3: Same Structure, Different Values

```
Tree p:        Tree q:
     1              1
    / \            / \
   2   3          2   4
```

### Key Check

```
p->val != q->val  (3 != 4)
```

### Final Result

```
false
```

---

## Time Complexity

```
O(N)
```

- Each node is visited **once**
- `N` = number of nodes in the smaller tree
- Stops early if mismatch found

---

## Space Complexity (Recursion Stack)

```
O(H)
```

Where `H` = height of the tree

| Tree Type     | Space      |
| ------------- | ---------- |
| Skewed tree   | `O(N)`     |
| Balanced tree | `O(log N)` |

⚠️ No extra data structures used.

---

## Important Notes (Interview Level)

- This is **DFS (Depth First Search)**
- Both structure **and** value must match
- Order of checks matters:

  - Null checks first
  - Value check after confirming nodes exist

---

## Common Mistakes (Avoid These)

❌ Checking values before null check
❌ Comparing only inorder traversals
❌ Ignoring structure, checking values only

---

## Key Concept Summary

| Concept          | Meaning                  |
| ---------------- | ------------------------ |
| DFS              | Recursive tree traversal |
| Base case        | Both null → true         |
| Structural check | One null → false         |
| Value check      | Values must match        |

---

## One-Line Memory Rule

> **Same Tree = Same structure + Same values**
