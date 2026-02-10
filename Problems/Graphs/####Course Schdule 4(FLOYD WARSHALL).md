# ✅ Course Prerequisite Check

### Three Correct Ways to Solve `checkIfPrerequisite`

Problem recap (1 line):

> For each query `(u, v)`, check whether **course `u` is a prerequisite of course `v`**,
> directly **or indirectly**.

This is **reachability in a directed graph**, queried many times.

---

## Core Graph Model (Same for all)

Directed graph:

```
u → v   means: u must be done before v
```

So the question becomes:

> **Is there a directed path from `u` to `v`?**

---

# 🟦 Solution 1: DFS per Query (Brute Reachability)

### Idea

For **each query**, run DFS:

- Start from `u`
- Try to reach `v`

If reachable → `true`, else `false`.

---

### Code (your version)

```cpp
class Solution {
    vector<vector<int>> adj;

public:
    vector<bool> checkIfPrerequisite(int n,
        vector<vector<int>>& prerequisites,
        vector<vector<int>>& queries) {

        adj.assign(n, {});
        for (auto& pre : prerequisites) {
            adj[pre[0]].push_back(pre[1]);
        }

        vector<bool> res;
        for (auto& q : queries) {
            res.push_back(dfs(q[0], q[1]));
        }
        return res;
    }

private:
    bool dfs(int node, int target) {
        if (node == target) return true;
        for (int nei : adj[node]) {
            if (dfs(nei, target))
                return true;
        }
        return false;
    }
};
```

---

### Dry Run

```
prerequisites = [[0,1],[1,2],[2,3]]
queries = [[0,3],[1,3],[3,0]]
```

Graph:

```
0 → 1 → 2 → 3
```

Query `[0,3]`:

```
dfs(0)
 → dfs(1)
   → dfs(2)
     → dfs(3)  ✓
```

Query `[3,0]`:

```
dfs(3) → no outgoing edges → false
```

---

### ❌ Problems with this approach

1. **No visited array** → infinite recursion if cycle exists
2. **Repeated DFS** → same paths recomputed again and again
3. Worst-case time:

   ```
   O(Q × (N + E))
   ```

---

### When to use

- Small constraints
- Learning / intuition
- Not interview-optimal

---

# 🟩 Solution 2: Topological Sort + Prerequisite Propagation (DP on DAG)

### Idea

This uses a **very important observation**:

> If
> `A → B` and `B → C`
> then `A` is also a prerequisite of `C`

So instead of answering queries later, we **precompute prerequisite sets**.

---

### How it works (step-by-step)

1. Build graph and indegree
2. Do **Kahn’s Algorithm** (topological order)
3. Maintain:

   ```
   prereqMap[x] = all prerequisites of x
   ```

4. While processing edges:
   - If `u → v`
     - `u` is prerequisite of `v`
     - **all prerequisites of `u` are also prerequisites of `v`**

---

### Code (your version)

```cpp
class Solution {
private:
    vector<unordered_set<int>> adj, prereqMap;
    vector<int> indegree;

public:
    vector<bool> checkIfPrerequisite(int n,
        vector<vector<int>>& pres,
        vector<vector<int>>& queries) {

        adj.assign(n, {});
        prereqMap.assign(n, {});
        indegree.assign(n, 0);

        for (auto& pre : pres) {
            indegree[pre[1]]++;
            adj[pre[0]].insert(pre[1]);
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indegree[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int node = q.front(); q.pop();

            for (int nei : adj[node]) {
                prereqMap[nei].insert(node);
                prereqMap[nei].insert(
                    prereqMap[node].begin(),
                    prereqMap[node].end()
                );

                if (--indegree[nei] == 0)
                    q.push(nei);
            }
        }

        vector<bool> res;
        for (auto& q : queries) {
            res.push_back(prereqMap[q[1]].count(q[0]));
        }
        return res;
    }
};
```

---

### Dry Run

```
0 → 1 → 2 → 3
```

Processing order:

```
0, 1, 2, 3
```

Updates:

```
prereq[1] = {0}
prereq[2] = {1,0}
prereq[3] = {2,1,0}
```

Query `[0,3]`:

```
0 ∈ prereq[3] → true
```

---

### Why this works

- DAG property ensures correct order
- Each node collects **all upstream nodes**
- Query becomes O(1)

---

### Complexity

```
Time:  O(N + E + N²)  (set unions)
Space: O(N²)
```

---

### When to use

- DAG guaranteed
- Medium constraints
- Interview-strong solution

---

# 🟥 Solution 3: Floyd–Warshall (All-Pairs Reachability)

### Idea

Instead of DFS per query or topo DP:

> **Precompute reachability between every pair of courses**

Classic **transitive closure**.

---

### Boolean Floyd–Warshall Rule

```
If i → k AND k → j
Then i → j
```

---

### Code (your version)

```cpp
class Solution {
public:
    vector<bool> checkIfPrerequisite(int n,
        vector<vector<int>>& pres,
        vector<vector<int>>& queries) {

        vector<vector<bool>> adj(n, vector<bool>(n, false));

        for (auto& pre : pres) {
            adj[pre[0]][pre[1]] = true;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adj[i][j] =
                        adj[i][j] || (adj[i][k] && adj[k][j]);
                }
            }
        }

        vector<bool> res;
        for (auto& q : queries) {
            res.push_back(adj[q[0]][q[1]]);
        }
        return res;
    }
};
```

---

### Dry Run

Initial:

```
0 → 1
1 → 2
2 → 3
```

After k = 1:

```
0 → 2
```

After k = 2:

```
0 → 3
1 → 3
```

Final matrix stores **all reachability**.

Query lookup is direct:

```
adj[u][v]
```

---

### Complexity

```
Time:  O(N³)
Space: O(N²)
```

---

### When to use

- `N ≤ 100`
- Many queries
- Cleanest & safest logic

---

# 🔍 Comparison Summary

| Approach       | Idea              | Time    | Space | Notes                   |
| -------------- | ----------------- | ------- | ----- | ----------------------- |
| DFS per query  | Search every time | Q·(N+E) | N     | Slow, needs visited     |
| Topo + DP      | Build prereq sets | ~N²     | N²    | Best interview solution |
| Floyd–Warshall | All-pairs closure | N³      | N²    | Easiest to reason       |
