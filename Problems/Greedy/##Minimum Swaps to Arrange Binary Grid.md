# Intuition

A grid is valid if all cells above the main diagonal are zero.

For row `i`, this means:

All columns `j > i` must be zero.

Instead of checking the entire row structure repeatedly, we observe that only the number of **trailing zeros** in each row matters.

If a row has at least `n - i - 1` trailing zeros, it can be placed at index `i`.

So the problem reduces to:

- Compute trailing zeros for each row.
- Rearrange rows using **minimum adjacent swaps** so that at position `i`, the row has at least `n - i - 1` trailing zeros.

This becomes a greedy + simulation problem.

---

# Approach

### Step 1: Count trailing zeros

For each row, count how many zeros appear consecutively from the right end.

Store this in an array:

```
trailing[i] = number of trailing zeros in row i
```

---

### Step 2: Place rows in correct order

For each position `i` from `0` to `n-1`:

- Required trailing zeros = `n - i - 1`

- Search from row `i` downward to find the first row `j` such that:

  ```
  trailing[j] >= required
  ```

- If no such row exists → return `-1`

- Otherwise, bring row `j` up to position `i` using adjacent swaps

- Count the number of swaps performed

We only search from `i` onward because rows before `i` are already correctly placed.

---

# Why Greedy Works

At each position, we pick the nearest row that satisfies the requirement.

Choosing any farther row would only increase the number of swaps.

Since the constraint must be satisfied at every index independently, this greedy choice is optimal.

---

# Complexity

- Time Complexity: **O(n²)**
  In the worst case, for each row we may scan the remaining rows and perform swaps.

- Space Complexity: **O(n)**
  We store trailing zeros for each row.

---

# Code

```cpp
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int size = grid.size();
        vector<int> trailing(size);
        int swaps = 0;

        // Step 1: count trailing zeros
        for (int i = 0; i < size; i++) {
            int zeroes = 0;
            for (int j = size - 1; j >= 0; j--) {
                if (grid[i][j] != 0)
                    break;
                zeroes++;
            }
            trailing[i] = zeroes;
        }

        // Step 2: arrange rows
        for (int i = 0; i < size; i++) {
            int trailingRequired = size - i - 1;

            int j = i;
            while (j < size && trailing[j] < trailingRequired) {
                j++;
            }

            if (j == size)
                return -1;

            while (j > i) {
                swap(trailing[j], trailing[j - 1]);
                swaps++;
                j--;
            }
        }

        return swaps;
    }
};
```

---

# Key Insight

The problem is not about counting total zeros.

It is about ensuring that for each position `i`, the row placed there has enough trailing zeros to satisfy the diagonal condition.

Once the grid is reduced to a trailing-zero array, the problem becomes a minimum adjacent swap simulation under positional constraints.

This abstraction makes the solution simple and efficient.
