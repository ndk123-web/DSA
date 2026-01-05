# Binary Tree Level Order Traversal (C++)

## Problem

Given the root of a binary tree, return the **level order traversal** of its nodes’ values
(i.e., level by level, from left to right).

---

## What “Level Order” Means

Traversal happens **level by level**:

```
        1
       / \
      2   3
         /
        4
```

Output:

```
[[1], [2,3], [4]]
```

---

## Approach 1: BFS (Breadth First Search) — **Natural Solution**

### Core Idea

> Visit nodes **level by level** using a **queue**.

Queue ensures:

- FIFO order
- All nodes of a level are processed before moving deeper

---

### BFS Code (Your Solution)

```cpp
class Solution {
private:
    vector<vector<int>> res;

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            res.push_back(level);
        }

        return res;
    }
};
```

---

### BFS Logic Breakdown

1. Push root into queue
2. While queue is not empty:

   - Take queue size → number of nodes at current level
   - Pop exactly that many nodes
   - Push their children

3. Store each level separately

---

### BFS Dry Run

Tree:

```
        1
       / \
      2   3
         /
        4
```

Steps:

- Queue: `[1]` → level `[1]`
- Queue: `[2,3]` → level `[2,3]`
- Queue: `[4]` → level `[4]`

Final result:

```
[[1], [2,3], [4]]
```

---

## Approach 2: DFS (Depth First Search) — **Controlled Trick**

### Core Idea

> Use DFS but **track depth**, and create a new level only when first visiting that depth.

This is **not natural BFS**, but works correctly with discipline.

---

### DFS Code (Your Earlier Solution)

```cpp
class Solution {
private:
    vector<vector<int>> res;

    void dfs(TreeNode* root, int depth) {
        if (!root) return;

        if (res.size() == depth)
            res.push_back({});

        res[depth].push_back(root->val);

        dfs(root->left, depth + 1);
        dfs(root->right, depth + 1);
    }

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        res.clear();
        dfs(root, 0);
        return res;
    }
};
```

---

### DFS Logic Breakdown

- `depth` tells which level the node belongs to
- If first time reaching that depth → create a vector
- Push node value into `res[depth]`
- Continue DFS normally

---

### DFS Dry Run (Same Tree)

Paths:

- Visit `1` at depth `0`
- Visit `2` at depth `1`
- Visit `3` at depth `1`
- Visit `4` at depth `2`

Result:

```
[[1], [2,3], [4]]
```

---

## BFS vs DFS (Clear Comparison)

| Aspect               | BFS            | DFS               |
| -------------------- | -------------- | ----------------- |
| Traversal nature     | Level by level | Depth first       |
| Extra structure      | Queue          | Recursion stack   |
| Code clarity         | ⭐⭐⭐⭐       | ⭐⭐⭐            |
| Natural for problem  | ✅ Yes         | ❌ No (but works) |
| Interview preference | ⭐⭐⭐⭐       | ⭐⭐              |

---

## Time Complexity (Both)

```
O(N)
```

Every node is visited once.

---

## Space Complexity

### BFS

```
O(N)
```

Queue can hold an entire level.

### DFS

```
O(H) recursion stack + O(N) result
```

`H` = height of tree.

---

## When to Use What

### Use BFS when:

- Level order traversal
- Shortest path
- Nearest node problems

### Use DFS when:

- Tree depth/height
- Path-based logic
- Subtree problems

---

## One-Line Memory Rule

> **Level order = BFS by default**
> DFS only when depth control is intentional.
