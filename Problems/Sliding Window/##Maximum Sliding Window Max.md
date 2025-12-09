
---
# 📘 **Sliding Window Maximum — Brute → Better → Optimal**

Given an array `nums` and integer `k`, return the **maximum value in every sliding window of size k**.
---

# ## 🥉 1. Brute Force (Check max in each window)

### **Time: O(n · k)**

### **Space: O(1)**

### **Idea**

For every window `[i … i+k-1]`, loop inside and find the maximum.

### **Code**

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;

        for (int i = 0 ; i <= n - k; i++) {
            int currentMax = INT_MIN;
            for (int j = i ; j < i + k; j++) {
                currentMax = max(currentMax, nums[j]);
            }
            res.push_back(currentMax);
        }

        return res;
    }
};
```

### **Short Comment**

- Very slow; re-scans the entire window every time
- Good for understanding basics only

---

# ## 🥈 2. Better Approach — Max-Heap (Remove Out-of-Window)

### **Time: O(n log n)**

### **Space: O(n)**

### **Idea**

- Use a **max heap** storing `{value, index}`
- Push each element
- Before taking top, remove elements whose index is out of window

### **Code**

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int,int>> pq; // {value, index}
        vector<int> res;
        int n = nums.size();

        for (int right = 0; right < n; right++) {
            pq.push({nums[right], right});

            // window size reached
            if (right + 1 >= k) {
                // remove elements out of window
                while (!pq.empty() && pq.top().second <= right - k)
                    pq.pop();

                res.push_back(pq.top().first);
            }
        }

        return res;
    }
};
```

### **Short Comment**

- Faster than brute but still log operations
- Heap may contain many old values

---

# ## 🥇 3. Optimal — Monotonic Deque

### **Time: O(n)**

### **Space: O(k)**

### **Idea**

Use a **deque storing indices**

- Maintain elements in **decreasing order**
- Deque front always holds index of maximum for current window
- Before pushing new element:

  - Remove all elements smaller than it from back

- Remove front if it goes out of window

### **Code**

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;             // stores indices of useful elements
        int n = nums.size();
        vector<int> res(n - k + 1);
        int left = 0, right = 0;

        while (right < n) {

            // Remove smaller elements from the back
            while (!dq.empty() && nums[dq.back()] < nums[right])
                dq.pop_back();

            dq.push_back(right);

            // Remove element if it's out of the current window
            if (left > dq.front())
                dq.pop_front();

            // Once we have window size k, record answer
            if (right + 1 >= k) {
                res[left] = nums[dq.front()];
                left++;
            }

            right++;
        }

        return res;
    }
};
```

### **Short Comment**

- Best solution
- Every element added and removed at most once → O(n)
- Deque maintains a decreasing sequence of values

---

# ## 🏁 Summary Table

| Approach            | Time       | Space    | Notes            |
| ------------------- | ---------- | -------- | ---------------- |
| **Brute Force**     | O(nk)      | O(1)     | Very slow        |
| **Heap**            | O(n log n) | O(n)     | Faster but heavy |
| **Deque (Optimal)** | **O(n)**   | **O(k)** | Best method      |

---

# 🎯 Final Takeaway

Sliding Window Maximum is a classic problem:

- Brute → understand concept
- Heap → optimize selection
- Deque → pure linear-time performance

Deque method is standard for interviews and must be mastered.

---
