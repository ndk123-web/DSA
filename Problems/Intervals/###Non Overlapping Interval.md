## Non-overlapping Intervals

### Problem

You are given an array of intervals where `intervals[i] = [start_i, end_i]`.
Return the **minimum number of intervals to remove** so that the remaining intervals are non-overlapping.

Note:

* Intervals like `[1,2]` and `[2,3]` are **non-overlapping**
* Intervals like `[1,3]` and `[2,4]` are **overlapping**

---

## Intuition

This is not a merge problem.
This is a **greedy selection problem**.

Instead of thinking:

> “Which intervals to remove?”

Think:

> **“Which intervals to keep?”**

Goal:

* Keep maximum number of non-overlapping intervals
* Removals = total − kept

---

## Key Idea

When two intervals overlap, we must remove one.

Which one?

> Always remove the interval with the **larger end**

Because:

* Larger end blocks more future intervals
* Smaller end leaves more room

---

## Core Logic

Sort intervals by start.

Maintain:

```text id="k1"
lastEnd = end of last selected interval
```

---

### Case 1: No Overlap

```text id="k2"
current_start >= lastEnd
```

Safe:

* Keep interval
* Update:

```text id="k3"
lastEnd = current_end
```

---

### Case 2: Overlap

```text id="k4"
current_start < lastEnd
```

Conflict:

* Remove one interval
* Increment count

Decision:

```text id="k5"
lastEnd = min(lastEnd, current_end)
```

Keep the interval with smaller end.

---

## Algorithm

1. Sort intervals by start
2. Initialize:

   * `count = 0`
   * `lastEnd = intervals[0][1]`
3. Iterate from second interval:

   * If overlap → increment count and shrink using `min`
   * Else → update `lastEnd`
4. Return count

---

## Code (C++)

```cpp id="x4m3eh"
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        int count = 0;
        int lastEnd = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < lastEnd) {
                // Overlap → remove one
                count++;

                // Keep interval with smaller end
                lastEnd = min(lastEnd, intervals[i][1]);
            } else {
                // No overlap
                lastEnd = intervals[i][1];
            }
        }

        return count;
    }
};
```

---

## Example

### Input

```text id="ex1"
intervals = [[1,2],[2,3],[3,4],[1,3]]
```

### Process

* Start with `[1,2]`
* `[2,3]` → no overlap → keep
* `[3,4]` → no overlap → keep
* `[1,3]` → overlap → remove (end is larger)

### Output

```text id="ex2"
1
```

---

## Complexity

* Time: `O(n log n)` (sorting)
* Space: `O(1)` (no extra structure)

---

## Key Takeaway

When intervals overlap:

> Do not merge. Do not pick arbitrarily.
> Always keep the interval with the **earliest finishing time**.

---

## One-line Insight

This problem reduces to:

> Greedily selecting intervals with minimum end time to maximize non-overlapping intervals.
