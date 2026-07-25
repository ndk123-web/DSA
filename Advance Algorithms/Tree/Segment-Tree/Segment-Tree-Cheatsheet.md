# Segment Tree - Complete Cheatsheet

## 🎯 Top Links
- **Used For**: Range queries + point/range updates on dynamic arrays
- **Time Complexity**: O(log n) per operation
- **Build Time**: O(n)
- **Space Complexity**: O(n) array-based, O(n) pointer-based
- **Key Advantage**: Handles ANY associative operation (sum, max, min, GCD, etc.)

---

## 1. WHAT IS SEGMENT TREE?

A **Segment Tree** is a binary tree data structure that:
- Divides array into segments recursively
- Each node stores aggregate (sum, max, min, etc.) of its range
- Enables O(log n) range queries and point updates
- Can be extended to support range updates with lazy propagation

**Key Insight**: Hierarchical decomposition of array enables fast queries by combining pre-computed ranges.

---

## 2. WHY USE SEGMENT TREE?

### Comparison Table

| Scenario        | Array | Fenwick    | Segment Tree |
| --------------- | ----- | ---------- | ------------ |
| Range Sum Query | O(n)  | O(log n)   | O(log n)     |
| Point Update    | O(1)  | O(log n)   | O(log n)     |
| Range Update    | O(n)  | O(n log n) | O(log n)*    |
| Range Min/Max   | O(n)  | ❌          | O(log n)     |
| Range GCD/LCM   | O(n)  | ❌          | O(log n)     |

*With lazy propagation

### Use Cases
✅ Any range query problem (sum, min, max, GCD, etc.)
✅ Dynamic updates while answering queries
✅ Range updates needed (lazy propagation)
✅ Complex aggregate functions

---

## 3. HOW IT WORKS

### Tree Structure (Array-Based)

```
Array: [1, 3, 5, 7]

Tree visualization (1-indexed):
               [1,16]
              /      \
          [1,8]       [9,16]
         /     \      /     \
      [1,4]  [5,8]  [9,12] [13,16]
      /  \    /  \   /  \    /   \
   [1,2][3,4][5,6][7,8]...

Values at nodes (for sum):
           16
          /  \
        4     12
       / \    /  \
      1  3   5+7  0
      |  |   |
      1  3   5  7
```

### Implementation Styles

**1. Array-Based (Implicit tree)**
```cpp
// Tree stored in array
// For node at index i:
//   left child:  2*i
//   right child: 2*i+1
//   parent:      i/2

vector<int> tree(4*n);
```

**2. Pointer-Based (Explicit tree)**
```cpp
// Tree using pointers
struct SegmentNode {
    int l, r, val;
    SegmentNode *left, *right;
};
```

---

## 4. CORE OPERATIONS

### A. BUILD (Tree Construction)

**Logic**: Recursively split range in half until single elements

```cpp
// Array-based
void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2*node, l, mid);        // left child
    build(2*node+1, mid+1, r);    // right child
    tree[node] = tree[2*node] + tree[2*node+1];  // combine
}
```

**Pointer-based** (from attachment):
```cpp
SegmentNode* build(int l, int r) {
    SegmentNode* node = new SegmentNode(l, r);
    
    if (l == r) {
        node->val = arr[l];
        return node;
    }
    
    int mid = l + (r - l) / 2;
    node->left = build(l, mid);
    node->right = build(mid + 1, r);
    node->val = node->left->val + node->right->val;  // merge
    return node;
}
```

**Time**: O(n) | **Space**: O(n)

---

### B. QUERY (Range Query)

**Logic**: If range overlaps completely, return node value. If partial, recurse on children.

```cpp
// Array-based
int query(int node, int l, int r, int ql, int qr) {
    // no overlap
    if (r < ql || l > qr) 
        return 0;  // or INT_MIN for max
    
    // complete overlap
    if (l >= ql && r <= qr) 
        return tree[node];
    
    // partial overlap - recurse
    int mid = l + (r - l) / 2;
    int lval = query(2*node, l, mid, ql, qr);
    int rval = query(2*node+1, mid+1, r, ql, qr);
    return lval + rval;  // combine operation
}
```

**Pointer-based** (from attachment):
```cpp
int query(SegmentNode* node, int ql, int qr) {
    if (!node) return 0;
    
    int l = node->l, r = node->r;
    
    // no overlap
    if (l > qr || r < ql) 
        return 0;
    
    // complete overlap
    if (l >= ql && r <= qr) 
        return node->val;
    
    // partial overlap
    int lval = query(node->left, ql, qr);
    int rval = query(node->right, ql, qr);
    return lval + rval;
}
```

**Time**: O(log n)

---

### C. UPDATE (Point Update)

**Logic**: Navigate to leaf, update value, propagate changes upward

