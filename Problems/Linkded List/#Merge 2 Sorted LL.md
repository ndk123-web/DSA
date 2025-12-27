# Merge Two Sorted Linked Lists (C++)

## Problem Statement

You are given the heads of two **sorted** singly linked lists `list1` and `list2`.

Merge the two lists into **one sorted linked list** and return its head.

---

## Example

**Input**

```
list1: 1 → 3 → 5
list2: 2 → 4 → 6
```

**Output**

```
1 → 2 → 3 → 4 → 5 → 6
```

---

## Why This Problem Is Tricky

- Linked lists do **not** allow random access
- You must carefully handle:

  - Head creation
  - Pointer movement
  - Empty list cases

- One wrong pointer update = segmentation fault

---

## Key Pointer Idea

We use **two pointers** to traverse both lists and **build a new list** node by node.

Pointers used:

| Pointer   | Role                        |
| --------- | --------------------------- |
| `list1`   | Traverses first list        |
| `list2`   | Traverses second list       |
| `newHead` | Head of merged list         |
| `curr`    | Tail pointer of merged list |

---

## Edge Case (VERY IMPORTANT)

If one list is already empty:

```cpp
if (!list1) return list2;
if (!list2) return list1;
```

Without this, code will crash when accessing `curr->next`.

---

## Algorithm (Step-by-Step)

1. Handle empty list cases
2. Compare current nodes of both lists
3. Pick the smaller value
4. Create a new node and attach it
5. Move forward in the list from which value was taken
6. Repeat until one list ends
7. Attach remaining nodes from the non-empty list

---

## Correct C++ Implementation

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        // Edge cases
        if (!list1) return list2;
        if (!list2) return list1;

        ListNode* newHead = nullptr;
        ListNode* curr = nullptr;

        while (list1 && list2) {
            int val;

            if (list1->val <= list2->val) {
                val = list1->val;
                list1 = list1->next;
            } else {
                val = list2->val;
                list2 = list2->next;
            }

            // First node creation
            if (!newHead) {
                newHead = new ListNode(val);
                curr = newHead;
            } else {
                curr->next = new ListNode(val);
                curr = curr->next;
            }
        }

        // Append remaining nodes
        while (list1) {
            curr->next = new ListNode(list1->val);
            curr = curr->next;
            list1 = list1->next;
        }

        while (list2) {
            curr->next = new ListNode(list2->val);
            curr = curr->next;
            list2 = list2->next;
        }

        return newHead;
    }
};
```

---

## Dry Run (Short)

```
list1 = 1 → 3 → 5
list2 = 2 → 4 → 6

Take 1 → new list: 1
Take 2 → 1 → 2
Take 3 → 1 → 2 → 3
Take 4 → 1 → 2 → 3 → 4
Take 5 → 1 → 2 → 3 → 4 → 5
Append 6
```

---

## Time & Space Complexity

| Metric           | Value    |
| ---------------- | -------- |
| Time Complexity  | O(n + m) |
| Space Complexity | O(n + m) |

(`n` = nodes in list1, `m` = nodes in list2)

---

## Common Mistakes (Avoid These)

❌ Accessing `curr->next` when `curr == NULL`
❌ Forgetting to handle empty input lists
❌ Updating `newHead` multiple times
❌ Over-complicating equal values logic
❌ Losing the head pointer

---

## Interview Tip

> If pointer logic feels complex, **use a dummy node** — it removes head edge cases.

But writing this version shows **strong pointer understanding**, which interviewers like.

---

## One-Line Summary

We merge two sorted linked lists by repeatedly selecting the smaller node, creating a new node, and carefully advancing pointers without losing the list structure.
