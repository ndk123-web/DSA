# 📘 Course Schedule (LeetCode – Medium)

---

## 🧠 Problem Summary

You are given `numCourses` courses labeled from `0` to `numCourses - 1`.

Each prerequisite `[a, b]` means:

> To take course `a`, you must first complete course `b`.

Your task is to determine **whether it is possible to finish all courses**.

This boils down to:

> **Does the directed graph contain a cycle or not?**

---

# ✅ Approach 1: DFS (Cycle Detection)

## 🔹 Intuition

If there is a **cycle** in course dependencies, then it is **impossible** to complete all courses.

DFS helps us detect cycles by tracking the **current recursion path**.

- If during DFS we revisit a node that is already in the current path → **cycle detected**
- If no cycle exists → all courses can be completed

---

## 🔹 Key Idea

- Use a `visited` set to represent the **current DFS path**
- Once DFS finishes for a course, remove it from `visited`
- If any DFS returns `false`, answer is `false`

---

## 🔹 Approach

1. Build adjacency list:
   - `course → prerequisites`

2. For each course:
   - Run DFS

3. In DFS:
   - If course already in `visited` → cycle → return `false`
   - If no prerequisites → safe → return `true`
   - Otherwise DFS on prerequisites

4. If all DFS calls succeed → return `true`

---

## 🔹 Complexity

- **Time Complexity:** `O(V + E)`
- **Space Complexity:** `O(V + E)` (recursion stack + graph)

---

## 🔹 Code (DFS – Cycle Detection)

```cpp
class Solution {
private:
    unordered_set<int> visited;
    unordered_map<int, vector<int>> mapp;

    bool dfs(int course) {
        if (visited.count(course))
            return false; // cycle detected

        if (mapp[course].empty())
            return true; // no dependency

        visited.insert(course);
        for (int& pre : mapp[course]) {
            if (!dfs(pre))
                return false;
        }
        visited.erase(course);

        return true;
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        for (int i = 0; i < numCourses; i++)
            mapp[i] = {};

        for (auto& pre : prerequisites)
            mapp[pre[0]].push_back(pre[1]);

        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i))
                return false;
        }
        return true;
    }
};
```

---

## 🔑 Key Insight (DFS)

> **Cycle in dependency graph ⇒ cannot finish courses**

DFS directly answers:

> _“Is there any circular dependency?”_

---

# ✅ Approach 2: BFS (Kahn’s Algorithm – Indegree Optimized)

## 🔹 Intuition

A course can be taken **only when all its prerequisites are completed**.

So:

- Courses with `indegree = 0` can be taken immediately
- Completing a course reduces indegree of dependent courses
- If we can process all courses → no cycle

---

## 🔹 Definitions (Very Important)

- **indegree[i]** = number of prerequisites for course `i`
- **adj[u]** = list of courses that depend on `u`

---

## 🔹 Approach

1. Build graph:
   - `b → a` (because `a` depends on `b`)

2. Compute indegree for each course
3. Push all courses with `indegree = 0` into queue
4. BFS:
   - Pop course
   - Reduce indegree of neighbors
   - If indegree becomes 0 → push into queue

5. Count finished courses
6. If `finished == numCourses` → return `true`

---

## 🔹 Complexity

- **Time Complexity:** `O(V + E)`
- **Space Complexity:** `O(V + E)`

---

## 🔹 Code (BFS – Indegree / Kahn’s Algorithm)

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        queue<int> q;
        int finished = 0;

        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]); // b → a
            indegree[pre[0]]++;
        }

        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int course = q.front();
            q.pop();
            finished++;

            for (int& next : adj[course]) {
                indegree[next]--;
                if (indegree[next] == 0)
                    q.push(next);
            }
        }

        return finished == numCourses;
    }
};
```

---

## 🔑 Key Insight (BFS)

> **If all nodes can be removed by repeatedly deleting zero-indegree nodes, then the graph is acyclic.**

---

# 🔍 DFS vs BFS (Quick Comparison)

| Aspect           | DFS         | BFS (Indegree)         |
| ---------------- | ----------- | ---------------------- |
| Detects cycle    | ✅ Directly | ✅ Indirectly          |
| Uses recursion   | Yes         | No                     |
| Easier to reason | For cycles  | For scheduling         |
| Gives order      | ❌          | ✅ (with modification) |

---

## 🧠 Final Takeaway

- **DFS** answers: _“Is there a cycle?”_
- **BFS (Kahn)** answers: _“Can I finish all courses step by step?”_
- Both are valid and optimal
- BFS is preferred if course order is also required
