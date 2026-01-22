# 🧩 Generate Parentheses

## 📌 Problem Statement

Given an integer `n`, generate **all combinations of well-formed parentheses** consisting of `n` pairs of parentheses.

---

## 🔍 Key Observations

- A valid parentheses string:
  - Never has more `)` than `(` at any point.
  - Has exactly `n` opening `(` and `n` closing `)` parentheses.

- The total length of each valid string is `2 * n`.

---

## 🧠 Core Idea

We build the string **character by character** using **backtracking**, while maintaining two counts:

- `open` → number of `'('` used so far
- `close` → number of `')'` used so far

At every step, we only make **valid choices**.

---

## 🛠️ Rules for Adding Parentheses

1. We can add `'('` **only if**:

   ```
   open < n
   ```

   (we cannot exceed `n` opening brackets)

2. We can add `')'` **only if**:

   ```
   close < open
   ```

   (we cannot close more brackets than we have opened)

These two rules guarantee that:

- The string is always valid.
- No invalid sequence is ever generated.

---

## 🧠 Backtracking Strategy

- Start with an empty string.
- Try adding `'('` and `')'` where allowed.
- Once the string length becomes `2 * n`, it is a valid result.
- Backtrack automatically by returning from recursion.

---

## 💻 Code (LeetCode Accepted)

```cpp
class Solution {
private:
    vector<string> res;
    int n;

    void dfs(int open, int close, string part) {
        // base case: valid length reached
        if (part.size() == n * 2) {
            res.push_back(part);
            return;
        }

        // try adding '(' if possible
        if (open < n) {
            dfs(open + 1, close, part + "(");
        }

        // try adding ')' if valid
        if (close < open) {
            dfs(open, close + 1, part + ")");
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        this->n = n;
        dfs(0, 0, "");
        return res;
    }
};
```

---

## 🧠 Dry Run Example

### Input

```
n = 3
```

### Recursive Construction

```
((()))
(()())
(())()
()(())
()()()
```

---

## ⏱️ Time Complexity

- **O(Cₙ)** where `Cₙ` is the `n`-th **Catalan number**
- Approximate growth:

  ```
  Cₙ ≈ (4ⁿ) / (n^(3/2) * √π)
  ```

This is optimal because **every valid sequence must be generated**.

---

## 📦 Space Complexity

- **O(n)** recursion stack
- Output space not counted (LeetCode convention)

---

## 🧠 Why This Works (Important Insight)

> We never generate invalid strings.

Unlike brute force (generating all `2^(2n)` strings and filtering),
this approach **prunes invalid paths early**, making it efficient.

---

## 🔑 Interview One-Liner

> “We generate parentheses using backtracking by ensuring the number of closing brackets never exceeds opening brackets, and the total number of opening brackets does not exceed `n`.”

---

## 🔄 Pattern Recognition

This problem follows the **Constraint-Based Backtracking** pattern.

Same pattern appears in:

- Permutations
- Subsets
- N-Queens
- Sudoku
