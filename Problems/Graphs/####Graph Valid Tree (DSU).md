# Graph Valid Tree

### DFS & Union-Find (DSU) with Dry Run

---

## What is a Valid Tree?

An **undirected graph** is a valid tree **iff**:

1. **No cycle**
2. **Exactly `n - 1` edges**
3. **All nodes connected (single component)**

Break **any one** → not a tree.

---

## Fundamental Law (yaad rakhna)

> **Tree = exactly one unique path between any two nodes**

So:

- New edge creates **alternate path** → **cycle**

Both DFS and Union-Find detect **alternate paths**, bas tareeka alag hai.

---

# Approach 1: DFS (Depth First Search)

## Core DFS Idea (Undirected Graph)

Undirected graph mein edge dono taraf hoti hai.

So:

- Parent pe wapas aana → normal
- **Visited node (not parent)** → alternate path → cycle

### Golden Rule

```
visited[neighbor] == true AND neighbor != parent  → cycle
```

---

## 🧪 DFS Dry Run

### ✅ VALID TREE

```
n = 5
edges = [0-1, 0-2, 0-3, 1-4]
```

Graph:

```
    0
  / | \
 1  2  3
 |
 4
```

DFS steps:

```
0 → 1 → 4
1 → 0 (parent, ignore)
0 → 2
0 → 3
```

Observations:

- Kabhi visited + not parent nahi mila
- All nodes visited
- edges = n - 1

✅ Valid tree

---

### ❌ INVALID TREE (Cycle)

```
edges = [0-1, 1-2, 2-3, 3-0]
```

Graph:

```
0 — 1
|   |
3 — 2
```

DFS path:

```
0 → 1 → 2 → 3
```

At `3`:

- neighbor = `0`
- `visited[0] == true`
- `0 != parent (2)`

💥 Alternate path found
❌ Cycle → not a tree

---

## DFS Code (with short comments)

```cpp
class Solution {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    bool dfs(int node, int parent) {
        visited[node] = true; // mark current node

        for (int nei : adj[node]) {
            if (!visited[nei]) {
                // explore unvisited neighbor
                if (!dfs(nei, node))
                    return false;
            }
            else if (nei != parent) {
                // visited but not parent → cycle
                return false;
            }
        }
        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1)
            return false; // tree must have exactly n-1 edges

        adj.assign(n, {});
        visited.assign(n, false);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        if (!dfs(0, -1))
            return false; // cycle detected

        // connectivity check
        for (bool v : visited)
            if (!v) return false;

        return true;
    }
};
```

---

# Approach 2: Union-Find (Disjoint Set Union)

## Core Union-Find Idea

Union-Find tracks **components**.

> If two nodes are already in the **same component**
> and you add an edge → **cycle**

---

## 🧪 Union-Find Dry Run

### ✅ VALID TREE

```
edges = [0-1, 0-2, 0-3, 1-4]
```

Initial:

```
{0} {1} {2} {3} {4}
```

Step by step:

```
0-1 → {0,1}
0-2 → {0,1,2}
0-3 → {0,1,2,3}
1-4 → {0,1,2,3,4}
```

- No edge connects same component
- edges = n - 1

✅ Valid tree

---

### ❌ INVALID TREE (Cycle)

```
edges = [0-1, 1-2, 2-3, 3-0]
```

Before last edge:

```
{0,1,2,3}
```

Edge `3-0`:

- 3 and 0 already connected
- New edge creates alternate path

💥 Cycle detected
❌ Not a tree

---

## Union-Find Code (with short comments)

```cpp
class Solution {
private:
    vector<int> parent;

    int find(int node) {
        if (parent[node] == node)
            return node;          // leader found
        return find(parent[node]); // follow parent
    }

    bool unionSet(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv)
            return false; // same component → cycle

        parent[pv] = pu; // merge components
        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1)
            return false; // mandatory tree rule

        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i; // each node its own leader

        for (auto& e : edges) {
            if (!unionSet(e[0], e[1]))
                return false; // cycle found
        }
        return true;
    }
};
```

---

## DFS vs Union-Find (Short)

| DFS                         | Union-Find                |
| --------------------------- | ------------------------- |
| Path-based                  | Component-based           |
| Uses parent in recursion    | Uses parent array         |
| Explicit connectivity check | Guaranteed by `n-1` edges |
| Easier to visualize         | Cleaner code              |
