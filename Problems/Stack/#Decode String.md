# 🔐 Decode String — Stack Based Explanation (Clear & Practical)

## 📘 Problem Summary

You are given an encoded string where patterns follow this rule:

```
k[encoded_string]
```

* `k` is a positive integer
* `encoded_string` inside brackets must be repeated `k` times
* Patterns can be **nested**

---

## 🎯 Goal

Return the **fully decoded string**.

---

## 🧠 Core Idea (Very Important)

> **Whenever we see `[`, we save the current state.**
> **Whenever we see `]`, we resolve the current block and merge it back.**

To handle nesting, we use **two stacks**:

* One stack for **strings**
* One stack for **repeat counts**

---

## 💻 Code (With Short Comments)

```cpp
class Solution {
public:
    string decodeString(string s) {
        string cur = "";              // current decoded string at this level
        vector<string> chars;         // stack to store previous strings
        vector<int> ints;             // stack to store repeat counts
        int k = 0;                    // number before '['

        for (char c : s) {
            if (isdigit(c)) {
                // build multi-digit number
                k = k * 10 + (c - '0');
            }
            else if (c == '[') {
                // save current state
                chars.push_back(cur);
                ints.push_back(k);
                cur = "";             // reset for inner block
                k = 0;
            }
            else if (c == ']') {
                // close one encoded block
                string temp = cur;            // decoded inner string
                cur = chars.back();           // previous outer string
                int count = ints.back();      // repetition count
                chars.pop_back();
                ints.pop_back();

                // append repeated inner string
                for (int i = 0; i < count; i++) {
                    cur += temp;
                }
            }
            else {
                // normal character
                cur += c;
            }
        }
        return cur;
    }
};
```

---

## 🔑 Key Logic at `]` (Most Confusing Part)

```cpp
string temp = cur;
cur = chars.back();
int count = ints.back();
```

### Meaning:

* `temp` → **string decoded inside the current brackets**
* `cur` → **string before this bracket level**
* `count` → **how many times to repeat `temp`**

Then:

```
cur = cur + temp (count times)
```

---

## 🧪 Full Dry Run Example

### Input

```
"2[a3[b]]c"
```

---

### Step-by-step

| Read | cur         | chars stack | ints stack | Action            |
| ---- | ----------- | ----------- | ---------- | ----------------- |
| `2`  | ""          | []          | []         | build number      |
| `[`  | ""          | [""]        | [2]        | save state        |
| `a`  | "a"         | [""]        | [2]        | append            |
| `3`  | "a"         | [""]        | [2]        | build number      |
| `[`  | ""          | ["", "a"]   | [2,3]      | save state        |
| `b`  | "b"         | ["", "a"]   | [2,3]      | append            |
| `]`  | "abbb"      | [""]        | [2]        | resolve `3[b]`    |
| `]`  | "abbbabbb"  | []          | []         | resolve `2[abbb]` |
| `c`  | "abbbabbbc" | []          | []         | append            |

---

## ✅ Final Output

```
abbbabbbc
```

---

## 🧠 Mental Model (Lock This 🔒)

> **At `[` → save context**
> **At `]` → repeat current block and merge back**

Inner strings are always resolved **before** outer ones.

---

## ⏱️ Complexity Analysis

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(n)`

---

## ⭐ Final Takeaway

* Stack handles nesting cleanly
* `temp` always holds the inner decoded string
* `cur` always represents the current working level

Once this logic clicks, **all nested string problems become easy**.
