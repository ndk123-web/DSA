# 3924. Minimum Threshold Path With Limited Heavy Edges

## Problem Link

3924. Minimum Threshold Path With Limited Heavy Edges 

## Problem Description

You are given an undirected weighted graph with $n$ nodes and a set of edges. A **threshold** value determines whether an edge is **light** (weight $\le$ threshold) or **heavy** (weight $>$ threshold). A path is valid if it contains **at most $k$ heavy edges**. Your goal is to find the **minimum integer threshold** such that a valid path exists from `source` to `target`.

---

## My Playbook Entry (The "Tell")

* 
**Pattern 1: Binary Search on Answer.** This is used because the problem exhibits **monotonicity**: as the threshold increases, more edges become "light," making it easier to find a valid path.


* 
**Pattern 2: Modified Dijkstra.** Instead of finding the shortest path based on weight, we find the path with the **minimum count of heavy edges**.


* 
**The "Trick":** For a fixed threshold, redefine edge costs: light edges cost **0** and heavy edges cost **1**.



---

## Strategy: Binary Search + Dijkstra

We search for the optimal threshold within the range of possible edge weights $[0, \text{max\_weight}]$.

1. 
**Binary Search:** In each step, pick a `mid` value as the potential threshold.


2. **Modified Dijkstra Check:**
* Initialize a `dist` array to infinity to track the minimum heavy edges needed to reach each node.


* Use a min-priority queue to explore paths, prioritizing those with fewer heavy edges.


* 
**Relaxation:** If `dist[u] + cost < dist[v]`, update `dist[v]` and push to the queue.




3. 
**Validation:** If `dist[target] \le k`, the threshold is valid; try a smaller value.



---

## Implementation

```cpp
class Solution {
public:
    bool canReach(int threshold, int n, vector<vector<pair<int, int>>>& adj, int src, int target, int k) {
        // Minimum heavy edges needed to reach each node
        vector<int> dist(n, 1e9); 
        dist[src] = 0;

        // {heavy_edges_count, current_node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [current_heavy, u] = pq.top();
            pq.pop();

            if (current_heavy > dist[u]) continue; 
            if (u == target) return current_heavy <= k;

            for (auto& edge : adj[u]) {
                int w = edge.first;
                int v = edge.second;
                
                // Redefine cost: Heavy = 1, Light = 0
                int cost = (w > threshold) ? 1 : 0; 
                
                if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[target] <= k;
    }

    int minimumThreshold(int n, vector<vector<int>>& edges, int source, int target, int k) {
        // 1. Build Adjacency List for UNDIRECTED graph
        vector<vector<pair<int, int>>> adj(n);
        int max_w = 0;
        for (auto& e : edges) {
            adj[e[0]].push_back({e[2], e[1]});
            adj[e[1]].push_back({e[2], e[0]});
            max_w = max(max_w, e[2]);
        }

        // 2. Binary Search on Answer
        int low = 0, high = max_w, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canReach(mid, n, adj, source, target, k)) {
                ans = mid;
                high = mid - 1; 
            } else {
                low = mid + 1; 
            }
        }
        return ans;
    }
};

```

---

## Complexity Analysis

* 
**Time Complexity:** $O(\log(\text{max\_weight}) \cdot (E \log V))$. The binary search performs $\log(\text{max\_weight})$ checks, and each check is a Dijkstra run taking $O(E \log V)$.


* 
**Space Complexity:** $O(V + E)$. Required for the adjacency list, the distance array, and the priority queue.