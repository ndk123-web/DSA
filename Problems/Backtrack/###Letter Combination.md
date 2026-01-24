# 📱 Letter Combinations of a Phone Number

## 📌 Problem Statement

Given a string `digits` containing digits from `2` to `9`, return **all possible letter combinations** that the number could represent.

Each digit maps to letters as on a traditional phone keypad.

---

## 🔍 Key Observations

- Each digit maps to **3 or 4 letters**
- One letter must be chosen from **each digit**
- The order of digits must be preserved
- This naturally forms a **tree of choices**, making it a **backtracking problem**

---

## 🧠 Intuition

For every digit:

- We try all letters mapped to that digit
- For each chosen letter, we recursively process the next digit

So the problem becomes:

> “For each position, try all possible letters and move forward.”

---

## 🛠️ Approach Overview

We solve this using **DFS + Backtracking**.

We maintain:

- `idx` → current position in the digit string
- `oneres` → current combination being built

At each step:

1. Convert current digit to its mapped letters
2. Try each letter
3. Add it to the current string
4. Recurse to the next digit
5. Backtrack

---

## 🟢 Approach 1 — Vector-Based Phone Mapping

### 💡 Idea

- Use a `vector<string>` where index = digit
- Direct indexing gives fast access
- Simple and clean

---

### 💻 Code

```cpp
class Solution {
private:
    vector<string> phonePad = {
        "", "", "abc", "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    vector<string> res;
    string oneres;

    void combiner(string& digits, int idx) {
        if (idx == digits.size()) {
            res.push_back(oneres);
            return;
        }

        int curr = digits[idx] - '0';
        string letters = phonePad[curr];

        for (char ch : letters) {
            oneres.push_back(ch);
            combiner(digits, idx + 1);
            oneres.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return res;
        combiner(digits, 0);
        return res;
    }
};
```

---

### ✅ Pros

- Fast lookup (O(1))
- No hashing overhead
- Clean and interview-friendly

---

## 🟢 Approach 2 — HashMap-Based Phone Mapping

### 💡 Idea

- Use `unordered_map<int, string>` to map digits to letters
- More explicit and readable
- Useful when mappings are dynamic

---

### 💻 Code

```cpp
class Solution {
private:
    unordered_map<int, string> phoneMap = {
        {2,"ABC"}, {3,"DEF"}, {4,"GHI"}, {5,"JKL"},
        {6,"MNO"}, {7,"PQRS"}, {8,"TUV"}, {9,"WXYZ"}
    };

    vector<string> res;
    string oneres;

    void combiner(string& digits, int idx) {
        if (idx == digits.size()) {
            res.push_back(oneres);
            return;
        }

        int curr = digits[idx] - '0';
        string letters = phoneMap[curr];

        for (char ch : letters) {
            oneres.push_back(tolower(ch));
            combiner(digits, idx + 1);
            oneres.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return res;
        combiner(digits, 0);
        return res;
    }
};
```

---

### ✅ Pros

- Clear mapping
- Easy to extend or modify

### ❌ Cons

- Slightly slower due to hashing (still acceptable)

---

## 🧠 Example

### Input

```
digits = "23"
```

### Output

```
["ad","ae","af","bd","be","bf","cd","ce","cf"]
```

---

## ⏱️ Time Complexity (IMPORTANT)

Let:

- `n` = number of digits
- each digit has at most **4 letters**

### 🔹 Number of combinations

Each digit branches into up to 4 choices:

```
Total combinations = 4^n
```

### 🔹 Work per recursive call

- Push / pop = O(1)
- Loop size ≤ 4 (constant)

So:

### ✅ Final Time Complexity

[
O(4^n)
]

---

## 📦 Space Complexity

- Recursion depth = `n`
- Current string size = `n`

### ✅ Space Complexity

[
O(n)
]

(Output space not counted)

---

## 🧠 Why It Is NOT `n^n`

- `n` = number of digits
- branching factor ≠ `n`
- branching factor = number of letters (≤ 4)

So growth is:

```
4 × 4 × 4 ... (n times)
```

Not:

```
n × n × n
```

---

## 🔑 Interview One-Liner

> “Each digit maps to up to 4 letters, so for `n` digits we generate `O(4^n)` combinations using backtracking.”

---

## 🔄 Pattern Recognition

This exact pattern appears in:

- Permutations
- Subsets
- Combination Sum
- Word Search

Once you understand **branching factor × depth**, exponential problems become predictable.
