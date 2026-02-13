# 🧮 Evaluate Division

### 🧠 Weighted Union-Find (Disjoint Set Union with Ratio Tracking)

---

# # Intuition

Each equation like:

```
A / B = k
```

means there is a mathematical relationship between variables A and B.

This can be represented as a graph:

- A → B with weight k
- B → A with weight 1/k

Instead of performing DFS for every query, we can optimize using **Union-Find (Disjoint Set Union)** while maintaining **relative ratios** between connected variables.

The idea is:

- Each variable belongs to a connected component.
- We maintain the ratio of each variable relative to its root.
- If two variables share the same root, their ratio can be computed directly.

---

# # Key Idea

We maintain two maps:

```
parent[x]  → DSU parent
weight[x]  → x / parent[x]
```

After path compression:

```
weight[x] = x / root
```

So for any two variables `a` and `b` in same component:

```
a / b = weight[a] / weight[b]
```

---

# # Approach

### Step 1 — Initialize DSU

For each variable:

```
parent[x] = x
weight[x] = 1
```

### Step 2 — Union Operation

For equation:

```
a / b = value
```

Let:

```
rootA = find(a)
rootB = find(b)
```

If roots differ:

```
parent[rootA] = rootB
weight[rootA] = value * (weight[b] / weight[a])
```

This preserves equation consistency.

---

### Step 3 — Path Compression in find()

While compressing path:

```
weight[x] *= weight[originalParent]
parent[x] = root
```

This ensures:

```
weight[x] = x / root
```

---

### Step 4 — Answer Queries

For query (a, b):

- If either variable not present → return -1
- If roots different → return -1
- Else:

```
a / b = weight[a] / weight[b]
```

---

# # Complexity

Let N = number of variables
Let Q = number of queries

### Time Complexity

- Union operations: O(N α(N))
- Query operations: O(Q α(N))
- Overall: **O((N + Q) α(N))**

(α(N) is inverse Ackermann — practically constant)

### Space Complexity

- O(N)

---

# # Code

```cpp
class Solution {
private:
    unordered_map<string, string> parents;
    unordered_map<string, double> weight;

    string find(string x) {
        if (parents[x] != x) {
            string originalParent = parents[x];
            parents[x] = find(parents[x]);
            weight[x] = weight[x] * weight[originalParent];
        }
        return parents[x];
    }

    void unite(string a, string b, double value) {
        if (!parents.count(a)) {
            parents[a] = a;
            weight[a] = 1;
        }

        if (!parents.count(b)) {
            parents[b] = b;
            weight[b] = 1;
        }

        string rootA = find(a);
        string rootB = find(b);

        if (rootA != rootB) {
            parents[rootA] = rootB;
            weight[rootA] = value * (weight[b] / weight[a]);
        }
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {

        for (int i = 0; i < equations.size(); i++) {
            unite(equations[i][0], equations[i][1], values[i]);
        }

        vector<double> res;

        for (auto &q : queries) {
            string a = q[0], b = q[1];

            if (!parents.count(a) || !parents.count(b)) {
                res.push_back(-1.0);
            }
            else if (find(a) != find(b)) {
                res.push_back(-1.0);
            }
            else {
                res.push_back(weight[a] / weight[b]);
            }
        }

        return res;
    }
};
```

---

# 🔍 Dry Run Example

## Input

```
equations = [["a","b"],["b","c"],["ab","bc"]]
values    = [4.0,1.0,3.25]
queries   = [["a","c"],["b","a"],["c","c"],["ab","a"],["d","d"]]
```

---

## After Processing Equations

### Equation 1: a / b = 4

```
a → b
weight[a] = 4
```

### Equation 2: b / c = 1

```
a → b → c
weight[b] = 1
```

### Equation 3: ab / bc = 3.25

Separate component:

```
ab → bc
weight[ab] = 3.25
```

---

## Final Parent Structure (after path compression)

```
a  → c
b  → c
c  → c
ab → bc
bc → bc
```

Weights:

```
weight[a]  = 4
weight[b]  = 1
weight[c]  = 1
weight[ab] = 3.25
weight[bc] = 1
```

---

## Query Results

### a / c

```
4 / 1 = 4
```

### b / a

```
1 / 4 = 0.25
```

### c / c

```
1
```

### ab / a

Different roots → -1

### d / d

Not present → -1

---

# ✅ Final Output

```
[4.0, 0.25, 1.0, -1.0, -1.0]
```

---

# 🔥 Final Understanding

This problem is:

> Connected Components + Ratio Algebra

Weighted Union-Find stores:

```
weight[x] = x / root
```

So any division inside the same component becomes a simple division of stored ratios.
