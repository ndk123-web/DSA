# Intuition

For every bar in the histogram, we want to know:

```text id="f0js05"
how far this height can expand left and right
```

because the rectangle height is limited by the:

```text id="f1js06"
minimum height in the chosen range
```

---

# Example

```text id="f2js07"
heights = [2,1,5,6,2,3]
```

Consider height `5`:

```text id="f3js08"
2 1 5 6 2 3
    ^
```

Height `5` can expand through:

```text id="f4js09"
6
```

because:

```text id="f5js10"
6 >= 5
```

But expansion stops at:

```text id="f6js11"
2
```

because:

```text id="f7js12"
2 < 5
```

So valid range becomes:

```text id="f8js13"
[5,6]
```

Width:

```text id="f9js14"
2
```

Area:

```text id="g0js15"
5 × 2 = 10
```

---

# Key Observation

For every bar:

We need:

```text id="g1js16"
Previous Smaller Element
Next Smaller Element
```

because smaller bars stop rectangle expansion.

---

# Monotonic Increasing Stack

We maintain a stack of indices whose heights are:

```text id="g2js17"
increasing
```

Meaning:

```text id="g3js18"
heights[stack[0]] < heights[stack[1]] < ...
```

---

# Core Idea

A bar remains inside the stack while:

```text id="g4js19"
its rectangle can still expand toward right
```

When a smaller height appears:

```text id="g5js20"
rectangle expansion stops
```

So we finalize the area for that height.

---

# Width Formula (Most Important Part)

When a bar at index `k` is popped:

```text id="g6js21"
i          -> first smaller bar on the right
stack.top() -> first smaller bar on the left
```

So valid rectangle exists:

```text id="g7js22"
between left smaller and right smaller
```

Width becomes:

```text id="g8js23"
right - left - 1
```

---

# Cases

## Case 1 — Stack Empty

No smaller element on left.

Rectangle extends from:

```text id="g9js24"
0 to i-1
```

Width:

```cpp id="h0js25"
width = i
```

---

## Case 2 — Stack Not Empty

Left smaller index exists.

Width:

```cpp id="h1js26"
width = i - stack.top() - 1
```

---

# Why We Iterate Till `i <= n`

Suppose array is increasing:

```text id="h2js27"
1 2 3 4
```

No smaller element appears.

So remaining bars never get processed.

To force processing:

We run one extra iteration:

```cpp id="h3js28"
i == n
```

which acts like an imaginary:

```text id="h4js29"
height = 0
```

and flushes the stack.

---

# Dry Run

```text id="h5js30"
heights = [2,1,5,6,2,3]
```

---

## i = 0 → 2

Push index 0.

Stack:

```text id="h6js31"
[0]
```

---

## i = 1 → 1

```text id="h7js32"
1 < 2
```

So height `2` dies here.

Pop index 0.

Height:

```text id="h8js33"
2
```

Width:

```text id="h9js34"
1
```

Area:

```text id="i0js35"
2
```

Push index 1.

---

## i = 2 → 5

Push.

Stack:

```text id="i1js36"
[1,2]
```

---

## i = 3 → 6

Push.

Stack:

```text id="i2js37"
[1,2,3]
```

---

## i = 4 → 2

Now:

```text id="i3js38"
2 < 6
```

Pop 6.

Height:

```text id="i4js39"
6
```

Width:

```text id="i5js40"
1
```

Area:

```text id="i6js41"
6
```

---

Still:

```text id="i7js42"
2 < 5
```

Pop 5.

Now:

* left smaller = index 1
* right smaller = index 4

Width:

```text id="i8js43"
4 - 1 - 1 = 2
```

Area:

```text id="i9js44"
5 × 2 = 10
```

Maximum area becomes:

```text id="j0js45"
10
```

---

# Complexity Analysis

## Time Complexity

Each index is:

* pushed once
* popped once

So:

```text id="j1js46"
O(n)
```

---

## Space Complexity

```text id="j2js47"
O(n)
```

for stack.

---

# C++ Code

```cpp id="j3js48"
class Solution {
public:
    int largestRectangleArea(vector<int>& nums) {

        stack<int> st;

        int n = nums.size();

        int maxArea = 0;

        for (int i = 0; i <= n; i++) {

            // Current smaller height means
            // rectangles for taller bars end here
            while (!st.empty() &&
                   (i == n || nums[st.top()] > nums[i])) {

                int h = nums[st.top()];
                st.pop();

                int w = st.empty()
                            ? i
                            : i - st.top() - 1;

                maxArea = max(maxArea, h * w);
            }

            st.push(i);
        }

        return maxArea;
    }
};
```

---

# Core Monotonic Stack Pattern

This problem teaches a new monotonic stack pattern:

```text id="j4js49"
range expansion / boundary discovery
```

instead of just:

```text id="j5js50"
next greater element
```

The stack helps determine:

```text id="j6js51"
how long a height can survive continuously
```
