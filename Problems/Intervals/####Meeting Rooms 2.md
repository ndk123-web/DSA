# Meeting Rooms II

## Intuition

The problem reduces to finding the **maximum number of meetings happening at the same time**.

A room can only host one meeting at a time. If multiple meetings overlap, we need additional rooms. Therefore, the minimum number of rooms required is equal to the **maximum number of concurrent (overlapping) meetings**.

---

## Approach

1. **Sort the intervals by start time**
   This ensures we process meetings in chronological order.

2. **Use a min-heap (priority queue)**

   * The heap stores **end times of ongoing meetings**.
   * The smallest end time is always at the top.

3. **Iterate through intervals**

   * For each meeting:

     * Remove all meetings from the heap that have already ended
       (`end <= current start`)
     * Add the current meeting’s end time to the heap
     * Track the maximum size of the heap

4. **Result**

   * The maximum heap size encountered during iteration is the answer

---

## Key Insight

* The heap represents **currently active meetings**
* Heap size at any moment = **rooms currently in use**
* Maximum heap size over time = **minimum rooms required**

---

## Complexity Analysis

* **Time Complexity:**

  * Sorting: `O(n log n)`
  * Heap operations: `O(n log n)`
  * Overall: `O(n log n)`

* **Space Complexity:**

  * Heap storage: `O(n)`

---

## Code

```cpp
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        if (n == 0) 
            return 0;   

        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.start < b.start;
        });

        priority_queue<int, vector<int>, greater<>> pq;
        pq.push(intervals[0].end);

        int rooms = 1;

        for (int i = 1; i < n; i++) {
            while (!pq.empty() && pq.top() <= intervals[i].start){
                pq.pop();
            }

            pq.push(intervals[i].end);
            rooms = max(rooms, (int)pq.size());
        }

        return rooms;
    }
};
```

---

## Summary

* Track active meetings using a min-heap of end times
* Remove finished meetings before adding a new one
* The peak number of active meetings determines the answer