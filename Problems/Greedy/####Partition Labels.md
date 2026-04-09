## Partition Labels

### Problem Summary

Given a string `s` consisting of lowercase English letters, partition it into as many parts as possible such that each letter appears in at most one part. Return a list of integers representing the size of these parts.

---

### Approach: Greedy + Last Occurrence Tracking

The key idea is to ensure that every character in a partition does not appear outside that partition. To achieve this, we:

1. Record the last occurrence index of each character in the string.
2. Traverse the string while maintaining a current partition boundary.
3. Expand the current partition to include the farthest last occurrence of all characters seen so far.
4. When the current index reaches this boundary, a valid partition is found.

---

### Algorithm

1. Create a map to store the last occurrence of each character.
2. Initialize:

   * `start` = 0 (start of current partition)
   * `end` = 0 (end boundary of current partition)
3. Iterate through the string:

   * Update `end = max(end, last_occurrence[s[i]])`
   * If `i == end`, it means all characters in the current partition are fully contained:

     * Compute partition size: `end - start + 1`
     * Add it to result
     * Update `start = i + 1`
4. Return the result.

---

### Code

```cpp
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = s.size();
        vector<int> res;
        unordered_map<char, int> mapp;

        // store the last index of each character
        for (int i = 0; i < n; i++) {
            mapp[s[i]] = i;
        }

        int start = 0;
        int end = 0;

        for (int i = 0; i < n; i++) {

            // expand partition to the farthest last occurrence
            end = max(end, mapp[s[i]]);

            // if current index reaches partition boundary
            if (i == end) {
                res.push_back(end - start + 1);
                start = i + 1;
            }
        }

        return res;
    }
};
```

---

### Complexity Analysis

* Time Complexity: O(n)

  * One pass to build the map
  * One pass to form partitions

* Space Complexity: O(1)

  * At most 26 lowercase letters in the map

---

### Key Insight

A partition can only end when all characters within it have no occurrences beyond that point. This is ensured by tracking the maximum last occurrence index during traversal.

---

### Example

Input:

```
s = "xyxxyzbzbbisl"
```

Output:

```
[5, 5, 1, 1, 1]
```

Explanation:

* "xyxxy" contains all occurrences of `x` and `y`
* "zbzbb" contains all occurrences of `z` and `b`
* Remaining characters are unique and form individual partitions
