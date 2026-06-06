## Reverse Bits

### Intuition

We are given a 32-bit integer and need to reverse its binary representation.

Key observation:

* Bits are processed from **least significant bit (LSB)** to **most significant bit (MSB)**.
* While extracting bits from `n` (right side), we build the result `res` from left to right.

---

### Approach

* Initialize `res = 0`.
* Iterate exactly **32 times** (since input is a 32-bit integer).
* At each step:

  1. Shift `res` left to make space.
  2. Extract the last bit of `n` using `n & 1`.
  3. Insert this bit into `res` using OR.
  4. Shift `n` right to process the next bit.

---

### Code

```cpp id="7gq7i1"
int reverseBits(int n) {
    int res = 0;

    for (int i = 0; i < 32; i++) {
        res = res << 1;
        res = res | (n & 1);
        n = n >> 1;
    }

    return res;
}
```

---

### Dry Run

Input:

```id="gnh9ux"
n = 1010 (10 in decimal)
```

Steps:

```id="qkg20b"
Iteration 1: res=0 → add 0 → res=0
Iteration 2: res=0 → add 1 → res=1
Iteration 3: res=1 → shift→10 → add 0 → res=10
Iteration 4: res=10 → shift→100 → add 1 → res=101
```

Remaining iterations add zeros (since n becomes 0).

Final:

```id="y3b03d"
res = 0101 (5)
```

---

### Complexity

* Time: O(1) (fixed 32 iterations)
* Space: O(1)

---

### Key Insight

The operation:

```id="kh9c2m"
res = (res << 1) | (n & 1)
```

means:

* shift result to make space
* take last bit of `n`
* insert it into result

---

### Important Notes

* Always iterate **32 times**, not until `n == 0`
* Handles leading zeros correctly
* No need for string conversion

---

### Concept

> Reverse bits by extracting from right and building from left using shift + mask operations.
