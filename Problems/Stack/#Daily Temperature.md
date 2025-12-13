
---

# 📘 **Daily Temperatures — Brute to Optimal**

Given an array `temperatures`, return an array `answer` such that:

> `answer[i]` = number of days you have to wait after day `i` to get a **warmer temperature**.
> If no future day exists, put `0`.

---

## 🧠 Core Observation

For each day `i`, we need to find the **next day `j > i`** such that:

```
temperatures[j] > temperatures[i]
```

This is a classic **Next Greater Element** type problem.

---

## 🥉 **Approach 1 — Brute Force (Extra Index Variable)**

### **Time:** `O(n²)`

### **Space:** `O(1)`

### **Idea**

- For every day `i`, check all future days `j`
- First day where temperature is higher → answer
- Uses an extra index variable `k` to fill result

### **Code**

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        int k = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] < nums[j]) {
                    res[k] = j - i;
                    break;
                }
            }
            k++;
        }

        return res;
    }
};
```

### **Comment**

- Works but inefficient
- Extra variable `k` unnecessary
- Re-checks same elements again and again

---

## 🥈 **Approach 2 — Cleaner Brute Force (Direct Indexing)**

### **Time:** `O(n²)`

### **Space:** `O(1)`

### **Idea**

- Same brute force logic
- Directly store answer at index `i`
- Cleaner and less error-prone than Approach 1

### **Code**

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] < nums[j]) {
                    res[i] = j - i;
                    break;
                }
            }
        }

        return res;
    }
};
```

### **Comment**

- Better brute-force version
- Still too slow for large input
- Time limit issues for big `n`

---

## 🥇 **Approach 3 — Optimal (Monotonic Stack)**

### **Time:** `O(n)`

### **Space:** `O(n)`

### **Key Idea**

Use a **monotonic decreasing stack**:

- Stack stores pairs `{temperature, index}`
- Stack maintains **decreasing temperatures**
- When a warmer temperature appears:

  - Pop all smaller temperatures
  - Calculate waiting days

Each index is pushed and popped **only once** → `O(n)`.

---

### **Why Monotonic Stack Works Here**

If today's temperature is higher than previous days:

- Those previous days finally found their answer
- No need to check them again in the future

---

### **Code**

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& nums) {
        vector<pair<int,int>> st;   // {temperature, index}
        int n = nums.size();
        vector<int> res(n, 0);

        for (int i = 0; i < n; i++) {

            // resolve all colder days
            while (!st.empty() && st.back().first < nums[i]) {
                res[st.back().second] = i - st.back().second;
                st.pop_back();
            }

            // push current day
            st.push_back({nums[i], i});
        }

        return res;
    }
};
```

---

## 🧪 Example Dry Run

Input:

```
[73, 74, 75, 71, 69, 72, 76, 73]
```

Output:

```
[1, 1, 4, 2, 1, 1, 0, 0]
```

Explanation:

- 73 → 74 (1 day)
- 75 → 76 (4 days)
- 76 → no warmer day → 0

---

## 🏁 **Comparison Summary**

| Approach            | Time     | Space    | Notes        |
| ------------------- | -------- | -------- | ------------ |
| Brute (with k)      | O(n²)    | O(1)     | Works, messy |
| Brute (clean)       | O(n²)    | O(1)     | Cleaner      |
| **Monotonic Stack** | **O(n)** | **O(n)** | Optimal      |

---

## 🎯 Final Takeaway

- This is a **classic monotonic stack problem**
- Pattern applies to:

  - Next Greater Element
  - Stock Span
  - Daily Temperatures
  - Histogram problems

> **Whenever you hear “next greater in future” → think MONOTONIC STACK**

---
