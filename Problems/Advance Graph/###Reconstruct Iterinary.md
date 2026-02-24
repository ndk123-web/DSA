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

Perfect. We’ll extend the README properly and include the `vector + erase` approach with complexity discussion — like a clean LeetCode editorial.

Below is the updated README section you can paste under your solution.

---

## Alternative Approach: Using `vector` Instead of `priority_queue`

Instead of using a min-heap to maintain lexicographical order, we can use:

```cpp
unordered_map<string, vector<string>> adj;
```

### Key Idea

* Store all destinations in a vector
* Sort each adjacency list once
* Always pick the smallest lexicographical destination
* Remove the used edge
* Apply the same postorder DFS (Hierholzer’s algorithm)

---

## Implementation (Vector + Erase)

```cpp
class Solution {
private:
    unordered_map<string, vector<string>> adj;
    vector<string> res;

    void dfs(string node) {
        while (!adj[node].empty()) {
            string next = adj[node].front();
            adj[node].erase(adj[node].begin());  // consume ticket
            dfs(next);
        }
        res.push_back(node);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {

        // Build adjacency list
        for (auto& t : tickets) {
            adj[t[0]].push_back(t[1]);
        }

        // Sort each list lexicographically
        for (auto& [src, dests] : adj) {
            sort(dests.begin(), dests.end());
        }

        dfs("JFK");

        reverse(res.begin(), res.end());
        return res;
    }
};
```

---

## Why This Works

This still follows **Hierholzer’s Algorithm**:

1. Always use the smallest available edge.
2. Remove the edge immediately after using it.
3. Add node to result only when no outgoing edges remain.
4. Reverse at the end.

Even though both of these itineraries are valid:

```
["JFK","SEA","JFK","HOU","JFK"]
["JFK","HOU","JFK","SEA","JFK"]
```

We must return the lexicographically smaller one.

Since:

```
"HOU" < "SEA"
```

We must choose `"HOU"` first when starting from `"JFK"`.

Sorting guarantees that.

---

## Complexity Analysis

Let E = number of tickets

### Priority Queue Approach

* Insert edges: O(E log E)
* Pop edges during DFS: O(E log E)
* Total: O(E log E)

### Vector + Erase Approach

* Sorting adjacency lists: O(E log E)
* Each erase from front: O(n)
* In worst case, repeated shifting leads to O(E²)

So:

* `priority_queue` → more efficient for large input
* `vector + erase` → simpler but potentially slower

---

## When to Use Which?

If constraints are small → vector approach is fine.

If constraints are large (like in real interviews or competitive programming) → prefer min-heap.

Both are correct implementations of the same underlying algorithm:

**Eulerian Path construction using postorder DFS.**

---

## Core Insight

This problem is not about DFS alone.

It is about:

* Using every edge exactly once
* Starting from a fixed node
* Maintaining lexicographical order

Which is a classic **Eulerian Path + Hierholzer’s Algorithm** pattern.

Once that pattern is recognized, the rest is implementation detail.
