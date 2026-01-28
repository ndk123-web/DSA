# 📘 Extra Characters in a String

**(Trie + Dynamic Programming)**

---

## 🧠 Problem Intuition

You are given:

- a string `s`
- a dictionary of valid words

You want to split `s` into **non-overlapping substrings** such that:

- each chosen substring exists in the dictionary
- some characters may be left unused (extra characters)

👉 **Goal:** minimize the number of extra characters left.

Dictionary words can be reused any number of times.

---

## 🔍 Key Observation

At any index `i` in the string, you have **two choices**:

1. Treat `s[i]` as an **extra character**
2. Try to match **any dictionary word starting at index `i`**

The optimal answer depends on making the best choice at every index.

This is a classic **optimal substructure** → Dynamic Programming.

---

## 🧩 DP Definition

Let:

```
dp[i] = minimum extra characters in substring s[i ... end]
```

Final answer will be:

```
dp[0]
```

---

## 🧠 DP Transition (Core Logic)

At index `i`:

### Option 1: Skip current character

Treat `s[i]` as extra.

```
cost = 1 + dp[i + 1]
```

---

### Option 2: Use a dictionary word starting at `i`

If substring `s[i...j]` is a valid dictionary word:

```
cost = dp[j + 1]
```

Because:

- characters `i` to `j` are covered by a word
- extra characters depend only on the remaining suffix

---

### DP Formula

```
dp[i] = min(
    1 + dp[i+1],
    dp[j+1] for all dictionary words s[i...j]
)
```

---

## 🌳 Why Trie?

Without Trie:

- for every index `i`, you'd check **every dictionary word**
- inefficient

With Trie:

- walk character by character from index `i`
- stop immediately when no word matches
- efficiently detect all dictionary words starting at `i`

👉 Trie is a **helper for fast prefix matching**, DP is the main logic.

---

## 🧠 Important Mental Model (VERY IMPORTANT)

- `i` and `j` → indices in string `s`
- `curr` → pointer inside Trie
- `j` and `curr` always move **together**
- when `curr->isEnd == true`, it means:

```
s[i...j] is a valid dictionary word
```

So we can safely jump to `dp[j+1]`.

---

## 🧪 Example Walkthrough

```
s = "neetcodes"
dictionary = ["neet", "code", "neetcode"]
```

Best split:

```
"neet" + "code" + "s"
```

Extra characters = `1`

DP builds from right to left:

- `dp[8] = 1` ("s")
- `dp[4] = 1` ("code" + dp[8])
- `dp[0] = 1` ("neet" + dp[4])

Answer = `dp[0] = 1`

---

## ✅ Implementation

```cpp
struct TrieNode {
    TrieNode* next[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            next[i] = nullptr;
    }
};

class Solution {
private:
    TrieNode* root;

    void insertStr(string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->next[idx])
                curr->next[idx] = new TrieNode();
            curr = curr->next[idx];
        }
        curr->isEnd = true;
    }

public:
    int minExtraChar(string s, vector<string>& dictionary) {
        root = new TrieNode();

        // Build Trie
        for (auto& word : dictionary)
            insertStr(word);

        int n = s.size();
        vector<int> dp(n + 1, 0);

        // Bottom-up DP
        for (int i = n - 1; i >= 0; i--) {
            // Option 1: skip character
            dp[i] = 1 + dp[i + 1];

            // Option 2: match dictionary words using Trie
            TrieNode* curr = root;
            for (int j = i; j < n; j++) {
                int idx = s[j] - 'a';
                if (!curr->next[idx])
                    break;

                curr = curr->next[idx];
                if (curr->isEnd) {
                    dp[i] = min(dp[i], dp[j + 1]);
                }
            }
        }
        return dp[0];
    }
};
```

---

## ⏱️ Time Complexity

- **Trie construction:**
  `O(total characters in dictionary)`

- **DP computation:**
  Worst case: `O(n²)`
  (each index `i` walks forward until Trie path breaks)

Efficient in practice due to early Trie pruning.

---

## 🧠 Why Greedy Fails

Greedy choices like:

- “always take longest word”
- “always take shortest word”

can fail because:

- local best choice does not guarantee global minimum extras

DP ensures **global optimality**.

---

## 📌 Final Takeaways

- This is a **string segmentation + optimization** problem
- DP decides **what to do**
- Trie helps decide **what is possible**
- `dp[j+1]` means “skip the whole matched word”

Once this clicks:

- Word Break
- Autocomplete
- Dictionary segmentation
- NLP tokenization

all become natural extensions.

---

### 🔒 One-line Lock

> **If a word covers `s[i…j]`, then extra characters depend only on `j+1` onward.**
