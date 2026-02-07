# Course Schedule II (Topological Sort)

---

## 🔍 What is Topological Sort? (actual meaning)

**Topological sort** means:

> Arrange nodes of a **directed graph** such that
> for every dependency `b → a`, **`b` appears before `a`** in the ordering.

In this problem:

- `[a, b]` means **b must be taken before a**
- So order must respect **dependencies**
- If there is a **cycle**, ordering is impossible

---

# ✅ Solution 1: DFS + Topological Sort (Post-order)

### 🧠 Intuition

- Use DFS to detect **cycles**
- Add a course to the order **after all its prerequisites are processed**
- This is called **post-order DFS**
- Use:
  - `visit` → current recursion path (cycle detection)
  - `seen` → already added to result

---

### ⚙️ Approach

1. Build graph: `course → prerequisites`
2. Run DFS for each course
3. If a course appears again in the current DFS path → cycle
4. Add course to order after DFS finishes
5. If no cycle → return order

---

### ⏱ Complexity

- **Time:** `O(V + E)`
- **Space:** `O(V + E)`

---

### 💻 Code (DFS + Topological)

```cpp
class Solution {
private:
    unordered_set<int> visit;   // current DFS path
    unordered_set<int> seen;    // already added to order
    vector<int> order;
    unordered_map<int, vector<int>> mapp;

    bool dfs(int course) {
        if (visit.count(course))
            return false; // cycle

        if (mapp[course].empty()) {
            if (!seen.count(course)) {
                seen.insert(course);
                order.push_back(course);
            }
            return true;
        }

        visit.insert(course);
        for (auto& pre : mapp[course]) {
            if (!dfs(pre))
                return false;
        }
        visit.erase(course);

        if (!seen.count(course)) {
            seen.insert(course);
            order.push_back(course);
        }
        return true;
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& pres) {
        for (auto& pre : pres)
            mapp[pre[0]] = {};

        for (auto& pre : pres)
            mapp[pre[0]].push_back(pre[1]);

        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i))
                return {};
        }

        return order;
    }
};
```

---

# ✅ Solution 2: BFS + Indegree (Kahn’s Algorithm) ✅ (Recommended)

### 🧠 Intuition

- A course with **indegree = 0** has no prerequisites
- Such courses can be taken immediately
- After taking a course, reduce indegree of dependent courses
- If all courses are processed → valid order
- Otherwise → cycle exists

---

### ⚙️ Approach

1. Build graph: `b → a`
2. Compute indegree for each course
3. Push all `indegree = 0` courses into queue
4. BFS:
   - Pop course
   - Add to result
   - Reduce indegree of neighbors

5. If result size < numCourses → cycle

---

### ⏱ Complexity

- **Time:** `O(V + E)`
- **Space:** `O(V + E)`

---

### 💻 Code (BFS + Indegree)

```cpp
class Solution {
private:
    vector<vector<int>> adj;
    vector<int> indegree;

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& pres) {
        adj.assign(numCourses, {});
        indegree.assign(numCourses, 0);
        queue<int> q;
        vector<int> res;

        for (auto& pre : pres) {
            indegree[pre[0]]++;            // a depends on b
            adj[pre[1]].push_back(pre[0]); // b → a
        }

        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int course = q.front();
            q.pop();
            res.push_back(course);

            for (auto& nei : adj[course]) {
                if (--indegree[nei] == 0)
                    q.push(nei);
            }
        }

        if (res.size() != numCourses)
            return {}; // cycle

        return res;
    }
};
```

---

## 🧠 Final Takeaway (important)

> **Topological sort ensures dependency order.**
> DFS does it using **post-order**,
> BFS does it using **indegree = 0 elimination**.

---

### 🔥 Recommendation (honest)

- DFS solution → good for understanding cycles
- **BFS (Kahn) → best for interviews & clarity**
