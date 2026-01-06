# Binary Tree Right Side View (C++)

## Problem

Given the root of a binary tree, imagine yourself standing on the **right side** of it.
Return the values of the nodes you can see **from top to bottom**.

👉 **Exactly one node per level** (the rightmost visible one).

---

## Key Observation (Very Important)

> **Right side view = rightmost node at each level**

Does **not** mean:

- only `right` children
- ignoring left subtree

---

## Approach 1: BFS + Level Vector (Straightforward)

### Idea

- Do **level order traversal (BFS)**
- Store all nodes of a level
- Pick the **last element** of that level

### Code (Your Solution #1)

```cpp
class Solution {
    queue<TreeNode*> q;
    vector<int> res;

public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return res;

        q.push(root);

        while(!q.empty()) {
            int levelSize = q.size();
            vector<int> level;

            for (int i = 0 ; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            res.push_back(level[level.size() - 1]);
        }

        return res;
    }
};
```

### Why it Works

- BFS guarantees level-by-level processing
- Last node of a level = rightmost node

### Complexity

- **Time:** `O(N)`
- **Space:** `O(N)` (queue + level vector)

### Verdict

✅ Correct
⚠️ Slightly extra space due to `level` vector

---

## Approach 2: BFS without Level Vector (Optimized BFS)

### Idea

- Still BFS
- But instead of storing the whole level
- Directly pick the node when `i == levelSize - 1`

### Code (Your Solution #2)

```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) return res;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int lvl = q.size();

            for (int i = 0; i < lvl; i++) {
                TreeNode* node = q.front();
                q.pop();

                if (i == lvl - 1) {
                    res.push_back(node->val);
                }

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return res;
    }
};
```

### Why it Works

- `lvl` fixes the **boundary of the current level**
- `i == lvl - 1` → last node of that level

### Complexity

- **Time:** `O(N)`
- **Space:** `O(N)` (queue only)

### Verdict

✅ Correct
⭐ **Best BFS solution**
⭐ Interview-preferred BFS version

---

## Approach 3: DFS (Right-first Traversal)

### Idea

- Use DFS instead of BFS
- Always go **right first**
- First node visited at a depth = visible from right

### Core DFS Rule

> If this depth is visited **for the first time**, store the node.

---

### Code (Your Solution #3 – cleaned explanation)

```cpp
class Solution {
private:
    unordered_map<int, int> mapp;
    vector<int> res;

    void view(TreeNode* root, int d) {
        if (!root) return;

        // first node at this depth
        if (mapp.find(d) == mapp.end()) {
            mapp[d] = root->val;
            res.push_back(root->val);
        }

        view(root->right, d + 1);
        view(root->left, d + 1);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return res;
        view(root, 0);
        return res;
    }
};
```

### Why it Works

- DFS goes depth-first
- Visiting **right before left** ensures:

  - Rightmost node is seen first at each level

- First node per depth = right side view

### Complexity

- **Time:** `O(N)`
- **Space:** `O(H)` recursion stack
  (`H = height of tree`)

### Verdict

✅ Correct
⚠️ `unordered_map` not strictly needed
⚠️ DFS solution is more “tricky” but elegant

---

## DFS Optimization Tip (Important)

You actually **don’t need the map**.

This is enough:

```cpp
if (res.size() == depth)
    res.push_back(root->val);
```

Because:

- First visit at that depth is the rightmost (due to right-first DFS)

---

## Comparison Summary

| Approach           | Technique | Extra Space | Clarity    | Interview |
| ------------------ | --------- | ----------- | ---------- | --------- |
| BFS + level vector | BFS       | High        | Very clear | ✅        |
| BFS (i == last)    | BFS       | Medium      | ⭐⭐⭐⭐   | ⭐⭐⭐⭐  |
| DFS right-first    | DFS       | Low         | Tricky     | ⭐⭐⭐    |
