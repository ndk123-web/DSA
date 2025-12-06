
---

# Longest Substring Without Repeating Characters

**LeetCode 3**
**Pattern:** Sliding Window
**Difficulty:** Medium

Given a string `s`, return the length of the **longest substring without repeating characters**.

---

#  Brute Force (for understanding only)

Try all substrings → check duplicates.

* Time: O(n³) (generate + check)
* Space: O(n)

Not acceptable for `n = 50,000`.

---

#  Optimal Approach 1

# Sliding Window using HashSet (Left Shrinks Until Window Valid)

### **Idea**

Maintain a sliding window `[left ... right]` that always contains **unique characters**.

For each character at `right`:

* If it already exists in the window → shrink window from left until duplicate removed.
* Insert current character into the set.
* Update maximum window length.

### **Code**

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> hashSet;
        int left = 0;
        int longest = 0;

        for (int right = 0; right < s.size(); right++) {

            // shrink window until s[right] becomes unique
            while (hashSet.count(s[right])) {
                hashSet.erase(s[left]);
                left++;
            }

            // valid window, insert
            hashSet.insert(s[right]);

            // update longest valid window
            longest = max(longest, right - left + 1);
        }

        return longest;
    }
};
```

### **Why it works**

* Every character gets inserted and removed at most once → O(n)
* At all times, the window contains **distinct** characters.

### **Complexity**

|       | Value                          |
| ----- | ------------------------------ |
| Time  | O(n)                           |
| Space | O(min(n, charset)) → max ~ 256 |

---

#  Optimal Approach 2

# Sliding Window using HashMap (Track Last Seen Index)

### **Idea**

Instead of shrinking step-by-step, jump `left` directly past the last occurrence of the duplicate.

Example:
If current char `'b'` was last seen at index `1`, and now you're at index `r = 4`,
move:

```
left = max(left, last_position['b'] + 1)
```

### **Code**

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp; // last seen index
        int left = 0, longest = 0;

        for (int right = 0; right < s.size(); right++) {

            // if duplicate found inside window, shift left
            if (mp.count(s[right])) {
                left = max(left, mp[s[right]] + 1);
            }

            // update last seen index
            mp[s[right]] = right;

            // window size
            longest = max(longest, right - left + 1);
        }

        return longest;
    }
};
```

### **Why it works**

* Use direct jump instead of step-by-step window shrinking.
* Works in O(n) time.

### **Complexity**

|       | Value |
| ----- | ----- |
| Time  | O(n)  |
| Space | O(n)  |

---

# 🔍 Comparison of the Two Optimal Solutions

| Approach                   | When left moves            | How duplicates removed | Speed | Memory          |
| -------------------------- | -------------------------- | ---------------------- | ----- | --------------- |
| **HashSet Sliding Window** | Move left 1 step at a time | Remove chars gradually | O(n)  | Lower           |
| **HashMap Sliding Window** | Jump left directly         | Uses last-seen index   | O(n)  | Slightly higher |

**Set approach** → simpler
**Map approach** → more efficient when many duplicates occur

Both pass all constraints.

---

# Final Recommendation

Use **HashMap approach** in interviews: it shows stronger understanding.
Use **HashSet approach** when asked for a "sliding window + unique substring" pattern explicitly.

---