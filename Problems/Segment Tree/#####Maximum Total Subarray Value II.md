# Intuition

A brute-force approach would generate all possible subarrays and compute:

```text
max(subarray) - min(subarray)
```

for each one.

However, an array of length `n` contains:

```text
n * (n + 1) / 2
```

subarrays, which is too large.

The key observation is that for a **fixed left boundary** `l`, the sequence:

```text
value(l, n-1)
value(l, n-2)
value(l, n-3)
...
value(l, l)
```

is always non-increasing.

Where:

```text
value(l, r) = max(nums[l..r]) - min(nums[l..r])
```

---

## Why is it non-increasing?

Suppose we compare:

```text
[l..r]
```

and

```text
[l..r-1]
```

The interval `[l..r]` contains every element of `[l..r-1]` plus one extra element.

Therefore:

```text
max(l,r) >= max(l,r-1)
min(l,r) <= min(l,r-1)
```

which implies:

```text
max(l,r) - min(l,r)
>=
max(l,r-1) - min(l,r-1)
```

So for every fixed `l`, we get a sorted chain:

```text
(l,n-1)
(l,n-2)
(l,n-3)
...
(l,l)
```

---

# Example

```text
nums = [4,2,5,1]
```

For:

```text
l = 0
```

```text
[0,3] = 4
[0,2] = 3
[0,1] = 2
[0,0] = 0
```

For:

```text
l = 1
```

```text
[1,3] = 4
[1,2] = 3
[1,1] = 0
```

For:

```text
l = 2
```

```text
[2,3] = 4
[2,2] = 0
```

These chains are already sorted in descending order.

---

# Heap Observation

Each fixed left boundary produces one sorted chain.

```text
Chain 0:
[0,3] -> [0,2] -> [0,1] -> [0,0]

Chain 1:
[1,3] -> [1,2] -> [1,1]

Chain 2:
[2,3] -> [2,2]

Chain 3:
[3,3]
```

Initially, we insert the first element of every chain into a max heap:

```text
(0,n-1)
(1,n-1)
(2,n-1)
...
```

The heap now contains the largest candidate from every chain.

---

# Heap Processing

When we pop:

```text
(l,r)
```

we add its value to the answer.

The next candidate from the same chain is:

```text
(l,r-1)
```

So we push:

```text
(l,r-1)
```

back into the heap.

This is exactly the same idea as:

```text
Merge K Sorted Lists
```

where after removing the current maximum element from a list, we reveal the next element from that list.

---

# Segment Tree

We frequently need:

```text
max(nums[l..r])
min(nums[l..r])
```

for arbitrary intervals.

A Segment Tree stores:

```text
maximum value in a range
minimum value in a range
```

allowing each query to be answered in:

```text
O(log n)
```

time.

Thus:

```text
value(l,r)
=
max(nums[l..r]) - min(nums[l..r])
```

can be computed efficiently.

---

# Algorithm

1. Build a Segment Tree storing range minimum and maximum.
2. For every left boundary `i`, push:

```text
(i, n-1)
```

into a max heap.
3. Repeat `k` times:

* Pop the largest value.
* Add it to the answer.
* Push `(l, r-1)` if it is a valid interval.

4. Return the accumulated answer.

---

# Complexity Analysis

Segment Tree Build:

```text
O(n)
```

Each Heap Operation:

```text
O(log n)
```

Each Segment Tree Query:

```text
O(log n)
```

We perform at most `k` extractions.

Total Complexity:

```text
O(n + k log n)
```

Space Complexity:

```text
O(n)
```

for the Segment Tree and Heap.

---

# Key Insight

Instead of generating all `O(n²)` subarrays, observe that for every fixed left boundary, subarray values form a sorted sequence.

This transforms the problem into:

```text
Find the top k values among n sorted chains.
```

which can be solved efficiently using a max heap and a Segment Tree.


```cpp
struct SegmentNode {
    int l, r;
    SegmentNode *left, *right;
    long long mx, mn;

    SegmentNode(int l, int r) {
        this->l = l;
        this->r = r;
        left = nullptr;
        right = nullptr;
    }

    ~SegmentNode() {
        delete left;
        delete right;
    }
};

class SegmentTree {
public:
    SegmentNode* root;
    vector<int> nums;

    SegmentTree(vector<int>& nums) {
        this->nums = nums;
        root = build(0, nums.size() - 1);
    }

    ~SegmentTree() { delete root; }

    SegmentNode* build(int l, int r) {

        SegmentNode* node = new SegmentNode(l, r);

        if (l >= r) {
            node->mx = nums[l];
            node->mn = nums[l];
            return node;
        }

        int m = l + (r - l) / 2;

        node->left = build(l, m);
        node->right = build(m + 1, r);

        node->mn = min(node->left->mn, node->right->mn);
        node->mx = max(node->left->mx, node->right->mx);

        return node;
    }

    pair<long long, long long> query(SegmentNode* node, int ql, int qr) {

        if (!node) {
            return {LLONG_MAX, LLONG_MIN};
        }

        // no overlap
        if (node->l > qr || node->r < ql) {
            return {LLONG_MAX, LLONG_MIN};
        }

        // complete overlap
        if (node->l >= ql && node->r <= qr) {
            return {node->mn, node->mx};
        }

        auto left = query(node->left, ql, qr);
        auto right = query(node->right, ql, qr);

        return {
            min(left.first, right.first), max(left.second, right.second)
        };
    }
};

class Solution {
public:

    /*
        inutiton is
        nums = 1,2,3,4,5,6
        idx  = 0,1,2,3,4,5

        1. assume [0-5] index
        
        observation:
            - when we fix left and decrease the right we see pattern 
            - left = 0, for each(right--) => (5,4,3,2,1,0)
            - left = 1, for each(right--) => (4,3,2,1,0)
            - left = 2, for each(right--) => (3,2,1,0)
        
        now see we need maximum one with distinct left,right

        1. we store the diff in heap for (left++ and right = fixed)
            - like (0-5) then (1,5) then (2,5) , (3,5), (4,5), (5,5)
            
            initial heap value diff = (5,4,3,2,1,0)

        2. now we see that decreasing sort from right one see 
            - always left to right is higher
            - meaning left = 0, right = n is higher 
            - now then here can be greater one 
                - (either previous heap values that we stored or current max idx , right - 1)
                - ex: (0-5) is current best now, now best (0-4) or (1-5)  
    */

    long long maxTotalValue(vector<int>& nums, int k) {
        priority_queue<array<long long, 3>> pq;
        SegmentTree* segment = new SegmentTree(nums);
        int n = nums.size();

        // store value (i to n - 1)
        for (int i = 0; i < n - 1; i++) {
            auto p = segment->query(segment->root, i, n - 1);

            pq.push({(p.second - p.first), i, n - 1});
        }

        long long res = 0;
        while (k-- && !pq.empty()) {

            auto v = pq.top();
            pq.pop();

            int l = v[1];
            int r = v[2];

            res = res + v[0];

            if (l < r - 1) {

                auto p = segment->query(segment->root, l, r - 1);

                pq.push({(p.second - p.first), l, r - 1});
            }
        }

        delete segment;
        return res;
    }
};
```