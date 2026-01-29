# 📘 Verifying an Alien Dictionary (LeetCode 953)

## 🧠 Problem Summary

You are given:

- `words[]` → a list of words written in an alien language
- `order` → a permutation of lowercase English letters defining the alien alphabet order

Your task is to **verify** whether the given words are sorted **lexicographically** according to the alien alphabet.

> ⚠️ You do NOT need to sort the words — only check if the current order is valid.

---

## 📜 Lexicographical Rules (Core Concept)

Lexicographical (dictionary) order works as follows:

1. Compare words **character by character** from left to right
2. At the **first mismatch**, the character with **smaller rank** in the alien alphabet decides the order
3. If all characters match up to the length of the shorter word:
   - The **shorter word is considered smaller**

Example:

```
"app" < "apple"
```

---

## 🔑 Key Idea Used in Both Solutions

Alien alphabet order is converted into a **ranking system**:

```
character → position in alien alphabet
```

Once we have ranks, comparison becomes straightforward.

---

# 🧪 Solution 1: Readable / Brute-Style (Using Hash Map)

### 💡 Intuition

- Convert alien order into a map: `char → rank`
- Compare each **adjacent pair** of words
- For each pair:
  - Compare characters one by one
  - Decide order at first mismatch
  - If no mismatch → apply prefix rule

This approach prioritizes **clarity and readability**.

---

### ✅ Code (Readable Version)

```cpp
class Solution {
private:
    unordered_map<char,int> mapp;

    bool checkStrings(string s1, string s2) {
        int i = 0, j = 0;

        while (i < s1.size() && j < s2.size()) {
            if (mapp[s1[i]] == mapp[s2[j]]) {
                i++; j++;
                continue;
            }
            if (mapp[s1[i]] > mapp[s2[j]])
                return false;
            return true;
        }

        // Prefix rule
        if (i != s1.size())
            return false;

        return true;
    }

public:
    bool isAlienSorted(vector<string>& words, string order) {
        int cnt = 0;
        for (char c : order)
            mapp[c] = cnt++;

        for (int i = 1; i < words.size(); i++) {
            if (!checkStrings(words[i-1], words[i]))
                return false;
        }
        return true;
    }
};
```

---

### 🧠 Why This Works

- First mismatch decides order
- Prefix case handled explicitly
- Adjacent comparison is sufficient (no need to compare all pairs)

---

### ⏱️ Complexity

- **Time:** `O(N × L)`
- **Space:** `O(26)` (hash map)

Where:

- `N` = number of words
- `L` = max length of a word

---

# ⚡ Solution 2: Optimized (Using Fixed Array Instead of Hash Map)

### 💡 Optimization Idea

Since:

- characters are only `'a'` to `'z'`
- alphabet size is fixed (26)

We can replace `unordered_map` with a simple **array** for faster access and cleaner code.

---

### ✅ Code (Optimized Version)

```cpp
class Solution {
private:
    int rank[26];

    bool checkStrings(string& s1, string& s2) {
        int i = 0;
        while (i < s1.size() && i < s2.size()) {
            if (rank[s1[i] - 'a'] == rank[s2[i] - 'a']) {
                i++;
                continue;
            }
            return rank[s1[i] - 'a'] < rank[s2[i] - 'a'];
        }
        return s1.size() <= s2.size();
    }

public:
    bool isAlienSorted(vector<string>& words, string order) {
        for (int i = 0; i < 26; i++)
            rank[order[i] - 'a'] = i;

        for (int i = 1; i < words.size(); i++) {
            if (!checkStrings(words[i-1], words[i]))
                return false;
        }
        return true;
    }
};
```

---

### 🚀 Why This Is Better

- No hashing overhead
- Faster constant-time access
- Preferred in interviews and competitive programming

---

### ⏱️ Complexity

- **Time:** `O(N × L)`
- **Space:** `O(26)` (constant)

---

## 🆚 Comparison of Both Approaches

| Aspect             | Readable (Map) | Optimized (Array) |
| ------------------ | -------------- | ----------------- |
| Readability        | ⭐⭐⭐⭐       | ⭐⭐⭐            |
| Performance        | ⭐⭐⭐         | ⭐⭐⭐⭐          |
| Interview-friendly | ✅             | ✅                |
| Beginner-friendly  | ✅             | ⚠️                |
