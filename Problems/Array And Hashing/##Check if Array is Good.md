# 2784. Check if Array is Good

## Intuition

A valid array is a permutation of:

```text id="1z2t7i"
[1, 2, 3, ..., n-1, n, n]
```

This means:

* Numbers from `1` to `n-1` appear exactly once
* Largest number `n` appears twice
* Total size becomes `n + 1`

Instead of checking permutations directly, we can sort the array.

After sorting, a valid array must look like:

```text id="uq3cth"
1 2 3 ... n-1 n-1
```

because:

* array size = `n`
* maximum value must be `n-1`

---

# Approach

1. Sort the array
2. Check whether maximum element equals `size - 1`
3. Verify numbers from `1` to `n-2` appear in order
4. Verify last two elements are equal

---

# Code

```cpp id="x6dl0r"
class Solution {
public:
    bool isGood(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        int n = nums.size();

        // maximum element must be n-1
        if (nums[n - 1] != n - 1)
            return false;

        // check sequence 1 to n-1
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] != i + 1)
                return false;
        }

        // largest element must appear twice
        return nums[n - 1] == nums[n - 2];
    }
};
```

---

# Complexity Analysis

* Sorting: `O(n log n)`
* Traversal: `O(n)`

Overall:

```text id="xqo3qf"
Time Complexity: O(n log n)
Space Complexity: O(1)
```
