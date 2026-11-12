# Ultimate Master DSA Pattern Revision Sheet

> **Goal**: One single file to revise **all core DSA patterns, keyword triggers, visual mental models, and template code** before coding interviews.

---

## ⚡ Master Problem-to-Pattern Keyword Matrix

When reading any DSA problem statement, use this fast mental lookup table:

| Problem Statement Keywords | Data Structure / Technique | Core Mental Model / Pattern |
|---|---|---|
| *"Contiguous subarray / substring of length K or condition X"* | **Sliding Window** | Expand `right`, shrink `left` when condition breaks |
| *"Sorted array / Search in $O(\log N)$ / Find Min/Max boundary"* | **Binary Search** | Mid calculation, search space reduction |
| *"Pair sum in sorted array / Palindrome / Partition"* | **Two Pointers** | `left` at start, `right` at end |
| *"Subarray sum equals K / Continuous range sums"* | **Prefix Sum + Hash Map** | $P[j] - P[i-1] = K \implies P[i-1] = P[j] - K$ |
| *"Next Greater Element / Next Smaller / Histogram Area"* | **Monotonic Stack** | Stack stores monotonic indices |
| *"Top K elements / Kth Smallest / Median of Stream"* | **Min/Max Heap** | Priority Queue of size $K$ |
| *"All combinations / Permutations / Subsets / Grid path exploration"* | **Backtracking** | Choose $\rightarrow$ Explore $\rightarrow$ Unchoose (Pop) |
| *"Shortest path in unweighted graph / Level order traversal"* | **BFS (Queue)** | Queue + `visited` set |
| *"Connected components / Cycle detection / Topological order"* | **DFS / Union-Find / Kahn's** | Recursion stack or Disjoint Set Union (DSU) |
| *"Shortest path with non-negative edge weights"* | **Dijkstra's Algorithm** | Priority Queue storing `(distance, node)` |
| *"Min/Max total cost with overlapping subproblems"* | **Dynamic Programming** | State definition $\rightarrow$ Recurrence relation $\rightarrow$ Memo/Tabulation |
| *"Prefix matching / Auto-complete / Word Search"* | **Trie (Prefix Tree)** | Tree of 26-child nodes |

---

# 1. Array & Two Pointers

### ⚡ Patterns:
1. **Opposite Direction Pointers** (Two Sum II, Valid Palindrome, Container With Most Water)
2. **Fast & Slow Pointers** (Cycle Detection, Remove Duplicates)
3. **Dutch National Flag / 3-Pointers** (Sort Colors 0s, 1s, 2s)

### 💻 Template: Opposite Pointers
```cpp
int left = 0, right = n - 1;
while (left < right) {
    int current_sum = nums[left] + nums[right];
    if (current_sum == target) return {left, right};
    else if (current_sum < target) left++;
    else right--;
}
```

---

# 2. Sliding Window Pattern

### ⚡ Patterns:
1. **Fixed Window Size $K$** (Max Sum Subarray of size $K$)
2. **Variable Window Size** (Longest Substring Without Repeating Characters, Minimum Window Substring)

### 💻 Template: Dynamic Variable Window
```cpp
unordered_map<char, int> freq;
int left = 0, max_len = 0;

for (int right = 0; right < s.length(); right++) {
    freq[s[right]]++;
    
    // Shrink window if condition is violated
    while (/* invalid condition e.g. freq[s[right]] > 1 */) {
        freq[s[left]]--;
        if (freq[s[left]] == 0) freq.erase(s[left]);
        left++;
    }
    
    max_len = max(max_len, right - left + 1);
}
```

---

# 3. Prefix Sum + Hash Map

⚡ **Key Formula**: $\text{SubarraySum}(i, j) = \text{Prefix}[j] - \text{Prefix}[i-1] = K$.

### 💻 Template: Subarray Sum Equals K
```cpp
int count = 0, current_sum = 0;
unordered_map<int, int> prefix_counts;
prefix_counts[0] = 1; // Base case: empty prefix

for (int num : nums) {
    current_sum += num;
    if (prefix_counts.count(current_sum - k)) {
        count += prefix_counts[current_sum - k];
    }
    prefix_counts[current_sum]++;
}
```

---

# 4. Binary Search & Search Space Optimization

### ⚡ Patterns:
1. **Classic Binary Search** (Find index of target in sorted array)
2. **Binary Search on Answer** (Capacity To Ship Packages, Koko Eating Bananas, Minimized Maximum)

