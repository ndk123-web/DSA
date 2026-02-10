# 🔗 Number of Connected Components in an Undirected Graph

## Problem Summary

You are given:

- `n` nodes labeled `0` to `n-1`
- An undirected edge list `edges`

Each edge `[u, v]` means there is a connection between `u` and `v`.

### Task

Return the **number of connected components** in the graph.

---

## Key Definition (very important)

A **connected component** is a group of nodes such that:

- Every node in the group can reach every other node in the group
- There is **no path** to nodes outside the group

Isolated nodes count as **their own components**.

---

## Example

```
n = 4
edges = [[2,3],[1,2],[1,3]]
```

Graph:

```
0        1
         | \
         2--3
```

Components:

```
{0}, {1,2,3}
```

Answer: **2**

---

# 🟦 Solution 1: DFS (Graph Traversal)

### Core Idea

> **Each DFS call from an unvisited node discovers exactly one connected component.**

### Rule

- If a node is unvisited → start DFS → increment component count
- DFS marks the entire component as visited

---

### Algorithm

1. Build adjacency list (undirected)
2. Maintain `visited[]`
3. Loop over all nodes:
   - If node is unvisited:
     - `components++`
     - Run DFS from that node

---

### Code (DFS)

```cpp
class Solution {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    void dfs(int node) {
        visited[node] = true;
        for (int nei : adj[node]) {
            if (!visited[nei]) {
                dfs(nei);
            }
        }
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        adj.assign(n, {});
        visited.assign(n, false);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                components++;
                dfs(i);
            }
        }
        return components;
    }
};
```

---

### Dry Run (DFS)

```
nodes = 0,1,2,3
edges = [[2,3],[1,2],[1,3]]
```

- Start DFS at `0` → component #1 → `{0}`
- Next unvisited: `1` → component #2 → `{1,2,3}`
- All nodes visited

Answer = **2**

---

### Complexity

- **Time:** `O(n + edges)`
- **Space:** `O(n + edges)`

---

### When to Use

- Simple
- Easy to explain
- Works well when recursion depth is safe

---

# 🟩 Solution 2: DSU (Union-Find) + Sort + Prev

### Core Idea

1. Use DSU to build parent relationships
2. Normalize all nodes to their **final root**
3. Count distinct roots

---

### Why Normalization is Needed

In DSU:

- `parent[i]` is **not guaranteed** to be the final root
- You must call `find(i)` to know which component `i` belongs to

---

### Algorithm

1. Initialize `parent[i] = i`
2. Union all edges
3. For each node: `parent[i] = find(i)`
4. Sort `parent`
5. Count distinct values

---

### Code (DSU + sort)

```cpp
class Solution {
private:
    vector<int> parent;

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;

        for (auto& e : edges) {
            int p1 = find(e[0]);
            int p2 = find(e[1]);
            if (p1 != p2) {
                parent[p2] = p1;
            }
        }

        // normalize parents
        for (int i = 0; i < n; i++)
            parent[i] = find(i);

        sort(parent.begin(), parent.end());

        int components = 1;
        for (int i = 1; i < n; i++) {
            if (parent[i] != parent[i - 1])
                components++;
        }

        return components;
    }
};
```

---

### Dry Run Insight

Before normalization:

```
parents = [0,1,1,2]
```

After `parent[i] = find(i)`:

```
parents = [0,1,1,1]
```

Distinct roots → `{0,1}` → **2 components**

---

### Complexity

- **Time:** `O(n log n)`
- **Space:** `O(n)`

---

### When to Use

- When you already used DSU
- When component IDs are needed later
- Slightly more code, slightly more error-prone

---

# 🟥 Solution 3: DSU with `components--` (Canonical & Best)

### Core Idea (Most Important DSU Insight)

> Initially, every node is its own component
> Every **successful union** reduces the component count by **1**

---

### Algorithm

1. Initialize `components = n`
2. For each edge:
   - If roots are different:
     - Union them
     - `components--`

3. Return `components`

No sorting.
No normalization loop.

---

### Code (Best DSU Version)

```cpp
class Solution {
private:
    vector<int> parent;

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;

        int components = n;

        for (auto& e : edges) {
            int p1 = find(e[0]);
            int p2 = find(e[1]);
            if (p1 != p2) {
                parent[p2] = p1;
                components--;
            }
        }

        return components;
    }
};
```

---

### Dry Run (Canonical DSU)

```
n = 4
components = 4
```

- union(2,3) → components = 3
- union(1,2) → components = 2
- union(1,3) → same root → ignore

Final answer = **2**

---

### Complexity

- **Time:** `O(n + edges * α(n))`
- **Space:** `O(n)`

(α = inverse Ackermann, effectively constant)

---

### When to Use

- **Best interview answer**
- Cleanest logic
- Least bug-prone
- Scales well

---

# 🔍 Final Comparison

| Approach         | Key Idea           | Time       | Space  | Notes               |
| ---------------- | ------------------ | ---------- | ------ | ------------------- |
| DFS              | Count DFS starts   | O(n+e)     | O(n+e) | Simple & intuitive  |
| DSU + Sort       | Count unique roots | O(n log n) | O(n)   | Needs normalization |
| DSU components-- | Count merges       | O(n+e)     | O(n)   | **Best solution**   |
