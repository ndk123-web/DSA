## Dijkstra’s Algorithm

---

# 1️⃣ Why this algorithm exists

Many problems in graphs ask:

```text
What is the shortest distance from a source node to all other nodes?
```

But graphs may have **weights on edges**.

Example:

```
A --5--> B
A --2--> C
C --1--> B
```

Shortest path from `A → B` is **not** the direct edge (5).

It is:

```
A → C → B
2 + 1 = 3
```

So we need an algorithm that:

- explores multiple paths
- keeps track of minimum distances
- always chooses the best next node

That algorithm is **Dijkstra**.

---

# 2️⃣ What Dijkstra actually solves

Dijkstra finds:

```text
Shortest path from ONE source node
to ALL other nodes
```

Conditions:

- Graph may be **directed or undirected**
- Edge weights must be **non-negative**

If negative weights exist → **Bellman-Ford is used instead**.

---

# 3️⃣ Core idea of the algorithm

The algorithm always expands the **node with the smallest distance discovered so far**.

Think of distance like **water spreading from source**.

```
source
   ↓
neighbors
   ↓
neighbors of neighbors
```

But we always pick the **closest node first**.

---

# 4️⃣ Data structures used

Dijkstra mainly uses two things.

### 1️⃣ Distance array

```
dist[i] = shortest known distance from source → i
```

Initially:

```
dist[source] = 0
dist[others] = ∞
```

---

### 2️⃣ Min Heap (Priority Queue)

This always gives the node with the **smallest current distance**.

```
priority_queue< pair<distance,node> >
```

Why?

Because we always process the **closest node first**.

---

# 5️⃣ Algorithm flow

Step-by-step:

### Step 1

Initialize distances

```
dist[source] = 0
dist[others] = ∞
```

Push source into min heap.

---

### Step 2

Pop the node with the **minimum distance**.

```
current = pq.top()
```

---

### Step 3

Relax its edges.

Relaxation means:

```
if dist[current] + weight < dist[neighbor]
    update distance
```

```
dist[neighbor] = dist[current] + weight
```

Push the updated node again into the heap.

---

### Step 4

Repeat until heap becomes empty.

At the end:

```
dist[i] = shortest path from source → i
```

---

# 6️⃣ Visual Example

Graph:

```
0 --4--> 1
0 --1--> 2
2 --2--> 1
1 --1--> 3
2 --5--> 3
```

Start from `0`.

---

### Step 1

```
dist = [0, ∞, ∞, ∞]
```

Heap:

```
(0,0)
```

---

### Step 2

Process node `0`.

```
0 → 1 (4)
0 → 2 (1)
```

Update:

```
dist[1] = 4
dist[2] = 1
```

Heap:

```
(1,2)
(4,1)
```

---

### Step 3

Process node `2`.

```
2 → 1 (2)
```

New distance:

```
1 + 2 = 3 < 4
```

Update:

```
dist[1] = 3
```

Heap:

```
(3,1)
(4,1)
```

---

### Step 4

Process node `1`.

```
1 → 3 (1)
```

Update:

```
dist[3] = 4
```

---

Final distances:

```
0 → 0 = 0
0 → 1 = 3
0 → 2 = 1
0 → 3 = 4
```

---

# 7️⃣ Code (C++)

Standard adjacency list implementation.

```cpp
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        vector<int> dist(V, INT_MAX);

        dist[src] = 0;
        pq.push({0, src});

        while(!pq.empty()) {

            auto [d, node] = pq.top();
            pq.pop();

            for(auto &edge : adj[node]) {

                int neighbor = edge.first;
                int weight = edge.second;

                if(dist[node] + weight < dist[neighbor]) {

                    dist[neighbor] = dist[node] + weight;

                    pq.push({dist[neighbor], neighbor});
                }
            }
        }

        return dist;
    }
};
```

---

# 8️⃣ Time Complexity

For graph:

```
V = vertices
E = edges
```

Complexity:

```
O(E log V)
```

Why?

Because each edge update may push into the heap.

Heap operations cost:

```
log V
```

---

# 9️⃣ Why greedy works here

Dijkstra is a **greedy algorithm**.

Key property:

```
When we pop a node from the min heap,
its shortest distance is already finalized.
```

Why?

Because all edge weights are **non-negative**.

So no future path can make it shorter.

---

# 🔟 Real world uses

Dijkstra is used everywhere.

### GPS navigation

```
Google Maps
Uber routing
```

### Networking

```
Internet routing protocols
(OSPF)
```

### Game engines

```
NPC movement
shortest pathfinding
```

---

# 1️⃣1️⃣ When NOT to use Dijkstra

Dijkstra fails if graph contains:

```
negative edge weights
```

Example:

```
A → B = 5
A → C = 2
C → B = -10
```

Dijkstra would choose wrong path.

For such graphs use:

```
Bellman-Ford
```

---

# 1️⃣2️⃣ Pattern recognition (very important for DSA)

Whenever you see:

```
shortest path
minimum effort
minimum cost
grid traversal
weighted graph
```

Think:

```
Dijkstra
```

Common LeetCode problems:

- Network Delay Time
- Path With Minimum Effort
- Cheapest Flights Within K Stops
- Swim in Rising Water