### 💻 Template: Binary Search on Answer Space
```cpp
int low = min_possible, high = max_possible, ans = -1;
while (low <= high) {
    int mid = low + (high - low) / 2;
    if (isValid(mid, nums, k)) {
        ans = mid;        // Store feasible answer
        high = mid - 1;   // Try searching for smaller valid value (Minimization)
    } else {
        low = mid + 1;
    }
}
```

---

# 5. Monotonic Stack Pattern

⚡ **Mental Hook**: Maintained stack elements are strictly increasing or decreasing.
- **Next Greater Element**: Decreasing Stack (top is smaller).
- **Next Smaller Element**: Increasing Stack (top is larger).

### 💻 Template: Next Greater Element
```cpp
vector<int> res(n, -1);
stack<int> st; // Stores indices

for (int i = 0; i < n; i++) {
    while (!st.empty() && nums[st.top()] < nums[i]) {
        res[st.top()] = nums[i];
        st.pop();
    }
    st.push(i);
}
```

---

# 6. Linked List Fast/Slow & In-Place Reversal

### ⚡ Key Tricks:
- **Cycle Detection**: `slow = slow->next`, `fast = fast->next->next`.
- **Finding Middle**: When `fast` reaches end, `slow` is at middle.
- **In-place Reversal**: Maintain `prev`, `curr`, `next_node`.

### 💻 Template: In-Place Reversal
```cpp
ListNode* prev = nullptr, *curr = head;
while (curr != nullptr) {
    ListNode* next_node = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next_node;
}
return prev; // New head
```

---

# 7. Binary Trees & BST Patterns

### ⚡ Traversal Patterns:
- **DFS Traversals**: Preorder (Root-L-R), Inorder (L-Root-R $\rightarrow$ Sorted for BST), Postorder (L-R-Root).
- **BFS Level Order**: Queue with inner `size` loop.
- **Tree Diameter / Max Path Sum**: Return bottom-up height to parent while updating global `ans = max(ans, left + right + node->val)`.

### 💻 Template: BFS Level Order Traversal
```cpp
vector<vector<int>> res;
if (!root) return res;
queue<TreeNode*> q;
q.push(root);

while (!q.empty()) {
    int level_size = q.size();
    vector<int> level_nodes;
    for (int i = 0; i < level_size; i++) {
        TreeNode* curr = q.front(); q.pop();
        level_nodes.push_back(curr->val);
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    res.push_back(level_nodes);
}
```

---

# 8. Heaps & Priority Queues (Top-K Pattern)

⚡ **Mental Hook**:
- To find **Top K Largest** elements $\rightarrow$ Use **Min-Heap** of size $K$.
- To find **Top K Smallest** elements $\rightarrow$ Use **Max-Heap** of size $K$.

### 💻 Template: Kth Largest Element
```cpp
priority_queue<int, vector<int>, greater<int>> min_heap; // Min heap
for (int num : nums) {
    min_heap.push(num);
    if (min_heap.size() > k) {
        min_heap.pop(); // Evict smallest
    }
}
return min_heap.top(); // Kth largest remains at top
```

---

# 9. Backtracking (Subsets, Permutations, Combinations)

### 💻 Template: Standard Backtracking
```cpp
void backtrack(int start, vector<int>& nums, vector<int>& path, vector<vector<int>>& res) {
    res.push_back(path); // Record decision state
    
    for (int i = start; i < nums.size(); i++) {
        // Handle duplicates if sorted: if (i > start && nums[i] == nums[i-1]) continue;
        path.push_back(nums[i]);                  // CHOOSE
        backtrack(i + 1, nums, path, res);        // EXPLORE
        path.pop_back();                          // UNCHOOSE (Backtrack)
    }
}
```

---

# 10. Graphs: BFS, DFS, Union-Find & Dijkstra

