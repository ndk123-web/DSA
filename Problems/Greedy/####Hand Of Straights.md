# Hand of Straights – Greedy + Frequency Map

## Problem Statement

You are given an array `hand` representing cards and an integer `groupSize`.

Return `true` if it is possible to rearrange the cards into groups such that:

* Each group has exactly `groupSize` cards
* Each group contains consecutive numbers

Otherwise, return `false`.

---

## Intuition

This is a greedy + frequency problem.

Key idea:
Always start forming a group from the smallest available card.

---

## Core Observation

If a number `x` exists, then for a valid group:

```
x → x+1 → x+2 → ... → x + groupSize - 1
```

All must exist in sufficient quantity.

---

## Approach

### Step 1: Frequency Map

Track how many times each card appears:

```
value → count
```

### Step 2: Sort the Array

Sorting ensures:

* We always start from the smallest available card
* Greedy decision becomes valid

### Step 3: Build Groups

For each number in sorted order:

* If it is still available (count > 0)

  * Start a group from it
  * Try to build `groupSize` consecutive elements
  * Decrease frequency for each used element

---

## Code

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        unordered_map<int,int> mapp;
        int n = hand.size();

        // frequency map
        for (int& h : hand) {
            mapp[h]++;
        }

        // sort to always pick smallest first
        sort(hand.begin(), hand.end());

        for (int i = 0; i < n; i++) {

            // if already used, skip
            if (mapp[hand[i]] > 0) {
                mapp[hand[i]]--;

                int sm = hand[i];

                // build remaining group
                for (int j = 0; j < groupSize - 1; j++) {
                    if (mapp[sm + 1] > 0) {
                        mapp[sm + 1]--;
                        sm = sm + 1;
                    } else {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};
```

---

## Dry Run

### Input:

```
hand = [1,2,3,3,4,4,5,6]
groupSize = 4
```

### Sorted:

```
[1,2,3,3,4,4,5,6]
```

### Frequency:

```
1:1, 2:1, 3:2, 4:2, 5:1, 6:1
```

### Process:

Start at 1:

```
1 → 2 → 3 → 4
```

Update:

```
1:0, 2:0, 3:1, 4:1
```

Next available = 3:

```
3 → 4 → 5 → 6
```

All cards used.

---

## Complexity

* Time: O(n log n) (sorting)
* Space: O(n) (frequency map)

---

## Key Concepts

* Greedy: Always start from smallest
* HashMap: Track frequency
* Sorting: Maintain order

---

## Core Insight

If the smallest available card cannot form a valid group, then no solution exists.

---

## One-Line Summary

Always form consecutive groups starting from the smallest unused number.
