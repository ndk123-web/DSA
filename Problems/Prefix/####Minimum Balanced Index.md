# Intuition

We are given an array `nums`. We must find the **smallest index `i`** such that:

```text
sum(nums[0 ... i-1]) == product(nums[i+1 ... n-1])
```

In other words:

* The **sum of all elements on the left side** of index `i`
* must equal the **product of all elements on the right side**.

Example:

```
nums = [2,4,1,2,3]
```

Check index `1`:

```
Left Sum  = 2
Right Product = 1 * 2 * 3 = 6   → not equal
```

Check index `2`:

```
Left Sum = 2 + 4 = 6
Right Product = 2 * 3 = 6
```

Balanced index = **2**

Return **2**.

---

# Key Observation

If we compute the **left sum and right product separately for every index**, the complexity becomes:

```
O(n²)
```

because for every index we would recompute sums and products.

Instead we can maintain them **incrementally** in one pass.

---

# Approach

### Step 1 — Compute total sum

First calculate the sum of all elements.

```text
leftsum = sum(nums)
```

This represents the sum of the entire array.

---

### Step 2 — Traverse from right to left

We maintain two variables:

```
leftsum      → sum of elements to the left
rightproduct → product of elements to the right
```

Initially:

```
leftsum = total sum
rightproduct = 1
```

While traversing from right to left:

1️⃣ Remove the current element from the sum

```
leftsum -= nums[i]
```

Now:

```
leftsum = sum(nums[0 ... i-1])
```

2️⃣ Check if the condition holds

```
leftsum == rightproduct
```

If true → return index `i`.

3️⃣ Update the right product

```
rightproduct *= nums[i]
```

Now it represents:

```
product(nums[i ... n-1])
```

---

# Important Optimization

Observe the pattern:

```
leftsum      → always decreases
rightproduct → always increases
```

Once:

```
rightproduct > leftsum
```

they can **never become equal again**.

Therefore we can safely stop early.

To avoid overflow while checking multiplication, we use:

```
rightproduct > leftsum / nums[i]
```

instead of:

```
rightproduct * nums[i] > leftsum
```

This prevents integer overflow.

---

# Code

```cpp
class Solution {
public:
    int smallestBalancedIndex(vector<int>& nums) {

        long long leftsum = 0;
        unsigned long long rightproduct = 1;

        for (int x : nums)
            leftsum += x;

        for (int i = nums.size() - 1; i >= 0; i--) {

            leftsum -= nums[i];

            if (leftsum == rightproduct)
                return i;

            if (nums[i] != 0 && rightproduct > leftsum / nums[i])
                break;

            rightproduct *= nums[i];
        }

        return -1;
    }
};
```

---

# Complexity

### Time Complexity

```
O(n)
```

We traverse the array only once.

---

### Space Complexity

```
O(1)
```

Only constant extra variables are used.

---

# Key Concepts

### Prefix Sum

We maintain the **sum of elements to the left** dynamically.

```
leftsum -= nums[i]
```

---

### Suffix Product

We maintain the **product of elements to the right** dynamically.

```
rightproduct *= nums[i]
```

---

### Monotonic Property

During traversal:

```
leftsum      ↓ decreases
rightproduct ↑ increases
```

Therefore equality can happen **at most once**, allowing early termination.

---

# Summary

The core idea is to maintain:

```
Left Sum   → decreasing
Right Prod → increasing
```

By updating both while traversing the array once, we efficiently find the **smallest balanced index** without recomputing sums or products repeatedly.

The overflow-safe check:

```
rightproduct > leftsum / nums[i]
```

ensures correctness when dealing with very large numbers.
