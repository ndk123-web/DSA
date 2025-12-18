# 📈 Online Stock Span (Monotonic Stack)

This repository contains an efficient solution to the **Online Stock Span** problem using a **monotonic stack**.



## 🧠 Problem Statement

We receive stock prices **one day at a time**.  
For each day, we need to calculate the **span** of the stock price.

### 👉 What is Span?
The span of today’s stock price is the **maximum number of consecutive days (including today)** going backwards such that:

```

past_price ≤ today_price

```

The moment we encounter a price **greater than today’s price**, the span stops.



## ✅ Example

**Input prices:**
```

[100, 80, 60, 70, 60, 75, 85]

```

**Output spans:**
```

[1, 1, 1, 2, 1, 4, 6]

```

Explanation for `75`:
- 75 ≥ 60 ✅
- 75 ≥ 70 ✅
- 75 ≥ 60 ✅
- 75 < 80 ❌ (stop)

Span = **4**



## 🚀 Key Insight

> We **do not search for larger prices** in the past.  
> We **remove all smaller or equal prices** because they are part of the span.

This allows us to avoid repeated comparisons and achieve optimal performance.



## 🧩 Approach (Monotonic Stack)

We use a stack that stores:
```

(price, span)

```

### Algorithm:
1. Initialize `span = 1` (today counts).
2. While the stack is not empty and:
```

stack.top().price ≤ current price

````
- Add `stack.top().span` to `span`
- Pop the stack
3. Push `(current price, span)` into the stack.
4. Return `span`.



## 💻 Implementation (C++)

```cpp
class StockSpanner {
private:
 stack<pair<int,int>> st; // {price, span}

public:
 StockSpanner() {}

 int next(int price) {
     int span = 1;

     while (!st.empty() && st.top().first <= price) {
         span += st.top().second;
         st.pop();
     }

     st.push({price, span});
     return span;
 }
};
````



## ⏱️ Time & Space Complexity

* **Time Complexity:**
  `O(1)` amortized per call
  (Each element is pushed and popped at most once)

* **Space Complexity:**
  `O(n)` for the stack



## 🎯 Why This Works

* Smaller prices in the past can **never block future spans**
* The stack always maintains a **strictly decreasing order of prices**
* This avoids redundant comparisons



## 📌 Summary

* Span = count of consecutive past days with price ≤ today
* Use a **monotonic decreasing stack**
* Efficient, clean, and interview-ready solution