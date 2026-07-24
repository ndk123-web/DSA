# Fenwick Tree (Binary Indexed Tree) - Complete Cheatsheet

## 🎯 Top Links
- **Also Known As**: Binary Indexed Tree (BIT)
- **Use When**: Frequent prefix sum queries + point updates needed
- **Time Complexity**: O(log n) per operation
- **Space Complexity**: O(n)

---

## 1. WHAT IS FENWICK TREE?

A **Fenwick Tree (BIT)** is a data structure that efficiently maintains cumulative frequency tables and allows you to:
- Update a single element in O(log n)
- Query prefix sum up to index i in O(log n)
- Calculate range sum in O(log n)

**Key Insight**: Uses binary representation to determine which nodes to update/query.

---

## 2. WHY USE FENWICK TREE?

| Problem Type                      | Naive        | Fenwick Tree  |
| --------------------------------- | ------------ | ------------- |
| Point update + Prefix sum         | O(n) or O(1) | O(log n) both |
| Multiple queries on dynamic array | O(n²)        | O(n log n)    |
| Inversion count                   | O(n²)        | O(n log n)    |

---

## 3. HOW IT WORKS

### 🔑 Core Concept: Binary Representation

The magic is in **idx & -idx** which isolates the rightmost set bit.

**Example**:
```
idx = 5 (binary: 101)
-idx = -5 (two's complement: ...11111011)
idx & -idx = 1 (rightmost bit)

idx = 6 (binary: 110)
-idx = -6 (two's complement: ...11111010)
idx & -idx = 2 (rightmost bit)
```

### Tree Structure

```
Array:     [1, 2, 3, 4, 5, 6]
Index (1): [1, 2, 3, 4, 5, 6]

BIT positions (what range each covers):
BIT[1] = sum of arr[1..1]       (1 element)
BIT[2] = sum of arr[1..2]       (2 elements)
BIT[3] = sum of arr[3..3]       (1 element)
BIT[4] = sum of arr[1..4]       (4 elements)
BIT[5] = sum of arr[5..5]       (1 element)
BIT[6] = sum of arr[5..6]       (2 elements)
```

---

## 4. OPERATIONS IN DETAIL

### A. UPDATE(index, value)

**Logic**: Add `value` to position, propagate upward using `idx + (idx & -idx)`

```cpp
void update(int idx, int value) {
    while (idx < fenwickTree.size()) {
        fenwickTree[idx] += value;
        idx = idx + (idx & -idx);  // Move to next position
    }
}
```

**Example**: Update index 3 by +5
```
idx=3: BIT[3] += 5
idx=3+(1)=4: BIT[4] += 5
idx=4+(4)=8: Stop (out of bounds)
```

---

### B. QUERY(index)

**Logic**: Sum from 1 to index by going backward using `q - (q & -q)`

```cpp
int query(int q) {
    int sum = 0;
    while (q > 0) {
        sum += fenwickTree[q];
        q = q - (q & -q);  // Move to previous position
    }
    return sum;
}
```

**Example**: Query up to index 5
```
q=5: sum += BIT[5]
q=5-1=4: sum += BIT[4]
q=4-4=0: Stop
Returns: BIT[5] + BIT[4]
```

---

### C. RANGE QUERY(L, R)

**Logic**: `query(R) - query(L-1)`

```cpp
int rangeQuery(int l, int r) {
    if (l == 0) return query(r);
    return query(r) - query(l - 1);
}
```

**Example**: Sum from index 2 to 5
```
rangeQuery(2, 5) = query(5) - query(1)
```

---

## 5. INITIALIZATION

```cpp
vector<int> arr = {1, 4, 6, 4, 3, 2};
vector<int> fenwickTree(arr.size() + 1, 0);

// Method 1: O(n log n)
for (int i = 0; i < arr.size(); i++) {
    update(i + 1, arr[i]);
}

// Method 2: O(n) - More optimal
for (int i = 1; i <= n; i++) {
    fenwickTree[i] += arr[i-1];
    int j = i + (i & -i);
    if (j <= n) fenwickTree[j] += fenwickTree[i];
}
```

---

## 6. KEY IMPLEMENTATION DETAILS

| Aspect            | Details                                |
| ----------------- | -------------------------------------- |
| **Indexing**      | Use 1-based indexing (index 0 unused)  |
| **Size**          | BIT size = n+1 (where n is array size) |
| **Rightmost Bit** | `x & -x` isolates it                   |
| **Next Index**    | `idx + (idx & -idx)` for update        |
| **Prev Index**    | `idx - (idx & -idx)` for query         |

---

## 7. COMPLETE CODE TEMPLATE

```cpp
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int size) {
        n = size;
        tree.resize(n + 1, 0);
    }

    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & (-idx);
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }

    int rangeQuery(int l, int r) {
        if (l == 0) return query(r);
        return query(r) - query(l - 1);
    }
};
```

---

## 8. COMMON APPLICATIONS

### 🔴 **Inversion Count**
Count pairs (i, j) where i < j but arr[i] > arr[j]

**Logic**: Process right to left, for each element query count of smaller elements already processed

### 🔴 **Range Sum Queries with Updates**
Maintain dynamic array and answer range sum queries efficiently

### 🔴 **Difference Array Operations**
Apply range increment in O(log n) using BIT

### 🔴 **Coordinate Compression**
When array values are large but count is small

---

## 9. COMPLEXITY ANALYSIS

```
Operation          Time       Space     Notes
─────────────────────────────────────────────
Build              O(n log n) O(n)      
Update             O(log n)   -         Single operation
Query              O(log n)   -         Single operation
Range Query        O(log n)   -         2 queries
All updates        O(n log n) -         n updates
All queries        O(n log n) -         n queries
```

---

## 10. INTERVIEW TIPS

✅ **Do**:
- Always use 1-based indexing
- Initialize tree with size n+1
- Use `idx & -idx` trick confidently
- Handle edge cases: L=0, R=n, single element

❌ **Don't**:
- Use 0-based indexing (confusing with BIT logic)
- Forget tree size = n+1
- Confuse update direction with query direction

---

## 11. SIMILAR DATA STRUCTURES

| Structure        | Strength                            | Weakness               |
| ---------------- | ----------------------------------- | ---------------------- |
| **Segment Tree** | More versatile (any associative op) | O(4n) space            |
| **Fenwick Tree** | Space efficient                     | Limited to prefix sums |
| **Naive Array**  | Simple                              | O(n) per operation     |
| **Square Root**  | Simple to implement                 | O(√n) ops              |

---

## 12. PRACTICE PROBLEMS

**Classic**:
- Count Inversions
- Range Sum Query - Mutable
- Prefix and Suffix Sums

**Advanced**:
- 2D Fenwick Tree
- Offline Range Sum with updates
- Dynamic range queries

---

## 13. QUICK REFERENCE

```
Key Formula: idx & -idx = rightmost set bit

Update Path: idx → idx + (idx & -idx) → ...
Query Path:  idx → idx - (idx & -idx) → ...

Why it works: Each node is responsible for a 
specific power of 2 range of elements
```

---

## Visual Example

```
Query path for idx=13:
13 (1101) - sum of arr[13]
12 (1100) - add arr[9..12]
8 (1000)  - add arr[1..8]
Return: arr[1..13]

Update path for idx=5:
5 (0101) - update arr[5]
6 (0110) - update range [5..6]
8 (1000) - update range [1..8]
```
