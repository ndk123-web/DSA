## Range Queries

### [Pattern-1 Foundation]
1. Range Sum Query Immutable (LeetCode 303)
   - Trick -> Use prefix sum array to answer range sum queries in O(1) time after O(n) preprocessing., prefix[R] - prefix[L-1]

   1.  Segment Tree Approach
```cpp
class NumArray {
public:
    vector<long long> segment;
    long long res = 0;
    int N;

    NumArray(vector<int>& nums) {
        N = nums.size();
        segment.resize(4*N, 0);

        build(nums, 1, 0, N - 1);
    }

    void build(vector<int>& nums, int node, int st, int end) {
        if (st == end) {
            segment[node] = nums[st];
            return;
        }

        int mid = st + (end - st) / 2;
        build(nums, 2 * node, st, mid);
        build(nums, 2 * node + 1, mid + 1, end);

        segment[node] = segment[node * 2] + segment[node * 2 + 1];
    }

    int query(int node, int ql, int qr, int l, int r) {
        if (l > qr || r < ql)
            return 0;

        if (l >= ql && r <= qr)
            return segment[node];

        int mid = l + (r - l) / 2;
        return query(node * 2, ql, qr, l, mid) +
               query(node * 2 + 1, ql, qr, mid + 1, r);
    }

    int sumRange(int left, int right) {
        return query(1, left, right, 0, N - 1);
    }
};
```

   2. Fenwick Tree Approach / Binary Indexed Tree Approach
```cpp
class NumArray {
public:
    vector<int> fenwick;

    void add(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int idx = i + 1;
            while (idx <= nums.size()) {
                fenwick[idx] += nums[i];
                idx = idx + (idx & -idx);
            }
        }
    }

    int query(int q) {
        int sum = 0;
        q++;
        while (q > 0) {
            sum += fenwick[q];
            q = q - (q & -q);
        }

        return sum;
    }

    NumArray(vector<int>& nums) {
        fenwick.resize(nums.size() + 1, 0);
        add(nums);
    }

    int sumRange(int left, int right) {
        
        if (left == 0)
            return query(right);

        return query(right) - query(left - 1);
    }
};
```

2. Range Sum Query Mutable (LeetCode 307)
   - Trick -> Use Binary Indexed Tree (Fenwick Tree) or Segment Tree to answer range sum queries and update values in O(log n) time.
    i. Segment Tree Approach
```cpp
class NumArray {
public:
    int N;
    vector<long long> segment;
    vector<int> nums;

    NumArray(vector<int>& nums) {
        N = nums.size();
        segment.resize(4*N, 0);

        this->nums = nums;

        build(nums, 1, 0, N - 1);
    }

    void build(vector<int>& nums, int node, int l, int r) {
        if (l == r) {
            segment[node] = nums[l];
            return;
        }

        int mid = l + (r - l) / 2;
        build(nums, 2 * node, l, mid);
        build(nums, 2 * node + 1, mid + 1, r);

        segment[node] = segment[2 * node] + segment[2 * node + 1];
        return;
    }

    void updateSeg(int l, int r, int node, int idx, int val) {
        if (l == r) {
            segment[node] = val;
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid)
            updateSeg(l, mid, node * 2, idx, val);

        else
            updateSeg(mid + 1, r, node * 2 + 1, idx, val);

        segment[node] = segment[node * 2] + segment[node * 2 + 1];
        return;
    }

    void update(int index, int val) { updateSeg(0, N - 1, 1, index, val); }

    int query(int node, int l, int r, int ql, int qr) {
        if (l > qr || r < ql)
            return 0;

        if (l >= ql && r <= qr)
            return segment[node];

        int mid = l + (r - l) / 2;
        return query(node * 2, l, mid, ql, qr) +
               query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    int sumRange(int left, int right) {
        return query(1, 0, N - 1, left, right);
    }
};
```
    ii. Fenwick Tree Approach
