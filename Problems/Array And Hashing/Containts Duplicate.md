# 1. Concatenation of Array

Given an integer array `nums` of length `n`, create an array `ans` of length `2n` such that:

- `ans[i] = nums[i]`
- `ans[i + n] = nums[i]`

Basically, ans = nums + nums.

---

## 1. Why (Intuition)

This is a warm-up array question.  
The goal is to understand basic array manipulation, indexing, and how to create a larger output array.  
No complex pattern – just duplicating the same array into a new container.

---

## 2. Problem Breakdown

**Input:**  
`nums = [1,2,3]`

**Output:**  
`[1,2,3,1,2,3]`

**Edge Cases:**

- Empty array → return empty
- Single element → duplicate once
- Large array → ensure O(n) time

---

## 3. Brute Force

### Idea

- Create an empty vector `ans`.
- First loop: push all elements of nums.
- Second loop: push all elements again.

### Dry Run

nums = [1,2,3]

After loop 1 → ans = [1,2,3]  
After loop 2 → ans = [1,2,3,1,2,3]

### Brute Force Code

```cpp
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {

        int n = nums.size();
        vector<int> ans;

        // first iteration to store all nums values
        for (int i = 0 ; i < n ; i++) {
            ans.push_back(nums[i]);
        }

        // second iteration to store all nums values
        for (int i = 0 ; i < n ; i++) {
            ans.push_back(nums[i]);
        }

        return ans;
    }
};
```

## Complexity

- Time: O(2n) ≈ O(n)
- Space: O(2n) → output array

## 4. Optimal Solution

- Pattern

  - Direct indexing in a fixed-size array.

- Reason

  - Why push twice when you can fill both halves in one loop?
  - Minimize extra operations and avoid repeated vector resizing.

- Steps
  1. Create an output vector of size 2n.
  2. For each index i, assign:
  3. ans[i] = nums[i]
  4. ans[i+n] = nums[i]

## Optimal Code

```cpp
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {

        int n = nums.size();

        // create the doubled size vector
        vector<int> ans(n*2);

        // in one iteration work done
        for (int i = 0 ; i < n ; i++) {
            ans[i] = nums[i];
            ans[n+i] = nums[i];
        }

        return ans;
    }
};
```

## 5. Examples

- Example 1

```bash
Input:
nums = [1,2,3]
Output:
[1,2,3,1,2,3]
```

- Example 2

```bash
Input:
[5]
Output:
[5,5]
```

6. Complexity
   - Time: O(n)
   - Space: O(2n) (required for output)
