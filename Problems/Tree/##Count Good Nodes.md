# Count Good Nodes in Binary Tree (C++)

## Problem Statement

You are given the root of a binary tree.

A node **X** is called a **good node** if on the path from the root to X,
there is **no node with a value greater than X**.

Return the total number of good nodes in the tree.

---

## Key Definition (Must Be Clear)

> A node is **good** if
> `node->val >= maximum value seen on the path from root to that node`

Root is **always a good node**.

---

## Example

```
        3
       / \
      1   4
         / \
        1   5
```

Good nodes:

- `3` (root)
- `4` (>= 3)
- `5` (>= 4)

Answer: **3**

---

# Approach 1 — Store Path & Recompute Max

### Idea

- Maintain a `path` vector containing values from root to current node
- At each node:

  - Find max value in `path`
  - Compare it with current node

- Backtrack after recursion

### Code

```cpp
class Solution {
private:
    int count;

    void good(TreeNode* root, vector<int>& path) {
        if (!root) return;

        int max_val = path.empty()
                        ? root->val
                        : *max_element(path.begin(), path.end());

        if (max_val <= root->val)
            count++;

        path.push_back(root->val);

        good(root->left, path);
        good(root->right, path);

        path.pop_back();
    }

public:
    int goodNodes(TreeNode* root) {
        vector<int> path;
        good(root, path);
        return count;
    }
};
```

---

### How It Works

- `path` represents root → current node
- `max_element()` finds max so far
- Backtracking ensures correct path for each branch

---

### Dry Run

Path: `3 → 4 → 5`

- At `3`: path empty → good
- At `4`: max(path)=3 → 4 ≥ 3 → good
- At `5`: max(path)=4 → 5 ≥ 4 → good

---

### Time Complexity

```
O(N²)   (worst case)
```

Because:

- For each node, `max_element()` takes `O(H)`
- In skewed tree, `H ≈ N`

---

### Space Complexity

```
O(H)
```

- Path vector
- Recursion stack

---

### Verdict

✅ Correct
❌ Inefficient
❌ Recomputes max repeatedly

---

# Approach 2 — Carry Maximum So Far (Optimal)

### Idea

- Instead of storing entire path
- Carry **maximum value seen so far** as a parameter
- Update it when a good node is found

This is the **intended solution**.

---

### Code

```cpp
class Solution {
private:
    int count;

    void good(TreeNode* root, int max_till_now) {
        if (!root) return;

        if (root->val >= max_till_now) {
            count++;
            max_till_now = root->val;
        }

        good(root->left, max_till_now);
        good(root->right, max_till_now);
    }

public:
    int goodNodes(TreeNode* root) {
        good(root, root->val);
        return count;
    }
};
```

---

### How It Works

- `max_till_now` always holds the max value from root to parent
- No extra data structure
- Each node processed once

---

### Dry Run (Same Tree)

```
Call good(3, 3) → good
Call good(4, 3) → good → max = 4
Call good(5, 4) → good → max = 5
```

---

### Time Complexity

```
O(N)
```

Each node visited once.

---

### Space Complexity

```
O(H)
```

Only recursion stack.

---

### Verdict

✅ Correct
✅ Optimal
✅ Interview-preferred
✅ Clean logic

---

# Comparison Summary

| Aspect           | Approach 1 | Approach 2 |
| ---------------- | ---------- | ---------- |
| Uses path vector | Yes        | No         |
| Recomputes max   | Yes        | No         |
| Time complexity  | O(N²)      | **O(N)**   |
| Space            | O(H)       | O(H)       |
| Interview ready  | ❌         | ✅         |
