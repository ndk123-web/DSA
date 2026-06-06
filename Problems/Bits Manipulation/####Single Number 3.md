# 260. Single Number III

## Intuition

We are given an array where:

```text id="4epvsl"
Every element appears exactly twice
except two elements
which appear exactly once.
```

We need to find those two unique numbers.

The constraints require:

```text id="ytwejlwm"
O(n) Time
O(1) Extra Space
```

which immediately suggests using **XOR**.

---

## Key Observation 1: XOR Removes Duplicates

We know:

```text id="lmdqqw"
a ^ a = 0
```

and

```text id="4t8h5r"
a ^ 0 = a
```

Therefore:

```text id="x1vfb0"
1 ^ 2 ^ 1 ^ 3 ^ 2 ^ 5
```

becomes:

```text id="hnd6xq"
(1 ^ 1) ^ (2 ^ 2) ^ 3 ^ 5
```

↓

```text id="jcb7xy"
3 ^ 5
```

All duplicates disappear.

---

## Key Observation 2: XOR Gives Information About Differences

Suppose:

```text id="zpgcaj"
a = 3 = 011
b = 5 = 101
```

Then:

```text id="8e11mq"
a ^ b
```

becomes:

```text id="ghlsww"
011
101
---
110
```

Notice:

```text id="if7bgg"
XOR produces 1
only where bits differ.
```

Therefore:

```text id="j4e3m5"
xorforall = a ^ b
```

guarantees that there exists at least one bit where:

```text id="5b8xmq"
a and b are different.
```

---

## Key Observation 3: Use a Differing Bit to Separate Numbers

From:

```text id="y8gmf1"
xorforall
```

we find any set bit.

For example:

```text id="cb57f3"
xorforall = 110
```

Choose:

```text id="b4dc3f"
010
```

---

Now divide all numbers into two groups:

### Group 1

Numbers having this bit set.

### Group 2

Numbers not having this bit set.

---

Example:

```text id="a7p25x"
nums = [1,2,1,3,2,5]
```

Using:

```text id="e6xcm4"
mask = 010
```

---

Group 1:

```text id="ujjlwm"
2 3 2
```

---

Group 2:

```text id="sdw9vp"
1 1 5
```

---

## Why Does This Work?

The two unique numbers:

```text id="0gb1nd"
a and b
```

must differ at the chosen bit.

Therefore:

```text id="djlwmn"
a and b
```

are forced into different groups.

---

Meanwhile duplicates:

```text id="z1dfg0"
7 and 7
```

have identical bits.

Therefore both copies always go into the same group.

Inside each group:

```text id="8h5ys0"
duplicate ^ duplicate = 0
```

and disappear.

Only the unique number survives.

---

## Dry Run

### Input

```text id="fihhnn"
nums = [1,2,1,3,2,5]
```

---

### Step 1: XOR Everything

```text id="ubwhp5"
1 ^ 2 ^ 1 ^ 3 ^ 2 ^ 5
```

↓

```text id="gbayxh"
3 ^ 5
```

↓

```text id="vj44m9"
6
```

Binary:

```text id="rjlwm6"
110
```

---

### Step 2: Find First Set Bit

Choose:

```text id="a7lz3e"
010
```

Therefore:

```cpp id="yjshfk"
mask = 2
```

---

### Step 3: Partition Numbers

Check whether:

```text id="4ghrfm"
bit1
```

is set.

---

Group 1:

```text id="g2qjlwm"
2 3 2
```

---

Group 2:

```text id="egbc5w"
1 1 5
```

---

### Step 4: XOR Within Groups

Group 1:

```text id="r1h5oo"
2 ^ 3 ^ 2
```

↓

```text id="n8whpu"
3
```

---

Group 2:

```text id="hhcjlwm"
1 ^ 1 ^ 5
```

↓

```text id="emh3ti"
5
```

---

Answer:

```text id="tjlwmh"
[3,5]
```

---

## Approach

### Step 1

XOR all numbers.

```cpp id="nqj9a0"
xorforall ^= num;
```

After this:

```text id="kjlwmv"
xorforall = unique1 ^ unique2
```

---

### Step 2

Find any set bit in:

```text id="mj3hng"
xorforall
```

This bit represents a position where the two unique numbers differ.

---

### Step 3

Create a mask:

```cpp id="7l80oz"
mask = (1LL << i);
```

---

### Step 4

Partition numbers according to that bit.

```cpp id="vxjlwm"
if (((num >> bit) & (mask >> bit)) == 1)
```

---

### Step 5

XOR numbers inside each partition.

Duplicates cancel.

Unique numbers remain.

---

## Code

```cpp id="h4cjlwm"
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {

        long long xorforall = 0;

        for (int& num : nums)
            xorforall ^= num;

        long long mask = -1;
        long long bit = -1;

        for (int i = 0; i <= 32; i++) {

            if (((xorforall >> i) & 1) == 1) {
                mask = (1LL << i);
                bit = i;
                break;
            }
        }

        int group1 = 0;
        int group2 = 0;

        for (int& num : nums) {

            if (((num >> bit) & (mask >> bit)) == 1)
                group1 ^= num;
            else
                group2 ^= num;
        }

        return {group1, group2};
    }
};
```

---

## Correctness Proof

### Lemma 1

All duplicate numbers cancel during XOR.

Because:

```text id="s6jlwm"
a ^ a = 0
```

Therefore after XORing the entire array:

```text id="w5n7c5"
xorforall = unique1 ^ unique2
```

---

### Lemma 2

Since:

```text id="tvjlwm"
unique1 != unique2
```

their XOR contains at least one set bit.

Therefore a bit position exists where the two unique numbers differ.

---

### Lemma 3

Using that differing bit as a partition guarantees:

```text id="tjlwmx"
unique1
```

and

```text id="yjz9j0"
unique2
```

fall into different groups.

---

### Lemma 4

Any duplicate pair has identical bits.

Therefore both copies always enter the same group.

Inside that group:

```text id="1hjlwm"
x ^ x = 0
```

and they disappear.

---

### Theorem

After XORing each group separately:

```text id="4njlwm"
group1 = unique number #1
group2 = unique number #2
```

Therefore the algorithm correctly returns the two unique elements.

---

## Complexity Analysis

### Time Complexity

```text id="vzjlwm"
O(n)
```

One pass for XOR.

One pass for partitioning.

---

### Space Complexity

```text id="brjlwm"
O(1)
```

Only a few variables are used.

---

## Pattern Recognition

When you see:

```text id="ywjlwm"
Every element appears twice
except one
```

Think:

```text id="phjlwm"
XOR all elements
```

(LeetCode 136)

---

When you see:

```text id="e1jlwm"
Every element appears twice
except two elements
```

Think:

```text id="evjlwm"
XOR all
↓
Find differing bit
↓
Partition
↓
XOR each partition
```