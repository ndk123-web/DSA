# 🧠 Intuition

The words are already sorted according to an unknown alien alphabet.

If two adjacent words differ at some position, then the first differing character tells us the order of those two letters.

Example:

```
"hrn"
"hrf"
```

At index 2:
`n != f`

Since `"hrn"` comes before `"hrf"`,
we conclude:

```
n < f
```

This gives us a **directed edge**:

```
n → f
```

If we collect all such constraints, we form a directed graph.

The problem then becomes:

> Find a valid ordering of characters that satisfies all directed edges.

This is exactly **Topological Sort**.

If the graph has a cycle, then no valid ordering exists.

---

# 🚀 Approach

### 1️⃣ Collect All Unique Characters

Every character appearing in the input must appear in the final answer — even if it has no edges.

We initialize their indegree to 0.

---

### 2️⃣ Build Directed Graph

For each adjacent pair of words:

- Compare character by character.

- Stop at the first differing character.

- Add a directed edge:

  ```
  word1[i] → word2[i]
  ```

- Increase indegree of `word2[i]`.

We stop after first difference because only that difference determines lexicographic order.

---

### ❗ Edge Case 1 — Invalid Prefix Case

Example:

```
["abc", "ab"]
```

Comparison:

- a == a
- b == b

No differing character found.

But first word is longer than second.

This is invalid because:

In lexicographic order, a prefix must come before the longer word.

Valid:

```
["ab", "abc"]
```

Invalid:

```
["abc", "ab"]
```

So if:

- No difference found
- And first word is longer

Return `""`.

---

### 3️⃣ Prevent Duplicate Edges

If the same ordering rule appears multiple times,
we must avoid incrementing indegree twice.

Before adding edge `u → v`,
check if it already exists.

---

### 4️⃣ Perform Topological Sort (Kahn’s Algorithm)

- Push all characters with indegree 0 into queue.
- Repeatedly:
  - Remove node from queue
  - Append to result
  - Decrease indegree of neighbors
  - Push neighbor when indegree becomes 0

---

### ❗ Edge Case 2 — Cycle Detection

If a cycle exists:

Example:

```
["z","x","z"]
```

We get:

```
z → x
x → z
```

Both nodes have indegree 1.
Queue starts empty.

No node can be processed.

If number of processed characters < total unique characters,
there is a cycle.

Return `""`.

---

### ❗ Edge Case 3 — Single Word Input

Example:

```
["abc"]
```

There are no constraints.
All characters are valid in any order.

Return all unique characters.

Our approach handles this because:
All characters have indegree 0 → all enter queue.

---

# ⏱ Complexity

- Time complexity:
  $$O(C + E)$$
  where
  C = total unique characters
  E = total edges (at most C²)

- Space complexity:
  $$O(C + E)$$
  for adjacency list and indegree map.

---

# 💻 Code

```cpp
class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, vector<char>> adj;
        unordered_map<char, int> indegree;

        // 1️⃣ Collect all unique characters
        for (string &word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }

        // 2️⃣ Build graph
        for (int i = 1; i < words.size(); i++) {
            string &a = words[i - 1];
            string &b = words[i];

            int len = min(a.size(), b.size());
            int j = 0;

            while (j < len && a[j] == b[j]) {
                j++;
            }

            // ❗ Prefix invalid case
            if (j == len) {
                if (a.size() > b.size()) {
                    return "";
                }
                continue;
            }

            char from = a[j];
            char to   = b[j];

            // prevent duplicate edges
            bool exists = false;
            for (char nei : adj[from]) {
                if (nei == to) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                adj[from].push_back(to);
                indegree[to]++;
            }
        }

        // 3️⃣ Topological Sort
        queue<char> q;
        for (auto &p : indegree) {
            if (p.second == 0) {
                q.push(p.first);
            }
        }

        string result;

        while (!q.empty()) {
            char curr = q.front();
            q.pop();

            result.push_back(curr);

            for (char nei : adj[curr]) {
                indegree[nei]--;
                if (indegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        // ❗ Cycle detection
        if (result.size() != indegree.size()) {
            return "";
        }

        return result;
    }
};
```
