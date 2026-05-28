# 3093. Longest Common Suffix Queries

## Intuition

For every query string, we need to find a word in `wordsContainer` having the **longest common suffix**.

A Trie normally helps with **prefix matching**, not suffix matching.

### Key observation

If we reverse every word:

```text
suffix match → prefix match
```

Example:

```text
abcd → dcba
bcd  → dcb
```

Both original words end with `"bcd"`.

After reversing:

```text
dcba
dcb
```

Now they start with `"dcb"`.

So:

> Longest common suffix problem becomes longest common prefix problem after reversing.

---

# Data stored in each Trie node

Each Trie node stores:

### `child[26]`

Pointers to next characters.

---

### `minLen`

Shortest word length among all words passing through this node.

Used because:

If multiple words share same suffix,
we need the shortest word.

---

### `bestIndex`

Index of that shortest word.

If two words have same length,
store smaller index.

---

# Building the Trie

Insert all container words **from end → start**.

While inserting:

Update every node:

```text
Among all words reaching this node,
which one is the best candidate?
```

Store:

```text
minLen
bestIndex
```

---

# Querying

For each query:

Traverse the Trie from end → start.

Keep moving while character exists.

When traversal stops:

Current node represents the **longest matched suffix**.

Return:

```cpp
curr->bestIndex
```

---

# Example

## wordsContainer

```text
["abcd", "bcd", "xbcd"]
```

Inserted in reverse:

```text
dcba
dcb
dcbx
```

Trie:

```text
root
 |
 d
 |
 c
 |
 b
/ \
a  x
```

---

## Query `"cd"`

Traverse backwards:

```text
d -> c
```

Stop at node `c`

Node `c` stores:

```text
bestIndex = 1
```

Answer:

```text
wordsContainer[1] = "bcd"
```

---

# Complexity Analysis

Let:

* `N = total characters in wordsContainer`
* `Q = total characters in wordsQuery`

---

## Time Complexity

### Build Trie

```text
O(N)
```

Each character inserted once.

---

### Query

```text
O(Q)
```

Each query character traversed once.

---

### Total

```text
O(N + Q)
```

---

## Space Complexity

Trie stores every inserted character once.

```text
O(N)
```

---

# C++ Solution

```cpp
class TrieNode {
public:
    TrieNode* child[26];
    int bestIndex;
    int minLen;

    TrieNode() {
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;

        bestIndex = 1e9;
        minLen = 1e9;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (child[i]) delete child[i];
        }
    }
};

class Trie {
public:
    TrieNode* root = new TrieNode();

    ~Trie() {
        delete root;
    }

    void update(TrieNode* node, int len, int idx) {
        if (node->minLen > len ||
            (node->minLen == len && node->bestIndex > idx)) {
            node->minLen = len;
            node->bestIndex = idx;
        }
    }

    void insert(string& s, int index) {
        TrieNode* curr = root;
        int len = s.size();

        update(curr, len, index);

        for (int i = len - 1; i >= 0; i--) {
            int c = s[i] - 'a';

            if (!curr->child[c])
                curr->child[c] = new TrieNode();

            curr = curr->child[c];

            update(curr, len, index);
        }
    }

    int getBestIndex(string& s) {
        TrieNode* curr = root;

        for (int i = s.size() - 1; i >= 0; i--) {
            int c = s[i] - 'a';

            if (!curr->child[c])
                break;

            curr = curr->child[c];
        }

        return curr->bestIndex;
    }
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        Trie trie;

        for (int i = 0; i < wordsContainer.size(); i++) {
            trie.insert(wordsContainer[i], i);
        }

        vector<int> ans;

        for (string& q : wordsQuery) {
            ans.push_back(trie.getBestIndex(q));
        }

        return ans;
    }
};
```
