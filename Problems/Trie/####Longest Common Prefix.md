# 14. Longest Common Prefix

## Intuition

We need to find the **longest prefix common to all strings**.

A Trie is a natural fit because:

> Trie stores words character by character from left to right.

So common prefix simply means:

> how far we can move from the root while all words still share the same path.

---

## Key Observation

While traversing the Trie:

We can continue only if:

### 1. Current node has exactly **one child**

Meaning all strings still follow the same path.

### 2. Current node is **not end of a word**

If one word ends here, common prefix cannot go beyond this point.

---

# Approach

### Step 1 — Insert all strings into Trie

Each character creates or follows a Trie node.

Mark last node:

```cpp id="nfxv8w"
isEnd = true
```

---

### Step 2 — Traverse from root

Move downward while:

```text id="i9nv03"
exactly one child exists
and
current node is not end of word
```

Append that character into answer.

---

### Step 3 — Stop when:

* node has more than one child → branching starts
* node is end of word → one word ended

Then return built prefix.

---

# Example

Input:

```text id="8egfbj"
["flower", "flow", "flight"]
```

---

Trie:

```text id="y4iw8l"
root
 |
 f
 |
 l
 / \
o   i
```

---

Traversal:

### root

1 child → `f`

answer:

```text id="fpn0s9"
"f"
```

---

### node `f`

1 child → `l`

answer:

```text id="grvhvd"
"fl"
```

---

### node `l`

2 children:

```text id="nrv2rd"
o
i
```

Branch found.

Stop.

Return:

```text id="hzj3t8"
"fl"
```

---

# Complexity Analysis

Let:

* `N` = number of strings
* `M` = total characters across all strings

---

## Time Complexity

### Insert

Each character inserted once:

```text id="4u7wkm"
O(M)
```

---

### Prefix Search

At most traverse smallest prefix length:

```text id="6x0xyq"
O(L)
```

where `L` = longest common prefix length

---

## Total

```text id="lzok8e"
O(M)
```

---

## Space Complexity

Trie stores every character once:

```text id="wcf2yz"
O(M)
```

---

# C++ Solution

```cpp id="b7f6ci"
struct TrieNode {
    TrieNode* child[26];
    bool isEnd;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            child[i] = nullptr;
        }
        isEnd = false;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (child[i]) {
                delete child[i];
            }
        }
    }
};

class Trie {
public:
    TrieNode* root = new TrieNode();

    ~Trie() {
        delete root;
    }

    void insert(string& s) {
        TrieNode* curr = root;

        for (char ch : s) {
            int idx = ch - 'a';

            if (!curr->child[idx]) {
                curr->child[idx] = new TrieNode();
            }

            curr = curr->child[idx];
        }

        curr->isEnd = true;
    }

    string findCommonPrefix() {
        TrieNode* curr = root;
        string res = "";

        while (curr) {
            if (curr->isEnd)
                break;

            int cnt = 0;
            int nextIndex = -1;

            for (int i = 0; i < 26; i++) {
                if (curr->child[i]) {
                    cnt++;
                    nextIndex = i;
                }
            }

            if (cnt != 1)
                break;

            res += char(nextIndex + 'a');
            curr = curr->child[nextIndex];
        }

        return res;
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        if (strs.size() == 1)
            return strs[0];

        Trie trie;

        for (string& s : strs) {
            trie.insert(s);
        }

        return trie.findCommonPrefix();
    }
};
```
