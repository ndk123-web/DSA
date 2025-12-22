# 🧮 Integer Square Root (`mySqrt`) — Binary Search Explained

We are asked to compute:

> **The integer square root of `x`**
> i.e. **the largest integer `k` such that `k * k ≤ x`**

This is also known as:

```
floor(sqrt(x))
```

---

## ✅ Example Expectations

| x   | sqrt(x) | Integer Answer |
| --- | ------- | -------------- |
| 4   | 2       | 2              |
| 8   | 2.82    | 2              |
| 15  | 3.87    | 3 ❌ (not 4)   |
| 16  | 4       | 4              |

👉 **For `x = 15`, answer is `3`, NOT `4`**
Because `4 × 4 = 16 > 15`.

---

## 💻 Correct Code (With Explanation)

```cpp
class Solution {
public:
    int mySqrt(int x) {
        int left = 0;
        int right = x;
        int res = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if ((long long)mid * mid > x) {
                right = mid - 1;
            }
            else if ((long long)mid * mid < x) {
                res = mid;          // mid is a valid answer
                left = mid + 1;     // try to find a larger valid one
            }
            else {
                return mid;         // perfect square found
            }
        }
        return res;
    }
};
```

---

# ❓ Doubt 1: Why `(long long)` is required?

### ❌ What goes wrong without `(long long)`?

`mid` is an `int`.
So:

```cpp
mid * mid   // int × int → int
```

This can **overflow**.

### 🚨 Overflow Example

```cpp
x = 2147483647 (INT_MAX)
mid = 46341
```

Math:

```
46341 × 46341 = 2147488281 (greater than INT_MAX)
```

But in `int`:

```
overflow → garbage / negative value
```

➡️ Comparison becomes WRONG
➡️ Binary search goes in the wrong direction

---

## ✅ Why `(long long)` fixes it

```cpp
(long long) mid * mid
```

Steps internally:

1. `mid` converted to `long long`
2. multiplication done in `long long`
3. no overflow
4. comparison is correct

---

# ❓ Doubt 2: `(long long)` vs `int` comparison — what happens internally?

Example:

```cpp
(long long)mid * mid > x   // x is int
```

### 🔧 C++ Rule (Type Promotion)

When two different types are compared:

- **smaller type is promoted**
- comparison happens in the larger type

So internally:

```cpp
(long long)(mid * mid) > (long long)x
```

✔️ Safe
✔️ Correct
✔️ No overflow

---

# ❓ Doubt 3: Why `res = mid` only when `mid*mid < x`?

This is the **core logic**.

---

## 🎯 Goal Restated

We want:

```
largest mid such that mid*mid ≤ x
```

So we maintain:

> **`res` = best valid answer found so far**

---

## Case Analysis

### 🔴 Case 1: `mid*mid > x`

```cpp
right = mid - 1;
```

- `mid` is too large
- invalid candidate
- **DO NOT update `res`**

---

### 🟢 Case 2: `mid*mid < x`

```cpp
res = mid;
left = mid + 1;
```

- `mid` is valid
- maybe a larger valid square root exists
- store it
- move right

---

### 🟢 Case 3: `mid*mid == x`

```cpp
return mid;
```

- perfect square
- cannot get better answer

---

## 🔑 Binary Search Invariant

> **`res` always stores the last `mid` such that `mid*mid ≤ x`**

---

# 🧪 Dry Run: `x = 15`

Expected answer: **3**

---

### Initial

```
left = 0, right = 15, res = 0
```

---

### Iteration 1

```
mid = 7
7*7 = 49 > 15
→ right = 6
```

---

### Iteration 2

```
mid = 3
3*3 = 9 < 15
→ res = 3
→ left = 4
```

---

### Iteration 3

```
mid = 5
5*5 = 25 > 15
→ right = 4
```

---

### Iteration 4

```
mid = 4
4*4 = 16 > 15
→ right = 3
```

---

### Loop ends

```
left = 4, right = 3
```

Return:

```
res = 3
```

✅ Correct

---

# ❗ Important Correction to Your Thought

> ❌ “I think output should be 4 for x = 15”

Wrong because:

```
4*4 = 16 > 15
```

Problem asks for **integer square root**, not rounded value.

---

# 🧠 One-Line Mental Model (Lock This 🔒)

> **Binary search finds the largest `mid` whose square does not exceed `x`.**

---

# ⏱️ Complexity

| Metric | Value      |
| ------ | ---------- |
| Time   | `O(log x)` |
| Space  | `O(1)`     |

---

# ✅ Final Takeaways

- `(long long)` prevents overflow
- comparison promotes `int → long long`
- `res` tracks last valid answer
- answer is **floor(sqrt(x))**, not rounded

---
