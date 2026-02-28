# 🔹 Cheapest Flights Within K Stops

---

# 1️⃣ Bellman-Ford (Edge-Limited Relaxation)

## 🧠 Intuition

We are looking for the cheapest path from `src` to `dst` with at most `k` stops.

Since:

- `k` stops means at most `k + 1` edges,
- we only need shortest paths that use up to `k + 1` edges.

Bellman-Ford naturally computes shortest paths using a limited number of edges.

Key idea:

- After 1 iteration → shortest paths using at most 1 edge.
- After 2 iterations → shortest paths using at most 2 edges.
- After i iterations → shortest paths using at most i edges.

So we run relaxation `k + 1` times.

---

## 🚀 Approach

1. Initialize `prices[src] = 0`, others = `INT_MAX`.
2. Run loop `k + 1` times:
   - Use a temporary copy of the previous distances.
   - Relax all edges using values from previous iteration.

3. Return `prices[dst]` if reachable.

Important:
We use a temporary array to prevent multiple edges being used in the same iteration.

---

## ⏱ Complexity

- Time complexity:
  **O(k \* E)**
  where E = number of flights.

- Space complexity:
  **O(n)**

---

## 💻 Code

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights,
                          int src, int dst, int k) {

        vector<int> prices(n, INT_MAX);
        prices[src] = 0;

        for (int i = 0; i <= k; i++) {
            vector<int> tempPrices = prices;

            for (auto &flight : flights) {
                int s = flight[0];
                int d = flight[1];
                int c = flight[2];

                if (prices[s] == INT_MAX)
                    continue;

                tempPrices[d] = min(tempPrices[d], prices[s] + c);
            }

            prices = tempPrices;
        }

        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }
};
```

---

# 2️⃣ Dijkstra Without Pruning (Heap-Based)

## 🧠 Intuition

We try to adapt Dijkstra’s algorithm.

State in heap:

```
(cost, node, stopsUsed)
```

We expand cheapest cost first while respecting the stop constraint.

However, without pruning, the same node can be revisited many times with different stop counts. This can lead to state explosion and TLE.

---

## 🚀 Approach

1. Build adjacency list.
2. Use min-heap storing `(cost, node, stops)`.
3. Expand while `stops <= k + 1`.
4. Update cheapest cost when destination is found.

This works logically but can be inefficient.

---

## ⏱ Complexity

- Time complexity:
  Potentially exponential in worst case (can TLE).

- Space complexity:
  Large due to repeated state pushes.

---

## 💻 Code

```cpp
class Solution {
private:
    unordered_map<int, vector<pair<int, int>>> adj;
    priority_queue<
        pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<>
    > pq;

public:
    int findCheapestPrice(int n, vector<vector<int>>& flights,
                          int src, int dst, int k) {

        for (auto &flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        int cheapPrice = INT_MAX;
        pq.push({0, {src, 0}});

        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();

            int cost = p.first;
            int node = p.second.first;
            int stops = p.second.second;

            if (stops > k + 1)
                continue;

            for (auto &nei : adj[node]) {
                int tcost = cost + nei.second;
                int tstops = stops + 1;

                if (tstops > k + 1)
                    continue;

                if (nei.first == dst)
                    cheapPrice = min(cheapPrice, tcost);

                pq.push({tcost, {nei.first, tstops}});
            }
        }

        return cheapPrice == INT_MAX ? -1 : cheapPrice;
    }
};
```

---

# 3️⃣ Dijkstra With Pruning (Optimized)

## 🧠 Intuition

We improve the previous approach by pruning unnecessary states.

Observation:

If we have already reached a node with fewer stops,
there is no benefit in exploring it again with more stops.

So we maintain:

```
minStops[node] = minimum stops used to reach this node
```

If current stops exceed `minStops[node]`,
we skip.

This prevents exponential explosion.

---

## 🚀 Approach

1. Build adjacency list.
2. Use min-heap `(cost, node, stops)`.
3. Maintain `minStops[node]`.
4. Skip states where:
   - stops > k + 1
   - stops > minStops[node]

5. Return when destination is popped from heap.

---

## ⏱ Complexity

- Time complexity:
  Approximately **O(E log V)** in practice.

- Space complexity:
  **O(V + E)**

---

## 💻 Code

```cpp
class Solution {
private:
    unordered_map<int, vector<pair<int, int>>> adj;
    priority_queue<
        pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<>
    > pq;

public:
    int findCheapestPrice(int n, vector<vector<int>>& flights,
                          int src, int dst, int k) {

        vector<int> minStops(n, INT_MAX);

        for (auto &flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        pq.push({0, {src, 0}});

        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();

            int cost = p.first;
            int node = p.second.first;
            int stops = p.second.second;

            if (node == dst)
                return cost;

            if (stops > k + 1 || stops > minStops[node])
                continue;

            minStops[node] = stops;

            for (auto &nei : adj[node]) {
                pq.push({cost + nei.second, {nei.first, stops + 1}});
            }
        }

        return -1;
    }
};
```

---

# 🔥 Final Comparison

| Approach              | Best For                   | Pros               | Cons                       |
| --------------------- | -------------------------- | ------------------ | -------------------------- |
| Bellman-Ford          | Strict edge limit problems | Clean, predictable | Slightly slower if k large |
| Dijkstra (no pruning) | Conceptual understanding   | Easy adaptation    | May TLE                    |
| Dijkstra (pruned)     | Competitive coding         | Fast & elegant     | Slightly tricky logic      |

---
