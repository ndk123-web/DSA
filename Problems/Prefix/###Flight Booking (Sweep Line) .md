# Intuition

A booking `[first, last, seats]` means:

```text
Add `seats` to every flight from `first` to `last`
```

The brute-force approach updates every index in the range:

```cpp
for(int i = first; i <= last; i++)
    res[i] += seats;
```

But this becomes expensive for large inputs.

Instead, we use:

* **Sweep Line**
* **Difference Array**
* **Prefix Sum**

The main observation is:

> For a range update, only the starting and ending boundaries matter.

---

# Key Idea (Difference Array)

For a booking:

```text
[first, last, seats]
```

We mark:

```text
+seats at first
-seats after last
```

Meaning:

```cpp
diff[first] += seats;
diff[last + 1] -= seats;
```

This creates a **difference array** that stores only the changes.

Later, applying a **prefix sum** reconstructs the final values.

---

# Example

## Input

```text
bookings = [[1,2,10],[2,3,20],[2,5,25]]
n = 5
```

Initial array:

```text
0 0 0 0 0
```

---

## Booking 1 → `[1,2,10]`

```text
+10 at index 0
-10 at index 2
```

Array:

```text
10 0 -10 0 0
```

---

## Booking 2 → `[2,3,20]`

```text
+20 at index 1
-20 at index 3
```

Array:

```text
10 20 -10 -20 0
```

---

## Booking 3 → `[2,5,25]`

```text
+25 at index 1
```

(No subtraction because range ends at last index)

Array:

```text
10 45 -10 -20 0
```

---

# Prefix Sum Reconstruction

Now accumulate values:

```text
10
10 + 45 = 55
55 - 10 = 45
45 - 20 = 25
25
```

Final result:

```text
[10,55,45,25,25]
```

---

# Why Prefix Sum Works

The difference array stores:

```text
where an effect starts
where an effect ends
```

While traversing left → right:

* Positive values activate contributions
* Negative values deactivate contributions

The prefix sum maintains all currently active contributions.

This is the essence of the **Sweep Line technique**.

---

# Algorithm

For every booking:

1. Add seats at `first - 1`
2. Remove seats at `last` (if within bounds)

After processing all bookings:

3. Compute prefix sum

---

# Complexity Analysis

## Time Complexity

```text
O(bookings + n)
```

* Each booking processed once
* One prefix sum traversal

---

## Space Complexity

```text
O(n)
```

---

# C++ Code

```cpp
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {

        vector<int> res(n, 0);

        // Difference Array / Sweep Line
        for (auto& booking : bookings) {

            int seats = booking[2];
            int first = booking[0];
            int last  = booking[1];

            // Start contribution
            res[first - 1] += seats;

            // End contribution
            if (last < n)
                res[last] -= seats;
        }

        // Prefix Sum Reconstruction
        for (int i = 1; i < n; i++) {
            res[i] += res[i - 1];
        }

        return res;
    }
};
```
