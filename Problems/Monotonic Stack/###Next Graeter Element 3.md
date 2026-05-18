# Intuition

We need to find:

```text id="n1jn03"
the smallest integer greater than n
```

using exactly the same digits.

This is exactly the definition of:

```text id="n2jn04"
Next Permutation
```

---

# Example

```text id="n3jn05"
n = 123
```

Permutations in increasing order:

```text id="n4jn06"
123
132
213
231
312
321
```

The next greater number after `123` is:

```text id="n5jn07"
132
```

---

# Key Observation

To get the next greater permutation:

We should make the:

```text id="n6jn08"
smallest possible increase
```

not a huge change.

---

# Core Next Permutation Logic

The algorithm works in 3 steps:

1. Find the pivot
2. Find the next greater digit
3. Reverse the suffix

---

# Step 1 — Find Pivot

Traverse from right to left.

Find first index where:

```text id="n7jn09"
str[i] < str[i+1]
```

Why?

Because from the right side:

```text id="n8jn10"
digits are already in descending order
```

and cannot produce a larger permutation by themselves.

---

# Example

```text id="n9jn11"
12443322
```

From right:

```text id="o0jn12"
3 > 2
3 > 2
4 > 3
4 > 3
2 < 4
```

Pivot:

```text id="o1jn13"
index of 2
```

---

# Why Pivot Matters

Pivot is the digit we must increase slightly to get the next larger number.

---

# Step 2 — Find Next Greater Digit

Search from right side again.

Find the first digit greater than pivot.

Why from right?

Because the suffix is descending.

So the first greater element from right is the:

```text id="o2jn14"
smallest greater digit
```

which gives minimum increase.

---

# Example

```text id="o3jn15"
12443322
```

Pivot:

```text id="o4jn16"
2
```

Next greater digit:

```text id="o5jn17"
3
```

Swap:

```text id="o6jn18"
13443222
```

---

# Step 3 — Reverse Suffix

After swapping:

The right side is still in descending order.

To get the smallest possible number:

```text id="o7jn19"
convert suffix into ascending order
```

using reverse.

---

# Example

Before reverse:

```text id="o8jn20"
13443222
```

Suffix descending:

```text id="o9jn21"
443222
```

Reverse:

```text id="p0jn22"
222344
```

Final answer:

```text id="p1jn23"
13222344
```

---

# Why Reverse Works

The suffix is already descending.

Reversing makes it ascending in:

```text id="p2jn24"
O(n)
```

which gives the smallest lexicographical arrangement.

---

# Edge Case

If no pivot exists:

Example:

```text id="p3jn25"
54321
```

Entire number is descending.

No greater permutation possible.

Return:

```text id="p4jn26"
-1
```

---

# Overflow Handling

The result may exceed:

```text id="p5jn27"
32-bit signed integer
```

So after conversion:

```cpp id="p6jn28"
(newN <= INT_MAX)
```

otherwise return `-1`.

---

# Complexity Analysis

## Time Complexity

### Finding pivot

```text id="p7jn29"
O(n)
```

### Finding next greater digit

```text id="p8jn30"
O(n)
```

### Reversing suffix

```text id="p9jn31"
O(n)
```

Total:

```text id="q0jn32"
O(n)
```

---

## Space Complexity

```text id="q1jn33"
O(n)
```

for string conversion.

---

# C++ Code

```cpp id="q2jn34"
class Solution {
public:
    int nextGreaterElement(int n) {

        // Single digit cannot have next permutation
        if (n / 10 == 0) {
            return -1;
        }

        string str = to_string(n);

        int pivot = -1;

        // Step 1: Find pivot
        for (int i = str.size() - 2; i >= 0; i--) {

            if ((str[i] - '0') < (str[i + 1] - '0')) {
                pivot = i;
                break;
            }
        }

        // No greater permutation exists
        if (pivot == -1)
            return -1;

        // Step 2: Find next greater digit
        for (int j = str.size() - 1; j >= pivot; j--) {

            if ((str[j] - '0') > (str[pivot] - '0')) {

                swap(str[j], str[pivot]);
                break;
            }
        }

        // Step 3: Reverse suffix
        reverse(str.begin() + pivot + 1, str.end());

        long long newN = stoll(str);

        return (newN <= INT_MAX) ? newN : -1;
    }
};
```

---

# Core Pattern

Whenever you see:

```text id="q3jn35"
next larger arrangement
next lexicographical order
next permutation
```

think:

1. Find pivot
2. Swap with next greater element
3. Reverse suffix
