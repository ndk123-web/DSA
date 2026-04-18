# Excel Sheet Column Title

## Intuition

The problem resembles base conversion, but with a key difference: Excel columns are 1-indexed (A = 1, ..., Z = 26) instead of 0-indexed.

A direct division approach fails because there is no representation for zero. To handle this, we shift the number by 1 before applying modulo and division.

We extract characters from right to left (least significant position first), similar to how digits are extracted in base conversion.

---

## Logic

1. Treat the number as a modified base-26 system.
2. At each step:

   * Subtract 1 from the current number to align with 0-based indexing.
   * Compute `(n - 1) % 26` to get the current character index.
   * Append the corresponding character.
   * Update `n = (n - 1) / 26` to move to the next position.
3. Continue until the number becomes less than 27.
4. Handle the final remaining character.
5. Reverse the result since characters are built from right to left.

---

## Approach 1 (Your Implementation)

### Code

```cpp
class Solution {
public:
    string convertToTitle(int columnNumber) {
        long long tc = (long long) columnNumber;
        unordered_map<int, char> mapp;

        // map 0-25 -> A-Z
        for (int i = 0; i < 26; i++) 
            mapp[i] = 'A' + i;

        string res = "";

        // extract characters from right to left
        while (tc >= 27) {
            long long mod = (tc - 1) % 26;  // get current position (0-25)
            res.push_back(mapp[mod]);

            tc = (tc - 1) / 26;            // reduce number
        }

        // handle last remaining character
        res.push_back(mapp[tc - 1]);

        reverse(res.begin(), res.end());   // reverse to correct order
        return res;
    }
};
```

---

## Complexity Analysis

* Time Complexity: O(log₍26₎ n)
  Each iteration reduces the number by a factor of 26.

* Space Complexity: O(log₍26₎ n)
  Result string stores the characters.

---

## Key Insight

* `(n - 1) % 26` gives the current character.
* `(n - 1) / 26` moves to the next position.
* The subtraction by 1 ensures correct handling of the 1-based system.

---

## Notes

* The use of `unordered_map` is not necessary and can be replaced with direct character arithmetic.
* The loop condition `tc >= 27` works but is not the most general form; a `tc > 0` loop is more standard.
* The approach correctly builds the string in reverse and then fixes the order.