```cpp
// Array-based
void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }
    
    int mid = l + (r - l) / 2;
    if (idx <= mid)
        update(2*node, l, mid, idx, val);
    else
        update(2*node+1, mid+1, r, idx, val);
    
    // Update parent
    tree[node] = tree[2*node] + tree[2*node+1];
}
```

**Pointer-based**:
```cpp
void update(SegmentNode* node, int idx, int val) {
    if (node->l == node->r) {
        node->val = val;
        return;
    }
    
    int mid = node->l + (node->r - node->l) / 2;
    if (idx <= mid)
        update(node->left, idx, val);
    else
        update(node->right, idx, val);
    
    node->val = node->left->val + node->right->val;
}
```

**Time**: O(log n)

---

### D. RANGE UPDATE (with Lazy Propagation)

**Logic**: Mark nodes for update, defer actual updates until needed

```cpp
struct SegmentNode {
    int l, r, val, lazy;
    SegmentNode *left, *right;
};

void push(SegmentNode* node) {
    if (node->lazy == 0) return;
    
    node->val += (node->r - node->l + 1) * node->lazy;
    
    if (node->left) node->left->lazy += node->lazy;
    if (node->right) node->right->lazy += node->lazy;
    
    node->lazy = 0;
}

void rangeUpdate(SegmentNode* node, int ql, int qr, int val) {
    // complete overlap
    if (node->l >= ql && node->r <= qr) {
        node->lazy += val;
        push(node);
        return;
    }
    
    // no overlap
    if (node->r < ql || node->l > qr) 
        return;
    
    // partial overlap
    push(node);
    rangeUpdate(node->left, ql, qr, val);
    rangeUpdate(node->right, ql, qr, val);
    
    node->val = node->left->val + node->right->val;
}
```

**Time**: O(log n) | **Space**: O(n) extra for lazy flags

---

## 5. DIFFERENT OPERATIONS

### Sum Queries
```cpp
// Combine: addition
tree[node] = tree[2*node] + tree[2*node+1];
// Base case: return 0 for no overlap
```

### Max Queries (from attachment)
```cpp
// Combine: maximum
node->val = max(node->left->val, node->right->val);
// Base case: return INT_MIN for no overlap
```

### Min Queries
```cpp
// Combine: minimum
tree[node] = min(tree[2*node], tree[2*node+1]);
// Base case: return INT_MAX for no overlap
```

### GCD/LCM Queries
```cpp
// GCD
tree[node] = __gcd(tree[2*node], tree[2*node+1]);
// Base case: return 0 for no overlap

// LCM
tree[node] = (tree[2*node] / __gcd(tree[2*node], tree[2*node+1])) * tree[2*node+1];
```

---

## 6. COMPLETE IMPLEMENTATION TEMPLATE

### Array-Based (Most Common)
```cpp
class SegmentTree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;
    
    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid)
            update(2*node, l, mid, idx, val);
        else
            update(2*node+1, mid+1, r, idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    
    int query(int node, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return 0;
        if (l >= ql && r <= qr) return tree[node];
        
        int mid = l + (r - l) / 2;
        int lval = query(2*node, l, mid, ql, qr);
        int rval = query(2*node+1, mid+1, r, ql, qr);
        return lval + rval;
    }
    
public:
    SegmentTree(vector<int> arr) {
        this->arr = arr;
        this->n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }
    
    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }
    
    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
```

### Pointer-Based (from attachment)
```cpp
struct SegmentNode {
    int l, r, val;
    SegmentNode *left, *right;
    
    SegmentNode(int l, int r) : l(l), r(r), val(0), left(nullptr), right(nullptr) {}
    ~SegmentNode() { delete left; delete right; }
};

class SegmentTree {
private:
    SegmentNode *root;
    vector<int> arr;
    
    SegmentNode* build(int l, int r) {
        SegmentNode* node = new SegmentNode(l, r);
        if (l == r) {
            node->val = arr[l];
            return node;
        }
        int mid = l + (r - l) / 2;
        node->left = build(l, mid);
        node->right = build(mid+1, r);
        node->val = node->left->val + node->right->val;
        return node;
    }
    
public:
    SegmentTree(vector<int> arr) : arr(arr) {
        root = build(0, arr.size() - 1);
    }
    
    ~SegmentTree() { delete root; }
};
```

---

## 7. COMPLEXITY ANALYSIS

| Operation     | Build | Query    | Update   | Range Update |
| ------------- | ----- | -------- | -------- | ------------ |
| Array-Based   | O(n)  | O(log n) | O(log n) | O(log n)*    |
| Pointer-Based | O(n)  | O(log n) | O(log n) | O(log n)*    |
| Space         | O(n)  | -        | -        | O(n)         |

*With lazy propagation

---

## 8. KEY DESIGN DECISIONS

