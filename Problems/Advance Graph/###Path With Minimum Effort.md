# 🔷 Path With Minimum Effort

## 🧠 Problem Summary

You are given a 2D grid `heights`.

- Start: `(0,0)`
- End: `(rows-1, cols-1)`
- Move: Up, Down, Left, Right
- Edge weight:
  `abs(height difference between adjacent cells)`

Path cost (Effort) is defined as:

> Maximum absolute difference between consecutive cells along the path.

Return the **minimum possible effort**.

---

# 🔥 Core Insight

This is NOT a normal shortest path problem.

Normal shortest path:

```
Total cost = sum of edges
```

Here:

```
Total cost = maximum edge along the path
```

We are minimizing the **worst jump**.

This is a **Min-Max Path Problem**.

---

# 💡 Why Dijkstra Works Here?

Dijkstra works whenever:

- Cost grows monotonically
- No negative weights

Here cost update rule is:

```
newEffort = max(currentEffort, edgeDifference)
```

Since:

```
max(a, b) >= a
```

Cost never decreases.

Greedy is safe.

So we use Dijkstra with modified relaxation.

---

# 🚀 Approach (Modified Dijkstra)

### Step 1: Maintain effort matrix

```
effort[r][c] = minimum effort required to reach (r,c)
```

Initialize all with `INT_MAX`.

Set:

```
effort[0][0] = 0
```

---

### Step 2: Min Heap

Store:

```
(effort_so_far, row, col)
```

Always expand the cell with smallest effort first.

---

### Step 3: Relax Neighbors

For each neighbor:

```
diff = abs(heights[nr][nc] - heights[r][c])
newEffort = max(currentEffort, diff)
```

If:

```
newEffort < effort[nr][nc]
```

Update and push to heap.

---

### Step 4: Stop Early

When we pop bottom-right cell from heap,
that effort is guaranteed minimum.

Return it.

---

# 🧩 C++ Implementation

```cpp
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();

        vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));

        priority_queue<
            pair<int, pair<int,int>>,
            vector<pair<int, pair<int,int>>>,
            greater<>
        > pq;

        pq.push({0, {0,0}});
        effort[0][0] = 0;

        vector<vector<int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

        while(!pq.empty()) {
            auto p = pq.top();
            pq.pop();

            int currEffort = p.first;
            int r = p.second.first;
            int c = p.second.second;

            if(r == rows-1 && c == cols-1)
                return currEffort;

            for(auto &d : dirs) {
                int nr = r + d[0];
                int nc = c + d[1];

                if(nr>=0 && nc>=0 && nr<rows && nc<cols) {
                    int diff = abs(heights[nr][nc] - heights[r][c]);
                    int newEffort = max(currEffort, diff);

                    if(newEffort < effort[nr][nc]) {
                        effort[nr][nc] = newEffort;
                        pq.push({newEffort, {nr,nc}});
                    }
                }
            }
        }

        return 0;
    }
};
```

---

# 🧪 Dry Run

Input:

```
[
 [1,1,1],
 [3,2,4],
 [2,5,4]
]
```

Start at (0,0)

Effort matrix initially:

```
0  INF INF
INF INF INF
INF INF INF
```

---

### Step 1:

Pop (0,0), effort = 0

Neighbors:

(1,0) → |3-1| = 2
newEffort = max(0,2) = 2

(0,1) → |1-1| = 0
newEffort = max(0,0) = 0

Push both.

Heap:

```
(0,0,1)
(2,1,0)
```

---

### Step 2:

Pop (0,1) effort=0

Neighbors:

(0,2) → diff=0 → effort=0
(1,1) → diff=1 → effort=1

Push both.

Heap:

```
(0,0,2)
(1,1,1)
(2,1,0)
```

---

### Step 3:

Pop (0,2)

Neighbors:
(1,2) → diff=3 → effort=3

Heap:

```
(1,1,1)
(2,1,0)
(3,1,2)
```

---

### Step 4:

Pop (1,1) effort=1

Neighbors:
(1,2) → diff=2 → newEffort=max(1,2)=2 (better than 3)
Update.

Heap:

```
(2,1,0)
(2,1,2)
```

Continue...

Eventually bottom-right (2,2) gets effort = 2.

Return 2.

---

# ⏱ Complexity

Let:

```
N = rows * cols
```

### Time Complexity:

Each cell inserted into heap at most once with better effort.

```
O(N log N)
```

Because heap operations cost log N.

---

### Space Complexity:

Effort matrix + heap

```
O(N)
```

---

# 🧠 Deep Conceptual Takeaway

Network Delay Time:
Minimize sum of weights.

Path With Minimum Effort:
Minimize maximum edge weight.

Both are Dijkstra.

Only relaxation formula changes.

This is the real power of Dijkstra:

It is not about addition.

It is about greedy expansion over monotonic cost functions.

---

# 🔥 Bonus Insight (Advanced Thinking)

This problem can also be solved using:

1. Binary Search + BFS
2. Minimum Spanning Tree (Kruskal + DSU)
