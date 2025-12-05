
---

# Boats to Save People — LeetCode 881

**Pattern:** Greedy, Two Pointers
**Difficulty:** Medium
**Topics:** Sorting, Greedy Optimization

---

# 1. Problem

You are given:

* `people[i]` = weight of the i-th person
* A boat with capacity `limit`
* Each boat can carry **at most 2 people**,
* Combined weight ≤ limit

Return the **minimum number of boats** required.

---

# 2. Brute Force (O(n²))

### Idea

For each heaviest unused person:

1. Try pairing him with the heaviest possible unused partner
2. If no partner fits → he goes alone
3. Mark used people
4. Count boats

This checks many combinations and is slow.

### Code

```cpp
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size();
        vector<bool> used(n, false);
        sort(people.begin(), people.end());

        int boats = 0;

        for (int i = n - 1; i >= 0; i--) {
            if (used[i]) continue;

            used[i] = true;
            boats++;

            for (int j = i - 1; j >= 0; j--) {
                if (!used[j] && people[i] + people[j] <= limit) {
                    used[j] = true;
                    break;
                }
            }
        }

        return boats;
    }
};
```

### Complexity

Time O(n²), Space O(n)

---

# 3. Optimal Greedy (Two Pointers)

### Core Logic

Sort the people.

Use two pointers:

* `right` → heaviest
* `left` → lightest

At each step:

* Always take the heaviest person (`right--`)
* Try pairing with lightest (`left++`), only if `lightest + heaviest` ≤ limit
* Every iteration consumes **one boat**

### Why this works

Pairing the heaviest with lightest **removes maximum weight** each time without wasting capacity.

### Code

```cpp
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int left = 0, right = people.size() - 1;
        int boats = 0;

        while (left <= right) {
            int remain = limit - people[right--];
            boats++;
            if (left <= right && people[left] <= remain) {
                left++;
            }
        }

        return boats;
    }
};
```

### Complexity

Time O(n log n), Space O(1)

---

# 4. Count-Sort + Two Pointers

(This is the version you asked to add.)

### Why use Count-Sort?

If person weights are small and bounded,
count sort is **faster** than comparison sorting:

* Normal sort → O(n log n)
* Count sort → O(n + maxWeight)

### Important

When filling the array back:

* Write the **value** (`w`)
* Repeat it `count[w]` times
* Do **not** write the frequency itself

### Code (Corrected Version)

```cpp
class Solution {
public:
    int numRescueBoats(vector<int>& nums, int limit) {
        int n = nums.size();

        // find max weight for count sort
        int maxW = *max_element(nums.begin(), nums.end());
        vector<int> count(maxW + 1, 0);

        // build frequency array
        for (int w : nums) count[w]++;

        // rebuild nums in sorted order
        int k = 0;
        for (int w = 0; w <= maxW; w++) {
            while (count[w] > 0) {
                nums[k++] = w;   // write weight, not frequency
                count[w]--;
            }
        }

        // optimal two-pointer greedy
        int left = 0, right = n - 1;
        int boats = 0;

        while (left <= right) {
            int remain = limit - nums[right--];
            boats++;

            if (left <= right && nums[left] <= remain) {
                left++;
            }
        }

        return boats;
    }
};
```

### Complexity

Time O(n + maxWeight) + O(n)
Space O(maxWeight)

---

# 5. Summary

| Approach                  | Time        | Space   | Notes                      |
| ------------------------- | ----------- | ------- | -------------------------- |
| Brute Force               | O(n²)       | O(n)    | Slow and not scalable      |
| Greedy + Two Pointers     | O(n log n)  | O(1)    | Cleanest and optimal       |
| Count Sort + Two Pointers | O(n + maxW) | O(maxW) | Faster for bounded weights |

Two-pointer method is the standard approach used in interviews and competitive programming.

---