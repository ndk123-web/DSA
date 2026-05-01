## Sum of Two Integers (Without Using `+` or `-`)

### Intuition

Addition can be decomposed into two independent operations:

1. **Sum without carry** → handled by XOR
2. **Carry generation** → handled by AND + left shift

Key observations:

* `a ^ b` adds bits where at least one is 1, ignoring carry
* `(a & b) << 1` computes carry and shifts it to the correct position

We repeatedly apply these until no carry remains.

---

### Approach

* Treat `a` as the running result and `b` as the carry.
* While carry (`b`) is non-zero:

  1. Compute carry: `(a & b) << 1`
  2. Update sum without carry: `a ^ b`
  3. Assign carry to `b`
* When carry becomes zero, `a` holds the final result.

---

### Code

```cpp
int getSum(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}
```

---

### Dry Run

Input:

```text
a = 5  (0101)
b = 3  (0011)
```

Iteration 1:

```text
carry = (0101 & 0011) << 1 = 0010
a = 0101 ^ 0011 = 0110 (6)
b = 0010 (2)
```

Iteration 2:

```text
carry = (0110 & 0010) << 1 = 0100
a = 0110 ^ 0010 = 0100 (4)
b = 0100 (4)
```

Iteration 3:

```text
carry = (0100 & 0100) << 1 = 1000
a = 0100 ^ 0100 = 0000 (0)
b = 1000 (8)
```

Iteration 4:

```text
carry = (0000 & 1000) << 1 = 0000
a = 0000 ^ 1000 = 1000 (8)
b = 0 → stop
```

Output:

```text
8
```

---

### Complexity

* Time: O(1) (at most 32 iterations for 32-bit integers)
* Space: O(1)

---

### Key Insight

```text
sum_without_carry = a ^ b  
carry = (a & b) << 1
```

Repeat until carry becomes zero.

---

### Concept

This approach simulates **binary addition at the hardware level**, where:

* XOR performs addition without carry
* AND identifies carry bits
* Left shift positions the carry correctly

---

### Notes

* Works for both positive and negative integers (2’s complement representation)
* No use of arithmetic operators like `+` or `-`
