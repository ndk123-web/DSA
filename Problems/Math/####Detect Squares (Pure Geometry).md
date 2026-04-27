## Detect Squares — Readme

---

## Intuition

A square aligned with the axes is fully determined if you fix one corner (the query point) and find its **diagonal corner**. Once the diagonal is known, the remaining two corners are uniquely determined by swapping coordinates.

Given a query point `(x2, y2)`, for any stored point `(x, y)`:

* If `(x, y)` is the **diagonal** of `(x2, y2)`, then the other two required points are:

  * `(x, y2)`
  * `(x2, y)`

So the task reduces to:

1. Iterate over all previously added points.
2. Treat each as a potential diagonal.
3. Check if it forms a valid square.
4. Count how many such squares exist using frequencies.

---

## Key Observation

A point `(x, y)` is a valid diagonal of `(x2, y2)` **iff**:

```
abs(x - x2) == abs(y - y2)
```

and

```
x != x2 and y != y2
```

Reason:

* Equal absolute differences ensure equal side lengths.
* Non-equality ensures we are not on the same row or column (which cannot form a square diagonal).

---

## Counting Logic

If `(x, y)` is a valid diagonal:

* Required points:

  * `(x, y2)` → same column as diagonal
  * `(x2, y)` → same row as diagonal

If these points exist multiple times, each occurrence contributes to distinct squares.

Number of squares contributed by this diagonal:

```
freq(x, y2) * freq(x2, y)
```

We sum this over all valid diagonals.

---

## Code

```cpp
class CountSquares {
private:
    map<vector<int>, int> freqMap;
    vector<vector<int>> points;

public:
    CountSquares() {}

    void add(vector<int> point) {
        freqMap[{point[0], point[1]}]++;
        points.push_back(point);
    }

    int count(vector<int> query) {
        int total = 0;
        int x2 = query[0];
        int y2 = query[1];

        for (vector<int>& point : points) {
            int x = point[0];
            int y = point[1];

            // Check if (x, y) is a valid diagonal
            if (abs(x - x2) == abs(y - y2) && x != x2 && y != y2) {

                // Count combinations using frequency
                total += freqMap[{x, y2}] * freqMap[{x2, y}];
            }
        }

        return total;
    }
};
```

---

## Why This Works

* We avoid generating all combinations of points.
* Instead, we fix one corner and search for valid diagonals.
* Once a diagonal is identified, the remaining two corners are deterministic.
* Using a frequency map ensures duplicates are handled correctly and efficiently.

---

## Complexity Analysis

### Time Complexity

* `add(point)` → `O(log n)` due to `map`
* `count(query)`:

  * Iterates over all stored points → `O(n)`
  * Each lookup in `map` → `O(log n)`

Overall:

```
count() = O(n log n)
```

---

### Space Complexity

* `points` stores all added points → `O(n)`
* `freqMap` stores frequencies → `O(n)`

Total:

```
O(n)
```

---

## Notes

* The approach is correct but not optimal due to `map<vector<int>, int>` usage.
* A more efficient implementation uses:

```
unordered_map<int, unordered_map<int, int>>
```

which reduces lookup to `O(1)` average time and improves overall performance.

---

## Core Takeaway

The problem is not about generating squares but about recognizing that:

> A square is uniquely defined by one corner and its diagonal, and the remaining points follow directly from coordinate alignment.
