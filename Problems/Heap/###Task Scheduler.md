# 📘 Task Scheduler 

## Problem Summary

You are given a list of CPU tasks represented by capital letters `A–Z` and a non-negative integer `n`.

Rules:

- Each task takes **1 unit of time**
- Same task must have **at least `n` units of cooldown** before it can run again
- CPU can be **idle** if no task is available

### Goal

Return the **minimum total time** required to finish all tasks.

---

## Key Insight

This is a **greedy scheduling + simulation** problem.

At every moment:

- Pick the task with **highest remaining frequency**
- If it can’t be run due to cooldown → CPU must **idle**

To manage this efficiently:

- **Max-Heap** → choose most frequent available task
- **Queue** → track tasks in cooldown with their next available time

---

## Data Structures Used

### 🔺 Max Heap (`priority_queue<int>`)

Stores:

```
remaining execution count of available tasks
```

Always gives the task we should run next.

---

### ⏳ Queue (`queue<pair<int,int>>`)

Stores:

```
{ remainingCount, timeWhenTaskCanBeUsedAgain }
```

This represents tasks currently in **cooldown**.

---

# 🟢 Solution 1 — Step-by-Step Time Simulation

### Idea

Simulate **every unit of time**, including idle slots.

---

### Code (with short comments)

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);

        // Count frequency of each task
        for (char& task : tasks)
            count[task - 'A']++;

        // Max-heap of remaining task counts
        priority_queue<int> heap;
        for (int& cnt : count)
            if (cnt > 0) heap.push(cnt);

        queue<pair<int, int>> q; // {remainingCount, availableTime}
        int time = 0;

        while (!heap.empty() || !q.empty()) {
            time++; // advance time by 1

            // Execute a task if available
            if (!heap.empty()) {
                int cnt = heap.top() - 1;
                heap.pop();

                if (cnt > 0)
                    q.push({cnt, time + n}); // put into cooldown
            }

            // Move task back to heap if cooldown finished
            if (!q.empty() && q.front().second == time) {
                heap.push(q.front().first);
                q.pop();
            }
        }

        return time;
    }
};
```

---

### How This Works (Flow)

1. At each time unit:

   - Try to run the most frequent available task

2. After running:

   - Reduce its count
   - Put it into cooldown (`time + n`)

3. If no task is available:

   - Time still moves forward (CPU idle)

4. Tasks re-enter heap when cooldown ends

---

### Complexity

```
Time  : O(total_time * log 26) ≈ O(total_time)
Space : O(26)
```

---

### Pros / Cons

✅ Very intuitive
✅ Easy to debug
❌ Simulates idle time step-by-step (slower)

---

# 🔵 Solution 2 — Optimized Time Jumping

### Idea

Instead of simulating **every idle unit**,
**jump time directly** to the next available task.

---

### Code (with short comments)

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);

        // Count task frequencies
        for (char& task : tasks)
            count[task - 'A']++;

        priority_queue<int> maxHeap;
        for (int& cnt : count)
            if (cnt > 0) maxHeap.push(cnt);

        queue<pair<int, int>> q; // {remainingCount, availableTime}
        int time = 0;

        while (!maxHeap.empty() || !q.empty()) {
            time++;

            if (maxHeap.empty()) {
                // No task available → jump to next available time
                time = q.front().second;
            } else {
                int cnt = maxHeap.top() - 1;
                maxHeap.pop();

                if (cnt > 0)
                    q.push({cnt, time + n});
            }

            // Release tasks whose cooldown finished
            if (!q.empty() && q.front().second == time) {
                maxHeap.push(q.front().first);
                q.pop();
            }
        }

        return time;
    }
};
```

---

### Why `time = q.front().second` is Correct

When:

```
maxHeap is empty
queue is NOT empty
```

It means:

- Tasks still exist
- All are in cooldown
- CPU **must be idle**

Instead of:

```
time++
time++
time++
```

We **fast-forward** directly to the next moment when a task becomes available.

This:

- Does NOT violate cooldown
- Does NOT skip valid execution
- Only skips forced idle time

---

### Complexity

```
Time  : O(number of tasks)
Space : O(26)
```

---

## Comparison of Both Solutions

| Aspect        | Solution 1   | Solution 2        |
| ------------- | ------------ | ----------------- |
| Simulation    | Step-by-step | Time jumping      |
| Idle handling | Explicit     | Optimized         |
| Speed         | Slower       | Faster            |
| Logic clarity | Very clear   | Slightly advanced |
| Interview     | ✅           | ✅                |

---

## Final Mental Model (Lock This In)

> **Heap = what task to run next** > **Queue = when a task can run again** > **Time jumps only when CPU is forced to idle**

---

## Final Recommendation

- Learn **Solution 1** to understand the flow
- Use **Solution 2** for optimized, production-ready code
- This pattern repeats in:

  - CPU scheduling
  - Rate limiting
  - Event simulation
  - Cooldown problems

---

### One-Line Takeaway

> **If nothing can run, don’t wait — jump time forward.**
