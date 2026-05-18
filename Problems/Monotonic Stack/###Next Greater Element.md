# Intuition

For every element in `nums1`, we need to find:

```text id="g3jm43"
the first greater element on the right side in nums2
```

A brute-force approach would scan to the right for every element, leading to:

```text id="g4jm44"
O(n²)
```

Instead, we can use a:

```text id="g5jm45"
Monotonic Decreasing Stack
```

to efficiently compute the next greater element for every number in `nums2`.

---

# Key Observation

While traversing `nums2`:

If the current number is greater than the stack top:

```text id="g6jm46"
current number becomes the next greater element
```

for all smaller elements waiting inside the stack.

---

# Monotonic Stack Idea

The stack stores:

```text id="g7jm47"
{value, index}
```

in decreasing order.

Example:

```text id="g8jm48"
nums2 = [1,3,4,2]
```

---

## Start

Stack:

```text id="g9jm49"
1
```

---

## Current = 3

Since:

```text id="h0jm50"
3 > 1
```

we found the next greater element for `1`.

So:

```text id="h1jm51"
next greater of 1 = 3
```

Pop `1`.

Push `3`.

---

## Current = 4

```text id="h2jm52"
4 > 3
```

So:

```text id="h3jm53"
next greater of 3 = 4
```

Pop `3`.

Push `4`.

---

## Current = 2

```text id="h4jm54"
2 < 4
```

Push `2`.

---

# Result for nums2

```text id="h5jm55"
1 -> 3
3 -> 4
4 -> -1
2 -> -1
```

---

# Why HashMap?

We need answers for elements in `nums1`.

So we store:

```text id="h6jm56"
value -> index in nums2
```

This allows O(1) lookup.

---

# Algorithm

1. Build a hashmap:

```text id="h7jm57"
value -> index
```

for `nums2`.

2. Use a monotonic decreasing stack to compute next greater elements.

3. Store results in `res`.

4. For every element in `nums1`,
   fetch answer from `res`.

---

# Complexity Analysis

## Time Complexity

### Stack Processing

Each element is:

* pushed once
* popped once

So:

```text id="h8jm58"
O(n)
```

### Building final answer

```text id="h9jm59"
O(m)
```

Total:

```text id="i0jm60"
O(n + m)
```

Where:

* `n = nums2.size()`
* `m = nums1.size()`

---

## Space Complexity

```text id="i1jm61"
O(n)
```

for:

* stack
* hashmap
* result array

---

# C++ Code

```cpp id="i2jm62"
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1,
                                   vector<int>& nums2) {

        vector<int> res(nums2.size(), -1);
        vector<int> ans(nums1.size(), -1);

        unordered_map<int, int> mapp;

        // value -> index mapping
        for (int i = 0; i < nums2.size(); i++) {
            mapp[nums2[i]] = i;
        }

        stack<pair<int, int>> st;

        // Monotonic Decreasing Stack
        for (int i = 0; i < nums2.size(); i++) {

            while (!st.empty() &&
                   st.top().first < nums2[i]) {

                res[st.top().second] = nums2[i];
                st.pop();
            }

            st.push({nums2[i], i});
        }

        // Build final answers for nums1
        for (int i = 0; i < nums1.size(); i++) {
            ans[i] = res[mapp[nums1[i]]];
        }

        return ans;
    }
};
```

---

# Core Monotonic Stack Pattern

Whenever you see:

```text id="i3jm63"
Next Greater Element
Next Smaller Element
Nearest Greater
Nearest Smaller
```

think:

```text id="i4jm64"
Monotonic Stack
```

because the stack efficiently maintains unresolved elements waiting for a future answer.
