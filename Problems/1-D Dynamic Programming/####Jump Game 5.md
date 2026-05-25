# Intuition

From every index `i`, we are allowed to jump:

* left upto `d` positions
* right upto `d` positions

But only if:

```txt id="2rf2qk"
arr[j] < arr[i]
```

Also, the jump stops immediately if we encounter:

```txt id="lhv8xo"
arr[j] >= arr[i]
```

because we cannot jump over taller or equal-height elements.

---

This creates a graph-like problem:

* every index = node
* valid jump = edge

And the question becomes:

# Starting from any index, what is the maximum number of indices we can visit?

This can be solved using:

# DFS + Memoization (Top Down DP)

---

# Key Observation

If we already know:

```txt id="9k6m4s"
maximum jumps possible from index j
```

then from current index `i`:

we can jump to `j`, so answer becomes:

1 + dfs(j)

because:

* `1` → current index
* `dfs(j)` → best path starting from `j`

We take the maximum among all valid left and right jumps.

---

# Why DP / Memoization?

Without memoization:

same indices would be recomputed multiple times.

Example:

```txt id="y0qvfr"
i -> j
k -> j
```

Then:

```txt id="ztp7gw"
dfs(j)
```

gets calculated again and again.

So we store:

```cpp id="jlwm4g"
dp[i]
```

meaning:

# maximum jumps possible starting from index `i`

Once computed, reuse it directly.

---

# Approach

We define:

```cpp id="5x4sl0"
dfs(i)
```

which returns:

# maximum number of jumps starting from index `i`

---

## Base Initialization

Every index alone counts as one position.

So:

```cpp id="n9m2xw"
ans = 1;
```

---

## Explore Left

Check all positions:

```txt id="7c6p1y"
i-1 to i-d
```

If:

```txt id="0m8qvf"
arr[j] >= arr[i]
```

we stop immediately.

Because jumping beyond that is not allowed.

Otherwise:

update:

ans=max(ans,1+dfs(j))

---

## Explore Right

Same logic:

Check:

```txt id="g1w7nt"
i+1 to i+d
```

Stop when:

```txt id="5z3vku"
arr[j] >= arr[i]
```

Otherwise:

update answer.

---

## Memoize

Store:

```cpp id="q8r5yl"
dp[i] = ans;
```

so next time we reuse it.

---

## Final Answer

Compute:

```cpp id="v6h4sn"
dfs(i)
```

for every index.

Take maximum.

---

# Dry Run

Example:

```txt id="x2k9wr"
arr = [6,4,14,6,8,13,9,7,10,6,12]
d = 2
```

---

Suppose:

```txt id="8t1pyo"
i = 4
arr[i] = 8
```

Check left:

```txt id="c7m4vl"
j=3 → 6 < 8 → valid
j=2 → 14 >= 8 → stop
```

Cannot move further left.

---

Check right:

```txt id="1n8qsf"
j=5 → 13 >= 8 → stop
```

No more right exploration.

---

So only valid jump:

```txt id="4v6tkn"
4 -> 3
```

Then:

dp[4]=1+dfs(3)

---

# Why `break`?

This is important.

If:

```txt id="9w3mru"
arr[j] >= arr[i]
```

we break because:

# we cannot jump over taller/equal building

Example:

```txt id="1x5nqp"
8 5 10 4
```

From `8`:

can jump to:

```txt id="u7m2vk"
5
```

but cannot jump to `4`

because `10` blocks the path.

So scanning stops.

---

# Complexity

* Time complexity:

```txt id="f4q9st"
O(n * d)
```

For each index we explore at most `d` left + `d` right positions once.

With memoization each `dfs(i)` is computed only once.

---

* Space complexity:

```txt id="r8v1km"
O(n)
```

For:

* DP array
* recursion stack

---

# Code

```cpp id="j5n8wx"
class Solution {
public:
    vector<int> dp;

    int dfs(vector<int>& arr, int d, int i) {

        if (dp[i] != -1) {
            return dp[i];
        }

        int ans = 1;

        // explore left
        for (int j = i - 1; j >= max(0, i - d); j--) {

            if (arr[j] >= arr[i])
                break;

            ans = max(ans, 1 + dfs(arr, d, j));
        }

        // explore right
        int n = arr.size();

        for (int j = i + 1; j <= min(n - 1, i + d); j++) {

            if (arr[j] >= arr[i])
                break;

            ans = max(ans, 1 + dfs(arr, d, j));
        }

        dp[i] = ans;
        return ans;
    }

    int maxJumps(vector<int>& arr, int d) {

        int n = arr.size();
        int res = 1;

        dp.resize(n, -1);

        for (int i = 0; i < n; i++) {
            res = max(res, dfs(arr, d, i));
        }

        return res;
    }
};
```
