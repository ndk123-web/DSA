
---

# #️⃣ **Valid Palindrome — LeetCode 125**

**Pattern:** Two Pointers / String Cleaning
**Difficulty:** Easy
**Topics:** Strings, Two Pointers, Alphanumeric Filtering

---

# 🔥 **PROBLEM**

Given a string `s`, return **true** if it is a palindrome.

Rules:

* Ignore **non-alphanumeric** characters
* Case-insensitive (A == a)
* Consider only `A-Z`, `a-z`, `0-9`

---

# ⭐ **APPROACH 1 — Two Pointers (In-Place, O(n), O(1) space)**

### ✔ WHY

We do not need to build a new string.
We can simply:

1. Skip all non-alphanumeric characters
2. Convert remaining characters to lowercase
3. Compare left & right characters

Two pointers meet in the center → palindrome.

---

# ⭐ **WHAT**

Key tools:

* `isalnum(c)` → checks if c is alphanumeric
* `tolower(c)` → converts to lowercase
* Two-pointer scanning

---

# ⭐ **CODE — Two Pointers Approach**

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {

            // skip non-alphanumeric from left
            while (left < right && !isalnum(s[left]))
                left++;

            // skip non-alphanumeric from right
            while (left < right && !isalnum(s[right]))
                right--;

            // compare after normalizing to lowercase
            if (tolower(s[left]) != tolower(s[right]))
                return false;

            left++;
            right--;
        }

        return true;
    }
};
```

---

# ⭐ **APPROACH 2 — Clean String + Reverse (Easy to write, O(n) time, O(n) space)**

### ✔ WHY

Sometimes easier to:

1. Build a filtered lowercase string containing only alphanumerics
2. Reverse it
3. Compare with original filtered version

---

# ⭐ **WHAT**

* `isalnum(c)` → keep valid characters
* `tolower(c)` → normalize
* `string(newString.rbegin(), newString.rend())`
  → creates reversed string from reverse iterators

---

# ⭐ **CODE — Clean String + Reverse**

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        string newString = "";

        for (char c : s) {
            if (isalnum(c)) {
                newString += tolower(c);
            }
        }

        // compare original cleaned vs reversed cleaned
        return newString == string(newString.rbegin(), newString.rend());
    }
};
```

---

# ⭐ **NEW CONCEPTS LEARNED**

### ✔ `isalnum(c)`

Returns **true** if character is:

* A-Z
* a-z
* 0-9

### ✔ `tolower(c)`

Converts uppercase → lowercase
Works only on chars.

### ✔ `string(newString.rbegin(), newString.rend())`

Creates a **new string** from reverse iterators → reversed string.
Example:

```cpp
string a = "abc";
string b(a.rbegin(), a.rend());  // "cba"
```

### ✔ Reverse Iterators

* `rbegin()` → last char
* `rend()` → before first char
  Used to build reversed strings easily.

---

# ⭐ **COMPLEXITY**

| Approach        | Time     | Space    |
| --------------- | -------- | -------- |
| Two Pointers    | **O(n)** | **O(1)** |
| Clean + Reverse | **O(n)** | **O(n)** |

---

# ⭐ **SUMMARY**

* Filter non-alphanumeric characters
* Compare characters case-insensitively
* Two-pointers = fastest
* Clean+reverse = easiest to write
* Use `isalnum`, `tolower`, and reverse iterators to simplify logic

---
