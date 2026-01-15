# 📘 Design Twitter 

## Problem Summary

Design a simplified Twitter that supports:

- Posting tweets
- Following / unfollowing users
- Fetching the **10 most recent tweets** in a user’s news feed

### Rules

- Tweet IDs are unique
- Tweets are ordered by **recency**
- News feed includes:

  - User’s own tweets
  - Tweets from users they follow

- Return **at most 10 tweets**, newest first

---

## Core Insight

This problem is about:

> **Merging tweets from multiple users based on time and returning Top-10**

So the real challenges are:

- Maintaining **tweet order**
- Handling **multiple followees**
- Efficiently extracting **latest tweets**

---

## Data Model (Common to Both Solutions)

### Tweets

```cpp
unordered_map<int, vector<pair<int,int>>> tweets;
```

Stores:

```
userId → [(time, tweetId), ...]
```

Time is required to compare recency.

---

### Follow Relationship

```cpp
followerId → list / set of followees
```

This direction is critical because:

> Feed is pulled by the follower, not pushed by followees.

---

# 🟢 Solution 1 — Brute Force (Max-Heap Merge)

This is **simple, intuitive, and correct**, but not optimized.

---

## Idea

1. Collect **all tweets** from:

   - User
   - All followees

2. Push them into a **max-heap by time**
3. Pop top 10 tweets

This is a **full merge + top-10 extraction**.

---

## Code (Brute Force)

```cpp
class Twitter {
private:
    unordered_map<int, vector<pair<int,int>>> tweets;
    unordered_map<int, vector<int>> followMap;
    int time = 0;

public:
    Twitter() {}

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        priority_queue<pair<int,int>> maxHeap;

        // Add user's own tweets
        for (auto& t : tweets[userId]) {
            maxHeap.push(t);
        }

        // Add followees' tweets
        for (int f : followMap[userId]) {
            for (auto& t : tweets[f]) {
                maxHeap.push(t);
            }
        }

        // Extract 10 most recent tweets
        while (!maxHeap.empty() && res.size() < 10) {
            res.push_back(maxHeap.top().second);
            maxHeap.pop();
        }

        return res;
    }

    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) return;

        auto& v = followMap[followerId];
        if (find(v.begin(), v.end(), followeeId) == v.end()) {
            v.push_back(followeeId);
        }
    }

    void unfollow(int followerId, int followeeId) {
        auto& v = followMap[followerId];
        auto it = find(v.begin(), v.end(), followeeId);
        if (it != v.end()) v.erase(it);
    }
};
```

---

## Why This Works

- Heap ensures **global ordering by time**
- Max-heap top is always the **most recent tweet**
- Correctly merges tweets across users

---

## Complexity (Brute Force)

Let:

- `T` = total tweets of user + followees

### Time

```
getNewsFeed → O(T log T)
```

### Space

```
O(T)
```

---

## Downsides

❌ Pushes **all tweets** into heap
❌ Inefficient when users have many tweets
❌ Not optimal for large inputs

---

## When to Use

- Learning / clarity
- Small constraints
- First working solution

---

# 🔵 Solution 2 — Optimized (Top-10 Min-Heap + Set)

This is the **interview-preferred and scalable solution**.

---

## Key Optimization Idea

> We only need the **latest 10 tweets** — everything else is irrelevant.

So:

- Maintain a **min-heap of size 10**
- Always discard older tweets
- Use a **set** for fast follow/unfollow

---

## Code (Optimized)

```cpp
class Twitter {
private:
    int time = 0;
    unordered_map<int, vector<pair<int,int>>> tweets;
    unordered_map<int, unordered_set<int>> followMap;

public:
    Twitter() {}

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> res;

        // Min-heap: oldest tweet on top
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        // Own tweets
        for (auto& t : tweets[userId]) {
            pq.push(t);
            if (pq.size() > 10) pq.pop();
        }

        // Followees' tweets
        for (int f : followMap[userId]) {
            for (auto& t : tweets[f]) {
                pq.push(t);
                if (pq.size() > 10) pq.pop();
            }
        }

        // Extract tweets (oldest → newest)
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }

        // Reverse to get newest → oldest
        reverse(res.begin(), res.end());
        return res;
    }

    void follow(int followerId, int followeeId) {
        if (followerId != followeeId)
            followMap[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        followMap[followerId].erase(followeeId);
    }
};
```

---

## Why This Is Better

- Heap never grows beyond **10**
- Old tweets are discarded immediately
- Follow operations are **O(1)**

---

## Complexity (Optimized)

Let:

- `F` = number of followees
- `T` = tweets per user

### Time

```
getNewsFeed → O((F × T) log 10) ≈ O(F × T)
```

### Space

```
O(10) heap + follow sets
```

---

## Comparison

| Aspect          | Brute Force | Optimized |
| --------------- | ----------- | --------- |
| Heap size       | All tweets  | Max 10    |
| Follow storage  | vector      | set       |
| Time            | O(T log T)  | O(T)      |
| Space           | O(T)        | O(1)      |
| Interview ready | ❌          | ✅        |

---

## Final Mental Model (Lock This In)

> **Feed generation = merge by time + top-K selection**

- Brute force → merge everything
- Optimized → keep only what matters

---

## Final Recommendation

- Start with **brute force** to understand correctness
- Move to **optimized** for interviews & scale
- Always ask:
  👉 _“Do I really need all elements, or only top-K?”_

---

### One-Line Takeaway

> **Correctness first, optimization second — but know both.**
