# 🍌 Koko Eating Bananas — Complete Explanation

---

## 🔹 Problem Recap

You are given:

- `piles[i]` → bananas in the `i`-th pile
- `h` → total hours available

Rules:

- Koko eats **only one pile per hour**
- She eats **at most `k` bananas per hour**
- If pile < `k`, she finishes it and **wastes remaining time**
- Goal: find the **minimum integer `k`** so all bananas are eaten within `h` hours

---

## 🔹 Core Observation (Very Important)

For a fixed eating speed `k`:

```
hours needed for one pile = ceil(pile / k)
```

Total hours:

```
total_hours = Σ ceil(piles[i] / k)
```

We must ensure:

```
total_hours ≤ h
```

---

# ✅ Solution 1: Brute Force (Correct but Slow)

### 🧠 Idea

- Try every `k` starting from `1`
- Calculate total hours
- Return first `k` that satisfies the condition

---

### 💻 Code (Brute Force)

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int k = 1;

        while (true) {
            int th = 0;
            for (int& pile : piles) {
                if (th > h) break;
                th += ceil((double)pile / k);
            }

            if (th <= h) return k;
            k++;
        }
    }
};
```

---

### ⚠️ Drawbacks

- Time Complexity: **O(maxPile × n)**
- Will **TLE** for large inputs
- Only good for understanding logic, **not production**

---

# 🔑 Important Concept: `ceil` Formula (New Learning)

### ❌ Wrong (integer division bug)

```cpp
ceil(pile / k)   // WRONG if both are int
```

Because:

- `pile / k` happens first → integer division
- Fraction lost before `ceil()`

---

### ✅ Correct Mathematical Identity

```
ceil(a / b) = (a + b - 1) / b
```

### ✅ Why it works

Example:

```
a = 25, b = 11
(25 + 11 - 1) / 11 = 35 / 11 = 3
```

This avoids floating point errors and is **industry standard**.

---

# ✅ Solution 2: Binary Search (Optimal & Interview Ready)

### 🧠 Why Binary Search Works

- `k` range is **monotonic**
- If a speed works → all higher speeds also work
- Search space:

  ```
  k ∈ [1, max(piles)]
  ```

---

### 💻 Code (Binary Search)

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        int res = 0;

        while (left <= right) {
            int k = left + (right - left) / 2;
            long long th = 0;

            for (auto& pile : piles) {
                th += (pile + k - 1) / k;   // ceil formula
            }

            if (th <= h) {
                res = k;
                right = k - 1;   // try smaller k
            } else {
                left = k + 1;    // need faster speed
            }
        }

        return res;
    }
};
```

---

### ⏱️ Complexity

| Approach      | Time Complexity     |
| ------------- | ------------------- |
| Brute Force   | O(maxPile × n)      |
| Binary Search | O(n log maxPile) ✅ |

---

## 🧠 Final Takeaways (Must Remember)

- **One pile per hour** → time is per pile
- Use:

  ```
  (pile + k - 1) / k
  ```

  instead of `ceil(pile / k)`

- Binary Search is the **expected solution**
- Brute force is only for understanding

---

## 🔥 Interview Line (You Can Say This)

> “Since required hours decreases monotonically as eating speed increases, we apply binary search on `k` between 1 and max pile size.”

---
