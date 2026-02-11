# 684. Redundant Connection

## 🧠 Intuition

Given graph started as a **tree** (connected, no cycles).
Then one extra edge was added.

Tree property:

- `n` nodes
- `n - 1` edges
- No cycle

Now edges count = `n`
⇒ Exactly **one cycle must exist**

So problem becomes:

> Find the edge which creates the cycle.

If multiple answers possible, return the one that appears **last in input**.

---

# ✅ Approach 1: Union-Find (Disjoint Set Union) — Recommended

## 🔍 Core Idea

Union-Find maintains connected components.

For each edge `[u, v]`:

- If `u` and `v` already have same parent →
  Adding this edge creates a **cycle**
  ⇒ This is the redundant edge.

Otherwise:

- Union them.

---

## ⚙️ Why It Works

In a tree:

- No two nodes already share the same root unless connected.
- If they do share the same root before adding edge → cycle detected.

---

## ⏱ Complexity

- **Time:** `O(N α(N))` (almost linear)
- **Space:** `O(N)`

---

## 💻 Code (Union-Find)

```cpp
class Solution {
private:
    vector<int> parents;
    vector<int> res;

    int find(int node) {
        if (node == parents[node]) {
            return node;
        }
        return find(parents[node]);
    }

    bool unionEdge(vector<int> edge) {
        int u = edge[0], v = edge[1];
        int pu = find(u);
        int pv = find(v);

        if (pu == pv) {
            res.push_back(u);
            res.push_back(v);
            return true; // cycle found
        }

        parents[pv] = pu;
        return false;
    }

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        parents.assign(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            parents[i] = i;
        }

        for (vector<int>& edge : edges) {
            if (unionEdge(edge)) {
                return res;
            }
        }

        return res;
    }
};
```

---

# ✅ Approach 2: DFS (Cycle Detection in Undirected Graph)

## 🔍 Core Idea

We build graph incrementally.

For each edge:

1. Add edge to adjacency list
2. Run DFS to check if a cycle exists
3. If cycle detected → return current edge

---

## ⚙️ Why It Works

In an undirected graph:

If during DFS:

- We visit a node that is already visited
- And it is **not the parent**

⇒ A cycle exists.

---

## ⏱ Complexity

- **Time:** `O(N²)` (worst case, because DFS for every edge)
- **Space:** `O(N)`

Less efficient than Union-Find.

---

## 💻 Code (DFS Method)

```cpp
class Solution {
private:
    vector<vector<int>> adj;
    vector<int> visit;

    bool dfs(int node, int parent) {
        visit[node] = true;

        for (int& nei : adj[node]) {
            if (!visit[nei]) {
                if (dfs(nei, node)) {
                    return true;
                }
            } else if (nei != parent) {
                return true; // cycle detected
            }
        }

        return false;
    }

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        adj.assign(n + 1, {});

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);

            visit.assign(n + 1, false);

            if (dfs(u, -1)) {
                return edge;
            }
        }

        return {};
    }
};
```

---

# 🔥 DFS vs Union-Find

| Method     | Time  | Cleanliness | Interview Preference |
| ---------- | ----- | ----------- | -------------------- |
| DFS        | O(N²) | Simple idea | Medium               |
| Union-Find | ~O(N) | Optimal     | High                 |

---

# 🧠 Final Takeaway

- A tree + one extra edge ⇒ exactly one cycle
- Detect cycle
- First edge that connects two already connected nodes ⇒ redundant edge
- **Union-Find is the cleanest and most optimal approach**

---

## 🎯 Interview One-Liner

> Since the graph was initially a tree, adding one extra edge must create exactly one cycle.
> Using Union-Find, we detect the first edge whose endpoints already belong to the same component.