```cpp
class NumArray {
public:
    vector<int> fenwick;
    vector<int> nums;
    int N = nums.size();

    NumArray(vector<int>& nums) {
        N = nums.size();
        fenwick.resize(N + 1, 0);
        this->nums = nums;

        build();
    }

    void build() {
        for (int i = 0; i < N; i++) {
            int idx = i + 1;

            while (idx <= N) {
                fenwick[idx] += nums[i];
                idx += (idx & -idx);
            }
        }
    }

    void updateFenwick(int idx, int val) {
        long long diff = val - nums[idx];
        nums[idx] = val;
        
        idx += 1;
        while (idx <= N) {
            fenwick[idx] += diff;
            idx += (idx & -idx);
        }
    }

    int query(int q) {
        q+=1;
        long long sum = 0;
        while (q > 0) {
            sum += fenwick[q];
            q -= (q & -q);
        }

        return sum;
    }

    void update(int index, int val) {
        updateFenwick(index, val);
    }

    int sumRange(int left, int right) {
        if (left == 0)
            return query(right);

        return query(right) - query(left - 1);
    }
};
```

### [Pattern-2 Compressed + Fenwick Tree]
3. Inversion Count in an Array (LeetCode 315)
    - Trick-> Use Fenwick tree , rank the elements and then use log(n) time to count inversion and update the tree
    - we can also use merge sort though it will take O(nlogn) time and O(n) space 
```cpp
class Solution {
public:
    vector<int> fenwick;
    unordered_map<int,int> mapp;
    vector<int> temp;

    // count less than or equal to q elements in the fenwick tree
    int query(int q) {
        int sum = 0;
        while (q > 0) {
            sum += fenwick[q];
            q = q - (q & -q);
        }

        return sum;
    }

    // update the fenwick tree with the rank of the element
    void update(int rank) {
        while (rank < fenwick.size()) {
            fenwick[rank]++;
            rank = rank + (rank & -rank);
        }
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        fenwick.resize(n + 1, 0);

        temp = nums;

        // rank it
        sort(temp.begin(), temp.end());
        for (int i = 0; i < n; i++) 
            mapp[temp[i]] = i + 1;
        
        // N (LogN + LogN) = N * 2LogN
        for (int i = n - 1; i >= 0; i--) {
            int rank = mapp[nums[i]];
            int cnt = 0;

            cnt += query(rank - 1);
            update(rank);

            res[i] = cnt;
        }

        return res;
    }
};
```

4. Reverse Pairs (LeetCode 493)
    - Trick-> Use Fenwick tree , rank the elements and then use log(n) time to count reverse pairs and update the tree
    - we can also use merge sort though it will take O(nlogn) time and O(n) space 
```cpp
class Solution {
public:
    unordered_map<long long, int> mapp;
    vector<long long> temp;
    vector<int> fenwick;

    int query(int q) {
        long long sum = 0;
        while (q > 0) {
            sum += fenwick[q];
            q -= (q & -q);
        }
        return sum;
    }

    void update(long long idx) {
        while (idx < fenwick.size()) {
            fenwick[idx]++;
            idx += (idx & -idx);
        }
    }

    int reversePairs(vector<int>& nums) {
        /*
            2 4 3 5 1

            1. 2 4 3 5 1,  4 8 6 10 2
            2. rank them after sorting
            3.

            Rank => 1 2 2 3 4 4 5 6 8 10
                =>  1 2 3 4 5 6 7 8 9 10

            fenwick => 0 0 1 0 0 0 0 0 0 0 0
                    => 0 1 2 3 4 5 6 7 8 9 10

            i = 1: rank = 2*1 = 2
        */

        // add num as well as 2*num to the temp array
        for (int& num : nums) {
            temp.push_back(num);
            temp.push_back(num * 2LL);
        }

        // rank them
        sort(temp.begin(), temp.end());
        
        // map the rank to the original number
        for (int i = 0; i < temp.size(); i++)
            mapp[temp[i]] = i + 1;

        // resize the fenwick tree to the size of the temp array
        fenwick.resize(temp.size() + 1, 0);
        
        int cnt = 0;
        for (int i = nums.size() - 1; i >= 0; i--) {
            int rank = mapp[nums[i]];

            // count the number of elements less than 2*num in the fenwick tree
            cnt += query(rank - 1);

            // update the fenwick tree with the rank of 2*num
            update(mapp[2LL * nums[i]]);
        }

        return cnt;
    }
};
```