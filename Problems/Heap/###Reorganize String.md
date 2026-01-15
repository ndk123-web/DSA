# 📘 Reorganize String 

## Problem Summary

Given a string `s`, rearrange the characters so that **no two adjacent characters are the same**.

If it is not possible, return an empty string `""`.

---

## Key Constraint (Very Important)

If any character appears **more than `(n + 1) / 2` times**,
then it is **impossible** to rearrange the string.

Why?
Because there won’t be enough “other characters” to separate it.

---

## Core Insight

This is a **greedy problem**.

At every step:

- We should place the character with **highest remaining frequency**
- While ensuring it does **not repeat immediately**

That naturally leads to using a **max heap**.

---

## Overview of the 3 Approaches

You implemented **three valid greedy strategies**:

| Approach              | Core Idea                             |
| --------------------- | ------------------------------------- |
| 1️⃣ Two-at-a-time      | Always take top 2 most frequent chars |
| 2️⃣ Prev-based (map)   | Hold last used char out of heap       |
| 3️⃣ Prev-based (array) | Same as 2, but optimized freq storage |

All three are **correct** and **accepted**.

---

# 🟢 Approach 1 — Two-at-a-Time Greedy

### Idea

- Always pick **two different characters** with highest frequency
- Place them together
- Reduce their counts and push back if needed

This guarantees:

- No adjacent duplicates
- Simple reasoning

---

### Code

```cpp
class Solution {
public:
    string reorganizeString(string s) {
        string res;
        unordered_map<char, int> freq;
        priority_queue<pair<int, char>> pq;

        for (char c : s) freq[c]++;

        for (auto& p : freq) {
            pq.push({p.second, p.first});
        }

        while (pq.size() >= 2) {
            auto [cnt1, ch1] = pq.top(); pq.pop();
            auto [cnt2, ch2] = pq.top(); pq.pop();

            res.push_back(ch1);
            res.push_back(ch2);

            if (--cnt1 > 0) pq.push({cnt1, ch1});
            if (--cnt2 > 0) pq.push({cnt2, ch2});
        }

        // One character may remain
        if (!pq.empty()) {
            if (pq.top().first > 1) return "";
            res.push_back(pq.top().second);
        }

        return res;
    }
};
```

---

### Why This Works

- By placing **two different characters together**, adjacency is always safe
- Any leftover character must have frequency `1`, otherwise impossible

---

### Complexity

```
Time:  O(n log k)
Space: O(k)
```

Where `k` = number of distinct characters (≤ 26)

---

### Pros / Cons

✅ Very intuitive
✅ Easy to reason about
❌ Slightly less flexible
❌ Special handling for leftover character

---

# 🔵 Approach 2 — Prev-Based Greedy (Using Map)

### Idea

- Use only **one character per iteration**
- The previously used character (`prev`) is **temporarily banned**
- After one step, `prev` is pushed back into heap

This ensures:

- Same character can never be picked twice in a row

---

### Code

```cpp
class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> freq;
        priority_queue<pair<int, char>> pq;
        int n = s.size();
        string res = "";

        for (char c : s) freq[c]++;

        for (auto& p : freq) {
            if (p.second > (n + 1) / 2) return "";
            pq.push({p.second, p.first});
        }

        pair<int, char> prev = {0, '#'};

        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();

            res.push_back(p.second);
            p.first--;

            if (prev.first > 0) pq.push(prev);

            prev = p;
        }

        return res;
    }
};
```

---

### Why This Works

**Invariant**:

> Heap contains all characters **except the one used in the previous step**

So:

- Adjacent duplicates are impossible
- Greedy always chooses the best available option

---

### Complexity

```
Time:  O(n log k)
Space: O(k)
```

---

### Pros / Cons

✅ Elegant
✅ Handles everything uniformly
❌ `prev` logic is subtle
❌ Easy to implement incorrectly

---

# 🟣 Approach 3 — Prev-Based (Optimized with Array)

### Idea

Same logic as Approach 2, but:

- Use `vector<int>(26)` instead of `unordered_map`
- Faster and simpler for lowercase letters

---

### Code

```cpp
class Solution {
public:
    string reorganizeString(string s) {
        vector<int> freq(26, 0);
        int n = s.size();

        for (char c : s)
            freq[c - 'a']++;

        priority_queue<pair<int,char>> pq;
        string res = "";

        for (int i = 0; i < 26; i++) {
            if (freq[i] > (n + 1) / 2) return "";
            if (freq[i] > 0)
                pq.push({freq[i], char('a' + i)});
        }

        pair<int, char> prev = {0, '#'};

        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();

            res.push_back(p.second);
            p.first--;

            if (prev.first > 0)
                pq.push(prev);

            prev = p;
        }

        return res;
    }
};
```

---

### Why This Is Better Than Map Version

- No hashing overhead
- Fixed-size frequency table
- Cleaner character mapping

---

### Complexity

```
Time:  O(n log 26) ≈ O(n)
Space: O(26)
```

---

## Comparison of All 3 Approaches

| Feature             | Two-at-a-time | Prev (Map) | Prev (Array) |
| ------------------- | ------------- | ---------- | ------------ |
| Greedy clarity      | ⭐⭐⭐⭐      | ⭐⭐⭐     | ⭐⭐⭐       |
| Implementation ease | ⭐⭐⭐⭐      | ⭐⭐       | ⭐⭐⭐       |
| Performance         | ⭐⭐⭐        | ⭐⭐⭐     | ⭐⭐⭐⭐     |
| Interview safety    | ⭐⭐⭐⭐      | ⭐⭐⭐     | ⭐⭐⭐⭐     |

---

## Final Mental Models (Lock These In)

### Two-at-a-time

> “Always place two different most frequent characters together.”

### Prev-based

> “The last used character is temporarily banned.”

Both are valid greedy strategies.

---

## Final Recommendation

- **For understanding** → Approach 1
- **For elegance** → Approach 2
- **For performance & cleanliness** → Approach 3

---

### One-Line Takeaway

> **Reorganize String is not about cooldowns or queues — it’s about controlling adjacency using greedy frequency selection.**
