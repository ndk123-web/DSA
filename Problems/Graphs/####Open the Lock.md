# 🔐 Open the Lock (BFS)

---

## 🧠 Intuition

The lock can be seen as a **graph of states** where:

- Each state is a 4-digit string from `"0000"` to `"9999"`
- From any state, we can rotate **one wheel at a time**:
  - `+1` or `-1` (circular: `9 → 0`, `0 → 9`)

- Each move costs **1 turn**

We need the **minimum number of turns** to reach the `target`, while avoiding `deadends`.

👉 Whenever a problem asks for _minimum steps_, **BFS** is the correct choice.

---

## 🔁 Key Observations

- Total states = `10^4 = 10000` (small enough for BFS)
- Each state has **8 neighbors** (4 wheels × 2 rotations)
- A `deadend` or `visited` state should never be revisited
- **The first time we reach the target in BFS = minimum turns**

---

# ✅ Solution 1: Simple BFS (Filtering in BFS Loop)

### 💡 Idea

- Generate **all possible children** for a state
- In the BFS loop:
  - Skip states already in `deadends / visited`
  - Mark visited **when pushing into the queue**

This keeps `children()` simple and makes BFS the single source of truth.

---

## 🛠 Approach

1. Store all `deadends` in a set
2. If `"0000"` is a deadend → return `-1`
3. Start BFS from `"0000"`
4. For each state:
   - Generate all neighbors
   - Skip visited / deadends
   - Push valid neighbors with `turns + 1`

5. If target is found → return turns
6. If BFS ends → return `-1`

---

## ⏱ Complexity

- **Time:** `O(10^4 × 8)` ≈ `O(1)`
- **Space:** `O(10^4)` (queue + visited set)

---

## 💻 Code (Solution 1)

```cpp
class Solution {
private:
    vector<string> childrens(string lock) {
        vector<string> res;
        for (int i = 0; i < 4; i++) {
            string next = lock;
            next[i] = (next[i] - '0' + 1) % 10 + '0';
            res.push_back(next);

            next = lock;
            next[i] = (next[i] - '0' + 9) % 10 + '0';
            res.push_back(next);
        }
        return res;
    }

public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> visited(deadends.begin(), deadends.end());
        if (visited.count("0000")) return -1;

        queue<pair<string,int>> q;
        q.push({"0000", 0});
        visited.insert("0000");

        while (!q.empty()) {
            auto [lock, turns] = q.front();
            q.pop();

            for (string child : childrens(lock)) {
                if (visited.count(child)) continue;
                if (child == target) return turns + 1;

                visited.insert(child);
                q.push({child, turns + 1});
            }
        }
        return -1;
    }
};
```

---

# ✅ Solution 2: Optimized BFS (Filtering in `children()`)

### 💡 Idea

- Use the same BFS logic
- **Prune early** by filtering deadends/visited states inside `children()`
- Slightly reduces unnecessary state generation

---

## 🛠 Approach

1. Use a global `unordered_set` for both `deadends` and `visited`
2. While generating children:
   - Only return states **not present in the set**

3. BFS logic remains the same

---

## ⏱ Complexity

- **Time:** `O(10^4)`
- **Space:** `O(10^4)`

(Same complexity, slightly cleaner runtime behavior)

---

## 💻 Code (Solution 2)

```cpp
class Solution {
private:
    unordered_set<string> sett;
    queue<pair<string,int>> q;

    vector<string> childrens(string& lock) {
        vector<string> res;
        for (int i = 0; i < 4; i++) {
            string next = lock;
            next[i] = (next[i] - '0' + 1) % 10 + '0';
            if (!sett.count(next))
                res.push_back(next);

            next = lock;
            next[i] = (next[i] - '0' + 9) % 10 + '0';
            if (!sett.count(next))
                res.push_back(next);
        }
        return res;
    }

public:
    int openLock(vector<string>& deadends, string target) {
        for (string& s : deadends)
            sett.insert(s);

        if (sett.count("0000")) return -1;
        if (target == "0000") return 0;

        q.push({"0000", 0});
        sett.insert("0000");

        while (!q.empty()) {
            auto [lock, turns] = q.front();
            q.pop();

            for (string& child : childrens(lock)) {
                if (child == target)
                    return turns + 1;

                sett.insert(child);
                q.push({child, turns + 1});
            }
        }
        return -1;
    }
};
```
