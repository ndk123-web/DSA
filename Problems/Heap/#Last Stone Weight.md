# 📘 Last Stone Weight

## Problem Summary

You are given a list of stone weights.

Rules:

1. Pick the **two heaviest stones**
2. Smash them:

   - If both weights are equal → both destroyed
   - Else → new stone with weight `(heavier - lighter)`

3. Insert the new stone back
4. Repeat until **at most one stone remains**

Return the weight of the last stone, or `0` if none remain.

---

## Key Insight (Why Heap Is Needed)

The problem **repeatedly asks for the two largest elements**.

This means:

- Order keeps changing after every smash
- One-pass or linear logic **cannot work**
- Sorting every time is too slow

👉 **Max-Heap (priority_queue)** is the perfect structure.

---

## Your Solution Code

```cpp
class Solution {
private:
    priority_queue<int> pq;

public:
    int lastStoneWeight(vector<int>& stones) {
        for (int& num : stones) {
            pq.push(num);
        }

        while (pq.size() != 1) {
            int ft = pq.top(); pq.pop();

            if (pq.size() == 1 && pq.top() == ft) return 0;

            int st = pq.top(); pq.pop();

            if (ft != st)
                pq.push(ft - st);
        }

        return pq.top();
    }
};
```

---

## How the Solution Works (Step-by-Step)

### 1️⃣ Build a Max-Heap

```cpp
for (int& num : stones)
    pq.push(num);
```

- `priority_queue<int>` in C++ is a **max-heap**
- `pq.top()` always gives the **largest stone**
- Heap internally rearranges elements automatically

---

### 2️⃣ Repeatedly Smash Stones

```cpp
while (pq.size() != 1)
```

We continue until:

- Only **one stone remains**, or
- No stone remains (handled implicitly)

---

### 3️⃣ Extract Two Heaviest Stones

```cpp
int ft = pq.top(); pq.pop();
int st = pq.top(); pq.pop();
```

- `ft` = heaviest stone
- `st` = second heaviest stone

This exactly matches the problem statement.

---

### 4️⃣ Handle Equal Stones Case

```cpp
if (pq.size() == 1 && pq.top() == ft) return 0;
```

Your intention here:

- If the last two stones are equal
- Both destroy each other
- Result is `0`

⚠️ This condition is **logically correct**, but **not required** (explained later).

---

### 5️⃣ Insert Remaining Stone (if any)

```cpp
if (ft != st)
    pq.push(ft - st);
```

- If stones are unequal
- Push the difference back into heap
- Heap reorders automatically

---

### 6️⃣ Final Answer

```cpp
return pq.top();
```

- If one stone remains → return its weight
- If none remain → `0` would already have been returned

---

## Dry Run Example

Input:

```
stones = [2,7,4,1,8,1]
```

Heap evolution:

```
[8,7,4,2,1,1]
8 & 7 → push 1 → [4,2,1,1,1]

4 & 2 → push 2 → [2,1,1,1]

2 & 1 → push 1 → [1,1,1]

1 & 1 → both destroyed → []
```

Output:

```
0
```

---

## Time & Space Complexity

### Time

- Building heap: `O(n)`
- Each pop/push: `O(log n)`
- At most `n` iterations

```
Overall: O(n log n)
```

### Space

- Heap stores at most `n` elements

```
O(n)
```

---

## What You Did Right ✅

- Used **max-heap correctly**
- Correctly modeled “two heaviest stones”
- Difference logic is accurate
- Handles duplicates naturally
- Matches problem constraints

---

## One Small Improvement (Important)

This check is **unnecessary**:

```cpp
if (pq.size() == 1 && pq.top() == ft) return 0;
```

Why?

Because this case is already handled naturally:

- If `ft == st`, you **don’t push anything**
- Heap size reduces correctly
- Final return will be `0` automatically

### Cleaner version of the loop:

```cpp
while (pq.size() > 1) {
    int ft = pq.top(); pq.pop();
    int st = pq.top(); pq.pop();

    if (ft != st)
        pq.push(ft - st);
}
return pq.empty() ? 0 : pq.top();
```

Same logic, fewer edge cases.

---

## Final Mental Model (Lock This In)

> **Heap problems are about maintaining priority dynamically, not about order.**

If a problem repeatedly says:

- “largest”
- “smallest”
- “top k”

👉 **Heap is the first thing you should think of.**
