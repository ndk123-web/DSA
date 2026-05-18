# C++ Competitive Programming Cheat Sheet

This is the practical version people actually use in interviews and CP.

---

# 1. Integer Data Types

| Type                 | Size    | Range         | Use Case           |
| -------------------- | ------- | ------------- | ------------------ |
| `short`              | 2 bytes | `-32k to 32k` | rarely used        |
| `int`                | 4 bytes | `±2e9`        | default integer    |
| `long long`          | 8 bytes | `±9e18`       | big math           |
| `unsigned int`       | 4 bytes | `0 to 4e9`    | non-negative only  |
| `unsigned long long` | 8 bytes | `0 to 1.8e19` | very huge positive |

---

# 2. Floating Point Types

| Type          | Precision  | Range     | Use              |
| ------------- | ---------- | --------- | ---------------- |
| `float`       | 6-7 digits | `1e38`    | rarely used      |
| `double`      | 15 digits  | `1e308`   | standard decimal |
| `long double` | 18+ digits | very huge | high precision   |

---

# 3. Most Important Approximations

Memorize these.

| Expression | Approx |
| ---------- | ------ |
| `2^10`     | `1e3`  |
| `2^20`     | `1e6`  |
| `2^30`     | `1e9`  |
| `2^31`     | `2e9`  |
| `2^60`     | `1e18` |
| `2^63`     | `9e18` |

---

# 4. Scientific Notation

| Notation | Meaning      |
| -------- | ------------ |
| `1e3`    | `1000`       |
| `1e6`    | `1000000`    |
| `1e9`    | `1000000000` |
| `1e18`   | huge         |

---

# 5. MOST IMPORTANT RULES

## Rule 1

If multiplication exists:

```cpp id="iqh9zf"
a * b
```

suspect overflow.

Use:

```cpp id="3np5kf"
long long
```

---

## Rule 2

If constraints contain:

```text id="nwjhhn"
1e18
```

always use:

```cpp id="hzkd88"
long long
```

---

## Rule 3

For sums:

Wrong:

```cpp id="8t2t1g"
int sum = 0;
```

Correct:

```cpp id="9efp51"
long long sum = 0;
```

---

## Rule 4 — The `1LL` Trick

Wrong:

```cpp id="d0pyqg"
long long ans = a * b;
```

because multiplication already overflowed.

Correct:

```cpp id="ij7gr2"
long long ans = 1LL * a * b;
```

---

# 6. Integer Overflow Example

```cpp id="0yjq6w"
int x = 2147483647;

cout << x + 1;
```

Output:

```text id="v2u26h"
-2147483648
```

Overflow wraps around.

No error.

---

# 7. Time Complexity Cheat Sheet

| Complexity   | Usually Safe |
| ------------ | ------------ |
| `O(1)`       | always       |
| `O(log n)`   | always       |
| `O(n)`       | `1e7`        |
| `O(n log n)` | `1e5 - 1e6`  |
| `O(n^2)`     | `1e3 - 1e4`  |
| `O(n^3)`     | `500`        |
| `O(2^n)`     | `20`         |
| `O(n!)`      | `10`         |

---

# 8. Constraint → Approach Mapping

| Constraint | Likely Solution         |
| ---------- | ----------------------- |
| `n <= 10`  | factorial / brute force |
| `n <= 20`  | bitmask / recursion     |
| `n <= 1e3` | `O(n^2)`                |
| `n <= 1e5` | sorting / hashing       |
| `n <= 1e6` | linear scan             |
| `n <= 1e9` | math / binary search    |

---

# 9. STL Complexity

| Operation           | Complexity       |
| ------------------- | ---------------- |
| `sort()`            | `n log n`        |
| `reverse()`         | `n`              |
| `map` insert        | `log n`          |
| `unordered_map` avg | `O(1)`           |
| `set` insert        | `log n`          |
| `vector push_back`  | amortized `O(1)` |

---

# 10. Important STL Data Structures

| DS               | Access     | Insert           | Ordered? |
| ---------------- | ---------- | ---------------- | -------- |
| `vector`         | `O(1)`     | end `O(1)`       | yes      |
| `set`            | `log n`    | `log n`          | sorted   |
| `unordered_set`  | `O(1)`     | `O(1)`           | no       |
| `map`            | `log n`    | `log n`          | sorted   |
| `unordered_map`  | `O(1)`     | `O(1)`           | no       |
| `priority_queue` | top `O(1)` | push/pop `log n` | heap     |

---

# 11. Binary Search Rule

Wrong:

```cpp id="mm4lhg"
mid = (l + r) / 2;
```

Correct:

```cpp id="vjlwmz"
mid = l + (r - l) / 2;
```

because `l+r` may overflow.

---

# 12. Modulo Rules

Most common:

```cpp id="tjlwmn"
1e9 + 7
```

Why?

* prime
* fits in int
* avoids overflow

---

# 13. String Basics

| Operation | Complexity       |
| --------- | ---------------- |
| access    | `O(1)`           |
| append    | `O(1)` amortized |
| substring | `O(n)`           |
| reverse   | `O(n)`           |

`std::string` is mutable in C++.

---

# 14. Recursion Limits

Safe recursion depth:

```text id="m62o9d"
~10^4
```

Beyond that:

* stack overflow possible

---

# 15. Fast CP Habits

Most CP people use:

```cpp id="2bzv8z"
using ll = long long;
```

and:

```cpp id="6u20qr"
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

---

# 16. Golden Rules to Solve Problems

## If:

### Sorting needed

Think:

```text id="x3q7m0"
sort + greedy
```

---

### Repeated lookup

Think:

```text id="x5jlwm"
hashmap
```

---

### Small constraints (`n <= 20`)

Think:

```text id="lw8f1t"
bitmask / recursion
```

---

### Large constraints (`1e5+`)

Think:

```text id="l9vhtv"
O(n log n) or O(n)
```

---

### Subarray problems

Think:

```text id="jlwm5r"
prefix sum / sliding window
```

---

### Immediate next/smallest/largest arrangement

Think:

```text id="q2o0js"
greedy
```

---

# 17. Most Common Interview Mistakes

| Mistake                                | Fix                   |
| -------------------------------------- | --------------------- |
| int overflow                           | use `long long`       |
| wrong complexity                       | map constraints first |
| recursion TLE                          | memoization           |
| sorting unnecessarily                  | use hash              |
| using `map` instead of `unordered_map` | know complexity       |
| off-by-one                             | dry run               |

---

# 18. Most Important Memory Shortcut

Just remember:

```text id="22vk2g"
int ≈ 2e9
long long ≈ 9e18
2^10 ≈ 1e3
```

From this, almost everything can be derived mentally.
