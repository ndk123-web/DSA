# Detect Cycle in a Linked List (Slow & Fast Pointers)

## Problem

Given the head of a singly linked list, check whether the list contains a **cycle**.

A cycle exists if any node's `next` pointer points back to a previous node.

---

## Your Code (with short comments)

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;          // empty list -> no cycle

        ListNode* slow = head;            // slow pointer (1 step)
        ListNode* fast = head->next;      // fast pointer (2 steps, starts ahead)

        while (slow && fast) {             // traverse while pointers are valid
            if (slow == fast) return true; // meeting point -> cycle exists

            slow = slow->next;             // move slow by 1
            fast = (fast->next)            // move fast by 2 (if possible)
                   ? fast->next->next
                   : fast->next;
        }

        return false;                      // fast reached NULL -> no cycle
    }
};
```

---

## Core Logic (Slow & Fast Pointer Idea)

- Two pointers move through the list at different speeds
- `slow` moves **1 step at a time**
- `fast` moves **2 steps at a time**

### Why this works

- If there is **no cycle**, `fast` will eventually reach `NULL`
- If there **is a cycle**, `fast` will loop around and **catch up** to `slow`
- When both pointers point to the **same node**, a cycle is confirmed

> This technique is called **Floyd’s Cycle Detection Algorithm**.

---

## Dry Run (Cycle Exists)

Example list:

```
1 → 2 → 3 → 4
      ↑       ↓
      ← ← ← ←
```

### Step-by-step

| Step  | slow | fast |
| ----- | ---- | ---- |
| Start | 1    | 2    |
| 1     | 2    | 4    |
| 2     | 3    | 3    |

- `slow == fast` at node `3`
- **Cycle detected → return true**

---

## Dry Run (No Cycle)

Example list:

```
1 → 2 → 3 → NULL
```

| Step  | slow | fast |
| ----- | ---- | ---- |
| Start | 1    | 2    |
| 1     | 2    | NULL |

- `fast` becomes `NULL`
- Loop ends
- **No cycle → return false**

---

## Important Details

- Comparison is done using:

  ```cpp
  slow == fast
  ```

  This compares **addresses**, not values

- Two different nodes can have the same value, but only identical pointers mean the same node

---

## Time & Space Complexity

| Metric | Value |
| ------ | ----- |
| Time   | O(n)  |
| Space  | O(1)  |

No extra memory is used.

---

## One-Line Summary

A cycle exists if a fast pointer moving two steps at a time ever meets a slow pointer moving one step at a time.
