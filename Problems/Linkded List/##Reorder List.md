# Reorder List (WHY Reverse Works + Code + Dry Run)

## Problem Recap

Given a singly linked list:

```
L0 → L1 → L2 → … → Ln
```

Reorder it to:

```
L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
```

Example:

```
Input : 1 → 2 → 3 → 4 → 5
Output: 1 → 5 → 2 → 4 → 3
```

---

## The Core Confusion (Very Important)

> **Question:**
> Mid find karne ke baad second part ko reverse karne se hi answer kaise ban jaata hai?

This is a **general linked-list transformation trick**, not a coincidence.

---

## Key Observation (Array vs Linked List Thinking)

If this were an array:

```
Index order needed: 0, 4, 1, 3, 2
```

But in a **singly linked list**:

- You **cannot move backward**
- You can only go forward

So the trick is:

> **Backward traversal ko forward traversal me convert kar do**

And the ONLY way to do that in a singly linked list is:

👉 **Reverse the second half**

---

## Why Split Into Two Halves?

For odd length list:

```
1 → 2 → 3 → 4 → 5
```

Middle element (`3`) should appear **only once at the end**.

So we split as:

```
First half : 1 → 2 → 3
Second half: 4 → 5
```

This guarantees:

- First half has ⌈n/2⌉ nodes
- Second half has ⌊n/2⌋ nodes

This balance is CRITICAL.

---

## Why Reverse the Second Half?

Second half:

```
4 → 5
```

Reverse it:

```
5 → 4
```

Now the list becomes:

```
First  : 1 → 2 → 3
Second : 5 → 4
```

👉 Now the **last elements are available in forward direction**.

This is the MAIN logic.

---

## Why Alternate Merge Works (Your Exact Logic)

You observed this correctly 👇

After reversing:

```
First  : 1 → 2 → 3
Second : 5 → 4
```

We merge like:

```
1 → 5 → 2 → 4 → 3
```

### Important Insight

We merge **only while second exists**.

Why?

- Second half is always **shorter or equal**
- Once second is exhausted, first already has the middle node

That middle node automatically lands at the end.

That’s why:

```
1 → 5 → 2 → 4
```

ke baad jab `4->next = 3` hota hai,
final list ban jaati hai:

```
1 → 5 → 2 → 4 → 3
```

No extra logic needed.

---

## Full Correct Code

```cpp
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // STEP 1: Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // STEP 2: Reverse second half
        ListNode* curr = slow->next;
        ListNode* prev = nullptr;
        slow->next = nullptr;  // split list

        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // STEP 3: Merge alternately
        ListNode* first = head;
        ListNode* second = prev;

        while (second) {
            ListNode* t1 = first->next;
            ListNode* t2 = second->next;

            first->next = second;
            second->next = t1;

            first = t1;
            second = t2;
        }
    }
};
```

---

## Complete Dry Run (1 → 2 → 3 → 4 → 5)

### Step 1: Split

```
First  : 1 → 2 → 3
Second : 4 → 5
```

### Step 2: Reverse second

```
Second : 5 → 4
```

### Step 3: Merge

| Step | List              |
| ---- | ----------------- |
| 1    | 1 → 5 → 2 → 3     |
| 2    | 1 → 5 → 2 → 4 → 3 |

Done.

---

## General Rule (VERY IMPORTANT)

> Whenever a problem asks for **front-back-front-back** ordering in a singly linked list:
>
> 🔹 Split
> 🔹 Reverse second half
> 🔹 Alternate merge

This pattern appears in MANY problems.

---

## One-Line Final Intuition

Reversing the second half converts backward traversal into forward traversal, making alternating merge possible using only next pointers.
