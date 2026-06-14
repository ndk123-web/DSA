# 3559. Number of Ways to Assign Edge Weights II

## Intuition

For every query `(u, v)`, we only care about the path between the two nodes.

Each edge on the path can be assigned:

```text
Weight = 1 or 2
```

If the path contains `d` edges, then:

```text
Total assignments = 2^d
```

We need the number of assignments whose total sum is **odd**.

---

## Key Observation

For any set of edges:

```text
Exactly half of the assignments produce an odd sum
Exactly half produce an even sum
```

Therefore:

```text
Odd assignments = 2^(d - 1)
```

where:

```text
d = number of edges in the path
```

The only exception is:

```text
d = 0
```

which happens when:

```text
u == v
```

In this case:

```text
Path sum = 0 (even)
Answer = 0
```

Thus, the problem reduces to:

```text
1. Find distance(u, v)
2. Answer = 2^(distance - 1)
```

---

# Distance Between Two Nodes

The distance between two nodes in a tree can be computed using the Lowest Common Ancestor (LCA).

Formula:

```text
distance(u, v)
=
depth[u]
+
depth[v]
-
2 × depth[LCA(u,v)]
```

---

## Why does this formula work?

Suppose:

```text
          1
        /   \
       2     3
      /       \
     6         7
```

Depths:

```text
depth[1] = 0
depth[2] = 1
depth[3] = 1
depth[6] = 2
depth[7] = 2
```

For:

```text
u = 6
v = 7
```

The LCA is:

```text
LCA(6,7) = 1
```

Distance:

```text
2 + 2 - 2 × 0 = 4
```

Actual path:

```text
6 -> 2 -> 1 -> 3 -> 7
```

which indeed contains:

```text
4 edges
```

---

# Binary Lifting

To answer LCA queries efficiently, we use Binary Lifting.

Define:

```cpp
dp[node][j]
```

as:

```text
The 2^j-th ancestor of node
```

Examples:

```text
dp[node][0] -> 1 ancestor above
dp[node][1] -> 2 ancestors above
dp[node][2] -> 4 ancestors above
dp[node][3] -> 8 ancestors above
```

---

## Building the DP Table

The first ancestor is simply the parent:

```cpp
dp[node][0] = parent
```

For larger jumps:

```text
2^j = 2^(j-1) + 2^(j-1)
```

Therefore:

```cpp
dp[node][j]
=
dp[
      dp[node][j-1]
   ][j-1]
```

Meaning:

1. Move up `2^(j-1)` ancestors.
2. From there move another `2^(j-1)` ancestors.

Total:

```text
2^j ancestors
```

---

# Lifting a Node

Suppose we want to move a node upward by `k` ancestors.

Example:

```text
k = 13
```

Binary representation:

```text
13 = 1101₂
```

which means:

```text
13 = 8 + 4 + 1
```

Instead of moving 13 times:

```text
parent
parent
parent
...
13 times
```

we jump:

```text
8 ancestors
4 ancestors
1 ancestor
```

This is done by checking each bit of `k`.

---

# LCA Algorithm

For two nodes:

```text
u and v
```

1. Make both nodes have the same depth.
2. Lift both nodes upward together from the largest jump to the smallest jump.
3. Stop when they become immediate children of the LCA.
4. Return their parent.

Why do we iterate from:

```cpp
LOG - 1 → 0
```

Because we greedily take the largest possible jump without crossing the LCA.

---

# Algorithm

1. Build the tree.
2. Run DFS to compute:

   * depth of every node
   * immediate parent (`dp[node][0]`)
3. Build Binary Lifting table.
4. For every query:

   * Find LCA.
   * Compute distance.
   * Return `2^(distance-1)`.

---

# Code

```cpp
class Solution {
public:
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> depth;
    int LOG;
    const int MOD = 1e9 + 7;

    void dfs(int u, int parent) {
        dp[u][0] = parent;

        for (int& v : adj[u]) {

            if (v == parent)
                continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    long long logPow(long long base, long long exp) {
        long long res = 1;

        while (exp > 0) {

            if (exp & 1)
                res = (res * base) % MOD;

            base = (base * base) % MOD;
            exp >>= 1;
        }

        return res;
    }

    // Move node upward by k ancestors
    int liftNode(int node, int k) {

        for (int j = 0; j < LOG; j++) {

            if (k & (1LL << j)) {

                node = dp[node][j];

                if (node == -1)
                    return -1;
            }
        }

        return node;
    }

    int LCA(int u, int v) {

        // Make u deeper
        if (depth[u] < depth[v])
            swap(u, v);

        // Bring u to same depth as v
        int diff = depth[u] - depth[v];
        u = liftNode(u, diff);

        if (u == v)
            return u;

        // Lift both together
        for (int j = LOG - 1; j >= 0; j--) {

            if (dp[u][j] != dp[v][j]) {

                u = dp[u][j];
                v = dp[v][j];
            }
        }

        // Parent of both is LCA
        return dp[u][0];
    }

    vector<int> assignEdgeWeights(vector<vector<int>>& edges,
                                  vector<vector<int>>& queries) {

        int n = edges.size() + 1;
        LOG = ceil(log2(n)) + 1;

        depth.resize(n + 1, 0);
        dp.resize(n + 1, vector<int>(LOG, -1));
        adj.resize(n + 1);

        // Build graph
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Root tree at node 1
        dfs(1, -1);

        // Build binary lifting table
        for (int j = 1; j < LOG; j++) {

            for (int node = 1; node <= n; node++) {

                if (dp[node][j - 1] != -1) {

                    dp[node][j] =
                        dp[ dp[node][j - 1] ][j - 1];
                }
            }
        }

        vector<int> res;

        for (auto& query : queries) {

            int u = query[0];
            int v = query[1];

            int lca = LCA(u, v);

            int dist =
                depth[u]
                + depth[v]
                - 2 * depth[lca];

            if (dist == 0)
                res.push_back(0);
            else
                res.push_back(logPow(2, dist - 1));
        }

        return res;
    }
};
```

# Complexity Analysis

### DFS

```text
O(N)
```

### Build Binary Lifting Table

```text
O(N log N)
```

### Each Query

* LCA:

```text
O(log N)
```

* Fast Power:

```text
O(log N)
```

Total per query:

```text
O(log N)
```

---

# Complexity

| Operation  | Complexity       |
| ---------- | ---------------- |
| DFS        | O(N)             |
| Build DP   | O(N log N)       |
| Each Query | O(log N)         |
| Total      | O((N + Q) log N) |
| Space      | O(N log N)       |

---

### Key Insight

The problem initially looks like an edge-weight assignment problem, but after observing that exactly half of all assignments have odd sum, it transforms into:

```text
Tree Distance Problem
        +
Binary Lifting
        +
LCA
```

Once the distance between two nodes is known, the answer follows directly from combinatorics.
