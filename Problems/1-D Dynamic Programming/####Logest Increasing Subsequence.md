# Longest Increasing Subsequence (LIS)

## Problem

Given an integer array `nums`, return the length of the **longest strictly increasing subsequence**.

A subsequence is a sequence derived from the array by deleting some or no elements **without changing the order** of the remaining elements.

Example:

```
Input: nums = [9,1,4,2,3,3,7]
Output: 4
```

One possible increasing subsequence:

```
1 → 2 → 3 → 7
```

Length = `4`.

---

# Intuition

For every element in the array, we want to know:

> If the subsequence **ends at this element**, what is the longest increasing subsequence length?

This leads to a natural dynamic programming solution.

---

# Approach 1 — Dynamic Programming (O(n²))

## State

```
dp[i] = length of the longest increasing subsequence ending at index i
```

Each element alone is a subsequence of length `1`.

```
dp[i] = 1
```

---

## Transition

For every pair `(j, i)` where `j < i`:

If

```
nums[j] < nums[i]
```

then we can extend the subsequence ending at `j`.

```
dp[i] = max(dp[i], dp[j] + 1)
```

---

## Example

```
nums = [1,3,6,7,9,4,10,5,6]
```

DP table evolves like:

```
index: 0 1 2 3 4 5 6 7 8
nums : 1 3 6 7 9 4 10 5 6
dp   : 1 2 3 4 5 3  6 4 5
```

Longest subsequence length:

```
max(dp) = 6
```

Example subsequence:

```
1 → 3 → 6 → 7 → 9 → 10
```

---

## Code

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {

        int n = nums.size();
        vector<int> dp(n,1);

        for(int i=1;i<n;i++){

            for(int j=0;j<i;j++){

                if(nums[j] < nums[i]){
                    dp[i] = max(dp[i], dp[j] + 1);
                }

            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};
```

---

## Complexity

Time

```
O(n²)
```

Space

```
O(n)
```

---

# Approach 2 — Binary Search + Greedy (O(n log n))

Instead of storing full subsequences, we maintain a structure called `tails`.

```
tails[k] = smallest possible ending value of an increasing subsequence of length k+1
```

Key idea:

A **smaller ending value gives more chance to extend the subsequence later**.

---

## Example Walkthrough

```
nums = [9,1,4,2,3,3,7]
```

Build `tails` step by step.

```
9  → [9]

1  → replace 9
     [1]

4  → append
     [1,4]

2  → replace 4
     [1,2]

3  → append
     [1,2,3]

3  → replace 3
     [1,2,3]

7  → append
     [1,2,3,7]
```

Length of `tails`:

```
4
```

This equals the LIS length.

---

## Why Binary Search?

`tails` is always sorted:

```
1 < 2 < 3 < 7
```

So we use:

```
lower_bound()
```

to find the **first element ≥ current number**.

This gives `O(log n)` search time.

---

## Code

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {

        vector<int> tails;

        for(int num : nums){

            auto it = lower_bound(tails.begin(), tails.end(), num);

            if(it == tails.end())
                tails.push_back(num);
            else
                *it = num;
        }

        return tails.size();
    }
};
```

---

# Complexity

Time

```
O(n log n)
```

Space

```
O(n)
```

---

# Important Insight

The `tails` array **does not store the actual subsequence**.

It only stores the **best possible ending values** for subsequences of different lengths.

This greedy idea works because **smaller tail values leave more room for future elements**.

---

# Key Takeaways

• DP solution builds LIS ending at every index
• Answer is `max(dp)` because LIS can end anywhere
• Binary search solution keeps optimal subsequence endings
• `tails` stays sorted, enabling `O(log n)` search
