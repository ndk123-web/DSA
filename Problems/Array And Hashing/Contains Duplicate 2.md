# 2. Contains Duplicate

Given an integer array `nums`, return **true** if any value appears **at least twice**, otherwise return **false**.

This is one of the most common array + hashing interview warmup questions.

---

## 1. Why (Intuition)

The problem tests:

- Understanding of **hashing** (fast lookup)
- Ability to detect repeats efficiently
- Awareness of **time–space tradeoffs**
- Sorting vs HashSet vs custom tricks

Goal → identify if any element occurs more than once.

---

## 2. Problem Breakdown

### Input

- Array `nums` with `n` integers
- Values can be negative or large (up to 1e9)

### Output

- `true` if any number repeats
- `false` if all numbers are unique

### Edge Cases

- Empty array → no duplicates
- Single element → no duplicates
- Very large arrays → O(n) solution preferred
- Large value range → no frequency array possible

---

## 3. Brute Force — Sorting Approach

### Idea

Sort the array → duplicate values become adjacent → scan once.

### Steps

1. Sort `nums`
2. Check if any `nums[i] == nums[i-1]`

### Dry Run

nums = [3,1,4,1]  
sorted = [1,1,3,4]  
Duplicate found at index 1 → return true

### Complexity

- **Time:** O(n log n)
- **Space:** O(1) extra (in-place sort)

### Code

```cpp
bool containsDuplicate(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) return true;
    }
    return false;
}
```

## 4. Optimal Approach (Hashing)

- ✔ Approach A — Using unordered_map
  - Idea
  - Store frequency in hashmap.
  - If any frequency > 1, duplicate exists.

- Complexity
    - Time: O(n)
    - Space: O(n)

Code
```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_map<int,int> freq;
    for (int x : nums) {
        freq[x]++;
        if (freq[x] > 1) return true;
    }
    return false;
}
```


- ✔ Approach B — Using set (ordered set)

    - Idea
    1. Try inserting elements  one by one.
    2. If an element already exists → duplicate found.

- Complexity
    - Time: O(n log n)
    - Space: O(n)

Code
```cpp
bool containsDuplicate(vector<int>& nums) {
    set<int> st;
    for (int x : nums) {
        if (st.contains(x)) return true;
        st.insert(x);
    }
    return false;
}
```

- ✔ Approach C — Using unordered_set (BEST)
    
    - Idea
    1. HashSet gives O(1) average lookup.
    2. Insert each element; if already present → duplicate.

- Complexity
    - Time: O(n)
    - Space: O(n)

Code
```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x)) return true;
        seen.insert(x);
    }
    return false;
}
```

- ✔ Approach D — Size Comparison Trick (Cleanest)

    - Idea
    1. Insert all elements into an unordered_set.
    2. If duplicates existed → set size < array size.

- Steps
1. Create hashset
2. Insert all numbers
3. Compare sizes

- Complexity
  - Time: O(n)
  - Space: O(n)

Code
```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> uniqueValues;
    for (int num : nums)
        uniqueValues.insert(num);

    return uniqueValues.size() != nums.size();
}
```

## 5. Examples

```bash
- Example 1

Input:
[1,2,3,1]
Output:
true
Explanation: 1 appears twice.

- Example 2

Input:
[1,2,3,4]
Output:
false

- Example 3

Input:
[7,7,7,7]
Output:
true
```

## 6. Final Complexity Comparison
   1. Approach Time Space Notes
   2. Sorting O(n log n) O(1) 3. No hashing, but slower
   unordered_map O(n) O(n) Tracks counts
   4. set O(n log n) O(n) Balanced tree
   5. unordered_set O(n) O(n) Fastest & best
   6. size compare (set) O(n) O(n) Clean & short

## 7. Notes

- Best general solution: unordered_set

- Sorting is okay when space is restricted and duplicates detection order doesn't matter

- Map is overkill (counts not needed)

- Hash collisions theoretically slow but practically very fast

C++20 contains() is cleaner for sets

---