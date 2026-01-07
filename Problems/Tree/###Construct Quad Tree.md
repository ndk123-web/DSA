# Construct Quad Tree from Binary Grid (C++)

## Problem Statement

You are given an `n × n` binary grid (`0` or `1`).
You must construct a **Quad Tree** that represents this grid.

Each Quad-Tree node represents a **square sub-grid** and has:

- `isLeaf` → whether the square is uniform
- `val` → value of the square (only meaningful if `isLeaf = true`)
- 4 children:
  `topLeft`, `topRight`, `bottomLeft`, `bottomRight`

---

## Core Concept (Non-Negotiable)

> **Quad Tree node = one square area of the grid**

Rules:

1. If the area is **uniform** (all `0` or all `1`)
   → create a **leaf node**
2. If the area is **mixed**
   → split into **4 equal squares** and recurse

You **do NOT always go till 1×1**.
You stop **as soon as the area becomes uniform**.

---

# Solution 1 — _Check First, Then Divide_

### Idea

- First check if the current `n × n` area is uniform
- If yes → make leaf
- Else → divide into 4 parts and recurse

### Code

```cpp
class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        return dfs(grid, grid.size(), 0, 0);
    }

private:
    Node* dfs(vector<vector<int>>& grid, int n, int r, int c) {
        bool allSame = true;

        for (int i = 0; i < n && allSame; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[r][c] != grid[r + i][c + j]) {
                    allSame = false;
                    break;
                }
            }
        }

        if (allSame) {
            return new Node(grid[r][c] == 1, true);
        }

        int mid = n / 2;
        Node* topLeft = dfs(grid, mid, r, c);
        Node* topRight = dfs(grid, mid, r, c + mid);
        Node* bottomLeft = dfs(grid, mid, r + mid, c);
        Node* bottomRight = dfs(grid, mid, r + mid, c + mid);

        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }
};
```

### How It Works

- Explicitly scans the grid to detect uniformity
- Stops early when possible (good for large uniform blocks)

### Pros / Cons

✅ Very intuitive
❌ Repeated scanning → slower in worst case

---

# Solution 2 — _Divide First, Then Merge_

### Idea

- Always divide until size becomes `1×1`
- Build children first
- **Merge back** if all 4 children are uniform and same value

This is **bottom-up construction**.

### Code

```cpp
class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        return dfs(grid, grid.size(), 0, 0);
    }

private:
    Node* dfs(vector<vector<int>>& grid, int n, int r, int c) {
        if (n == 1) {
            return new Node(grid[r][c] == 1, true);
        }

        int mid = n / 2;
        Node* topLeft = dfs(grid, mid, r, c);
        Node* topRight = dfs(grid, mid, r, c + mid);
        Node* bottomLeft = dfs(grid, mid, r + mid, c);
        Node* bottomRight = dfs(grid, mid, r + mid, c + mid);

        if (topLeft->isLeaf && topRight->isLeaf &&
            bottomLeft->isLeaf && bottomRight->isLeaf &&
            topLeft->val == topRight->val &&
            topLeft->val == bottomLeft->val &&
            topLeft->val == bottomRight->val) {
            return new Node(topLeft->val, true);
        }

        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }
};
```

### Merge Logic (IMPORTANT)

> Merge only if:

- All 4 children are **leaf**
- All have **same value**

Then parent becomes a leaf.

### Pros / Cons

✅ No grid scanning
❌ Always goes down to 1×1 before merging

---

# Solution 3 — _Optimized with Shared Leaf Nodes (Flyweight)_

### Idea

Same as Solution 2, but:

- **Reuse a single node for all `0` leaves**
- **Reuse a single node for all `1` leaves**

Leaf nodes are **immutable**, so sharing is safe.

### Code

```cpp
class Solution {
private:
    Node* falseLeaf = new Node(false, true); // all 0s
    Node* trueLeaf  = new Node(true, true);  // all 1s

public:
    Node* construct(vector<vector<int>>& grid) {
        return dfs(grid, grid.size(), 0, 0);
    }

    Node* dfs(vector<vector<int>>& grid, int n, int r, int c) {
        if (n == 1)
            return grid[r][c] == 1 ? trueLeaf : falseLeaf;

        n /= 2;
        Node* topLeft = dfs(grid, n, r, c);
        Node* topRight = dfs(grid, n, r, c + n);
        Node* bottomLeft = dfs(grid, n, r + n, c);
        Node* bottomRight = dfs(grid, n, r + n, c + n);

        if (topLeft->isLeaf && topRight->isLeaf &&
            bottomLeft->isLeaf && bottomRight->isLeaf &&
            topLeft->val == topRight->val &&
            topLeft->val == bottomLeft->val &&
            topLeft->val == bottomRight->val) {
            return topLeft; // reuse shared leaf
        }

        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }
};
```

### Why Sharing Is Safe

- Leaf nodes are **read-only**
- No child pointers
- No mutation after creation

This is a classic **Flyweight Pattern**.

### Pros / Cons

✅ Lowest memory usage
✅ Fast merging
❌ Slightly harder to reason initially

---

# Comparison Summary

| Solution | Strategy               | Extra Scan | Memory     | Difficulty |
| -------- | ---------------------- | ---------- | ---------- | ---------- |
| 1        | Check → Divide         | Yes        | Medium     | Easy       |
| 2        | Divide → Merge         | No         | Medium     | Medium     |
| 3        | Divide → Merge + Share | No         | **Lowest** | Hard       |

---

# Time & Space Complexity

### Time

All solutions:

```
O(N²)
```

Every cell contributes once.

### Space

- Solution 1 & 2 → `O(number of nodes)`
- Solution 3 → **Optimized**, minimal leaf nodes

---

# Final Mental Model (Lock This)

> **Quad Tree = recursively split grid into squares
> Stop splitting when square becomes uniform
> Parent represents a larger square, child a smaller square**
