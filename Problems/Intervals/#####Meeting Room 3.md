# Meeting Rooms III

## Intuition

This problem extends the classic meeting room scheduling scenario with an additional constraint:
when no rooms are available, meetings are **delayed** instead of discarded.

The goal is not to minimize rooms, but to determine **which room is used the most**.

Key observations:

* Meetings must be processed in **increasing order of start time**
* At any moment:

  * Some rooms are **free**
  * Some rooms are **busy until a certain time**
* If no room is free, the meeting is **shifted forward** to the earliest available room while preserving its duration

---

## Approach

We use two min-heaps:

### 1. Available Rooms Heap

* Stores room indices
* Always gives the **smallest available room number**

### 2. Busy Rooms Heap

* Stores `{endTime, room}`
* Always gives the room that becomes free the earliest

---

## Algorithm

1. **Sort meetings by start time**

2. Initialize:

   * Min-heap for available rooms with all room indices `[0, ..., n-1]`
   * Min-heap for busy rooms
   * Array to count usage of each room

3. For each meeting `(start, end)`:

   ### Step 1: Free rooms

   * While the earliest ending meeting ends before or at current start:

     * Move that room back to available heap

   ### Step 2: Assign room

   * If there is an available room:

     * Assign meeting to smallest room
     * Push `{end, room}` into busy heap
   * Else:

     * Take the room that frees earliest
     * Delay meeting:

       * `newEnd = freeTime + duration`
     * Push `{newEnd, room}` into busy heap

   ### Step 3: Update usage count

4. Return the room with maximum usage
   (if tie, return smallest index)

---

## Key Insight

* Meetings are **never skipped**, only delayed
* The system behaves like a **timeline simulation based on events**
* The earliest finishing room determines delay when no room is free

---

## Dry Run

### Input:

```
n = 2
meetings = [(1,10), (2,10), (3,10), (4,10)]
```

### Step-by-step:

* Initially:

  * available = [0,1]
  * busy = []

---

#### Meeting (1,10)

* Assign room 0
* busy = [(10,0)]
* usage[0] = 1

---

#### Meeting (2,10)

* Assign room 1
* busy = [(10,0), (10,1)]
* usage[1] = 1

---

#### Meeting (3,10)

* No rooms available
* Earliest free = (10,0)
* Delay:

  * duration = 7
  * newEnd = 10 + 7 = 17
* busy = [(10,1), (17,0)]
* usage[0] = 2

---

#### Meeting (4,10)

* No rooms available
* Earliest free = (10,1)
* Delay:

  * duration = 6
  * newEnd = 10 + 6 = 16
* busy = [(16,1), (17,0)]
* usage[1] = 2

---

Final usage:

```
room 0 → 2
room 1 → 2
```

Return smallest index → **0**

---

## Complexity Analysis

### Time Complexity

* Sorting meetings: `O(m log m)`
* Heap operations per meeting: `O(log n)`
* Total: `O(m log m + m log n)`

Where:

* `m = number of meetings`
* `n = number of rooms`

---

### Space Complexity

* Heaps: `O(n)`
* Usage array: `O(n)`