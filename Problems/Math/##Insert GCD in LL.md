# Insert Greatest Common Divisors in Linked List

## Intuition

For every pair of adjacent nodes in the linked list, we need to insert a new node whose value is the GCD of the two nodes.

The core idea is simple:

* Traverse the list
* For each pair `(a, b)`
* Compute `gcd(a, b)`
* Insert a node between them

This can be done in two ways:

1. Build a new list
2. Modify the existing list in-place

---

## Logic

For every adjacent pair:

1. Take current node `A`
2. Take next node `B`
3. Compute `gcd(A, B)`
4. Insert a new node with this value between them

---

# Approach 1: Build New List

## Idea

Create a completely new linked list:

* Copy nodes from original list
* Insert GCD nodes in between

---

## Steps

1. Initialize new list with first node
2. Traverse original list
3. For each pair `(a, b)`:

   * Insert `gcd(a, b)`
   * Insert node `b`
4. Return new list

---

## Code

```cpp
class Solution {
private:
    int getGcd(int a, int b) {
        if (b == 0) 
            return a;
        return getGcd(b, (a % b));
    }

public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if (head == nullptr) return nullptr;

        ListNode* newHead = new ListNode(head->val);
        ListNode* root = newHead;
        ListNode* track = head;

        while(track != nullptr) {
            int a = track->val;
            track = track->next;

            if (track == nullptr) 
                return root;

            int b = track->val;

            int gcd = getGcd(a,b);
            newHead->next = new ListNode(gcd);
            newHead = newHead->next;

            newHead->next = new ListNode(b);
            newHead = newHead->next;
        }

        return root;
    }
};
```

---

## Complexity

* Time: O(n)
* Space: O(n) (new list created)

---

## Notes

* Simple and easy to reason about
* Uses extra memory
* Duplicates original nodes

---

# Approach 2: In-place Insertion (Optimal)

## Idea

Modify the original list directly:

* Insert new node between current and next node
* No extra list required

---

## Steps

1. Start from head
2. While current and next node exist:

   * Compute GCD
   * Create new node
   * Insert between them
3. Move forward

---

## Code

```cpp
class Solution {
public:
    int getGcd(int a, int b) {
        if (b == 0)
            return a;
        return getGcd(b, (a % b));
    }

    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* track = head;

        while (track != nullptr && track->next != nullptr) {
            ListNode* nextNode = track->next;

            int gcd = getGcd(track->val, nextNode->val);

            track->next = new ListNode(gcd);
            track->next->next = nextNode;

            track = nextNode;
        }

        return head;
    }
};
```

---

## Complexity

* Time: O(n)
* Space: O(1)

---

## Key Insight

* Always process pairs `(current, next)`
* Insert node in between without breaking the list
* Move pointer to next original node (skip inserted node)