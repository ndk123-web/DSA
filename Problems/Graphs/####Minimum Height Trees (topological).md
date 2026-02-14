# 🌳 Minimum Height Trees

---

# 🔵 Solution 1 — DFS Brute Force

## # Intuition

Height of a rooted tree = longest distance from root to any leaf.

So brute force idea is simple:

- For each node:
  - Treat it as root.
  - Run DFS.
  - Compute height.

- Pick node(s) with minimum height.

This works but is inefficient.

---

## # Approach

1. Build adjacency list.
2. For each node:
   - Run DFS avoiding parent.
   - Compute maximum depth.

3. Track minimum height.
4. Return nodes whose height equals minimum.

---

## # Complexity

Let `n` be number of nodes.

- DFS per node → O(n)
- Total → O(n²)

❌ Will TLE for large n.

---

## # Code (DFS Brute Force)

```cpp
class Solution {
private:
    vector<vector<int>> adj;

    int dfs(int node, int parent) {
        int maxDepth = 0;

        for (int nei : adj[node]) {
            if (nei == parent) continue;

            int depth = dfs(nei, node);
            maxDepth = max(maxDepth, depth);
        }

        return maxDepth + 1; // count nodes
    }

public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};

        adj.assign(n, {});

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> result;
        int minHeight = INT_MAX;

        for (int i = 0; i < n; i++) {
            int height = dfs(i, -1) - 1; // convert to edges
            minHeight = min(minHeight, height);
        }

        for (int i = 0; i < n; i++) {
            int height = dfs(i, -1) - 1;
            if (height == minHeight)
                result.push_back(i);
        }

        return result;
    }
};
```

---

# 🟢 Solution 2 — Topological BFS (Leaf Trimming) — Optimized

## # Intuition

Minimum Height Trees are always rooted at the **center(s)** of the tree.

Instead of checking every node:

We remove leaves layer by layer.

Why?

Because leaves are the outermost nodes.
Removing them shrinks the tree inward.

Eventually only 1 or 2 nodes remain.
Those are the centers.

---

## # Why Remaining > 2?

A tree can have at most 2 centers.

So we stop trimming when remaining nodes ≤ 2.

---

## # Approach

1. Build adjacency list.
2. Compute degree of each node.
3. Add all leaves (degree == 1) to queue.
4. While remaining > 2:
   - Remove current leaves.
   - Reduce neighbors’ degree.
   - Push new leaves.

5. Remaining nodes are answer.

---

## # Complexity

Each node removed once.
Each edge processed once.

Time Complexity:
[
O(n)
]

Space Complexity:
[
O(n)
]

---

## # Code (Optimized BFS)

```cpp
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};

        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            degree[e[0]]++;
            degree[e[1]]++;
        }

        queue<int> q;

        for (int i = 0; i < n; i++) {
            if (degree[i] == 1)
                q.push(i);
        }

        int remaining = n;

        while (remaining > 2) {
            int size = q.size();
            remaining -= size;

            for (int i = 0; i < size; i++) {
                int leaf = q.front();
                q.pop();

                for (int nei : adj[leaf]) {
                    degree[nei]--;
                    if (degree[nei] == 1)
                        q.push(nei);
                }
            }
        }

        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front());
            q.pop();
        }

        return result;
    }
};
```

---

# 🔥 Final Comparison

| Approach        | Idea                        | Complexity |
| --------------- | --------------------------- | ---------- |
| DFS brute force | Try every node as root      | O(n²)      |
| Topological BFS | Trim leaves to reach center | O(n)       |

---

# 🎯 Final Insight

Minimum Height Trees are not about calculating height repeatedly.

They are about finding the geometric center of the tree.

Leaf trimming reveals that center efficiently.
