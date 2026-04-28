## Intuition

The constraint (numbers up to 200 digits) immediately rules out converting strings into built-in numeric types. Any approach relying on `stoi`, `stoll`, or `long long` will overflow.

So the only viable path is to **simulate multiplication exactly the way we do it on paper**:

* Multiply each digit of `num1` with each digit of `num2`
* Place the result at the correct positional index
* Handle carry immediately

Key realization:

> Each digit multiplication contributes to a specific place value based on indices.

If `num1[i]` and `num2[j]` are multiplied, their contribution goes to:

```text
position = i + j
```

(after reversing, since index 0 represents units place)

---

## Approach

### Step 1: Reverse both strings

This simplifies indexing:

* Index `0` → units place
* Index `1` → tens place

So multiplication aligns naturally with index addition.

---

### Step 2: Initialize result array

```cpp
vector<int> res(n1 + n2, 0);
```

Why size `n1 + n2`?

* Maximum digits in result = sum of lengths

---

### Step 3: Digit-by-digit multiplication

Nested loop:

```cpp
for (i in num1)
    for (j in num2)
```

For each pair:

1. Multiply digits:

   ```cpp
   digit = (num1[i] - '0') * (num2[j] - '0');
   ```

2. Add to current position:

   ```cpp
   res[i + j] += digit;
   ```

3. Handle carry:

   ```cpp
   res[i + j + 1] += res[i + j] / 10;
   res[i + j] %= 10;
   ```

This ensures:

* Each index stores only a single digit (0–9)
* Overflow is pushed forward immediately

---

### Step 4: Build result string

* Skip leading zeros
* Convert digits back to string

---

## Key Insight

> Instead of multiplying numbers, we multiply digits and place them correctly based on positional value.

This line encodes the entire logic:

```cpp
res[i + j] += digit;
```

And these two lines ensure correctness:

```cpp
res[i + j + 1] += res[i + j] / 10;
res[i + j] %= 10;
```

They simulate carry propagation exactly like manual multiplication.

---

## Complexity

* Time complexity:

```text
O(n1 × n2)
```

Every digit of `num1` is multiplied with every digit of `num2`.

---

* Space complexity:

```text
O(n1 + n2)
```

For storing the result array.

---

## Code

```cpp
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")
            return "0";

        int n1 = num1.size(), n2 = num2.size();
        vector<int> res(n1 + n2, 0);

        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {

                int digit = (num1[i] - '0') * (num2[j] - '0');

                res[i + j] += digit;

                res[i + j + 1] += res[i + j] / 10;

                res[i + j] %= 10;
            }
        }

        stringstream result;
        int i = res.size() - 1;

        while (i >= 0 && res[i] == 0)
            i--;

        while (i >= 0)
            result << res[i--];

        return result.str();
    }
};
```

---

## Final Takeaway

This problem is a shift in thinking:

* Not about numbers → about digits
* Not about arithmetic → about positional contribution

Once you see that **index = place value**, the entire solution becomes mechanical.
