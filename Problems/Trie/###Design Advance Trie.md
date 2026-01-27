# 📘 Word Dictionary (Trie + DFS with Wildcard)

### Problem

Design a data structure that supports adding words and searching words with the `.` wildcard, where:

- `.` can match **any single lowercase letter**
- Words consist of lowercase English letters only

---

## 💡 Intuition

Normal Trie search works by following **one fixed path**.

But the wildcard `.` breaks this rule:

- `.` does **not** represent a character
- It represents **26 possibilities**

So the moment we see `.`, we cannot continue linearly.
We must **branch out and try all valid paths**.

That means:

> **Trie + DFS (backtracking)**

---

## 🧠 Key Insight

- Trie stores words efficiently using shared prefixes
- `search()` becomes recursive because:
  - Normal character → single path
  - `.` → multiple paths (branching)

---

## 🧱 Data Structure Used

### TrieNode

Each node contains:

- `ch` → character
- `others[26]` → pointers to next letters
- `isEnd` → marks completion of a word

```cpp
struct TrieNode {
    char ch;
    vector<TrieNode*> others;
    bool isEnd;
};
```

Root node is a dummy node and does not represent any character.

---

## 🛠️ Approach

### 1️⃣ Add Word

- Start from root
- For each character:
  - Create node if it doesn’t exist
  - Move to that node

- Mark the last node as `isEnd = true`

---

### 2️⃣ Search Word (with wildcard)

We use **DFS**:

#### Recursive function parameters:

- `word` → input word
- `node` → current Trie node
- `idx` → current index in word

#### Base Case:

- If `idx == word.length()`
  - Return `node->isEnd`

#### Case 1: Current character is `.`

- Try **all 26 children**
- If any path returns true → return true
- Else → return false

#### Case 2: Normal character

- If path doesn’t exist → return false
- Else → continue DFS on that path

---

## ✅ Correct Solution Code

```cpp
struct TrieNode {
    char ch;
    vector<TrieNode*> others;
    bool isEnd;

    TrieNode(char ch) {
        this->ch = ch;
        isEnd = false;
        others.resize(26, nullptr);
    }
};

class WordDictionary {
private:
    TrieNode* root;

    bool dfs(string& word, TrieNode* node, int idx) {
        if (idx == word.size())
            return node->isEnd;

        char ch = word[idx];

        if (ch == '.') {
            for (int i = 0; i < 26; i++) {
                if (node->others[i] != nullptr) {
                    if (dfs(word, node->others[i], idx + 1))
                        return true;
                }
            }
            return false;
        } else {
            if (node->others[ch - 'a'] == nullptr)
                return false;

            return dfs(word, node->others[ch - 'a'], idx + 1);
        }
    }

public:
    WordDictionary() {
        root = new TrieNode('\0');
    }

    void addWord(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->others[c - 'a'] == nullptr)
                curr->others[c - 'a'] = new TrieNode(c);

            curr = curr->others[c - 'a'];
        }
        curr->isEnd = true;
    }

    bool search(string word) {
        return dfs(word, root, 0);
    }
};
```

---

## ⏱️ Time Complexity

### Add Word

- **O(L)** where `L` is word length

### Search

- Best case: **O(L)**
- Worst case (all `.`): **O(26^L)**
  (branching at each level)

In practice, pruning happens early, so performance is good.

---

## 🧠 Why DFS is Mandatory Here

You **cannot** solve this with:

- Simple loops
- Single pointer traversal

Because wildcard means:

> “Try all possibilities and backtrack if needed”

That’s exactly what DFS is built for.

---

## 🚨 Common Mistakes (That You Avoided)

- Treating `.` like a normal character ❌
- Forgetting `isEnd = true` ❌
- Missing return after DFS ❌
- Out-of-bounds vector access ❌

---

## 📌 Final Takeaway

This problem is a **perfect example** of:

- Trie + recursion
- Linear vs branching traversal
- When brute force becomes elegant with pruning

Once you understand this, you also understand:

- Autocomplete
- Regex matching (basic)
- Search engines
- Spell checkers

This is **real engineering logic**, not just LeetCode.
