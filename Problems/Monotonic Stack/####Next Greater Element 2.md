# Intuition

This problem is a variation of:

```text id="j1jm65"
Next Greater Element
```

but with one extra twist:

```text id="j2jm66"
the array is circular
```

Meaning:

After reaching the last element, we continue again from the beginning.

---

# Example

```text id="j3jm67"
nums = [1,2,1]
```

For the last `1`:

Normally there is no greater element on the right.

But because the array is circular:

```text id="j4jm68"
we continue searching from the beginning
```

and find:

```text id="j5jm69"
2
```

So answer becomes:

```text id="j6jm70"
[2,-1,2]
```

---

# Brute Force

For every element:

1. Move right
2. Wrap around if needed
3. Find first greater element

Complexity:

```text id="j7jm71"
O(n²)
```

Too slow.

---

# Key Observation

This is still a:

```text id="j8jm72"
Next Greater Element
```

problem.

So we can use a:

```text id="j9jm73"
Monotonic Decreasing Stack
```

---

# Circular Array Trick

To simulate circular traversal:

We traverse the array:

```text id="k0jm74"
TWICE
```

instead of once.

---

# Why Twice Works

Suppose:

```text id="k1jm75"
nums = [1,2,1]
```

Imagine:

```text id="k2jm76"
1 2 1 | 1 2 1
```

Now every element can naturally see elements after wrapping around.

---

# Modulo Trick

```cpp id="k3jm77"
idx = i % n
```

This converts:

```text id="k4jm78"
0 1 2 3 4 5
```

into:

```text id="k5jm79"
0 1 2 0 1 2
```

creating circular traversal.

---

# Monotonic Stack Logic

The stack stores:

```text id="k6jm80"
{value, index}
```

in decreasing order.

When current value becomes greater than stack top:

```text id="k7jm81"
current value is the next greater element
```

for the stack top element.

---

# Example Dry Run

```text id="k8jm82"
nums = [1,2,1]
```

---

# i = 0

```text id="k9jm83"
idx = 0
nums[idx] = 1
```

Push:

```text id="l0jm84"
(1,0)
```

---

# i = 1

```text id="l1jm85"
nums[idx] = 2
```

Since:

```text id="l2jm86"
2 > 1
```

Next greater for index `0` is:

```text id="l3jm87"
2
```

Pop stack.

Push:

```text id="l4jm88"
(2,1)
```

---

# i = 2

```text id="l5jm89"
nums[idx] = 1
```

Smaller than stack top.

Push:

```text id="l6jm90"
(1,2)
```

---

# Second Pass

## i = 3

```text id="l7jm91"
idx = 0
nums[idx] = 1
```

No updates.

---

## i = 4

```text id="l8jm92"
idx = 1
nums[idx] = 2
```

Now:

```text id="l9jm93"
2 > 1
```

So next greater for index `2` becomes:

```text id="m0jm94"
2
```

---

# Final Answer

```text id="m1jm95"
[2,-1,2]
```

---

# Why Push Only During First Pass?

```cpp id="m2jm96"
if (i < n)
```

Because:

* first pass → inserts unresolved elements
* second pass → only helps resolve remaining answers

Otherwise duplicate indices would be pushed again.

---

# Algorithm

1. Traverse array `2*n` times.
2. Use modulo to simulate circular traversal.
3. Maintain monotonic decreasing stack.
4. Whenever current element is greater than stack top:

   * update answer
   * pop stack
5. Push elements only during first traversal.

---

# Complexity Analysis

## Time Complexity

Each element:

* pushed once
* popped once

So:

```text id="m3jm97"
O(n)
```

---

## Space Complexity

```text id="m4jm98"
O(n)
```

for stack and result array.

---

# C++ Code

```cpp id="m5jm99"
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {

        int n = nums.size();

        stack<pair<int, int>> st;

        vector<int> res(n, -1);

        for (int i = 0; i < 2 * n; i++) {

            int idx = i % n;

            while (!st.empty() &&
                   st.top().first < nums[idx]) {

                res[st.top().second] = nums[idx];
                st.pop();
            }

            // Push only during first traversal
            if (i < n) {
                st.push({nums[i], i});
            }
        }

        return res;
    }
};
```

---

# Core Pattern

Whenever you see:

```text id="m6jn00"
circular next greater
circular next smaller
```

common trick is:

```text id="m7jn01"
Traverse array twice using modulo
```

combined with:

```text id="m8jn02"
Monotonic Stack
```