### ⚡ Decision Tree:
- **Unweighted Shortest Path** $\rightarrow$ **BFS**
- **Cycle Detection / Connected Components** $\rightarrow$ **DFS / Union-Find**
- **Dependency Ordering / Pre-requisites** $\rightarrow$ **Topological Sort (Kahn's Algorithm - In-degree Queue)**
- **Weighted Shortest Path ($w \ge 0$)** $\rightarrow$ **Dijkstra's Algorithm**

### 💻 Template: Dijkstra's Algorithm
```cpp
vector<int> dist(V, INT_MAX);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

dist[src] = 0;
pq.push({0, src}); // {distance, node}

while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    
    for (auto& [v, weight] : adj[u]) {
        if (dist[u] + weight < dist[v]) {
            dist[v] = dist[u] + weight;
            pq.push({dist[v], v});
        }
    }
}
```

---



### ⚡ Topological Sorting — Kahn's Algorithm (BFS)

- **Use case**: Find a valid ordering of tasks/courses when some tasks depend on others.
- **Graph requirement**: Directed Acyclic Graph (DAG). A directed cycle means no valid topological ordering exists.
- **Indegree**: Number of incoming edges (unfinished prerequisites) for a node.
- **Core idea**:
  1. Build the directed adjacency list and calculate each node's indegree.
  2. Push every node with indegree `0` into a queue; these tasks have no pending prerequisites.
  3. Pop a node, add it to the ordering, and decrement the indegree of each outgoing neighbour.
  4. Whenever a neighbour's indegree becomes `0`, push it into the queue.
  5. If the ordering contains all `V` nodes, a topological ordering exists; otherwise, a cycle is present.
- **Cycle detection**: Processed node count `!= V` means at least one directed cycle blocks the remaining nodes.
- **Complexity**: `O(V + E)` time and `O(V + E)` space.

### 💻 Template: Kahn's Algorithm (Topological Order)

```cpp
vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);

    // Calculate indegree of every node.
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;

    // Start with nodes that have no prerequisites.
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        // Completing u removes its outgoing dependency edges.
        for (int v : adj[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Empty result means a directed cycle exists.
    if (order.size() != V) return {};
    return order;
}
```

- **Classic applications**: Course Schedule (LC 207 — cycle detection) and Course Schedule II (LC 210 — return the ordering).




### ⚡ Union-Find / Disjoint Set Union (DSU)

- **Use case**: Maintain and merge connected components; efficiently check whether two nodes belong to the same component.
- **Core operations**:
  - `find(x)`: return the representative (root) of the component containing `x`.
  - `unite(a, b)`: merge the components containing `a` and `b).
- **Optimizations**:
  - **Path compression**: During `find`, make visited nodes point directly to the root.
  - **Union by size**: Attach the smaller component's root below the larger component's root.
- **Complexity**: With path compression and union by size, operations take amortized `O(α(V))), effectively constant time; space is `O(V)`.
- **Cycle detection in an undirected graph**: For each edge `(u, v)`, if `find(u) == find(v)`, the edge connects nodes already in the same component and creates a cycle; otherwise, unite them.

### 💻 Template: Union-Find with Path Compression + Union by Size

```cpp
class DSU {
    vector<int> parent;
    vector<int> sz;

public:
    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB) return false;

        // Union by size: keep the larger component as the root.
        if (sz[rootA] < sz[rootB]) {
            swap(rootA, rootB);
        }

        parent[rootB] = rootA;
        sz[rootA] += sz[rootB];
        return true;
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};
```


### ⚡ Bellman-Ford Algorithm

- **Use case**: Single-source shortest paths when edge weights may be negative.
- **Core idea**: Repeatedly relax every directed edge. For edge `u -> v` with weight `w`, update `dist[v]` when `dist[u] + w < dist[v]`.
- **Why `V - 1` rounds?** A shortest path without a cycle uses at most `V - 1` edges. Each full round guarantees propagation across at least one additional edge, regardless of edge ordering.
- **Negative cycle detection**: After the `V - 1` rounds, another possible relaxation means a negative-weight cycle is reachable from the source.
- **Important**: Standard in-place Bellman-Ford reads and writes the same `dist` array. Updates may propagate across multiple edges in one round depending on edge order; the `V - 1`-round guarantee still holds. Use a copied array per round when you specifically need to limit paths to at most one additional edge per round (for example, a bounded-flights variant).
- **Complexity**: `O(V * E)` time and `O(V)` auxiliary space.

### 💻 Template: Standard Bellman-Ford

```cpp
// edges contains {u, v, weight}; graph is directed.
vector<long long> bellmanFord(
    int V,
    const vector<vector<int>>& edges,
    int src
) {
    const long long INF = LLONG_MAX;
    vector<long long> dist(V, INF);
    dist[src] = 0;

    // Relax every edge V - 1 times.
    for (int i = 0; i < V - 1; i++) {
        bool changed = false;

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            if (dist[u] == INF) continue; // Ignore unreachable u.

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }

        if (!changed) break; // Early exit: no more improvements.
    }

    // A further relaxation indicates a source-reachable negative cycle.
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return {}; // Empty result signals a reachable negative cycle.
        }
    }

    return dist;
}
```

### ⚡ Bipartite Graph — 2-Coloring (BFS / DFS)

