# 🧩 Palindrome Partitioning

## 📌 Problem Statement

Given a string `s`, partition `s` such that **every substring of the partition is a palindrome**.
Return all possible palindrome partitionings of `s`.

---

## 🧠 Intuition

We process the string **from left to right** and try to cut it at different positions.

At each index:

- We try **all possible substrings starting at that index**
- If a substring is a palindrome, we choose it
- Then we recursively solve the remaining string

This is a classic **backtracking + recursion** problem where we explore all valid partitions.

---

## 🛠️ Approach

1. Start recursion from index `0`.
2. At a given index `idx`, try all substrings `s[idx…i]`.
3. If the substring is a palindrome:
   - Add it to the current partition
   - Recurse for the remaining string starting at `i + 1`

4. When `idx == s.size()`, a valid partition is formed — add it to the result.
5. Backtrack by removing the last added substring.

---

## 💻 Code

```cpp
class Solution {
private:
    vector<vector<string>> res;
    vector<string> oneres;

    bool isPalindrome(string &s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }

    void part(string &s, int idx) {
        if (idx == s.size()) {
            res.push_back(oneres);
            return;
        }

        for (int i = idx; i < s.size(); i++) {
            if (!isPalindrome(s, idx, i)) continue;

            oneres.push_back(s.substr(idx, i - idx + 1));
            part(s, i + 1);
            oneres.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s) {
        part(s, 0);
        return res;
    }
};
```

---

## 🧠 Example

### Input

```
s = "aab"
```

### Output

```
[
 ["a","a","b"],
 ["aa","b"]
]
```

---

## ⏱️ Time Complexity

### 🔹 Worst Case Analysis

Worst case string:

```
s = "aaaaa..."
```

- Every substring is a palindrome
- No pruning happens

There are `N - 1` possible cut positions in a string of length `N`.

Each position has **2 choices**:

- Cut
- Do not cut

So total possible partitions:

```
2^(N - 1)
```

For each partition:

- We may store up to `N` substrings

### ✅ Final Time Complexity

[
O(N \times 2^N)
]

---

## 📦 Space Complexity

- Recursion depth: `O(N)`
- Output storage is exponential (not counted as auxiliary space)

### ✅ Space Complexity

[
O(N)
]

---

## 🧠 Why Exponential Is Inevitable

Although:

- The number of choices decreases as recursion goes deeper
  the **total number of valid partitions** is still exponential.

This happens because:

- Each character boundary independently decides **cut / no-cut**
- These independent decisions multiply, not add

---

## 🔑 Key Insight (Important)

> Levels do not add up — **branches multiply**.

Even though:

```
level 1 → N choices
level 2 → N-1 choices
level 3 → N-2 choices
```

The total number of paths (leaf nodes) is still exponential.

---

## 🏁 Interview One-Liner

> “We use backtracking to try all palindrome prefixes, and in the worst case, there are `2^(N-1)` partitions, each taking `O(N)` time to build.”

---

## 🔄 Pattern Recognition

This exact pattern appears in:

- Word Break
- Restore IP Addresses
- Combination Sum (string variants)

Once this logic is clear, **all partition-based backtracking problems become predictable**.

---

### ✅ Final Takeaway

- Depth = `N`
- Number of partitions = `2^(N-1)`
- Work per partition = `O(N)`
- **Total = `O(N × 2^N)`**
