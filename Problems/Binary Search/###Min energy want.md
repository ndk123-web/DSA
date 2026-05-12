# Intuition

We can complete the tasks in any order, so choosing the correct order is the key observation.

Suppose we have:

```text
(1,100) and (50,51)
```

If we perform `(50,51)` first:

```text
100 -> 50
```

Now we cannot start `(1,100)` because it requires `100` energy.

But if we perform `(1,100)` first:

```text
100 -> 99
```

then `(50,51)` can easily be completed.

This tells us that tasks with larger:

minimum-actual

should be completed earlier because they require a large temporary amount of energy.

After fixing the order, we binary search the minimum starting energy.

---

# Approach

1. Sort tasks based on:

```text
(minimum - actual)
```

in ascending order.

2. Traverse tasks from back to front so that tasks with larger differences are processed first.

3. Use binary search on the answer:

   * If we can finish all tasks with energy `mid`,
     try smaller energy.
   * Otherwise increase the energy.

4. In `canWeFinish()`:

   * If current energy is smaller than required minimum energy,
     return `false`.
   * Otherwise subtract the actual energy consumed.

---

# Complexity

* Time complexity:

```text
O(n log n + n log(1e9))
```

* Sorting takes:

```text
O(n log n)
```

* Binary search runs about:

\log_2(10^9) \approx 31

times, and each check takes:

```text
O(n)
```

---

* Space complexity:

```text
O(1)
```

excluding sorting internals.

---

# Code

```cpp
class Solution {
public:
    bool canWeFinish(vector<vector<int>>& tasks, int energy) {

        for (int i = tasks.size() - 1; i >= 0; i--) {

            int actual = tasks[i][0];
            int minimumEnergyWant = tasks[i][1];

            if (energy < minimumEnergyWant) {
                return false;
            }

            energy -= actual;
        }

        return true;
    }

    int minimumEffort(vector<vector<int>>& tasks) {

        sort(tasks.begin(), tasks.end(),
             [](const vector<int>& a, const vector<int>& b) {

                 return (a[1] - a[0]) < (b[1] - b[0]);
             });

        int n = tasks.size();

        int maxElement = tasks[n - 1][1];

        int low = 0;
        int high = maxElement * n;

        int res = maxElement;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (canWeFinish(tasks, mid)) {

                res = mid;
                high = mid - 1;

            } else {

                low = mid + 1;
            }
        }

        return res;
    }
};
```
