# 📘 Longest Happy String

## Problem Summary

You are given three integers:

```
a → maximum count of 'a'
b → maximum count of 'b'
c → maximum count of 'c'
```

You must build the **longest possible string** such that:

1. The string contains **only** `'a'`, `'b'`, `'c'`
2. It **does not contain** `"aaa"`, `"bbb"`, or `"ccc"`
3. It uses **at most** `a`, `b`, `c` occurrences respectively
4. If multiple answers exist, return **any**
5. If no valid string exists, return `""`

---

## Key Difference from Reorganize String

| Reorganize String  | Longest Happy String  |
| ------------------ | --------------------- |
| Must use all chars | May stop early        |
| No 2 same adjacent | No 3 same consecutive |
| Fixed length       | Variable length       |
| Always finish      | Sometimes must stop   |

👉 This difference is why this problem feels harder.

---

## Core Greedy Insight

> **At each step, try to use the character with the highest remaining count —
> but never allow the same character three times in a row.**

If the best choice is illegal:

- Try the second-best choice
- If no alternative exists → stop

---

## Why a Max Heap?

We always want the character with:

- **Highest remaining count**
- So we can spread it out safely

Heap stores:

```
(count, character)
```

Top of heap = most frequent remaining character.

---

## Algorithm (High Level)

1. Push `(count, char)` into max heap (only if count > 0)
2. While heap is not empty:

   - Take the most frequent character `p1`
   - If adding it causes `xxx`:

     - Try second most frequent `p2`
     - If not available → break
     - Use `p2`, decrement count, push back
     - Push `p1` back unchanged

   - Else:

     - Use `p1`, decrement count, push back if needed

3. Return result

---

## Correct Implementation

```cpp
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        string res = "";
        priority_queue<pair<int, char>> pq;

        if (a > 0) pq.push({a,'a'});
        if (b > 0) pq.push({b,'b'});
        if (c > 0) pq.push({c,'c'});

        while (!pq.empty()) {
            auto p1 = pq.top();
            pq.pop();

            int n = res.size();
            if (n >= 2 && p1.second == res[n - 1] && p1.second == res[n - 2]) {
                // Using p1 would cause "xxx"
                if (pq.empty()) break;

                auto p2 = pq.top();
                pq.pop();

                res.push_back(p2.second);
                p2.first--;

                if (p2.first > 0)
                    pq.push(p2);

                pq.push(p1);  // put p1 back unchanged
            } else {
                res.push_back(p1.second);
                p1.first--;

                if (p1.first > 0)
                    pq.push(p1);
            }
        }

        return res;
    }
};
```

---

## Dry Run (IMPORTANT)

### Example

```
a = 3, b = 4, c = 2
```

Initial heap:

```
(4,'b'), (3,'a'), (2,'c')
```

### Step-by-step

| Result      | Action                     |
| ----------- | -------------------------- |
| ""          | pick 'b'                   |
| "b"         | pick 'b'                   |
| "bb"        | cannot pick 'b' → pick 'a' |
| "bba"       | pick 'b'                   |
| "bbab"      | pick 'b'                   |
| "bbabb"     | cannot pick 'b' → pick 'a' |
| "bbabba"    | pick 'c'                   |
| "bbabbac"   | pick 'b'                   |
| "bbabbacb"  | pick 'a'                   |
| "bbabbacba" | stop                       |

No `"aaa"`, `"bbb"`, `"ccc"`
Used max characters → correct.

---

## Why the Algorithm Terminates

Important invariant:

> **Each iteration places exactly one character
> and reduces total remaining count**

Also:

- We never push characters with `0` count
- If no valid move exists → we break

So infinite loop is impossible.

---

## Edge Cases

### Case 1

```
a=0, b=0, c=3
```

Result:

```
"cc"
```

Third `'c'` cannot be placed.

---

### Case 2

```
a=1, b=1, c=7
```

Result:

```
"ccbccacc"
```

Stops early, still longest possible.

---

## Complexity

```
Time:  O((a+b+c) * log 3) ≈ O(n)
Space: O(3)
```

Very efficient.

---

## Common Mistakes (DO NOT DO THESE)

❌ Push zero-count characters into heap
❌ Decrement counts twice
❌ Try to “fix” after making an illegal move
❌ Forget to check second choice availability

---

## Mental Checklist for Revision

Before coding, ask:

1. What makes a move illegal? → **3 same in a row**
2. How do I detect it? → **check last two characters**
3. What if best move is illegal? → **try second-best**
4. What if no alternative? → **stop**

---

## One-Line Takeaway

> **This is a greedy simulation problem: always choose the best valid move, and stop when no safe move exists.**
