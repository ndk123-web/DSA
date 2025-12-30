# Find the Duplicate Number — Floyd’s Cycle Detection

## Problem Statement

You are given an array `nums` containing `n + 1` integers where:

- Each integer is in the range **[1, n] (inclusive)**
- Exactly **one number appears more than once**
- You must:

  - ❌ Not modify the array
  - ❌ Not use extra space
  - ✔️ Run in `O(n)` time

---

## Key Observations

1. **Array size = n + 1**
2. **Values range = 1 to n**
3. By the **Pigeonhole Principle**, at least one number must repeat.
4. The constraint forbids:

   - Sorting
   - Hash maps
   - Extra arrays

So we need a **mathematical / pointer-based solution**.

---

## Core Idea (Most Important)

> **Treat the array as a Linked List**
>
> - **Index = node**
> - **nums[index] = next pointer**

This transforms the problem into:

> **Find the entry point of a cycle in a linked list**

And that is solved using **Floyd’s Cycle Detection Algorithm (Tortoise & Hare)**.

---

## Why a Cycle Exists

- There are `n + 1` nodes (indices)
- Only `n` possible next pointers (values 1 to n)
- So two indices must point to the same next index
- This creates a **cycle**
- The **duplicate number = cycle entry point**

---

## Example

```text
nums = [1, 2, 3, 2, 2]
index  0  1  2  3  4
```

### Build the linked list (index → nums[index]):

```text
0 → 1 → 2 → 3
        ↑   ↓
        ← ← ←
```

- Cycle exists between `2 ↔ 3`
- Cycle entry = `2`
- Duplicate number = `2`

---

## Code

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;

        // Phase 1: Detect cycle
        while (true) {
            slow = nums[slow];          // move 1 step
            fast = nums[nums[fast]];    // move 2 steps
            if (slow == fast) break;
        }

        // Phase 2: Find cycle entry (duplicate)
        int slow2 = 0;
        while (true) {
            slow = nums[slow];
            slow2 = nums[slow2];
            if (slow == slow2) return slow;
        }

        return -1;
    }
};
```

---

## Phase 1 — Cycle Detection

```cpp
slow = nums[slow];
fast = nums[nums[fast]];
```

### What this means

- `slow` moves **1 edge**
- `fast` moves **2 edges**
- If a cycle exists, they **must meet inside the cycle**

### Dry Run (example)

```text
slow = 0 → 1 → 2
fast = 0 → 2 → 2
```

They meet ⇒ **cycle confirmed**

⚠️ Meeting point is NOT guaranteed to be the duplicate

---

## Phase 2 — Find the Duplicate (Cycle Entry)

```cpp
int slow2 = 0;
```

Now:

- `slow` is inside the cycle
- `slow2` starts from head (index 0)

Move both **one step at a time**:

```cpp
slow  = nums[slow];
slow2 = nums[slow2];
```

### Why this works

Mathematically:

```text
Distance(head → cycle entry)
=
Distance(meeting point → cycle entry)
```

So they will meet **exactly at the cycle entry**, which is the duplicate number.

---

## Phase 2 Dry Run

```text
slow  = 2
slow2 = 0

Iteration 1:
slow  = nums[2] = 3
slow2 = nums[0] = 1

Iteration 2:
slow  = nums[3] = 2
slow2 = nums[1] = 2
```

They meet at **2** ⇒ duplicate found ✅

---

## Important Clarifications

### Inclusive Range `[1, n]`

- Inclusive means **both 1 and n are allowed**
- No value can be `0` or `n + 1`
- This guarantees all pointers stay inside the array

---

## Common Mistake (Causes Confusion)

❌ Thinking **values are nodes**
✔️ **Indices are nodes**, values are pointers

Wrong thinking:

```text
1 → 2 → 3 → 2
```

Correct thinking:

```text
index → nums[index]
```

---

## Time & Space Complexity

- **Time:** `O(n)`
- **Space:** `O(1)` (no extra memory)

---

## One-Line Interview Explanation

> “We treat the array as a linked list where index is the node and value is the next pointer.
> Since one value repeats, a cycle forms.
> Floyd’s algorithm finds the cycle entry, which is the duplicate number.”

---

## Final Takeaway

- This is **not a trick**
- This is **cycle detection on a functional graph**
- Once the **index-as-node** model clicks, the solution becomes obvious
