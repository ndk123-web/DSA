## Insert Interval

### Problem

You are given a list of non-overlapping intervals sorted by start time. You are also given a new interval. Insert the new interval such that:

1. The resulting list remains sorted.
2. No intervals overlap (merge if necessary).

Return the updated list.

---

## Intuition

This is a **linear sweep + merge** problem.

Instead of trying to place the new interval at an exact position using multiple conditions, treat the process as a **scan across the timeline**.

At any point, an interval can be in one of three positions relative to `newInterval`:

1. Completely before
2. Overlapping
3. Completely after

We process these in order.

---

## Key Observations

Let:

```
current interval = [s, e]
newInterval = [ns, ne]
```

### 1. Completely before

```
e < ns
```

No overlap, safe to add as-is.

---

### 2. Overlapping

```
s <= ne
```

They intersect → merge:

```
ns = min(ns, s)
ne = max(ne, e)
```

Important:

* `newInterval` keeps expanding as long as overlap continues.
* It absorbs all overlapping intervals.

---

### 3. Completely after

```
s > ne
```

No more overlap possible because intervals are sorted.

---

## Algorithm

1. Add all intervals that end before `newInterval` starts.
2. Merge all overlapping intervals into `newInterval`.
3. Insert the merged `newInterval`.
4. Add remaining intervals.

---

## Code (Clean + Commented)

```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        int i = 0, n = intervals.size();
        vector<vector<int>> res;

        // -------------------------------
        // 1. Add all intervals BEFORE newInterval
        // Condition: current interval ends before new starts
        // intervals[i][1] < newInterval[0]
        // Example:
        // [1,2]   [new starts at 4]
        // Safe to push directly
        // -------------------------------
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i]);
            i++;
        }

        // -------------------------------
        // 2. Merge all OVERLAPPING intervals
        // Condition: current interval starts before new ends
        // intervals[i][0] <= newInterval[1]
        //
        // This works because:
        // - Left non-overlapping already removed
        // - Now only overlap or right-side remains
        //
        // We expand newInterval to include all overlaps
        // -------------------------------
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }

        // -------------------------------
        // 3. Insert the MERGED interval
        // At this point:
        // - All overlaps are absorbed
        // - newInterval is final
        // -------------------------------
        res.push_back(newInterval);

        // -------------------------------
        // 4. Add all remaining intervals (RIGHT side)
        // These intervals start after newInterval ends
        // No overlap possible anymore
        // -------------------------------
        while (i < n) {
            res.push_back(intervals[i]);
            i++;
        }

        return res;
    }
};
```

---

## Example

### Input

```
intervals = [[1,2],[3,5],[6,7],[8,10]]
newInterval = [4,9]
```

### Process

* Add `[1,2]` (before)
* Merge:

  * `[3,5]` → new becomes `[3,9]`
  * `[6,7]` → still `[3,9]`
  * `[8,10]` → new becomes `[3,10]`
* Insert `[3,10]`

### Output

```
[[1,2],[3,10]]
```

---

## Complexity

* Time: `O(n)`
* Space: `O(n)` (output array)

---

## Key Takeaways

* Do not try to detect exact insertion position.
* Think in terms of **three zones**: before, overlap, after.
* Treat `newInterval` as a **dynamic interval** that grows during merging.
* Once you exit overlap phase, no further merges are possible due to sorted order.

---

## One-line Insight

This problem reduces to:

> Scan once, merge overlaps into `newInterval`, and insert it at the correct boundary.
