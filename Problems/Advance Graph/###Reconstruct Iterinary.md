# Reconstruct Itinerary

## Problem Summary

We are given a list of flight tickets where each ticket is represented as:

```
[from, to]
```

All tickets:

- Form a valid itinerary
- Must be used exactly once
- Start from `"JFK"`
- If multiple itineraries exist, return the lexicographically smallest one

---

## Intuition

This problem is not a simple DFS traversal.

Key phrase:

> “Use each ticket exactly once”

That is the definition of an **Eulerian Path** in a directed graph.

An Eulerian Path is a path that uses every edge exactly once.

So we convert the problem:

- Airports → Nodes
- Tickets → Directed edges
- Find Eulerian Path starting from `"JFK"`

Additionally, we must ensure:

- When multiple outgoing edges exist,
- Always choose the lexicographically smallest one.

This is solved using **Hierholzer’s Algorithm**.

---

## Approach: Hierholzer’s Algorithm (DFS Based)

### Why Hierholzer?

For an Eulerian path in a directed graph:

- We traverse edges greedily
- Remove edges once used
- Add nodes to result only when no outgoing edges remain

This builds the path in reverse order.

---

## Algorithm Steps

1. Build adjacency list:
   - Use `unordered_map<string, min-heap>`
   - Min-heap ensures lexicographically smallest airport first

2. Perform DFS:
   - While current node has outgoing edges:
     - Pick smallest destination
     - Remove edge (pop from heap)
     - DFS(next)

   - When no edges left:
     - Add node to result

3. Reverse the result.

---

## Code

```cpp
class Solution {
private:
    unordered_map<string,
                  priority_queue<string, vector<string>, greater<string>>>
        adj;
    vector<string> res;

    void dfs(string node) {

        while (!adj[node].empty()) {
            string next = adj[node].top();
            adj[node].pop();  // consume ticket
            dfs(next);
        }

        res.push_back(node);  // postorder add
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {

        for (vector<string>& tick : tickets) {
            adj[tick[0]].push(tick[1]);
        }

        dfs("JFK");

        reverse(res.begin(), res.end());
        return res;
    }
};
```

---

## Why It Works

### 1. Edge Consumption

We remove edges as soon as we use them:

```
adj[node].pop();
```

This guarantees each ticket is used exactly once.

---

### 2. Postorder Insertion

We add node to result only after exploring all outgoing edges:

```
res.push_back(node);
```

This constructs the path in reverse.

Why?

Because in Eulerian traversal, when we hit a dead end, we record the node and backtrack.

---

### 3. Lexicographically Smallest Path

Using a min-heap:

```
priority_queue<string, vector<string>, greater<string>>
```

ensures smallest airport is always chosen first.

Thus among all valid Eulerian paths, we get the lexicographically smallest one.

---

## Example Dry Run

Input:

```
[["HOU","JFK"],
 ["SEA","JFK"],
 ["JFK","SEA"],
 ["JFK","HOU"]]
```

Graph:

JFK → HOU
JFK → SEA
HOU → JFK
SEA → JFK

Traversal order:

JFK → HOU → JFK → SEA → JFK

But due to postorder insertion, result builds as:

[JFK, SEA, JFK, HOU, JFK]

After reverse:

[JFK, HOU, JFK, SEA, JFK]

Correct output.

---

## Time Complexity

Let:

- V = number of airports
- E = number of tickets

Building graph:
O(E log E)

DFS traversal:
Each edge processed once → O(E log E)

Total:

O(E log E)

---

## Space Complexity

Adjacency list: O(E)
Recursion stack: O(E)
Result list: O(E)

Total: O(E)

---
