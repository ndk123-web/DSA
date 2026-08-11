## Link List Lists

1. Merge K Sorted Lists (Heap + Linked List) [LeetCode 23](https://leetcode.com/problems/merge-k-sorted-lists/)
2. Reverse Node in K Group (Track Group Pointer + help of dummy node) [LeetCode 25](https://leetcode.com/problems/reverse-nodes-in-k-group/)
3. All O'one Data Structure (Doubly Linked List + Hash Map) [LeetCode 432](https://leetcode.com/problems/all-oone-data-structure/)
4. Design a Text Editor (Doubly Linked List (head tail) or 2 Stack Approach) [LeetCode 173](https://leetcode.com/problems/binary-search-tree-iterator/)
5. Design a SkipList (Double Linked List + HashMap) [LeetCode 1206](https://leetcode.com/problems/design-skiplist/)
   
6. Swap Adjacent Nodes in a Linked List (Dummy Node + Pointer Manipulation) [LeetCode 24](https://leetcode.com/problems/swap-nodes-in-pairs/)
    - Trick -> 
```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* newHead = head;
        ListNode* curr = head;
        ListNode* prev = nullptr;

        if (!head || !head->next)
            return head;

        newHead = curr->next;

        while (curr && curr->next) {
            ListNode* c = curr;
            ListNode* n = curr->next;

            if (prev) 
                prev->next = n;

            c->next = n->next;
            n->next = c;

            prev = c;

            curr = c->next;
        }

        return newHead;
    }
};
```