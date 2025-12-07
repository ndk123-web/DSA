
---

# 📘 Permutation in String (Check Inclusion)

### **Brute → Better → Optimal (with code + comments)**

Problem:
Return **true** if `s2` contains any permutation of `s1` as a substring.

---

# ## 🥇 1. Brute Force — Sorting Each Substring

### **Time: O( (n − m) \* m log m )**

### **Space: O(m)**

### **Idea**

- Sort `s1`
- For every substring of `s2` of length `m = s1.size()`
- Sort that substring and compare
- If equal → permutation exists

### **Code**

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s2.size() < s1.size()) return false;

        sort(s1.begin(), s1.end());  // sorted target
        int m = s1.size();

        for (int left = 0; left <= s2.size() - m; left++) {
            string part = s2.substr(left, m);
            sort(part.begin(), part.end());     // sort window
            if (part == s1) return true;
        }

        return false;
    }
};
```

### **Short Comment**

- Sort s1
- Check every window of s2 by sorting
- Slow but easy brute force

---

# ## 🥈 2. Better Sliding Window (Window Frequency Count)

### **Time: O(n \* m)**

### **Space: O(26)**

### **Idea**

- For each window of size `m` in `s2`:

  - Build a frequency count
  - Compare with required freq of s1

- Still costly because every window is counted completely.

### **Code**

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int left = 0, right = s1.size() - 1;

        unordered_map<char,int> need;
        for (char c : s1) need[c]++;

        while (right < s2.size()) {
            int count[26] = {0};
            bool validChars = true;

            // Count frequency inside window
            for (int i = left; i <= right; i++) {
                if (!need.count(s2[i])) {
                    validChars = false;
                    break;
                }
                count[s2[i] - 'a']++;
            }

            // Compare both freq maps
            if (validChars) {
                bool freqMatch = true;
                for (auto &p : need) {
                    if (count[p.first - 'a'] != p.second)
                        freqMatch = false;
                }
                if (freqMatch) return true;
            }

            left++;
            right++;
        }

        return false;
    }
};
```

### **Short Comment**

- Count characters in every window
- Compare freq arrays
- Faster than brute but still **O(n\*m)**

---

# ## 🥉 3. Optimal Sliding Window (Incremental Frequency Update)

### **Time: O(n)**

### **Space: O(26)**

### **(Your final and correct solution)**

### **Idea**

- Build freq array for s1
- Build freq array for first window of s2
- Slide window by:

  - Add new char
  - Remove old char

- Compare two freq arrays in O(26)

### **Code**

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {

        if (s1.size() > s2.size())
            return false;

        vector<int> need(26, 0), window(26, 0);
        int k = s1.size() - 1;

        // Build s1 frequency
        for (int i = 0; i <= k; i++) {
            need[s1[i] - 'a']++;
        }

        // Build first window of s2
        for (int i = 0; i <= k; i++) {
            window[s2[i] - 'a']++;
        }

        if (window == need) return true;

        // Slide window across s2
        for (int i = k + 1; i < s2.size(); i++) {
            window[s2[i] - 'a']++;               // add right char
            window[s2[i - k - 1] - 'a']--;       // remove left char

            if (window == need) return true;
        }

        return false;
    }
};
```

### **Short Comment**

- Real sliding window
- Update only 2 characters per move
- Compare fixed-size freq array
- True O(n) solution

---

# ## 🏁 Summary Table

| Approach                                 | Time                 | Space | Notes                                   |
| ---------------------------------------- | -------------------- | ----- | --------------------------------------- |
| **Brute (Sorting Windows)**              | `O((n−m) * m log m)` | O(m)  | Sort each window                        |
| **Better (Recount Every Window)**        | `O(n * m)`           | O(26) | Recount full window + compare           |
| **Optimal (Sliding Window Freq Update)** | `O(n)`               | O(26) | Add/remove 1 char per move, best method |

---
