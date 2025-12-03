
---

# #️⃣ Valid Palindrome II — LeetCode 680

**Pattern:** Two Pointers / One Allowed Deletion
**Difficulty:** Easy–Medium
**Topics:** Strings, Two Pointers, Recursion

---

# 🔥 PROBLEM

Given a string `s`, return **true** if the string can be a palindrome **after deleting at most one character**.

Rules:

* You may delete **at most one** character.
* The remaining string must be palindrome.
* You cannot reorder characters; only skip one.

---


# 🟦 **WHY**

Normal palindrome requires:

```
s[l] == s[r] for all l, r
```

But here we get **1 chance** to skip mismatched character:

* Either skip left → check `s[l+1 ... r]`
* Or skip right → check `s[l ... r-1]`

This is the **core idea**.

---


# 🟩 **WHAT**

There are two valid approaches:

### 1️⃣ Recursive approach

* On mismatch → branch into two recursive calls
* Increase `removals` count
* Stop if removals > 1
* Continue checking inner substring

### 2️⃣ Two-pointer iterative + helper

* On mismatch → call helper to check the remaining substring
* No recursion needed
* This is the cleanest and fastest method

---


# 🟧 **HOW (LOGIC)**

### ✔ Step-1: Move inward while characters match

```
l++, r--
```

### ✔ Step-2: If mismatch happens:

We have two choices:

* Remove left character
  → check if `s[l+1 ... r]` is palindrome
* Remove right character
  → check if `s[l ... r-1]` is palindrome

If either one becomes a palindrome → answer is true.

### ✔ Step-3: If pointers cross → palindrome is valid.

---


# 🟥 **EXAMPLE WALKTHROUGH (“abca”)**

```
s = "abca"
 l     r
 a != a → match → move to next
```

Now:

```
 l   r
 b != c → mismatch → try two options:
```

### Option 1: Remove left ‘b’

Check `"bca"` → `"ca"` mismatch → fails

### Option 2: Remove right ‘c’

Check `"abc"` → `"bc"` mismatch → fails?
No—let’s check properly:

Case skip right:

```
 s = "abca"
 l = 0 ('a')
 r = 2 ('c')

 a == c → move inward
 l=1 ('b'), r=1 ('b')
 pointers crossed → return true
```

So `"abca"` is valid after removing `'c'`.

Final result: **true**

---


# 🟦 **SOLUTION 1 — Recursion (DFS with removal count)**

**Uses recursion with at most 1 allowed deletion.**

```cpp
class Solution {
public:
    bool helper(string& s, int left, int right, int removals) {
        if (removals > 1)
            return false;
        if (left >= right)
            return true;

        if (s[left] == s[right]) {
            return helper(s, left + 1, right - 1, removals);
        } else {
            return helper(s, left + 1, right, removals + 1) ||
                   helper(s, left, right - 1, removals + 1);
        }
    }

    bool validPalindrome(string s) {
        return helper(s, 0, s.size() - 1, 0);
    }
};
```

### ✔ Notes

* `removals` tracks how many characters we have skipped
* At mismatch: two recursion branches
* If removals exceed 1 → fail
* Only index-based recursion (no string slicing)

---


# 🟩 **SOLUTION 2 — Optimal Two-Pointer Approach (O(n), no recursion)**

**Cleaner, faster, and preferred in interviews.**

```cpp
class Solution {
public:
    bool isPal(string& s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }

    bool validPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l] == s[r]) {
                l++;
                r--;
            } else {
                return isPal(s, l + 1, r) || isPal(s, l, r - 1);
            }
        }

        return true;
    }
};
```

### ✔ Notes

* When mismatch occurs → check both options
* `isPal()` helper checks normal palindrome
* Only **1 extra delete allowed**

---


# ⚙️ COMPLEXITY

| Method      | Time     | Space              |
| ----------- | -------- | ------------------ |
| Recursion   | O(n)     | O(n) stack (worst) |
| Two-pointer | **O(n)** | **O(1)** (best)    |

---


# 📝 SUMMARY

* Core idea: **at most one deletion allowed**
* Mismatch → check `(l+1, r)` OR `(l, r-1)`
* Recursion and iteration both possible
* Two-pointer version is the cleanest and fastest

---