- **Definition**: An undirected graph is bipartite if its vertices can be divided into two groups such that every edge connects vertices from different groups.
- **Equivalent property**: A graph is bipartite if and only if it contains no odd-length cycle.
- **Core idea**: Color each connected component using two colors. Every neighbour must receive the opposite color. If an edge connects two vertices with the same color, the graph is not bipartite.
- **Disconnected graphs**: Start BFS/DFS from every uncolored vertex; checking only vertex `0` is insufficient.
- **Complexity**: `O(V + E)` time and `O(V)` auxiliary space.

### 💻 Template: Bipartite Check using BFS

```cpp
bool isBipartite(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> color(V, -1); // -1 = uncolored; 0 and 1 = two groups

    for (int start = 0; start < V; start++) {
        if (color[start] != -1) continue;

        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }

    return true;
}
```

- **Typical application**: LeetCode 785 — Is Graph Bipartite?

### ⚡ Cycle Detection in Graphs

#### Undirected Graph — DFS with Parent Tracking

- **Core idea**: During DFS, an already visited neighbour indicates a cycle only when that neighbour is not the current node's parent.
- **Why parent check?** In an undirected graph, every edge appears in both adjacency lists. The edge back to the parent is not a cycle.
- **Disconnected graphs**: Run DFS from every unvisited vertex.
- **Complexity**: `O(V + E)` time and `O(V)` auxiliary space, including recursion stack.

```cpp
bool dfsCycle(int u, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsCycle(v, u, adj, visited)) return true;
        } else if (v != parent) {
            return true;
        }
    }
    return false;
}

bool hasUndirectedCycle(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dfsCycle(i, -1, adj, visited)) return true;
    }
    return false;
}
```

#### Undirected Graph — BFS with Parent Tracking

- **Core idea**: Store `(node, parent)` in the queue. A visited neighbour other than the parent reveals a cycle.

```cpp
bool hasUndirectedCycleBFS(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    for (int start = 0; start < V; start++) {
        if (visited[start]) continue;
        queue<pair<int, int>> q;
        q.push({start, -1});
        visited[start] = true;

        while (!q.empty()) {
            auto [u, parent] = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push({v, u});
                } else if (v != parent) {
                    return true;
                }
            }
        }
    }
    return false;
}
```

#### Undirected Graph — DSU

- Process each edge `(u, v)`. If `find(u) == find(v)`, the endpoints are already connected, so this edge creates a cycle. Otherwise, unite their components.
- **Complexity**: `O(E α(V))` amortized time and `O(V)` auxiliary space.

```cpp
bool hasUndirectedCycleDSU(int V, vector<pair<int, int>>& edges) {
    DSU dsu(V);
    for (auto [u, v] : edges) {
        if (dsu.find(u) == dsu.find(v)) return true;
        dsu.unite(u, v);
    }
    return false;
}
```

#### Directed Graph — DFS with Recursion-Stack State

- **Core idea**: Use three states: `0 = unvisited`, `1 = currently in the recursion path`, `2 = fully processed`.
- An edge to a node in state `1` is a back edge and proves a directed cycle. An edge to a node in state `2` does not by itself prove a cycle.
- **Complexity**: `O(V + E)` time and `O(V)` auxiliary space.

```cpp
bool dfsDirectedCycle(int u, vector<vector<int>>& adj, vector<int>& state) {
    state[u] = 1; // In current DFS path
    for (int v : adj[u]) {
        if (state[v] == 1) return true;
        if (state[v] == 0 && dfsDirectedCycle(v, adj, state)) return true;
    }
    state[u] = 2; // Fully processed
    return false;
}

bool hasDirectedCycle(int V, vector<vector<int>>& adj) {
    vector<int> state(V, 0);
    for (int i = 0; i < V; i++) {
        if (state[i] == 0 && dfsDirectedCycle(i, adj, state)) return true;
    }
    return false;
}
```

- **Alternative**: Kahn's topological sort detects a directed cycle when fewer than `V` vertices are processed; see the Topological Sorting section.

### ⚡ Minimum Spanning Tree (MST)

- **Definition**: A spanning tree of a connected, weighted, undirected graph that includes all vertices, remains connected, and contains no cycle; an MST minimizes the sum of its edge weights.
- **Tree property**: Any spanning tree with `V` vertices has exactly `V - 1` edges.
- **Important distinction**: MST minimizes the total weight of the selected tree; it does not minimize each vertex's shortest-path distance from a source.
- **Negative edge weights**: Allowed.
- **Disconnected graph**: No spanning tree exists; a minimum spanning forest can be constructed instead.

#### Kruskal's Algorithm — Edge-Based Greedy

- **Core idea**: Sort all edges by increasing weight. Add an edge only if its endpoints belong to different DSU components; this avoids cycles.
- **Steps**: Sort edges; initialize DSU; process edges in ascending order, adding and uniting only when the roots differ; stop after `V - 1` selected edges.
- **Complexity**: `O(E log E)` time for sorting, plus near-constant amortized DSU operations; `O(V)` auxiliary space apart from edge storage.

