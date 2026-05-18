# Intuition

From any index `i`, we can move to:

1. `i - 1`
2. `i + 1`
3. Any index `j` where:

```text id="a9ow0q"
arr[i] == arr[j]
```

Since every move costs exactly `1 jump`, this becomes a classic:

```text id="0brk2m"
Shortest Path in an Unweighted Graph
```

And the best algorithm for shortest path in an unweighted graph is:

```text id="v1wsf2"
BFS (Breadth First Search)
```

---

# Graph Interpretation

Treat every index as a node.

Example:

```text id="z0g3j7"
arr = [100,-23,-23,404,100,23,23,23,3,404]
```

From index `0`:

```text id="0r3rwv"
0 -> 1
0 -> 4   (same value 100)
```

From index `1`:

```text id="r5wgzs"
1 -> 0
1 -> 2
1 -> 2   (same value -23)
```

We perform BFS level by level until reaching:

```text id="7om67l"
n - 1
```

The BFS level represents the minimum jumps.

---

# Key Optimization

A naive approach would repeatedly scan the entire array to find:

```text id="4lgtif"
arr[i] == arr[j]
```

which becomes very slow.

Instead, we preprocess:

```cpp id="d0tjsr"
value -> all indices having that value
```

Example:

```text id="jb6x5m"
100 -> [0,4]
23  -> [5,6,7]
404 -> [3,9]
```

This allows O(1)-style access to same-value neighbors.

---

# Important Optimization (Very Critical)

After processing all neighbors for a value:

```cpp id="u8jlwm"
indicesMap[arr[current]].clear();
```

Why?

Because otherwise:

every future occurrence of the same value would repeatedly traverse the same list again.

That could lead to:

```text id="zjlwmw"
O(n²)
```

Clearing ensures each value-group is processed only once.

---

# Algorithm

1. Build:

```cpp id="4oqf2l"
value -> list of indices
```

2. Start BFS from index `0`.

3. For each index:

   * Visit all same-value indices
   * Visit `i - 1`
   * Visit `i + 1`

4. Use a visited set to avoid revisiting nodes.

5. Return BFS level when reaching `n - 1`.

---

# Example

## Input

```text id="03ru0e"
arr = [100,-23,-23,404,100,23,23,23,3,404]
```

---

# Step 1: Build Map

```text id="hzy4a1"
100 -> [0,4]
-23 -> [1,2]
404 -> [3,9]
23 -> [5,6,7]
3 -> [8]
```

---

# BFS

## Level 0

Start:

```text id="7k2uvj"
index = 0
```

Neighbors:

```text id="5pvj0u"
1
4
```

---

## Level 1

Process:

```text id="mjlwm0"
1, 4
```

From `4`:

```text id="cwvv8f"
3
5
```

---

## Level 2

Process:

```text id="e9vq3f"
3,5
```

From `3`:

```text id="rjca5u"
9
```

Reached last index.

Answer:

```text id="jphsnm"
3
```

---

# Why BFS Works

BFS explores:

```text id="kkv67z"
all nodes reachable in 1 jump
then 2 jumps
then 3 jumps
```

So the first time we reach the last index is guaranteed to be:

```text id="zwjlwm"
minimum jumps
```

---

# Complexity Analysis

## Time Complexity

### Building map

```text id="q4zzny"
O(n)
```

### BFS traversal

Each:

* index visited once
* value-group processed once

Total:

```text id="t1m8m9"
O(n)
```

---

## Space Complexity

```text id="0ksl4q"
O(n)
```

for:

* hashmap
* queue
* visited set

---

# C++ Code

```cpp id="68u06r"
class Solution {
public:
    int minJumps(vector<int>& arr) {
        unordered_set<int> visited;
        unordered_map<int, vector<int>> indicesMap;
        queue<int> q;
        int step = 0;

        int n = arr.size();

        q.push(0);

        for (int i = 1; i < n; i++) {
            indicesMap[arr[i]].push_back(i);
        }

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                int currentNodeIdx = q.front();
                q.pop();

                // if last then return
                // BFS levels is our answer
                if (currentNodeIdx == n - 1) {
                    return step;
                }

                // all neibours that are arr[i] == arr[j]
                for (int nei : indicesMap[arr[currentNodeIdx]]) {
                    if (visited.count(nei))
                        continue;

                    q.push(nei);
                    visited.insert(nei);
                }

                // already putted into the processing queue so remove neibours
                indicesMap[arr[currentNodeIdx]].clear();

                // add i - 1
                if (currentNodeIdx - 1 >= 0 &&
                    !visited.count(currentNodeIdx - 1)) {
                    q.push(currentNodeIdx - 1);
                    visited.insert(currentNodeIdx - 1);
                }

                // add i + 1
                if (currentNodeIdx + 1 < n &&
                    !visited.count(currentNodeIdx + 1)) {
                    q.push(currentNodeIdx + 1);
                    visited.insert(currentNodeIdx + 1);
                }
            }

            step++;
        }

        return step;
    }
};
```
