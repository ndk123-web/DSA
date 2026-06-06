# 137. Single Number II

## Problem

We are given an array where:

```text id="ikb0ym"
Every element appears exactly 3 times
except one element
which appears exactly once.
```

We need to find that unique element.

Constraints require:

```text id="s6iuz7"
O(n) Time
O(1) Extra Space
```

---

# Why Normal XOR Fails?

For LeetCode 136:

```text id="jz1m4x"
2 ^ 2 = 0
```

so duplicates disappear.

---

But here:

```text id="ufp2e5"
2 ^ 2 ^ 2
```

becomes:

```text id="n6v4vu"
(2 ^ 2) ^ 2
=
0 ^ 2
=
2
```

The number survives.

Therefore XOR cannot eliminate elements appearing 3 times.

---

# Key Observation

Every number appearing 3 times contributes:

```text id="m50qz4"
3 copies of each bit
```

Let's look at a single bit position.

Suppose:

```text id="m5z5x4"
nums = [2,2,2,5]
```

Binary:

```text id="gxstsl"
2 = 0010
2 = 0010
2 = 0010
5 = 0101
```

---

Let's count bit 0:

```text id="5vjlwm"
0 + 0 + 0 + 1
=
1
```

---

Count bit 1:

```text id="hjlwm7"
1 + 1 + 1 + 0
=
3
```

---

Count bit 2:

```text id="rjlwmv"
0 + 0 + 0 + 1
=
1
```

---

# Magic Observation

For every bit:

```text id="mjlwmk"
Count % 3
```

removes contributions from numbers appearing 3 times.

---

Example:

```text id="jlwm1a"
3 % 3 = 0
```

Duplicate contribution disappears.

---

But:

```text id="djlwm4"
1 % 3 = 1
```

The unique number's bit survives.

---

# Bit-by-Bit Reconstruction

We reconstruct the answer one bit at a time.

For every bit:

```text id="qjlwm8"
0 → 31
```

count how many numbers have that bit set.

---

If:

```text id="hjlwmf"
count % 3 != 0
```

then the unique number must have that bit set.

---

We rebuild the number using:

```cpp id="wjlwmq"
res |= (1 << bit);
```

---

# Dry Run

### Input

```text id="xjlwm2"
[2,2,2,5]
```

Binary:

```text id="rjlwm9"
2 = 0010
5 = 0101
```

---

### Bit 0

```text id="ejlwm5"
0 + 0 + 0 + 1
=
1
```

```text id="ujlwm3"
1 % 3 = 1
```

Set bit 0.

---

### Bit 1

```text id="njlwm7"
1 + 1 + 1 + 0
=
3
```

```text id="kjlwm8"
3 % 3 = 0
```

Don't set.

---

### Bit 2

```text id="tjlwm5"
0 + 0 + 0 + 1
=
1
```

```text id="yjwlm2"
1 % 3 = 1
```

Set bit 2.

---

Result:

```text id="wjlwm1"
0101
```

which is:

```text id="pjlwm6"
5
```

Correct.

---

# Understanding the Code

## Counting Set Bits

```cpp id="mjlwm0"
(num >> bit) & 1
```

---

Suppose:

```text id="ejlwm4"
num = 13
```

Binary:

```text id="gjlwm9"
1101
```

Check bit 2:

```cpp id="sjlwm8"
(13 >> 2)
```

↓

```text id="djlwm7"
0011
```

Now:

```cpp id="fjlwm5"
0011 & 0001
```

↓

```text id="bjlwm3"
1
```

Bit is set.

---

## Setting a Bit

```cpp id="ajlwm1"
1 << bit
```

creates a mask.

Example:

```cpp id="zjlwm0"
1 << 3
```

↓

```text id="yjlwm9"
1000
```

---

Then:

```cpp id="xjlwm8"
res |= (1 << bit);
```

sets that bit inside the answer.

---

# Your Code

```cpp id="wjlwm7"
class Solution {
public:
    int singleNumber(vector<int>& nums) {

        int res = 0;

        for (int bit = 0; bit < 32; bit++) {

            int cnt = 0;

            for (int& num : nums) {

                if ((num >> bit) & 1 == 1)
                    cnt++;
            }

            if (cnt % 3 != 0) {

                int temp = (1 << bit);
                res = res | temp;
            }
        }

        return res;
    }
};
```

---

# Small Syntax Note

Prefer:

```cpp id="vjlwm6"
if (((num >> bit) & 1) == 1)
```

instead of:

```cpp id="ujlwm5"
if ((num >> bit) & 1 == 1)
```

because operator precedence can be confusing.

---

# Correctness Proof

### Lemma 1

Every number appearing three times contributes:

```text id="tjlwm4"
3 copies of each set bit
```

to the bit count.

---

### Lemma 2

Taking:

```text id="sjlwm3"
count % 3
```

removes all contributions from triplicated numbers.

---

### Lemma 3

Only the unique number contributes a remainder of:

```text id="rjlwm2"
1
```

for bits that are set.

---

### Lemma 4

Reconstructing all such bits recreates the unique number exactly.

---

### Theorem

The algorithm correctly returns the element that appears once.

---

# Complexity Analysis

### Time

Outer loop:

```text id="qjlwm1"
32 bits
```

Inner loop:

```text id="pjlwm0"
n elements
```

Total:

```text id="ojlwm9"
O(32 × n)
```

Since:

```text id="njlwm8"
32 is constant
```

we write:

```text id="mjlwm7"
O(n)
```

---

### Space

```text id="ljlwm6"
O(1)
```

Only a few variables are used.

---

# Pattern Recognition

When you see:

```text id="kjlwm5"
Every element appears twice except one
```

Think:

```text id="jjlwm4"
XOR
```

(LeetCode 136)

---

When you see:

```text id="ijlwm3"
Every element appears twice except two
```

Think:

```text id="hjlwm2"
Partition using XOR
```

(LeetCode 260)

---

When you see:

```text id="gjlwm1"
Every element appears three times except one
```

Think:

```text id="fjlwm0"
Count bits
Take modulo 3
Rebuild answer
```