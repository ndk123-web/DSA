# Intuition

From every index, we can jump in only two possible directions:

* left:

i-arr[i]

* right:

i+arr[i]

This naturally forms a graph traversal problem where:

* each index acts like a node
* jumps act like edges

The goal is:

# Can we reach any index whose value is `0` ?

This can be solved using:

# DFS + Visited Set

---

# Key Observation

While exploring indices, we may revisit the same index again and again, creating cycles.

Example:

```txt id="3wjlhm"
index A -> B
index B -> A
```

Without tracking visited indices, DFS would recurse infinitely.

So we maintain:

```cpp id="jlwm4k"
visitedIndices
```

to avoid revisiting already explored indices.

---

# Approach

We perform DFS starting from the given `start` index.

At every recursive call:

---

## Base Case 1

If index is:

* already visited
* out of bounds

then this path is invalid.

```cpp id="9jlwmx"
if (visitedIndices.count(startIndex) || startIndex < 0)
    return false;
```

---

## Base Case 2

If current value becomes:

```txt id="6jlwma"
0
```

then we successfully reached the destination.

```cpp id="8’winaq"
if(arr[startIndex] == 0)
    return true;
```

---

## Recursive Exploration

From current index:

```txt id="p’wini3"
i
```

we try:

---

### Left Jump

i-arr[i]

---

### Right Jump

i+arr[i]

If either path reaches `0`, answer becomes true.

---

# Dry Run

Example:

```txt id="y’wini7"
arr = [4,2,3,0,3,1,2]
start = 5
```

---

# Step 1

Current:

```txt id="v’wini1"
index = 5
value = 1
```

Possible jumps:

```txt id="x’wini4"
5-1 = 4
5+1 = 6
```

---

# Step 2

Go left:

```txt id="jjlwm1"
index = 4
value = 3
```

Possible jumps:

```txt id="4jlwmy"
4-3 = 1
4+3 = 7 (invalid)
```

---

# Step 3

Go to:

```txt id="4m’winim"
index = 1
value = 2
```

Possible jumps:

```txt id="v’wini7"
1-2 = -1 (invalid)
1+2 = 3
```

---

# Step 4

Go to:

```txt id="x’wini1"
index = 3
value = 0
```

Found target.

Return:

```txt id="y’wini4"
true
```

---

# Why Visited Set is Important

Suppose:

```txt id="0jlwmy"
arr = [1,1]
```

Transitions:

```txt id="7’winin"
0 -> 1
1 -> 0
```

Without visited tracking:

```txt id="2’wini5"
0 -> 1 -> 0 -> 1 -> ...
```

Infinite recursion.

Visited set prevents this.

---

# Complexity

* Time complexity:

```txt id="sjlwmo"
O(n)
```

Each index visited at most once.

---

* Space complexity:

```txt id="q0gqz0"
O(n)
```

For recursion stack + visited set.

---

# Code

```cpp id="mwo6rw"
class Solution {
public:

    unordered_set<int> visitedIndices;

    bool dfs(vector<int>& arr, int startIndex) {

        // already visited or invalid index
        if (visitedIndices.count(startIndex) || startIndex < 0) {
            return false;
        }

        // reached target
        if (arr[startIndex] == 0) {
            return true;
        }

        visitedIndices.insert(startIndex);

        bool left = false;
        bool right = false;

        // explore left jump
        if ((startIndex - arr[startIndex]) >= 0) {
            left = dfs(arr, startIndex - arr[startIndex]);
        }

        // explore right jump
        if ((startIndex + arr[startIndex]) < arr.size()) {
            right = dfs(arr, startIndex + arr[startIndex]);
        }

        return left || right;
    }

    bool canReach(vector<int>& arr, int start) {
        return dfs(arr, start);
    }
};
```
