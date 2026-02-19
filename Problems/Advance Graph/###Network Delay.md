# 🚀 Network Delay Time

## 🔎 Problem Summary

We are given:

- `n` nodes labeled from `1 → n`
- Directed edges `times[i] = (u, v, w)`
  meaning signal takes `w` time from `u → v`
- A starting node `k`

We must return:

- The **minimum time** required for all nodes to receive the signal
- If some node is unreachable → return `-1`

---

# 🧠 Core Insight

This is a **Single Source Shortest Path** problem.

We want:

> Shortest distance from node `k` to every other node.

Then answer =
`maximum distance among those shortest paths`.

Why maximum?
Because signal spreads outward, and the last node to receive it determines total delay.

---

# ✅ Approach 1: Dijkstra’s Algorithm (Recommended)

### 💡 Why Dijkstra?

- Directed graph
- Weighted edges
- Non-negative weights
- Single source

Perfect Dijkstra pattern.

---

## ⚙️ Algorithm

1. Build adjacency list.
2. Use min-heap (priority queue).
3. Always process smallest distance node first.
4. Mark visited nodes.
5. Track maximum shortest distance.
6. If visited count < n → return -1.

---

## 🧩 Implementation (C++)

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int,int>>> adj;

        // Build graph
        for (auto& t : times) {
            adj[t[0]].push_back({t[2], t[1]});
        }

        // Min heap: (distance, node)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        vector<bool> visited(n + 1, false);
        pq.push({0, k});

        int maxTime = 0;
        int count = 0;

        while (!pq.empty()) {
            auto [dist, node] = pq.top();
            pq.pop();

            if (visited[node]) continue;

            visited[node] = true;
            maxTime = dist;
            count++;

            for (auto& [weight, neighbor] : adj[node]) {
                if (!visited[neighbor]) {
                    pq.push({dist + weight, neighbor});
                }
            }
        }

        return count == n ? maxTime : -1;
    }
};
```

---

## ⏱ Time Complexity

- Building graph: **O(E)**
- Each edge pushed into heap once
- Heap operations: **O(E log V)**

Final:

```
Time Complexity: O(E log V)
Space Complexity: O(V + E)
```

Efficient and scalable.

---

# ✅ Approach 2: Floyd–Warshall Algorithm

### 💡 Why Floyd?

If we wanted shortest paths between **all pairs** of nodes.

Even though overkill here, it still works because constraints are small.

---

## ⚙️ Algorithm

1. Create distance matrix `n x n`
2. Initialize:
   - `dist[i][i] = 0`
   - `dist[u][v] = weight`

3. For each intermediate node `via`
   update:

   ```
   dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j])
   ```

4. After completion:
   - Check row `k`
   - Take max distance
   - If any INF → return -1

---

## 🧩 Implementation (C++)

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int INF = 1e9;
        vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

        // Initialize self distances
        for (int i = 1; i <= n; i++)
            dist[i][i] = 0;

        // Fill edges
        for (auto& t : times)
            dist[t[0]][t[1]] = t[2];

        // Floyd–Warshall
        for (int via = 1; via <= n; via++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][via] != INF && dist[via][j] != INF)
                        dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j]);
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[k][i] == INF)
                return -1;
            ans = max(ans, dist[k][i]);
        }

        return ans;
    }
};
```

---

## ⏱ Time Complexity

Triple nested loops:

```
Time Complexity: O(n³)
Space Complexity: O(n²)
```

Works because `n ≤ 100`.

---

# 🥊 Dijkstra vs Floyd–Warshall

| Feature         | Dijkstra      | Floyd–Warshall |
| --------------- | ------------- | -------------- |
| Use case        | Single source | All pairs      |
| Time            | O(E log V)    | O(n³)          |
| Space           | O(V + E)      | O(n²)          |
| Preferred here? | ✅ Yes        | ❌ Overkill    |

---

# 🎯 Final Verdict

For this problem:

> Dijkstra is the correct conceptual match.

Floyd–Warshall works but is unnecessary.

In interviews, choosing the right algorithm matters as much as writing it correctly.

---

# 🧠 Pattern Recognition Takeaway

When you see:

- Directed graph
- Weighted edges
- Non-negative weights
- Single source
