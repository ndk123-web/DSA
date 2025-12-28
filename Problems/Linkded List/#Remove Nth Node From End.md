# Remove Nth Node From End of Linked List (Length-Based Method)

## Problem Statement

Given the head of a singly linked list, remove the **n-th node from the end** of the list and return its head.

---

## Core Idea (Your Logic)

You solved this using a **2-pass approach**:

1. **First pass** → find the total length of the list
2. **Second pass** → locate the node such that:

```
(len - currentIndex) == n
```

That node is exactly the **n-th node from the end**.

This logic is **100% correct**.

---

## Your Code (With Short Comments)

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = 0;
        int currlen = 0;

        // First pass: calculate length
        ListNode* curr = head;
        while (curr) {
            len++;
            curr = curr->next;
        }

        // Second pass: remove target node
        curr = head;
        ListNode* prev = nullptr;

        while (curr) {
            // If this node is the nth from end
            if (len - currlen == n) {
                if (prev) {
                    prev->next = curr->next; // unlink node
                } else {
                    head = curr->next;       // removing head
                }
                break; // IMPORTANT: stop after deletion
            }
            prev = curr;
            curr = curr->next;
            currlen++;
        }

        return head;
    }
};
```

---

## Why `break` Is Important

Once the target node is removed:

- The list structure is already fixed
- Continuing traversal would make `prev` point to a deleted node
- That can corrupt pointer logic

So this line is **mandatory**:

```cpp
break;
```

---

## Dry Run Example

### Input

```
List: 1 → 2 → 3 → 4 → 5
n = 2
```

### Step 1: Length Calculation

```
len = 5
```

### Step 2: Traversal

| curr | currlen | len - currlen | Action |
| ---- | ------- | ------------- | ------ |
| 1    | 0       | 5             | skip   |
| 2    | 1       | 4             | skip   |
| 3    | 2       | 3             | skip   |
| 4    | 3       | 2             | REMOVE |

Node `4` is removed.

### Result

```
1 → 2 → 3 → 5
```

---

## Edge Case: Removing Head

Example:

```
List: 1 → 2 → 3
n = 3
```

Here:

```
len - currlen == n  → true at head
```

So:

```cpp
head = head->next;
```

Result:

```
2 → 3
```

---

## Time & Space Complexity

| Metric | Value           |
| ------ | --------------- |
| Time   | O(n) (2 passes) |
| Space  | O(1)            |

---

## Key Linked List Rule (Important)

> When deleting a node in a linked list, once the deletion is done, **stop traversal immediately** unless explicitly required.

---

## One-Line Summary

The n-th node from the end can be removed by first finding the list length, then deleting the node where `(length - index) == n`.

---

## Interview Note

This solution is valid and acceptable.
However, interviewers may also ask for a **one-pass slow–fast pointer solution**, which is an optimized version of the same idea.
