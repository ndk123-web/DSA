# 1483. Kth Ancestor of a Tree Node

## Intuition

We are given a tree and multiple queries:

```text
getKthAncestor(node, k)
```

A brute-force approach is:

```cpp
while (k-- > 0) {
    node = parent[node];
}
```

For each query we may move up `k` times.

### Problem

If:

```text
k = 100000
```

then one query alone can take:

```text
O(k)
```

which is too slow.

---

## Observation

Instead of storing only the direct parent, we can store ancestors at powers of 2.

For every node:

```text
dp[node][0] = 1-step ancestor
dp[node][1] = 2-step ancestor
dp[node][2] = 4-step ancestor
dp[node][3] = 8-step ancestor
...
```

### Example

Tree:

```text
        0
       / \
      1   2
     / \   \
    3   4   5
   /
  9
```

For node `9`:

```text
9 -> 3 -> 1 -> 0
```

Store:

```text
dp[9][0] = 3   (1 ancestor above)
dp[9][1] = 1   (2 ancestors above)
dp[9][2] = -1  (4 ancestors above doesn't exist)
```

Now we can jump multiple levels at once.

---

# DP Definition

Let:

```cpp
dp[node][j]
```

represent:

```text
2^j-th ancestor of node
```

Examples:

```text
dp[node][0] = 1-step ancestor
dp[node][1] = 2-step ancestor
dp[node][2] = 4-step ancestor
dp[node][3] = 8-step ancestor
```

---

# DP Transition

We already know:

```cpp
dp[node][0] = parent[node];
```

Now let's compute:

```cpp
dp[node][1]
```

which means:

```text
2-step ancestor
```

Example:

```text
9 -> 3 -> 1
```

So:

```cpp
dp[9][1] = dp[ dp[9][0] ][0]
          = dp[3][0]
          = 1
```

---

### General Formula

To get a `2^j` ancestor:

```text
2^j = 2^(j-1) + 2^(j-1)
```

Therefore:

```cpp
dp[node][j]
=
dp[
      dp[node][j-1]
  ][j-1]
```

Meaning:

1. Jump `2^(j-1)` ancestors.
2. From there jump another `2^(j-1)` ancestors.

Total:

```text
2^j ancestors
```

---

# Building the Table

First column:

```cpp
for (int node = 0; node < n; node++) {
    dp[node][0] = parent[node];
}
```

Remaining columns:

```cpp
for (int j = 1; j < LOG; j++) {

    for (int node = 0; node < n; node++) {

        if (dp[node][j - 1] != -1) {

            dp[node][j] =
                dp[ dp[node][j - 1] ][j - 1];
        }
    }
}
```

---

# Query Logic

Suppose:

```text
node = 9
k = 13
```

Binary:

```text
13 = 1101₂
```

Which means:

```text
13 = 8 + 4 + 1
```

Instead of moving up 13 times:

```text
parent
parent
parent
...
13 times
```

We can do:

```text
Jump 8 ancestors
Jump 4 ancestors
Jump 1 ancestor
```

using:

```text
dp[node][3]
dp[node][2]
dp[node][0]
```

---

## How Do We Know Which Jumps To Take?

Check every bit of `k`.

```cpp
for (int j = 0; j < LOG; j++) {

    if (k & (1LL << j)) {

        node = dp[node][j];

        if (node == -1)
            return -1;
    }
}
```

---

## Dry Run

### Query

```text
node = 9
k = 3
```

Binary:

```text
3 = 0011₂
```

Meaning:

```text
3 = 2 + 1
```

---

### j = 0

Bit is set.

Jump:

```cpp
node = dp[node][0];
```

```text
9 -> 3
```

Now:

```text
node = 3
```

---

### j = 1

Bit is set.

Jump:

```cpp
node = dp[node][1];
```

```text
3 -> 1 -> 0
```

Now:

```text
node = 0
```

---

### Remaining Bits

Not set.

Stop.

Answer:

```text
0
```

which is the 3rd ancestor of node 9.

---

# Why `LOG = ceil(log2(n)) + 1`?

Suppose:

```text
n = 100000
```

Maximum possible depth:

```text
99999
```

Need powers of 2 large enough to cover that depth.

```text
2^16 = 65536
2^17 = 131072
```

Therefore:

```cpp
LOG = ceil(log2(n)) + 1;
```

ensures we have enough columns.

---

# Code

```cpp
class TreeAncestor {
public:
    vector<vector<int>> dp;
    int LOG;

    TreeAncestor(int n, vector<int>& parent) {

        LOG = ceil(log2(n)) + 1;

        dp.resize(n, vector<int>(LOG, -1));

        // 2^0 ancestor (parent)
        for (int node = 0; node < n; node++) {
            dp[node][0] = parent[node];
        }

        // Build binary lifting table
        for (int j = 1; j < LOG; j++) {

            for (int node = 0; node < n; node++) {

                if (dp[node][j - 1] != -1) {

                    dp[node][j] =
                        dp[ dp[node][j - 1] ][j - 1];
                }
            }
        }
    }

    int getKthAncestor(int node, int k) {

        for (int j = 0; j < LOG; j++) {

            if (k & (1LL << j)) {

                node = dp[node][j];

                if (node == -1)
                    return -1;
            }
        }

        return node;
    }
};
```

# Complexity Analysis

### Preprocessing

Building DP table:

```text
N nodes
LOG columns
```

Time:

```text
O(N × LOG)
```

Space:

```text
O(N × LOG)
```

---

### Query

We check every bit of `k`.

Time:

```text
O(LOG)
```

---

# Complexity

| Operation   | Complexity |
| ----------- | ---------- |
| Build Table | O(N log N) |
| Query       | O(log N)   |
| Space       | O(N log N) |

## Key Idea

Instead of storing:

```text
1st ancestor
2nd ancestor
3rd ancestor
4th ancestor
...
```

we store:

```text
1
2
4
8
16
...
```

ancestor jumps.

Since every number can be represented in binary, we combine those jumps to reach any `k-th` ancestor in **O(log N)** time. 🚀
