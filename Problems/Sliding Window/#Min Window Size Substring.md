

---

# **Minimum Window Substring – Complete Notes (Brute + Optimal)**

## **Problem**

Given two strings **s** and **t**, return the **shortest continuous substring** of **s** that contains **every character of t** (including duplicates).

If no such substring exists → return `""`.

Example:

```
s = "OUZODYXAZV"
t = "XYZ"
Output = "YXAZ"
```

---

# -----------------------------------------------------

# **1. Brute Force Approach**

# -----------------------------------------------------

### **Idea**

Check **every possible substring** of `s`, count its characters, and see if it contains all characters of `t`.

### **Steps**

1. Pre-compute frequency of t’s characters.
2. For every `i` from `0 → n-1`
3. For every `j` from `i → n-1`
4. Build frequency of substring `s[i…j]`.
5. Check if it covers `t`.
6. Track the smallest valid substring.

### **Code (Brute Force)**

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        if (t.empty()) return "";

        int n = s.size();
        unordered_map<char,int> need;

        for (char c : t) need[c]++;

        int minLen = INT_MAX;
        int start = -1;

        for (int i = 0; i < n; i++) {
            unordered_map<char,int> window;

            for (int j = i; j < n; j++) {
                window[s[j]]++;

                // check if window covers t
                bool ok = true;
                for (auto &p : need) {
                    if (window[p.first] < p.second) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    int len = j - i + 1;
                    if (len < minLen) {
                        minLen = len;
                        start = i;
                    }
                    break; // further j will only increase length
                }
            }
        }

        return start == -1 ? "" : s.substr(start, minLen);
    }
};
```

### **Time Complexity**

```
O(n^3) → because:
- n^2 substrings
- each check takes up to O(52) (unique chars)
```

Too slow for large input.

---

# -----------------------------------------------------

# **2. Optimal Sliding Window Approach (O(n))**

# -----------------------------------------------------

### **Idea**

Use two pointers **left** and **right** and maintain:

* `window` frequency map of characters in current window
* `need` frequency map for characters of t
* `have`: how many required characters are fully satisfied
* `need`: how many total characters (unique) must be satisfied

Shrink window whenever all required characters are satisfied.

### **Optimal Code**

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> needMap, window;
        for (char c : t) needMap[c]++;

        int need = needMap.size();
        int have = 0;

        int left = 0;
        int resL = 0, resR = INT_MAX;

        for (int right = 0; right < s.size(); right++) {

            window[s[right]]++;

            if (needMap.count(s[right]) &&
                window[s[right]] == needMap[s[right]]) {
                have++;
            }

            while (have == need) {
                if ((right - left + 1) < (resR - resL)) {
                    resL = left;
                    resR = right + 1; // non-inclusive end
                }

                window[s[left]]--;

                if (needMap.count(s[left]) &&
                    window[s[left]] < needMap[s[left]]) {
                    have--;
                }

                left++;
            }
        }

        return resR == INT_MAX ? "" : s.substr(resL, resR - resL);
    }
};
```

---

# **Why this works**

* `right` expands window until all characters of `t` are included.
* `left` shrinks the window to find the smallest valid substring.
* `have == need` means current window contains every required character with correct frequencies.

---

# **Time Complexity**

```
O(n)
```

Each character is visited by left and right pointer at most once.

---

# **Final Summary**

| Approach               | Time  | Space           | Notes                            |
| ---------------------- | ----- | --------------- | -------------------------------- |
| Brute Force            | O(n³) | O(1)            | Simple but useless for big input |
| Optimal Sliding Window | O(n)  | O(unique chars) | Fast and standard solution       |

---