# 🔥 Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

---

# 🧠 Intuition

We are given an undirected weighted connected graph.
We need to classify edges into:

- **Critical edges** → removing them increases MST weight.
- **Pseudo-critical edges** → they can appear in _some_ MSTs but not all.

Key realization:

We don’t need to generate all MSTs.

Instead, for each edge, we perform controlled experiments:

1. Remove it and check if MST weight increases.
2. Force include it and check if MST weight remains optimal.

This is purely an application of Kruskal’s algorithm with DSU.

---

# 🚀 Approach

## Step 1 — Preprocess Edges

Store edges as:

```
(weight, u, v, originalIndex)
```

Sort them by weight.

---

## Step 2 — Compute Base MST

Run normal Kruskal to compute:

```
baseWeight
```

This is the minimum possible MST weight.

---

## Step 3 — For Each Edge i

### 🔹 Test 1 — Critical Check (Skip Edge)

Run Kruskal but skip edge `i`.

If:

- MST cannot be formed, OR
- New MST weight > baseWeight

Then edge `i` is **critical**.

Because without it, optimal MST is impossible.

---

### 🔹 Test 2 — Pseudo-Critical Check (Force Include Edge)

Force include edge `i` first:

- Add its weight
- Union its nodes
- Then run normal Kruskal

If final weight == baseWeight

Then edge `i` is **pseudo-critical**.

Because it can belong to at least one MST.

---

## Important Observations

- If an edge is critical, it cannot be pseudo-critical.
- If all edge weights are distinct, MST is unique.
  → No pseudo-critical edges exist.
- Pseudo-critical edges occur when multiple edges share equal weights.

---

# ⏱ Complexity

Let:

- n = number of nodes
- m = number of edges

For each edge, we run Kruskal once or twice.

- Time complexity:

  ```
  O(m log m + m * m * α(n))
  ```

  Which simplifies to:

  ```
  O(m²)
  ```

  (acceptable since m ≤ 200)

- Space complexity:

  ```
  O(n + m)
  ```

---

# 💻 Code

```cpp
class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py)
            return false;

        if (rank[px] > rank[py]) {
            parent[py] = px;
        } else if (rank[px] < rank[py]) {
            parent[px] = py;
        } else {
            parent[py] = px;
            rank[px]++;
        }

        return true;
    }
};

class Solution {
private:
    int buildMST(int n, vector<vector<int>>& edges, int skip, int force) {
        DSU dsu(n);
        int weight = 0;
        int edgesUsed = 0;

        if (force != -1) {
            auto &e = edges[force];
            if (dsu.unite(e[1], e[2])) {
                weight += e[0];
                edgesUsed++;
            }
        }

        for (int i = 0; i < edges.size(); i++) {
            if (i == skip) continue;
            if (i == force) continue;

            auto &e = edges[i];

            if (dsu.unite(e[1], e[2])) {
                weight += e[0];
                edgesUsed++;
            }
        }

        if (edgesUsed != n - 1)
            return INT_MAX;

        return weight;
    }

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
        int n, vector<vector<int>>& edges) {

        int m = edges.size();
        vector<vector<int>> newEdges;

        for (int i = 0; i < m; i++) {
            newEdges.push_back({edges[i][2], edges[i][0], edges[i][1], i});
        }

        sort(newEdges.begin(), newEdges.end());

        int baseWeight = buildMST(n, newEdges, -1, -1);

        vector<int> critical, pseudo;

        for (int i = 0; i < m; i++) {
            if (buildMST(n, newEdges, i, -1) > baseWeight) {
                critical.push_back(newEdges[i][3]);
            } else if (buildMST(n, newEdges, -1, i) == baseWeight) {
                pseudo.push_back(newEdges[i][3]);
            }
        }

        return {critical, pseudo};
    }
};
```
