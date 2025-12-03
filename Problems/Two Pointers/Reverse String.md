
---

# #️⃣ Reverse String — LeetCode 344

**Pattern:** Two Pointers
**Difficulty:** Easy
**Topics:** Strings, Two Pointer Swapping

---

# 🔥 WHY

We need to reverse the characters **in-place**, using **O(1)** extra memory.

Two pointers from both ends allow swapping characters efficiently without extra space.

---

# 🔥 WHAT

Use:

* `left` pointer at start (0)
* `right` pointer at end (n-1)

While `left < right` → swap characters and move pointers toward center.

---

# 🔥 HOW

1. Initialize pointers `left = 0` and `right = n-1`
2. Swap characters at these positions
3. Move inward:

   * `left++`
   * `right--`
4. Stop when they cross

This performs an in-place O(n) reversal.

---

# 🔥 CODE — Two Pointer Solution (O(n))

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            swap(s[left], s[right]); // swap characters
            left++;                  // move left pointer forward
            right--;                 // move right pointer backward
        }
    }
};
```

---

# ⚙️ COMPLEXITY

| Operation | Complexity          |
| --------- | ------------------- |
| Time      | **O(n)**            |
| Space     | **O(1)** (in-place) |

---

# 📝 SUMMARY

* Use two pointers
* Swap characters symmetrically
* In-place reversal
* Simple and optimal

---