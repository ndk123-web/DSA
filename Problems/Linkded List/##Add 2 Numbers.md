# Add Two Numbers (Linked List with Carry)

## Problem Statement

You are given two non-empty linked lists representing two non-negative integers.

- The digits are stored in **reverse order**
- Each node contains a **single digit**

Add the two numbers and return the sum as a linked list (also in reverse order).

---

## Example

### Example 1

```
Input:
 l1 = [1,2,3]
 l2 = [4,5,6]

Meaning:
 321 + 654 = 975

Output:
 [5,7,9]
```

### Example 2

```
Input:
 l1 = [9]
 l2 = [9]

Output:
 [8,1]
```

---

## Core Idea (Why Carry Method Works)

This problem mimics **normal addition** we do by hand:

- Add digits one by one
- Keep track of `carry`
- Store the result digit

We **never convert the list into an integer** to avoid overflow and to respect problem constraints.

---

## Key Observations

- Lists are in **reverse order**, so we can add from head directly
- Carry may produce an extra node at the end
- Lists may be of **different lengths**

---

## Algorithm (Step-by-Step)

1. Initialize `carry = 0`
2. Use a **dummy node** to simplify list creation
3. Loop while any list has nodes or `carry` exists
4. Add current digits and carry
5. Create a new node with `(sum % 10)`
6. Update `carry = sum / 10`

---

## Code (With Short Comments)

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;

        ListNode* dummy = new ListNode(); // dummy head
        ListNode* curr = dummy;           // pointer to build result

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int v1 = (l1 == nullptr) ? 0 : l1->val;
            int v2 = (l2 == nullptr) ? 0 : l2->val;

            int sum = v1 + v2 + carry;

            carry = sum / 10;             // calculate carry
            int digit = sum % 10;         // current digit

            curr->next = new ListNode(digit); // append digit
            curr = curr->next;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        return dummy->next;               // skip dummy node
    }
};
```

---

## Dry Run Example (9 + 9)

### Initial State

```
l1 = [9]
l2 = [9]
carry = 0
```

### Iteration 1

```
sum = 9 + 9 + 0 = 18
digit = 8
carry = 1
Result: 8
```

### Iteration 2

```
sum = 0 + 0 + 1 = 1
digit = 1
carry = 0
Result: 8 → 1
```

Loop ends.

---

## Dry Run Example (1,2,3 + 4,5,6)

```
Step 1: 1 + 4 = 5  → [5]
Step 2: 2 + 5 = 7  → [5 → 7]
Step 3: 3 + 6 = 9  → [5 → 7 → 9]
```

---

## Why Dummy Node Is Used

- Avoids special handling for the first node
- Simplifies pointer logic
- Makes code cleaner and safer

---

## Time & Space Complexity

| Metric | Value        |
| ------ | ------------ |
| Time   | O(max(n, m)) |
| Space  | O(max(n, m)) |

---

## Common Mistakes (Avoid These)

❌ Converting linked list to integer
❌ Forgetting carry at the end
❌ Not handling unequal list lengths
❌ Reversing output unnecessarily

---

## One-Line Summary

We add two numbers represented as linked lists by simulating digit-by-digit addition using a carry, building the result list with a dummy node.
