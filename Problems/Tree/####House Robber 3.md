# 📘 House Robber III 

## 1. Problem Overview

You are given a **binary tree** where:

- Each node represents a house.
- `node->val` is the money in that house.
- If **two directly connected houses (parent–child)** are robbed on the same night, the police are alerted.

### Objective

Return the **maximum amount of money** that can be robbed **without robbing any parent and child together**.

---

## 2. Core Observation (Very Important)

This is **not** a greedy problem.

At **every node**, you must choose between **two mutually exclusive decisions**:

1. **Rob this node**

   - Then you **cannot** rob its children
   - But you **can** rob its grandchildren

2. **Skip this node**

   - Then you are free to rob its children

This decision must be made **for every node**.

---

## 3. Approach 1 — Naive DFS (Exponential Time)

### Code

```cpp
class Solution {
public:
    int rob(TreeNode* root) {
        if (!root) return 0;

        int res = root->val;

        if (root->left)
            res += rob(root->left->left) + rob(root->left->right);

        if (root->right)
            res += rob(root->right->left) + rob(root->right->right);

        return max(res, rob(root->left) + rob(root->right));
    }
};
```

---

### How This Works

At each node:

- **Case 1: Rob this node**

  - Take `root->val`
  - Skip children
  - Add grandchildren results

- **Case 2: Skip this node**

  - Take best of left subtree
  - Take best of right subtree

Return the **maximum** of both.

---

### Dry Run Example

Tree:

```
        3
       / \
      2   3
       \   \
        3   1
```

At root (3):

- Rob root → `3 + rob(3) + rob(1) = 7`
- Skip root → `rob(2) + rob(3) = 5`

Answer = `7`

---

### Problem With This Approach ❌

The **same subtree is recomputed many times**.

Example:

- `rob(node X)` is called:

  - once when parent is robbed
  - once when parent is skipped

This creates **exponential recursion**.

### Complexity

```
Time  : O(2^n)
Space : O(height)
```

Correct logic, **terrible performance**.

---

## 4. Approach 2 — DFS + Memoization (Top-Down DP)

### Code

```cpp
class Solution {
private:
    unordered_map<TreeNode*, int> cache;

    int dfs(TreeNode* root) {
        if (cache.find(root) != cache.end())
            return cache[root];

        int res = root->val;

        if (root->left)
            res += dfs(root->left->left) + dfs(root->left->right);

        if (root->right)
            res += dfs(root->right->left) + dfs(root->right->right);

        res = max(res, dfs(root->left) + dfs(root->right));
        cache[root] = res;
        return res;
    }

public:
    int rob(TreeNode* root) {
        cache[nullptr] = 0;
        return dfs(root);
    }
};
```

---

### What Changed?

We added a **cache**:

```cpp
unordered_map<TreeNode*, int> cache;
```

- **Key** → node address (`TreeNode*`)
- **Value** → best money from that subtree

---

### Why This Fixes the Problem

Before computing:

```cpp
if (cache.find(root) != cache.end())
    return cache[root];
```

This ensures:

- Each subtree is computed **once**
- All future calls return in **O(1)**

---

### Dry Run Insight

When a subtree is solved:

```
cache[node] = best_result
```

If another recursion path reaches the same node:

- No recursion
- No explosion
- Just a lookup

---

### Complexity

```
Time  : O(n)
Space : O(n)   // cache + recursion stack
```

---

### Drawback ❌

- Extra memory
- Hash map overhead
- Slightly messy logic

This leads to the **final optimized solution**.

---

## 5. Approach 3 — Tree Dynamic Programming (Best Solution)

### Code

```cpp
class Solution {
private:
    pair<int, int> dfs(TreeNode* root) {
        if (!root)
            return {0, 0};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        int withRoot = root->val + left.second + right.second;
        int withoutRoot = max(left.first, left.second)
                        + max(right.first, right.second);

        return {withRoot, withoutRoot};
    }

public:
    int rob(TreeNode* root) {
        auto res = dfs(root);
        return max(res.first, res.second);
    }
};
```

---

## 6. Key Idea of Tree DP (THIS IS THE CORE)

Each node returns **two values**:

```
first  → max money if THIS node is robbed
second → max money if THIS node is skipped
```

So the function answers:

> “What happens **if you rob me**, and what happens **if you skip me**?”

---

## 7. Transition Logic Explained

### Rob Current Node

```cpp
withRoot = root->val
         + left.second
         + right.second;
```

Why?

- Parent robbed → children **must be skipped**

---

### Skip Current Node

```cpp
withoutRoot =
    max(left.first, left.second) +
    max(right.first, right.second);
```

Why?

- Parent skipped → children can be robbed **or** skipped

---

### Return Both States

```cpp
return {withRoot, withoutRoot};
```

---

## 8. Full Dry Run

Tree:

```
        3
       / \
      2   3
       \   \
        3   1
```

### Leaf Node (3)

```
{3, 0}
```

### Node 2

```
withRoot    = 2 + 0 + 0 = 2
withoutRoot = max(0,0) + max(3,0) = 3
→ {2,3}
```

### Root

```
withRoot    = 3 + 3 + 1 = 7
withoutRoot = max(2,3) + max(3,1) = 6
```

Final Answer:

```
max(7,6) = 7
```

---

## 9. Why This Is the Best Approach ✅

- No repeated computation
- No hashmap
- Clean logic
- Pure DP
- Interview-preferred

### Complexity

```
Time  : O(n)
Space : O(height)
```

---

## 10. Final Mental Model (Lock This In)

> **Tree DP means every node returns its complete future.**

In this problem:

```
Future = {rob, skip}
```

Once you think this way:

- Tree DP problems become mechanical
- Confusion disappears
- Code becomes predictable

---

## 11. Summary Comparison

| Approach   | Idea                  | Time | Space | Verdict |
| ---------- | --------------------- | ---- | ----- | ------- |
| Naive DFS  | Try all options       | 2^n  | h     | ❌      |
| DFS + Memo | Cache subtree results | n    | n     | ✅      |
| Tree DP    | Return states         | n    | h     | ⭐ Best |
