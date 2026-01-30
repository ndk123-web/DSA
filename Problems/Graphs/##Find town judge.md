# 📘 Find the Town Judge (LeetCode 997)

---

## 🧠 Problem Intuition

In a town with `n` people labeled `1` to `n`, a **town judge** is defined as someone who:

1. **Trusts nobody**
2. **Is trusted by everyone else**
3. **Is unique**

Given trust relationships `trust[a] = [x, y]` meaning _x trusts y_, we must identify the judge or return `-1` if none exists.

---

## 🔑 Key Observation

Each person has two independent properties:

- **Outgoing trust** → whom they trust
- **Incoming trust** → who trusts them

For a person `j` to be judge:

```
incoming[j] == n - 1
outgoing[j] == 0
```

This naturally leads to a **graph degree**–based solution.

---

# 🟢 Approach 1: In-Degree & Out-Degree Arrays (Clear & Intuitive)

### 💡 Idea

Maintain two arrays:

- `in[i]` → number of people who trust person `i`
- `out[i]` → number of people person `i` trusts

Each trust `[a, b]` updates:

```
out[a]++
in[b]++
```

Finally, scan for a person satisfying the judge conditions.

---

### ✅ Code (Approach 1)

```cpp
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> in(n + 1, 0), out(n + 1, 0);

        for (auto& v : trust) {
            in[v[1]]++;    // person v[1] is trusted
            out[v[0]]++;   // person v[0] trusts someone
        }

        for (int i = 1; i <= n; i++) {
            if (in[i] == n - 1 && out[i] == 0) {
                return i;
            }
        }
        return -1;
    }
};
```

---

### 🧠 Why This Works

- `out[i] == 0` ensures **judge trusts nobody**
- `in[i] == n - 1` ensures **everyone else trusts judge**
- Conditions are independent and sufficient

---

# ⚡ Approach 2: Single Score / Delta Array (Optimized)

### 💡 Optimization Insight

Instead of two arrays, we can **combine both conditions** into one:

Define:

```
delta[i] = incoming trust - outgoing trust
```

For each trust `[a, b]`:

```
delta[a]--   // a trusts someone
delta[b]++   // b is trusted
```

If a judge exists:

```
delta[judge] == n - 1
```

---

### ✅ Code (Approach 2)

```cpp
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        if (n == 1 && trust.empty())
            return 1;

        vector<int> delta(n + 1, 0);

        for (auto& v : trust) {
            delta[v[0]]--;  // outgoing trust
            delta[v[1]]++;  // incoming trust
        }

        for (int i = 1; i <= n; i++) {
            if (delta[i] == n - 1) {
                return i;
            }
        }
        return -1;
    }
};
```

---

### 🧠 Why This Works

Judge properties rewritten algebraically:

```
incoming = n - 1
outgoing = 0
→ incoming - outgoing = n - 1
```

So a **single value check** is sufficient.

---

## 🧪 Edge Cases Handled

| Case                       | Result        |
| -------------------------- | ------------- |
| `n = 1`, no trust          | `1`           |
| Multiple people with trust | correct judge |
| Judge trusts someone       | `-1`          |
| Someone not trusted by all | `-1`          |

---

## ⏱️ Time & Space Complexity

### Time Complexity

```
O(n + trust.size())
```

### Space Complexity

- Approach 1: `O(n)`
- Approach 2: `O(n)` (slightly less constant overhead)

---

## 🆚 Comparison of Approaches

| Aspect            | In/Out Arrays | Delta Array |
| ----------------- | ------------- | ----------- |
| Readability       | ⭐⭐⭐⭐      | ⭐⭐⭐      |
| Elegance          | ⭐⭐⭐        | ⭐⭐⭐⭐    |
| Memory            | O(n)          | O(n)        |
| Interview clarity | ✅            | ✅          |

---

## 🔒 Final Takeaway

> **Town Judge problem is a graph-degree problem disguised as a story.**
