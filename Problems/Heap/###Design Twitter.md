# Design Twitter

## Problem Summary

Design a simplified version of Twitter that supports the following operations:

- Post a tweet
- Follow / unfollow users
- Get a user’s news feed

### Rules

- Each tweet has a **unique tweetId**
- Each tweet takes place at a **specific time**
- A user’s news feed contains:

  - Their **own tweets**
  - Tweets from users they **follow**

- News feed shows **at most 10 tweets**
- Tweets are ordered from **most recent → least recent**

---

## Why This Problem Is Tricky

This is **not** just a map or list problem.

The hard part is:

> **Merging tweets from multiple users by recency and returning only the latest 10.**

That immediately tells us:

- We need **time ordering**
- We need **Top-K (10) most recent**
- We need **efficient merging**

👉 This naturally leads to **heap + timestamp**.

---

## High-Level Design

### Core Ideas

1. **Every tweet needs a timestamp**
2. **Each user can follow many users**
3. **News feed = merge tweets from multiple users**
4. **Only top 10 most recent tweets matter**

---

## Data Structures Used

### 1️⃣ Tweet Storage

```cpp
unordered_map<int, vector<pair<int,int>>> tweets;
```

Stores:

```
userId → [ (time, tweetId), ... ]
```

Each user’s tweets are naturally ordered by time.

---

### 2️⃣ Follow Relationships

```cpp
unordered_map<int, unordered_set<int>> followMap;
```

Stores:

```
follower → { followee1, followee2, ... }
```

A user can follow **multiple users**.

---

### 3️⃣ Max Heap (for News Feed)

```cpp
priority_queue<pair<int,int>>
```

Stores:

```
(time, tweetId)
```

Ensures we always get the **most recent tweet first**.

---

## Algorithm Breakdown

### 🔹 postTweet(userId, tweetId)

- Store `(time, tweetId)` in user’s tweet list
- Increment global timestamp

---

### 🔹 follow(followerId, followeeId)

- Add followee to follower’s follow set
- Ignore self-follow

---

### 🔹 unfollow(followerId, followeeId)

- Remove followee from follower’s follow set

---

### 🔹 getNewsFeed(userId)

1. Push **own tweets** into max heap
2. Push **followees’ tweets** into max heap
3. Pop **top 10 tweets** from heap
4. Return tweetIds in order

This is essentially a **k-way merge using a heap**.

---

## ✅ Correct & Working Code (With Short Comments)

```cpp
class Twitter {
private:
    int time = 0; // global timestamp

    // user -> list of {time, tweetId}
    unordered_map<int, vector<pair<int,int>>> tweets;

    // user -> set of followees
    unordered_map<int, unordered_set<int>> followMap;

public:
    Twitter() {}

    // Post a tweet
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time++, tweetId});
    }

    // Retrieve the 10 most recent tweets
    vector<int> getNewsFeed(int userId) {
        vector<int> res;

        // Max heap sorted by time
        priority_queue<pair<int,int>> pq;

        // Add user's own tweets
        for (auto &t : tweets[userId]) {
            pq.push(t);
        }

        // Add followees' tweets
        for (int followee : followMap[userId]) {
            for (auto &t : tweets[followee]) {
                pq.push(t);
            }
        }

        // Extract top 10 recent tweets
        while (!pq.empty() && res.size() < 10) {
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;
    }

    // Follow a user
    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) return;
        followMap[followerId].insert(followeeId);
    }

    // Unfollow a user
    void unfollow(int followerId, int followeeId) {
        followMap[followerId].erase(followeeId);
    }
};
```

---

## Complexity Analysis

### Time Complexity

- `postTweet` → **O(1)**
- `follow / unfollow` → **O(1)**
- `getNewsFeed`:

  - Push tweets into heap → `O(T log T)`
  - Extract 10 tweets → `O(10 log T)`

Where `T` = total tweets from user + followees.

---

### Space Complexity

- Tweets storage → **O(total tweets)**
- Follow relationships → **O(total follows)**
- Heap (temporary) → **O(T)**

---

## Common Mistakes (What NOT to Do)

❌ Storing only tweetId (no timestamp)
❌ Allowing only one followee per user
❌ Appending tweets instead of merging by time
❌ Forgetting the “latest 10 only” rule
❌ Not using a heap for ordering

---

## Final Mental Model (Lock This In)

> **Design Twitter = merge sorted streams by time**

- Each user’s tweets are a sorted stream
- News feed = merge all relevant streams
- Heap gives most recent tweet efficiently
- Return only top 10

---

## Interview Tip

If the interviewer asks:

> “Why heap?”

Answer:

> “Because we need to merge tweets from multiple users by recency and return only the top 10 efficiently.”

That’s the correct reasoning.

---

### One-Line Takeaway

> **If a system asks for ‘latest K from many sources’, think heap + timestamp.**