```cpp
struct Edge { int u, v, wt; };

long long kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.wt < b.wt;
    });

    DSU dsu(V);
    long long mstCost = 0;
    int edgesUsed = 0;

    for (const Edge& e : edges) {
        if (dsu.find(e.u) == dsu.find(e.v)) continue;
        dsu.unite(e.u, e.v);
        mstCost += e.wt;
        if (++edgesUsed == V - 1) break;
    }

    return edgesUsed == V - 1 ? mstCost : -1; // -1: disconnected
}
```

#### Prim's Algorithm — Vertex-Based Greedy

- **Core idea**: Grow one tree. At each step, choose the minimum-weight edge connecting a vertex already in the tree to one outside it.
- **Steps**: Start from any vertex with weight `0`; repeatedly extract the minimum candidate, skip visited vertices, add the selected weight, and push edges to unvisited neighbours. Finish after all `V` vertices are included.
- **Complexity**: `O(E log V)` time with an adjacency list and min-heap for a simple graph; `O(V + E)` auxiliary space including adjacency list and heap.

```cpp
long long primMST(int V, vector<vector<pair<int, int>>>& adj) {
    // Each adjacency entry is {neighbour, edgeWeight}.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(V, false);
    pq.push({0, 0}); // {edgeWeight, vertex}

    long long mstCost = 0;
    int verticesUsed = 0;

    while (!pq.empty()) {
        auto [wt, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;

        visited[u] = true;
        mstCost += wt;
        verticesUsed++;

        for (auto [v, edgeWt] : adj[u]) {
            if (!visited[v]) pq.push({edgeWt, v});
        }
    }

    return verticesUsed == V ? mstCost : -1; // -1: disconnected
}
```

#### Kruskal vs Prim — Quick Comparison

| Point | Kruskal | Prim |
|---|---|---|
| Greedy choice | Globally lightest safe edge | Lightest edge leaving the current tree |
| View | Edge-based | Vertex/tree-based |
| Main data structure | DSU + sorted edge list | Min-heap + visited array |
| Cycle handling | DSU rejects an edge joining the same component | Visited array skips included vertices |
| Typical complexity | `O(E log E)` | `O(E log V)` with adjacency list + heap |
| Disconnected graph | Produces a minimum spanning forest if run to completion | Repeat from unvisited vertices to produce a forest |

- **Common problems**: LeetCode 1584 — Min Cost to Connect All Points; LeetCode 1135 — Connecting Cities With Minimum Cost (Premium).

# 11. Dynamic Programming Patterns

| DP Category | State Definition | Transition Formula | Examples |
|---|---|---|---|
| **0/1 Knapsack** | `dp[i][w]` (Pick or Don't Pick item `i`) | `dp[i][w] = max(dp[i-1][w], val + dp[i-1][w-wt])` | Partition Equal Subset Sum, Target Sum |
| **Unbounded Knapsack** | `dp[w]` (Reuse item multiple times) | `dp[w] = min(dp[w], 1 + dp[w - coin])` | Coin Change, Rod Cutting |
| **LCS (Subsequence)** | `dp[i][j]` (LCS of `s1[0..i]` & `s2[0..j]`) | `s1[i]==s2[j] ? 1+dp[i-1][j-1] : max(dp[i-1][j], dp[i][j-1])` | Longest Common Subsequence, Edit Distance |
| **LIS (Increasing)** | `dp[i]` (Max LIS ending at index `i`) | `dp[i] = max(1, 1 + dp[j])` for all $j < i$ & $nums[j] < nums[i]$ | Longest Increasing Subsequence ($O(N \log N)$ with Binary Search) |

---

# 12. Quick Time Complexity Master Reference

| Algorithm / Operation | Time Complexity | Space Complexity |
|---|---|---|
| Hash Map Lookup / Insert | $O(1)$ avg, $O(N)$ worst | $O(N)$ |
| Priority Queue Push / Pop | $O(\log K)$ | $O(K)$ |
| Binary Search | $O(\log N)$ | $O(1)$ |
| Sorting (Merge / Quick Sort) | $O(N \log N)$ | $O(N)$ or $O(\log N)$ |
| Tree / Graph Traversal (DFS/BFS) | $O(V + E)$ | $O(V)$ |
| Dijkstra's Shortest Path | $O((V + E) \log V)$ | $O(V + E)$ |
| Topological Sort (Kahn's) | $O(V + E)$ | $O(V)$ |
