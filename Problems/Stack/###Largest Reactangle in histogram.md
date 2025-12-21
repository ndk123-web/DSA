# 📊 Largest Rectangle in Histogram

---

## 📘 Problem Statement (In Simple Words)

You are given a histogram where:

* Each bar has a height `heights[i]`
* Width of each bar is `1`

You must find the **largest possible rectangle area** that can be formed using **contiguous bars**.

### Rectangle rules:

* **Width** = number of continuous bars
* **Height** = minimum height among those bars

```
area = height × width
```

---

## 🧠 Key Observation (Very Important)

> A rectangle can never be taller than the **smallest bar** in the selected range.

Tall bars are limited by **shorter bars** around them.

---

# 1️⃣ Brute Force Approach (O(n²))

### 💡 Idea

* Fix a starting index `i`
* Extend to the right using index `j`
* Keep track of the **minimum height** seen so far
* Compute area for every subarray `[i … j]`

---

### 💻 Code (With Short Comments)

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        int n = heights.size();

        for (int i = 0; i < n; i++) {
            int minVal = INT_MAX;  // minimum height in range [i..j]

            for (int j = i; j < n; j++) {
                minVal = min(minVal, heights[j]);
                int width = j - i + 1;
                int area = minVal * width;
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};
```

---

### 🧪 Example

```
heights = [7,1,7,2,2,4]
```

Segment `[7,2,2,4]` →

* width = 4
* min height = 2
* area = 2 × 4 = **8**

---

### ⏱️ Complexity

| Metric | Value   |
| ------ | ------- |
| Time   | O(n²) ❌ |
| Space  | O(1)    |

✅ Easy to understand
❌ Too slow for large inputs

---

# 2️⃣ Optimal Approach — Monotonic Increasing Stack (O(n))

### 💡 Core Idea

> **Treat every bar as the height of a rectangle** and find how far it can extend left and right.

* Stack stores **indices** of bars
* Heights at those indices are **strictly increasing**
* When a smaller bar is found → rectangles are finalized

---

## 🧱 What Stack Represents

* Stack holds indices of bars
* Order ensures: `heights[stack[0]] < heights[stack[1]] < ...`

Each bar waits until a **smaller bar appears**, which fixes its rectangle boundary.

---

### 💻 Code (With Short Comments)

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxArea = 0;
        stack<int> st;  // stores indices

        for (int i = 0; i <= n; i++) {
            // pop when current bar is smaller
            while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
                int height = heights[st.top()];
                st.pop();

                // width calculation
                int width = st.empty() ? i : i - st.top() - 1;

                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        return maxArea;
    }
};
```

---

## 🔑 Width Formula (Most Important Part)

When a bar at index `k` is popped:

* `i` → first smaller bar on the **right**
* `st.top()` → first smaller bar on the **left** (after pop)

```
width = right − left − 1
```

### Cases:

#### Case 1: Stack is empty

```
left = -1
width = i
```

#### Case 2: Stack not empty

```
width = i − st.top() − 1
```

---

## 🧠 Why This Works

* Each bar is pushed and popped **once**
* Rectangle area for a bar is computed **only when it cannot extend further**
* Ensures **linear time complexity**

---

## 🧪 Same Example Dry Insight

```
[7,1,7,2,2,4]
```

The maximum rectangle is formed by:

```
[7,2,2,4]
height = 2
width = 4
area = 8
```

---

## ⏱️ Complexity

| Metric | Value  |
| ------ | ------ |
| Time   | O(n) ✅ |
| Space  | O(n)   |

---

## 🧠 Final Mental Model (Lock This 🔒)

> **Each bar decides its rectangle only when a smaller bar blocks it**

---

## 📌 Summary Table

| Approach    | Time  | Space | Notes                     |
| ----------- | ----- | ----- | ------------------------- |
| Brute Force | O(n²) | O(1)  | Simple but slow           |
| Stack       | O(n)  | O(n)  | Optimal & interview-ready |

---
