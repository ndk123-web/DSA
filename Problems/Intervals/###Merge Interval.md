## Merge Intervals

### Problem

You are given an array of intervals where `intervals[i] = [start_i, end_i]`. Merge all overlapping intervals and return a list of non-overlapping intervals that cover all the intervals in the input.

---

## Intuition

Intervals can overlap in multiple ways, but after sorting them by start time, the problem simplifies significantly.

Once sorted:

* Any potential overlap can only occur with the **previous interval**
* There is no need to check all intervals ahead

So the idea is:

> Maintain a result list and keep merging with the last interval if overlap exists

---

## Key Observation

After sorting:

```text
intervals[i][0] >= intervals[i-1][0]
```

So we only compare:

```text
current interval vs last merged interval
```

---

## Core Logic

Let:

* `last = res.back()`
* `curr = intervals[i]`

---

### Case 1: No Overlap

```text
last[1] < curr[0]
```

Meaning:

```text
[last_start ----- last_end]   [curr_start ----- curr_end]
```

No overlap → push current interval

---

### Case 2: Overlap

```text
curr[0] <= last[1]
```

Meaning:

```text
[last_start ----- last_end]
        [curr_start ----- curr_end]
```

Overlap → merge:

```text
last[1] = max(last[1], curr[1])
```

---

## Algorithm

1. Sort intervals based on start time
2. Initialize result with first interval
3. Traverse remaining intervals:

   * If no overlap → add to result
   * If overlap → merge with last interval
4. Return result

---

## Code (C++)

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;

        // Step 1: sort intervals by start time
        sort(intervals.begin(), intervals.end());

        // Step 2: add first interval
        res.push_back(intervals[0]);

        // Step 3: process remaining intervals
        for (int i = 1; i < intervals.size(); i++) {
            vector<int>& last = res.back();
            vector<int>& curr = intervals[i];

            // No overlap
            if (last[1] < curr[0]) {
                res.push_back(curr);
            }
            // Overlap
            else {
                last[1] = max(last[1], curr[1]);
            }
        }

        return res;
    }
};
```

---

## Example

### Input

```text
intervals = [[1,3],[2,6],[8,10],[15,18]]
```

### Process

* Start with `[1,3]`
* `[2,6]` overlaps → merge → `[1,6]`
* `[8,10]` no overlap → add
* `[15,18]` no overlap → add

### Output

```text
[[1,6],[8,10],[15,18]]
```

---

## Complexity

* Time Complexity: `O(n log n)` (sorting)
* Space Complexity: `O(n)` (output list)

---

## Key Takeaway

After sorting, merging intervals reduces to comparing each interval with the last merged interval and extending it if overlap exists.
