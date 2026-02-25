# 🔗 Min Cost to Connect Points

## 🧠 Problem Summary

You are given `n` points in 2D space.

The cost to connect two points is the **Manhattan Distance**:

[
|x1 - x2| + |y1 - y2|
]

You must connect all points such that:

- There is exactly **one path** between any two points
- Total cost is **minimum**

This is a classic **Minimum Spanning Tree (MST)** problem.

The graph is:

- Complete
- Weighted
- Undirected

Nodes = indices of points
Edges = Manhattan distance between every pair

---

# ✅ Solution 1 — Prim’s Algorithm (Min Heap)

### 🔹 Idea

Grow a tree from any starting node.

At every step:

- Pick the minimum edge connecting the current tree to an unvisited node.

Use a **min-heap** to always extract the smallest edge.

### 🔹 Time Complexity

- O(n² log n)
- Heap can contain up to O(n²) entries

### 🔹 Space Complexity

- O(n²) (heap in worst case)

---

### 💻 Code

```cpp
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> visited(n, false);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;

        minHeap.push({0, 0});  // {cost, node}
        int totalCost = 0;
        int edgesUsed = 0;

        while (edgesUsed < n) {
            auto [cost, node] = minHeap.top();
            minHeap.pop();

            if (visited[node]) continue;

            visited[node] = true;
            totalCost += cost;
            edgesUsed++;

            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    int dist = abs(points[node][0] - points[i][0]) +
                               abs(points[node][1] - points[i][1]);
                    minHeap.push({dist, i});
                }
            }
        }

        return totalCost;
    }
};
```

---

# ✅ Solution 2 — Kruskal’s Algorithm (DSU)

### 🔹 Idea

1. Generate all possible edges
2. Sort by weight
3. Pick smallest edges that don’t form cycles
4. Stop after selecting n-1 edges

Use **DSU (Disjoint Set Union)** to detect cycles.

### 🔹 Time Complexity

- Edge generation → O(n²)
- Sorting → O(n² log n)
- DSU operations → nearly O(1)

Overall → O(n² log n)

### 🔹 Space Complexity

- O(n²) for edges

---

### 💻 Code

```cpp
class Solution {
private:
    vector<int> parent;

    int find(int node) {
        if (parent[node] != node)
            parent[node] = find(parent[node]);  // path compression
        return parent[node];
    }

    bool unionNode(int a, int b) {
        int pa = find(a);
        int pb = find(b);

        if (pa == pb) return false;

        parent[pa] = pb;
        return true;
    }

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> edges;
        parent.resize(n);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        // generate unique edges
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dist = abs(points[i][0] - points[j][0]) +
                           abs(points[i][1] - points[j][1]);
                edges.push_back({dist, i, j});
            }
        }

        sort(edges.begin(), edges.end());

        int totalCost = 0;
        int edgesUsed = 0;

        for (auto &e : edges) {
            if (unionNode(e[1], e[2])) {
                totalCost += e[0];
                edgesUsed++;
                if (edgesUsed == n - 1) break;
            }
        }

        return totalCost;
    }
};
```

---

# ✅ Solution 3 — Prim’s Algorithm (Optimized, No Heap)

### 🔹 Idea

Since graph is dense (complete graph),
we don’t need a heap.

Maintain:

- `minDist[i]` → minimum cost to connect node i to current tree
- `visited[i]`

Each step:

- Pick smallest unvisited node
- Update distances

### 🔹 Time Complexity

- O(n²)

### 🔹 Space Complexity

- O(n)

This is the most optimal for this problem.

---

### 💻 Code

```cpp
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> minDist(n, INT_MAX);
        vector<bool> visited(n, false);

        minDist[0] = 0;
        int totalCost = 0;

        for (int count = 0; count < n; count++) {

            int u = -1;

            // find smallest unvisited node
            for (int i = 0; i < n; i++) {
                if (!visited[i] && (u == -1 || minDist[i] < minDist[u])) {
                    u = i;
                }
            }

            visited[u] = true;
            totalCost += minDist[u];

            // update neighbors
            for (int v = 0; v < n; v++) {
                if (!visited[v]) {
                    int dist = abs(points[u][0] - points[v][0]) +
                               abs(points[u][1] - points[v][1]);

                    minDist[v] = min(minDist[v], dist);
                }
            }
        }

        return totalCost;
    }
};
```

---

# 🏆 Which One Should You Use?

| Approach       | Time        | Best For                    |
| -------------- | ----------- | --------------------------- |
| Prim + Heap    | O(n² log n) | Sparse graphs               |
| Kruskal + DSU  | O(n² log n) | When edges given explicitly |
| Prim (No Heap) | O(n²)       | Dense graphs (this problem) |

Since this graph is complete,
**Prim without heap is the cleanest and fastest.**
