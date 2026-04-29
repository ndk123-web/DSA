## Add Binary

### Intuition

Binary addition follows the same rules as decimal addition, but in base 2.
At each step, we add corresponding bits from both strings along with a carry from the previous step.

Possible sums:

* 0 → result 0, carry 0
* 1 → result 1, carry 0
* 2 → result 0, carry 1
* 3 → result 1, carry 1

---

### Approach

* Use two pointers starting from the end of both strings.
* Maintain a `carry`.
* Iterate while there are still digits left in either string or a carry exists.
* At each step:

  * Add current digits and carry to get `sum`.
  * Append `(sum % 2)` to result.
  * Update carry as `(sum / 2)`.
* Reverse the result at the end since it is built from least significant bit to most significant bit.

---

### Code

```cpp
string addBinary(string a, string b) {
    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0;

    string res;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;

        if (i >= 0)
            sum += a[i--] - '0';

        if (j >= 0)
            sum += b[j--] - '0';

        res.push_back(sum % 2 + '0');
        carry = sum / 2;
    }

    reverse(res.begin(), res.end());
    return res;
}
```

---

### Dry Run

Input:

```
a = "111"
b = "111"
```

Steps:

```
i=2, j=2, carry=0 → sum=2 → push 0, carry=1
i=1, j=1, carry=1 → sum=3 → push 1, carry=1
i=0, j=0, carry=1 → sum=3 → push 1, carry=1
i=-1, j=-1, carry=1 → sum=1 → push 1, carry=0
```

Result (reversed):

```
1110
```

---

### Complexity

* Time: O(max(n, m))
* Space: O(max(n, m)) for result string

---

### Key Insight

The problem reduces to simulating binary addition using:

```
sum = bit_a + bit_b + carry
result_bit = sum % 2
carry = sum / 2
```

No integer conversion is required, which avoids overflow and keeps the solution optimal.
