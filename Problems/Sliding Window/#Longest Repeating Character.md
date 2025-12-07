---
# 📘 Longest Repeating Character Replacement

### **Brute → Better → Optimal (with code + short comments)**
---

# ## 🥇 1. Brute Force — O(n²) Time | O(1) Space

### **Idea**

Try every substring, count max frequency, check replacements needed.

### **Code**

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int longest = 0;

        for (int i = 0; i < n; i++) {
            int freq[26] = {0};
            int maxFreq = 0;

            for (int j = i; j < n; j++) {
                freq[s[j] - 'A']++;
                maxFreq = max(maxFreq, freq[s[j] - 'A']);

                int windowSize = j - i + 1;
                int replaceNeeded = windowSize - maxFreq;

                if (replaceNeeded <= k)
                    longest = max(longest, windowSize);
            }
        }

        return longest;
    }
};
```

### **Short Comment**

- Check all substrings
- Count max frequent char per substring
- If replacements ≤ k → update longest

---

# ## 🥉 2. Optimal Sliding Window — O(n) Time | O(1) Space

**(Your final correct version)**

### **Idea**

Maintain window `[left, right]`

- Track **max frequency** in window
- If replacements > k → shrink window
- Always update longest valid window

### **Code**

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char,int> freq;
        int left = 0, right = 1;
        int longest = 0, maxFreq = 1;
        int n = s.size();

        if (n == 1) return 1;

        freq[s[left]]++;

        while (right < n) {
            freq[s[right]]++;
            maxFreq = max(maxFreq, freq[s[right]]); // update max char in window

            int replaceNeeded = (right - left + 1) - maxFreq;

            if (replaceNeeded > k) { // window invalid → shrink
                freq[s[left]]--;
                left++;
            }

            longest = max(longest, right - left + 1); // update answer
            right++;
        }

        return longest;
    }
};
```

### **Short Comment**

- Sliding window
- Keep max freq in window
- If window invalid → shrink using left++
- Track largest valid window length

---

# ## 🏁 Summary Table

| Approach        | Time     | Space    | Notes                          |
| --------------- | -------- | -------- | ------------------------------ |
| **Brute Force** | O(n²)    | O(1)     | Checks all substrings          |
| **Optimal**     | **O(n)** | **O(1)** | Sliding window + maxFreq trick |
