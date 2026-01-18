# 🚗 Car Pooling

## Problem Summary

You are given:

- An integer `capacity` → total seats in the car
- A list of trips where

  ```
  trips[i] = [numPassengers, from, to]
  ```

Meaning:

- `numPassengers` get into the car at location `from`
- They get out at location `to`
- Car moves only **east** (locations increase)

### Goal

Return `true` if **at no point** the number of passengers in the car exceeds `capacity`, otherwise return `false`.

---

## Core Insight (Very Important)

This problem asks:

> **At any location, how many passengers are inside the car?**

So the problem is about:

- Overlapping intervals
- Tracking a **running passenger count**
- Ensuring it never exceeds `capacity`

This is why **sweep-line / prefix sum** logic fits perfectly.

---

# 🟢 Solution 1 — Heap Based (Active Trips Tracking)

### When to think of this?

When you want to **explicitly track which trips are currently active**.

---

## Idea

1. Sort trips by `from` (pickup location)
2. Maintain a **min-heap by `to` (drop location)** of active trips
3. Before adding a new trip:
   - Remove **all trips that already ended**
   - Subtract their passengers

4. Add current trip’s passengers
5. Check capacity

---

## Why Min-Heap `{to, passengers}`?

- The trip that ends **earliest** should be removed first
- If the earliest ending trip hasn’t ended, no other trip has
- Hence → **min-heap on `to`**

Heap invariant:

> Heap always contains **currently active trips**

---

## Code (Heap Approach)

```cpp
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {

        // Sort trips by starting location
        sort(trips.begin(), trips.end(),
             [](auto& a, auto& b) {
                 return a[1] < b[1];
             });

        // Min-heap: {end_location, passengers}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<>
        > pq;

        int curr = 0; // current passengers in car

        for (auto& trip : trips) {
            int pass = trip[0];
            int from = trip[1];
            int to   = trip[2];

            // Remove all trips that ended before current pickup
            while (!pq.empty() && pq.top().first <= from) {
                curr -= pq.top().second;
                pq.pop();
            }

            // Add current trip
            curr += pass;
            if (curr > capacity) return false;

            // Mark this trip as active
            pq.push({to, pass});
        }

        return true;
    }
};
```

---

## Dry Run (Heap Solution)

### Input

```
trips = [[2,1,3],[1,2,4],[2,3,5]]
capacity = 3
```

### Step-by-step

| Event               | Heap (to,pass) | curr |
| ------------------- | -------------- | ---- |
| Start               | empty          | 0    |
| Pickup at 1 (+2)    | (3,2)          | 2    |
| Pickup at 2 (+1)    | (3,2),(4,1)    | 3    |
| At 3 → remove (3,2) | (4,1)          | 1    |
| Pickup at 3 (+2)    | (4,1),(5,2)    | 3    |

Never exceeds capacity → `true`

---

## Complexity (Heap)

```
Time:  O(n log n)
Space: O(n)
```

---

# 🔵 Solution 2 — Map / Prefix Sum (Sweep Line)

### When to think of this?

When problem asks **“at any point”** and involves **interval overlap**.

This is the **simplest & most elegant solution**.

---

## Idea

Convert trips into **events**:

- At `from` → `+passengers`
- At `to` → `-passengers`

Then:

- Traverse locations in order
- Maintain running sum
- Check capacity

---

## Why `map<int,int>`?

- Automatically sorted by location (key)
- Perfect for simulating eastward movement

---

## Code (Map / Sweep Line)

```cpp
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {

        map<int, int> events;

        // Build passenger change events
        for (auto& trip : trips) {
            events[trip[1]] += trip[0]; // pickup
            events[trip[2]] -= trip[0]; // drop
        }

        int curr = 0;
        for (auto& [pos, delta] : events) {
            curr += delta;
            if (curr > capacity) return false;
        }

        return true;
    }
};
```

---

## Dry Run (Map Solution)

### Input

```
trips = [[2,1,3],[3,2,4]]
capacity = 4
```

### Events Map

```
1 → +2
2 → +3
3 → -2
4 → -3
```

### Simulation

| Location | Change | curr |
| -------- | ------ | ---- |
| 1        | +2     | 2    |
| 2        | +3     | 5 ❌ |

Return `false`.

---

## Complexity (Map)

```
Time:  O(n log n)
Space: O(n)
```

---

# 🆚 Heap vs Map Comparison

| Aspect                 | Heap   | Map  |
| ---------------------- | ------ | ---- |
| Tracks active trips    | ✅     | ❌   |
| Tracks passenger count | ✅     | ✅   |
| Code simplicity        | ❌     | ✅   |
| Conceptual clarity     | Medium | High |
| Interview preference   | ✅     | ✅   |
| Best for learning      | ❌     | ✅   |

---

## Key Mental Models (Lock These 🔒)

### Heap Model

> “Which trips are still active right now?”

### Map Model

> “How many passengers are in the car at this location?”

---

## Common Mistakes to Avoid

❌ Tracking only one previous trip
❌ Forgetting multiple trips can end at same location
❌ Using heap without removing **all** ended trips
❌ Overthinking when prefix sum is enough

---

## Final Takeaway (Very Important)

> **If a problem asks “at any point”, think prefix sum / sweep line first.**

Heap works, but map solution is:

- Cleaner
- Safer
- Easier to reason about

---

### One-line Summary

> **Car Pooling = cumulative passenger count over locations.**
