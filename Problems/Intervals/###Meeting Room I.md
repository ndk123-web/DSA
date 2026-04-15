## Meeting Rooms I

### Problem Statement

Given an array of meeting time intervals where each interval consists of a start and end time `[(start₁, end₁), (start₂, end₂), ...]`, determine if a person can attend all meetings.

A person can attend all meetings only if no two meetings overlap.

**Note:** `(0,8)` and `(8,10)` are not considered overlapping.

---

### Examples

**Example 1**

```
Input: intervals = [(0,30),(5,10),(15,20)]
Output: false
Explanation: (0,30) overlaps with (5,10) and (15,20)
```

**Example 2**

```
Input: intervals = [(5,8),(9,15)]
Output: true
Explanation: No meetings overlap
```

---

### Constraints

* `0 ≤ intervals.length ≤ 10^5`
* `start_i < end_i`

---

### Approach

#### Key Idea

Sort the intervals by start time and check for overlap between consecutive intervals.

If any interval ends after the next one starts, there is a conflict.

---

#### Algorithm

1. Sort intervals based on start time
2. Traverse the sorted list
3. For each pair of adjacent intervals:

   * If `current.end > next.start` → overlap exists → return false
4. If no overlaps found → return true

---

### Code (C++)

```cpp
class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        
        sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b) {
            return a.start < b.start;
        });

        for (int i = 0; i < intervals.size() - 1; i++) {
            if (intervals[i].end > intervals[i+1].start) {
                return false;
            }
        }

        return true;
    }
};
```

---

### Complexity Analysis

* **Time Complexity:** `O(n log n)` (sorting)
* **Space Complexity:** `O(1)` (in-place sorting)

---

### Key Observations

* Only adjacent intervals need to be checked after sorting
* Sorting guarantees that earlier meetings come first
* Overlap condition:

  ```
  prev.end > curr.start
  ```

---

### Summary

* Sort intervals by start time
* Check adjacent overlaps
* If any overlap exists → cannot attend all meetings
* Otherwise → all meetings are attendable
