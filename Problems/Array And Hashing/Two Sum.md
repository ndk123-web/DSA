***

# Two Sum

Given an integer array `nums` and an integer `target`, return the indices of the two numbers such that they add up to `target`.

***

## 1. Why (Intuition)

This problem tests:

- Ability to efficiently find pairs matching a given sum.
- Hash-based quick lookups and avoiding brute force O(n²) search.
- Understanding of time-space tradeoffs and mapping values to indices.

Goal → return two indices $$i, j$$ so $$nums[i] + nums[j] = target$$, each index used at most once.

***

## 2. Problem Breakdown

### Input

- Array `nums` of size $$n$$, integers (negative and large values possible).
- Integer `target`.

### Output

- Indices of the two numbers (unique solution guaranteed).

### Edge Cases

- Empty or single-element array → no solution.
- Unique solution required (no duplicates indices allowed).
- Multiple correct pairs possible—return any one.

***

## 3. Brute Force — Double Loop

### Idea

Try every possible pair and check sum.

### Steps

1. Loop `i` from 0 to n-1.
2. For each `i`, loop `j` from `i+1` to n-1.
3. If `nums[i] + nums[j] == target`, return `{i, j}`.

### Dry Run

```
nums = [2,7,11,15], target = 9

i=0, j=1: 2+7=9 (match) → return {0,1}
```

### Complexity

- **Time:** O(n²) checks all pairs.
- **Space:** O(1)

### Code

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> ans(2);

    for (int i = 0 ; i < n - 1 ; i++) {
        for (int j = i + 1; j < nums.size(); j++){
            if (nums[i] + nums[j] == target) {
                ans[0] = i; ans[1] = j;
            }
        }
    }
    return ans;
}
```

***

## 4. Optimal Approach — Hash Map

### Idea

Track previously seen numbers using a hash map. For every number $$x$$, check if $$target-x$$ was already seen.

### Steps

1. Loop `i` through the array.
2. For each `nums[i]`, check if `target - nums[i]` is in the hash map.
   - If yes, return both indices.
3. Insert `nums[i]` and its index into the map.

### Dry Run

```
nums = [2,7,11,15], target = 9

i=0: nums[0]=2, need = 7 (not seen), store 2:0
i=1: nums[1]=7, need = 2 (seen at index 0) → return {1,0}
```

### Complexity

- **Time:** O(n) (each element checked once).
- **Space:** O(n) map storage.

### Code

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> ans(2);
    unordered_map<int, int> hashTable;
    
    for (int i = 0; i < n; i++) {
        if (hashTable.find(target - nums[i]) != hashTable.end()) {
            ans[0] = i;
            ans[1] = hashTable[target - nums[i]];
        }
        hashTable[nums[i]] = i;
    }
    return ans;
}
```

***

## 5. Examples

```bash
- Example 1

Input:
nums = [2,7,11,15], target = 9
Output:
[0,1]
Explanation: nums[0] + nums[1] == 9

- Example 2

Input:
nums = [3,2,4], target = 6
Output:
[1,2]

- Example 3

Input:
nums = [3,3], target = 6
Output:
[0,1] or [1,0]
```

***

## 6. Final Complexity Comparison

| Approach      | Time      | Space   | Notes              |
|---------------|-----------|---------|--------------------|
| Double Loop   | O(n²)     | O(1)    | Slow, easy to code |
| Hash Map      | O(n)      | O(n)    | Fastest, common    |

***

## 7. Notes

- Hash map is always preferred for time efficiency.
- Double loop only works for very small arrays or educational settings.
- Hash table allows single-pass solution.
- Problem asks for indices, not values.
- Always consider map key as the value, value as the index for clarity.

***

This format gives a clear, interview-ready summary and detailed reference for the "Two Sum" problem with both classic and optimal solutions.