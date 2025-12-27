# Reverse Singly Linked List (C++)

## Problem

Reverse a singly linked list and return the new head.

---

## Code

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *next = head;
        ListNode *curr = head;
        ListNode *prev = nullptr;

        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};
```

---

## Why do we need pointers here?

A singly linked list looks like this:

```
1 -> 2 -> 3 -> NULL
```

Each node only knows **where the next node is**.
To reverse it, we must **change the direction of pointers**.

This means:

- Breaking the original link
- Reconnecting it backward
- Without losing access to remaining nodes

That’s why **multiple pointers are required**.

---

## Pointer Roles (Very Important)

| Pointer | Purpose                      |
| ------- | ---------------------------- |
| `curr`  | Current node being processed |
| `prev`  | Head of the reversed part    |
| `next`  | Temporarily stores next node |

👉 `next` is **critical**.
If you don’t save `curr->next` first, the remaining list is lost forever.

---

## Step-by-Step Logic

### Initial State

```
prev = NULL
curr = head
```

List:

```
1 -> 2 -> 3 -> NULL
```

---

### Iteration 1

```cpp
next = curr->next;   // next = 2
curr->next = prev;  // 1 -> NULL
prev = curr;        // prev = 1
curr = next;        // curr = 2
```

Now:

```
prev: 1 -> NULL
curr: 2 -> 3 -> NULL
```

---

### Iteration 2

```cpp
next = curr->next;   // next = 3
curr->next = prev;  // 2 -> 1
prev = curr;        // prev = 2
curr = next;        // curr = 3
```

Now:

```
prev: 2 -> 1 -> NULL
curr: 3 -> NULL
```

---

### Iteration 3

```cpp
next = curr->next;   // next = NULL
curr->next = prev;  // 3 -> 2
prev = curr;        // prev = 3
curr = next;        // curr = NULL
```

Now:

```
prev: 3 -> 2 -> 1 -> NULL
curr: NULL
```

Loop ends.

---

## Final Output

```cpp
return prev;
```

Because:

- `curr` becomes `NULL`
- `prev` points to the **new head**

Final list:

```
3 -> 2 -> 1 -> NULL
```

---

## Why `while (curr)`?

```cpp
while (curr)
```

Means:

- Keep processing until we reach the end of the list
- `curr == NULL` indicates list traversal is complete

---

## Time and Space Complexity

| Metric           | Value             |
| ---------------- | ----------------- |
| Time Complexity  | `O(n)`            |
| Space Complexity | `O(1)` (in-place) |

No extra data structures used.

---

## Common Mistakes (Avoid These)

❌ Forgetting to store `next`
❌ Writing `while (!curr)`
❌ Updating `curr` before reversing link
❌ Losing `head` pointer
❌ Confusing `curr` vs `prev`

---

## Core Rule to Remember

> **Always save `curr->next` before changing pointers**

This one rule prevents 90% of linked list bugs.

---

## Summary (In One Line)

We reverse the list by **redirecting each node’s `next` pointer to its previous node**, while safely moving forward using a temporary pointer.