| Choice               | Pros                          | Cons                  |
| -------------------- | ----------------------------- | --------------------- |
| **Array-Based**      | Cache friendly, less overhead | Fixed max size needed |
| **Pointer-Based**    | Dynamic, flexible             | More memory overhead  |
| **Lazy Propagation** | O(log n) range update         | Complex to implement  |
| **Iterative Build**  | No recursion depth issues     | Harder to understand  |
| **Recursive Build**  | Intuitive, cleaner code       | Stack depth O(log n)  |

---

## 9. COMMON APPLICATIONS

### 🔴 **Range Sum Query with Updates**
Query sum in range + update point

### 🔴 **Range Minimum/Maximum Query**
Find min/max in range efficiently

### 🔴 **Range GCD/LCM Query**
Compute GCD of range elements

### 🔴 **Range Update + Range Query**
Add value to range, then query (lazy propagation)

### 🔴 **Inversion Count**
Using coordinate compression and segment tree

### 🔴 **Skyline Problem**
Using segment tree with coordinate compression

### 🔴 **Count of Distinct Elements in Range**
Using segment tree with hashing

---

## 10. SEGMENT TREE vs FENWICK TREE

| Feature        | Segment Tree       | Fenwick Tree |
| -------------- | ------------------ | ------------ |
| Range Query    | ✅ Any operation    | ✅ Only sum   |
| Point Update   | O(log n)           | O(log n)     |
| Range Update   | O(log n)*          | O(n log n)   |
| Space          | O(n)               | O(n)         |
| Implementation | More complex       | Simpler      |
| Binary Ops     | Sum, Max, Min, GCD | Sum only     |

*With lazy propagation

---

## 11. INTERVIEW TIPS

✅ **Do**:
- Use array-based for speed if max size known
- Always handle edge cases: empty ranges, single elements
- Verify merge operation is correct (sum vs max vs gcd)
- Use 1-based indexing for array-based to simplify
- Practice lazy propagation thoroughly

❌ **Don't**:
- Mix up left/right child indices (2*i vs 2*i+1)
- Forget to update parent after child updates
- Use 0-based root for array-based (use index 1)
- Skip push() in lazy propagation
- Forget to handle the neutral element correctly

---

## 12. EDGE CASES TO HANDLE

```
1. Single element query: l == r case
2. Empty range: ql > qr 
3. No overlap: r < ql or l > qr
4. Query entire array: ql=0, qr=n-1
5. Query single element at boundaries
6. Update to same value (shouldn't matter)
7. Negative numbers in array
```

---

## 13. QUICK REFERENCE

```
Array-Based Indices:
- Node at i
- Left child: 2*i
- Right child: 2*i+1
- Parent: i/2
- Tree size: 4*n (worst case)

Pointer-Based:
- Each node stores l, r, val
- Recursively split: mid = l + (r-l)/2
- Build from [l..r]

Query Logic:
- No overlap: return neutral (0 for sum, INT_MIN for max)
- Complete overlap: return node->val
- Partial overlap: recurse on both children, merge

Update Logic:
- Navigate to leaf
- Update leaf value
- Backtrack and merge results
```

---

## 14. VISUAL EXAMPLE - Range Sum

```
Array: [1, 3, 5, 7]

Tree Structure:
             [16]         node 1
            /      \
        [4]          [12]    nodes 2,3
       /  \          /  \
     [1] [3]      [5]  [7]   nodes 4,5,6,7

Query(1, 3) = 3+5+7 = 15:
- At [16]: partial overlap with [1,4]
  - Query left [4] (nodes 0-1): partial
    - Query right [3]: complete overlap → return 3
  - Query right [12] (nodes 2-3): complete overlap → return 12
  - Return 3 + 12 = 15

Update(0, 10) - change arr[0] from 1 to 10:
- Navigate to leaf [1] at index 0
- Update: node->val = 10
- Backtrack: node->val = 10 + 3 = 13
- Backtrack: node->val = 13 + 12 = 25
```

---

## 15. LAZY PROPAGATION DEEP DIVE

**Problem**: Range updates are O(n) without optimization

**Solution**: Defer updates using lazy flags

```cpp
// Mark subtree for update, don't update recursively
if (range completely in [ql..qr]) {
    node->lazy += delta;  // Mark for later
    node->val += (node->r - node->l + 1) * delta;
    return;
}

// Push lazy value to children before using
void push(node) {
    if (node->lazy) {
        node->left->lazy += node->lazy;
        node->right->lazy += node->lazy;
        node->val += (r-l+1) * node->lazy;
        node->lazy = 0;
    }
}
```

**Time**: O(log n) per operation | **Space**: O(n) for lazy array

---

## 16. PRACTICE PROBLEMS

**Easy**:
- Range Sum Query - Immutable
- Range Sum Query - Mutable
- Range Maximum Query

**Medium**:
- Range Update Query - Add to Range
- Number of Visible People in a Queue
- Largest Rectangle in Histogram (with queries)

**Hard**:
- Skyline Problem
- Count of Smaller Numbers After Self (Inversion)
- Range Module
