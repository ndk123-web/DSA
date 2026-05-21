# Intuition

A brute force approach would compare every number in `arr1` with every number in `arr2` and calculate their common prefix length digit by digit.

However, this becomes too slow because:

```text
O(n × m × digits)
```

Instead of repeatedly comparing prefixes, we can preprocess all prefixes from `arr1` using a Trie.

A Trie naturally stores shared prefixes efficiently.
Each path in the Trie represents a digit sequence.

Then for every number in `arr2`, we simply traverse the Trie digit-by-digit and count how long the prefix matches.

---

# Approach

1. Create a Trie where each node stores children for digits `0-9`.
2. Insert all numbers from `arr1` into the Trie.
3. For every number in `arr2`:

   * convert it into a string
   * traverse the Trie digit-by-digit
   * stop when a digit path does not exist
   * count matched digits
4. Track the maximum matched prefix length.

---

# Complexity

* Time complexity:

```text
O((n + m) × d)
```

Where:

* `n = arr1.size()`
* `m = arr2.size()`
* `d = maximum number of digits`

---

* Space complexity:

```text
O(n × d)
```

For storing Trie nodes.

---

# Code

```cpp
struct TrieNode {
    bool isEnd;
    TrieNode* child[10];

    TrieNode() {
        isEnd = false;

        for (int i = 0; i < 10; i++) {
            child[i] = nullptr;
        }
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insertString(string s) {

        TrieNode* curr = root;

        for (char c : s) {

            int idx = c - '0';

            if (curr->child[idx] == nullptr) {
                curr->child[idx] = new TrieNode();
            }

            curr = curr->child[idx];
        }

        curr->isEnd = true;
    }

    int findMaxLen(string s) {

        TrieNode* curr = root;

        int cnt = 0;

        for (char c : s) {

            int idx = c - '0';

            // Prefix chain breaks
            if (curr->child[idx] == nullptr) {
                break;
            }

            cnt++;

            curr = curr->child[idx];
        }

        return cnt;
    }
};

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1,
                            vector<int>& arr2) {

        Trie trie;

        int mx = 0;

        // Build Trie using arr1
        for (int num : arr1) {

            trie.insertString(to_string(num));
        }

        // Find longest matching prefix
        for (int num : arr2) {

            mx = max(mx,
                     trie.findMaxLen(to_string(num)));
        }

        return mx;
    }
};
```
