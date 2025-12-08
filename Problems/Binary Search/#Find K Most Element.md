---

# 📘 **Find K Closest Elements — Brute → Optimal**

You are given a **sorted array**, and you must return **k elements closest to x**,
following the rule:

1. Smaller absolute difference → closer
2. If tie → smaller value is closer
3. Final answer must be sorted.

---

# ## 🥉 1. Brute Force (Sort by distance) — O(n log n)

### **Idea**

- For every element, compute `abs(arr[i] - x)`.
- Store elements with their distance.
- Sort by (distance → value).
- Pick first `k` elements.
- Sort final answer again (because problem requires sorted order).

### **Code**

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<pair<int,int>> v;
        for (int num : arr) {
            v.push_back({abs(num - x), num}); // {distance, value}
        }

        sort(v.begin(), v.end(), [](auto &a, auto &b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first;
        });

        vector<int> res;
        for (int i = 0; i < k; i++) res.push_back(v[i].second);

        sort(res.begin(), res.end());
        return res;
    }
};
```

### **Pros**

- Easiest to understand
- Works for any type of comparison

### **Cons**

- Sorting entire array → **O(n log n)**
- Not optimal for large input

---

# ## 🥈 2. Better Approach — Max Heap (Size = k)

### **Time: O(n log k)**

### **Space: O(k)**

### **Idea**

- Use a **max heap** to store k closest elements.
- Heap stores pairs `{distance, value}`.
- If heap size > k → pop the farthest element.
- At the end, heap contains the k closest values.
- Extract values and sort final output.

### **Code**

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        priority_queue<pair<int,int>> pq; // {distance, value}

        for (int num : arr) {
            int dist = abs(num - x);

            pq.push({dist, num});     // push current element
            if (pq.size() > k)        // if >k, remove farthest
                pq.pop();
        }

        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }

        sort(res.begin(), res.end()); // final sorted output
        return res;
    }
};
```

### **Pros**

- Faster than brute when **k << n**
- Very intuitive using heap

### **Cons**

- Still not the optimal possible
- Requires extra memory

---

# ## 🥇 3. Optimal — Binary Search + Two Pointers

### **Time: O(log n + k)**

### **Space: O(1)**

This is the best method.

### **Idea**

1. Use **binary search (`lower_bound`)** to find where `x` would fit.
2. Put two pointers around that position:

   ```
   right = lower_bound(...)
   left = right - 1
   ```

3. Expand outward k times:

   - Choose the closer between `arr[left]` and `arr[right]`.
   - Move the chosen pointer.

4. Sort the final selected elements (or use range directly).

### **Code**

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int l = 0, r = n;

        // Find the first index >= x
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] < x)
                l = m + 1;
            else
                r = m;
        }

        // r is the insert position of x
        int left = r - 1;
        int right = r;

        vector<int> res;

        while (k--) {
            if (left < 0) {
                res.push_back(arr[right++]);
            }
            else if (right >= n) {
                res.push_back(arr[left--]);
            }
            else if (abs(arr[left] - x) <= abs(arr[right] - x)) {
                res.push_back(arr[left--]);
            }
            else {
                res.push_back(arr[right++]);
            }
        }

        sort(res.begin(), res.end());
        return res;
    }
};
```

### **Pros**

- Fastest
- Zero extra memory
- Uses sorted property fully

### **Cons**

- Harder to implement
- Needs correct pointer logic

---

# ## 🏁 Summary Table

| Approach                        | Time             | Space    | Notes            |
| ------------------------------- | ---------------- | -------- | ---------------- |
| **Brute Sort by Distance**      | O(n log n)       | O(n)     | Easiest but slow |
| **Max Heap (k size)**           | O(n log k)       | O(k)     | Good improvement |
| **Binary Search + Two Pointer** | **O(log n + k)** | **O(1)** | Best & optimal   |

---
