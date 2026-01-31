# 📘 Clone Graph (LeetCode 133)

---

## 🧠 Problem Intuition

You are given a reference to a node in an **undirected connected graph**.

Each node contains:

- an integer value `val`
- a list of its neighbors

👉 Task: **Create a deep copy (clone) of the graph**, such that:

- every original node has **exactly one cloned node**
- edges in the cloned graph connect **only cloned nodes**
- the structure of the graph remains identical

---

## 🔑 Core Insight (MOST IMPORTANT)

Graphs may contain:

- cycles
- shared neighbors

So while cloning:

- **you cannot create a new node every time you see a node**
- you must **remember which nodes are already cloned**

👉 This is why **mapping is mandatory**.

```
original node → cloned node
```

Without this mapping:

- duplicate nodes are created
- cycles cause infinite loops
- graph structure breaks

---

## 🧩 Key Technique Used

Both approaches rely on:

```cpp
unordered_map<Node*, Node*> mapp;
```

Purpose:

- ensures **1-to-1 mapping**
- acts as both **visited set** and **clone lookup**

---

# 🟢 Approach 1: DFS (Recursive)

### 💡 Idea

- Use DFS to traverse the graph
- For each node:
  - If already cloned → return it
  - Otherwise:
    - Create a clone
    - Recursively clone all neighbors
    - Connect cloned neighbors

---

### ✅ DFS Code

```cpp
class Solution {
private:
    unordered_map<Node*, Node*> mapp;

    Node* dfs(Node* node) {
        if (node == nullptr)
            return nullptr;

        if (mapp.count(node))
            return mapp[node];

        Node* copy = new Node(node->val);
        mapp[node] = copy;

        for (Node* nei : node->neighbors) {
            copy->neighbors.push_back(dfs(nei));
        }

        return copy;
    }

public:
    Node* cloneGraph(Node* node) {
        return dfs(node);
    }
};
```

---

### 🧠 Why DFS Works

- Recursively explores the graph
- Mapping prevents infinite recursion in cycles
- Each node is cloned **once**

---

# 🔵 Approach 2: BFS (Iterative)

### 💡 Idea

- Use BFS traversal with a queue
- Clone nodes level by level
- When visiting neighbors:
  - Clone if not already cloned
  - Connect current clone to neighbor clone

---

### ✅ BFS Code

```cpp
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node)
            return nullptr;

        unordered_map<Node*, Node*> mapp;
        queue<Node*> q;

        mapp[node] = new Node(node->val);
        q.push(node);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            for (Node* nei : curr->neighbors) {
                if (mapp.find(nei) == mapp.end()) {
                    mapp[nei] = new Node(nei->val);
                    q.push(nei);
                }
                mapp[curr]->neighbors.push_back(mapp[nei]);
            }
        }

        return mapp[node];
    }
};
```

---

### 🧠 Why BFS Works

- Iterative traversal avoids recursion depth
- Mapping ensures no duplicate nodes
- Cycles are handled safely

---

## 🆚 DFS vs BFS Comparison

| Aspect               | DFS             | BFS       |
| -------------------- | --------------- | --------- |
| Traversal            | Recursive       | Iterative |
| Stack usage          | Recursion stack | Queue     |
| Cycle handling       | Map-based       | Map-based |
| Interview acceptance | ✅              | ✅        |

---

## ⏱️ Complexity Analysis

Let:

- `V` = number of nodes
- `E` = number of edges

### Time Complexity

```
O(V + E)
```

Each node and edge is processed once.

### Space Complexity

```
O(V)
```

For:

- clone map
- recursion stack (DFS) or queue (BFS)

---

## 🔒 Key Takeaways (VERY IMPORTANT)

- Graph cloning **always requires mapping**
- Never create a clone without checking the map
- Graph ≠ Tree → cycles exist
- Mapping acts as both:
  - visited set
  - clone reference
