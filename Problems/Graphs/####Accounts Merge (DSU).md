# 🧩 Accounts Merge — Solution 1

## Disjoint Set Union (Union-Find) with Path Compression

---

## # Intuition

Each email can be treated as a node in a graph.

If two emails appear in the same account, they belong to the same person, so we connect them.

The problem reduces to:

> Finding connected components among emails.

Union-Find efficiently groups connected emails into the same component.

---

## # Approach

1. **Initialize DSU**
   - Each email is its own parent.
   - Maintain a mapping `email → owner name`.

2. **Union Emails**
   - For each account:
     - Take the first email as base.
     - Union it with every other email in that account.

3. **Path Compression**
   - While finding root, compress the path:

     ```
     parent[x] = find(parent[x])
     ```

   - This flattens the tree and makes future operations faster.

4. **Group Emails by Root**
   - For every email:
     - Find its root.
     - Group emails sharing the same root.

5. **Build Result**
   - Sort each group’s emails.
   - Insert the owner's name at index 0.
   - Return the result.

---

## # Complexity

Let:

- N = total number of emails

### Time Complexity

- With path compression:
  **O(N α(N))**, where α is inverse Ackermann (almost constant)

### Space Complexity

- **O(N)**

---

## # Code

```cpp
class Solution {
private:
    unordered_map<string,string> parent;
    unordered_map<string,string> owner;

    string find(string s) {
        if (parent[s] == s)
            return s;
        return parent[s] = find(parent[s]);  // path compression
    }

    void unite(string a, string b) {
        string pa = find(a);
        string pb = find(b);
        if (pa != pb)
            parent[pb] = pa;
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {

        // Initialize DSU
        for (auto &acc : accounts) {
            string name = acc[0];
            for (int i = 1; i < acc.size(); i++) {
                parent[acc[i]] = acc[i];
                owner[acc[i]] = name;
            }
        }

        // Union emails
        for (auto &acc : accounts) {
            string base = acc[1];
            for (int i = 2; i < acc.size(); i++) {
                unite(base, acc[i]);
            }
        }

        // Group emails by root
        unordered_map<string, vector<string>> groups;
        for (auto &p : parent) {
            string email = p.first;
            string root = find(email);
            groups[root].push_back(email);
        }

        // Build result
        vector<vector<string>> res;
        for (auto &g : groups) {
            vector<string> emails = g.second;
            sort(emails.begin(), emails.end());
            emails.insert(emails.begin(), owner[g.first]);
            res.push_back(emails);
        }

        return res;
    }
};
```

---

---

# 🧩 Accounts Merge — Solution 2

## Disjoint Set Union without Path Compression

---

## # Intuition

The core idea remains the same:

- Emails are nodes.
- Accounts create connections.
- Connected emails belong to the same person.

However, in this version, we do not apply path compression during `find()`.

---

## # Approach

1. Initialize each email as its own parent.
2. Store `email → owner`.
3. Union all emails in the same account.
4. Group emails by root.
5. Sort each group and attach owner.

Without path compression, the DSU tree can become deep, making `find()` slower.

---

## # Complexity

Let:

- N = total number of emails

### Time Complexity

- Worst case: **O(N²)**
  (because DSU trees may become skewed)

### Space Complexity

- **O(N)**

---

## # Code

```cpp
class Solution {
private:
    unordered_map<string,string> parent;
    unordered_map<string,string> owner;

    string find(string s) {
        if (parent[s] == s)
            return s;
        return find(parent[s]);  // no path compression
    }

    void unite(string a, string b) {
        string pa = find(a);
        string pb = find(b);
        if (pa != pb)
            parent[pb] = pa;
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {

        for (auto &acc : accounts) {
            string name = acc[0];
            for (int i = 1; i < acc.size(); i++) {
                parent[acc[i]] = acc[i];
                owner[acc[i]] = name;
            }
        }

        for (auto &acc : accounts) {
            string base = acc[1];
            for (int i = 2; i < acc.size(); i++) {
                unite(base, acc[i]);
            }
        }

        unordered_map<string, vector<string>> groups;
        for (auto &p : parent) {
            string email = p.first;
            string root = find(email);
            groups[root].push_back(email);
        }

        vector<vector<string>> res;
        for (auto &g : groups) {
            vector<string> emails = g.second;
            sort(emails.begin(), emails.end());
            emails.insert(emails.begin(), owner[g.first]);
            res.push_back(emails);
        }

        return res;
    }
};
```

---

# 🔥 Final Takeaway

- This is a classic **connected components** problem.
- DSU is natural fit.
- Path compression turns it from quadratic worst-case to near-linear performance.
- Name is only a label — merging logic depends solely on email connectivity.
