# Intuition

For every element `nums[i]`, we need to find:

```text id="q4jp49"
the SECOND future element greater than nums[i]
```

Not the second maximum.

Not the second largest.

Specifically:

```text id="q5jp50"
the second greater element encountered while moving right
```

---

# Example

```text id="q6jp51"
nums = [2,4,0,9,6]
```

For `2`:

Future greater elements are:

```text id="q7jp52"
4
9
6
```

* First greater  → `4`
* Second greater → `9`

Answer for `2`:

```text id="q8jp53"
9
```

---

# Brute Force

For every index:

1. Scan all future elements
2. Count greater elements
3. Stop at second greater

Complexity:

```text id="q9jp54"
O(n²)
```

Too slow.

---

# Key Observation

This problem is an extension of:

```text id="r0jp55"
Next Greater Element
```

In normal NGE:

```text id="r1jp56"
element waits for first greater
```

using one monotonic stack.

---

# Here Elements Have Two States

Every element moves through phases:

---

## State 1

Waiting for:

```text id="r2jp57"
FIRST greater element
```

---

## State 2

Already found first greater.

Now waiting for:

```text id="r3jp58"
SECOND greater element
```

---

# Two Stack Idea

We use:

---

## Stack 1

```text id="r4jp59"
waitingListFirstGreater
```

Stores elements still waiting for their FIRST greater.

Maintains monotonic decreasing order.

---

## Stack 2

```text id="r5jp60"
waitingListSecondGreater
```

Stores elements that already found their first greater,
and now wait for SECOND greater.

This also behaves like a monotonic stack.

---

# Core Flow

When current number `nums[i]` arrives:

---

# Step 1 — Resolve Second Greater

If current value is greater than elements in stack2:

```text id="r6jp61"
current value becomes their SECOND greater
```

---

# Step 2 — Move From Stack1 → Stack2

If current value is greater than elements in stack1:

```text id="r7jp62"
current value becomes their FIRST greater
```

So those elements transition into:

```text id="r8jp63"
waiting for SECOND greater
```

and move to stack2.

---

# Important Ordering Detail

Directly pushing from stack1 → stack2 breaks monotonic order.

Because stacks are LIFO.

So we use temporary storage to preserve correct ordering.

---

# Why Ordering Matters

Suppose stack2 has:

```text id="r9jp64"
1 3 5
```

(top = 5)

Current:

```text id="s0jp65"
4
```

Now:

```text id="s1jp66"
4 > 5 ?
```

No.

Algorithm stops.

But:

```text id="s2jp67"
4 should resolve 1 and 3
```

They get blocked behind `5`.

So stack2 must maintain proper monotonic structure.

---

# Example Dry Run

```text id="s3jp68"
nums = [2,4,0,9,6]
```

---

## i = 0 → 2

```text id="s4jp69"
stack1 = [2]
stack2 = []
```

---

## i = 1 → 4

`4 > 2`

So:

```text id="s5jp70"
2 found FIRST greater
```

Move `2`:

```text id="s6jp71"
stack1 -> stack2
```

Now:

```text id="s7jp72"
stack1 = [4]
stack2 = [2]
```

---

## i = 2 → 0

```text id="s8jp73"
stack1 = [4,0]
stack2 = [2]
```

---

## i = 3 → 9

First resolve stack2:

```text id="s9jp74"
9 > 2
```

So:

```text id="t0jp75"
res[0] = 9
```

Now resolve stack1:

```text id="t1jp76"
9 > 0
9 > 4
```

Move both into stack2.

Now:

```text id="t2jp77"
stack1 = [9]
stack2 = [4,0]
```

---

## i = 4 → 6

Resolve stack2:

```text id="t3jp78"
6 > 0
```

So:

```text id="t4jp79"
res[2] = 6
```

Next:

```text id="t5jp80"
6 > 4
```

So:

```text id="t6jp81"
res[1] = 6
```

Final:

```text id="t7jp82"
[9,6,6,-1,-1]
```

---

# Complexity Analysis

## Time Complexity

Each element:

* pushed once
* popped once

from both stacks.

Total:

```text id="t8jp83"
O(n)
```

---

## Space Complexity

```text id="t9jp84"
O(n)
```

for:

* stacks
* result array

---

# C++ Code

```cpp id="u0jp85"
class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {

        int n = nums.size();

        stack<int> waitingListFirstGreater;
        stack<int> waitingListSecondGreater;

        vector<int> res(n, -1);

        for (int i = 0; i < n; i++) {

            // Resolve second greater
            while (!waitingListSecondGreater.empty() &&
                   nums[waitingListSecondGreater.top()] < nums[i]) {

                res[waitingListSecondGreater.top()] = nums[i];
                waitingListSecondGreater.pop();
            }

            // Temporary storage to preserve ordering
            vector<int> tempStorage;

            // Resolve first greater
            while (!waitingListFirstGreater.empty() &&
                   nums[i] > nums[waitingListFirstGreater.top()]) {

                tempStorage.push_back(
                    waitingListFirstGreater.top());

                waitingListFirstGreater.pop();
            }

            // Maintain monotonic order in stack2
            for (int j = tempStorage.size() - 1;
                 j >= 0;
                 j--) {

                waitingListSecondGreater.push(
                    tempStorage[j]);
            }

            // Current element waits for first greater
            waitingListFirstGreater.push(i);
        }

        return res;
    }
};
```

---

# Core Pattern

This problem teaches:

```text id="u1jp86"
multi-stage monotonic stack processing
```

Elements transition through states:

```text id="u2jp87"
waiting for first greater
        ↓
waiting for second greater
        ↓
resolved
```

A powerful extension of the standard Next Greater Element pattern.
