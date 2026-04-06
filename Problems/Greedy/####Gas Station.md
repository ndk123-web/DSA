# Gas Station – Brute Force vs Greedy (Optimal)

## Problem Statement

You are given two integer arrays:

* `gas[i]` → amount of fuel available at station `i`
* `cost[i]` → fuel required to travel from station `i` to `i+1`

The route is **circular**.

Return the index of the starting station such that you can complete the full circuit.
If it is not possible, return `-1`.

---

# 🧠 Core Idea

At each station:

```text
tank = tank + gas[i] - cost[i]
```

Define:

```text
diff[i] = gas[i] - cost[i]
```

---

# 🚀 Approach 1: Brute Force (Simulation)

## Idea

* Try every index `i` as starting point
* Simulate full circular traversal
* If tank never becomes negative → valid start

---

## Code

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

        int n = gas.size();

        for (int i = 0; i < n; i++) {

            int curr = i;
            int tank = 0;
            int cnt = 0;

            // simulate full circular traversal
            while (cnt < n) {

                tank += gas[curr] - cost[curr];

                // if tank becomes negative → fail
                if (tank < 0) break;

                curr = (curr + 1) % n;
                cnt++;
            }

            // if completed full circle
            if (cnt == n) return i;
        }

        return -1;
    }
};
```

---

## Dry Run (Example)

```text
gas  = [1,2,3,4]
cost = [2,2,4,1]
```

Try:

* Start 0 → fail
* Start 1 → fail
* Start 2 → fail
* Start 3 → success ✔️

---

## Complexity

* Time: `O(n²)`
* Space: `O(1)`

---

## Key Insight

> Check every possible start by simulation.

---

# ⚡ Approach 2: Greedy (Optimal)

## Idea

Instead of trying all indices:

* Track cumulative fuel (`tank`)
* Track total fuel (`total`)
* Reset start when failure happens

---

## Key Observations

### 1. Total Fuel Condition

```text
total = sum(gas[i] - cost[i])
```

* If `total < 0` → impossible ❌
* If `total ≥ 0` → solution exists ✔️

---

### 2. Greedy Reset Rule

If at index `i`:

```text
tank < 0
```

Then:

```text
start = i + 1
tank = 0
```

---

## Why?

> If you cannot reach `i` from current start,
> then none of the stations between start and `i` can be valid starting points.

---

## Code

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

        int tank = 0;
        int total = 0;
        int start = 0;

        for (int i = 0; i < gas.size(); i++) {

            int diff = gas[i] - cost[i];

            tank += diff;
            total += diff;

            // current start fails → shift start
            if (tank < 0) {
                start = i + 1;
                tank = 0;
            }
        }

        return total >= 0 ? start : -1;
    }
};
```

---

## Dry Run (Example)

```text
diff = [-1, 0, -1, +3]
```

| i | diff | tank | total | action          |
| - | ---- | ---- | ----- | --------------- |
| 0 | -1   | -1   | -1    | reset → start=1 |
| 1 | 0    | 0    | -1    | continue        |
| 2 | -1   | -1   | -2    | reset → start=3 |
| 3 | +3   | 3    | 1     | continue        |

Final:

```text
total = 1 ≥ 0 → valid
start = 3
```

---

## Complexity

* Time: `O(n)`
* Space: `O(1)`

---

# 📊 Comparison

| Approach    | Idea                  | Time  | Space |
| ----------- | --------------------- | ----- | ----- |
| Brute Force | Try all starts        | O(n²) | O(1)  |
| Greedy      | Skip invalid segments | O(n)  | O(1)  |

---

# 🧠 Key Concepts

### Brute Force

* Simulation-based
* Checks all possibilities

### Greedy

* Uses cumulative balance
* Skips invalid starting points
* Based on prefix sum logic

---

# 💥 Core Insight

> If you fail at index `i`,
> all indices between previous start and `i` are invalid.

---

# 🚀 Final One-Line Summary

> Total decides **if solution exists**,
> Greedy decides **where to start**.

---
