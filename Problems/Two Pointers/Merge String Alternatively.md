
---

# #️⃣ Merge Strings Alternately — LeetCode 1768

**Pattern:** Two Pointers / Simulation
**Difficulty:** Easy
**Topics:** Strings, Pointers, Greedy merge

---

# 🔥 PROBLEM

Given two strings `word1` and `word2`, merge them by taking characters **alternately** from each string.

If one string becomes empty first, append the **remaining characters** of the other string.

### Example

```
Input:  word1 = "abc", word2 = "pqr"
Output: "apbqcr"
```

---

# 🔥 WHY

We want to merge strings in an **alternating order**:

```
word1[0], word2[0], word1[1], word2[1], ...
```

We do this until one string ends, then append the rest.

---

# 🔥 WHAT

Use:

* Two pointers (`ptrOfWord1`, `ptrOfWord2`)
* A `flag` to decide whose turn it is
* Append remaining characters after the loop

---

# 🔥 HOW

1. Initialize pointers at 0
2. While both pointers are in range:

   * If flag = false → take from word1
   * If flag = true → take from word2
   * Flip the flag each time
3. After loop, append leftover characters from the longer string
4. Return merged result

---

# 🧩 **CODE — Clean Two Pointer / Flag Method**

```cpp
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int ptrOfWord1 = 0;
        int ptrOfWord2 = 0;
        int sizeOfWord1 = word1.size();
        int sizeOfWord2 = word2.size();
        string res;

        bool flag = false;  // false → take from word1, true → take from word2

        // Alternate while both have chars
        while (ptrOfWord1 < sizeOfWord1 && ptrOfWord2 < sizeOfWord2) {
            if (!flag)
                res += word1[ptrOfWord1++];
            else
                res += word2[ptrOfWord2++];
            flag = !flag;
        }

        // Append leftover from word1
        while (ptrOfWord1 < sizeOfWord1) {
            res += word1[ptrOfWord1++];
        }

        // Append leftover from word2
        while (ptrOfWord2 < sizeOfWord2) {
            res += word2[ptrOfWord2++];
        }

        return res;
    }
};
```

---

# ⚙️ COMPLEXITY

| Operation | Complexity                   |
| --------- | ---------------------------- |
| Time      | **O(n + m)**                 |
| Space     | **O(n + m)** (result string) |

---

# 📝 SUMMARY

* Two pointers walk through both strings
* Alternate selection using a boolean flag
* Append remaining characters
* Simple simulation: **clean, readable, efficient**

---