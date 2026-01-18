# 📌 Find Median from Data Stream

This problem asks us to design a data structure that supports:

- `addNum(int num)` → insert a number into the data stream
- `findMedian()` → return the median of all inserted numbers

The data arrives **continuously**, so reprocessing the entire dataset repeatedly is inefficient.

---

## 🧠 Understanding Median

- If total count is **odd** → middle element
- If total count is **even** → average of two middle elements

Median depends on **ordering**, not on sum or frequency.

---

## 1️⃣ Naive Approach (Sorting Every Time)

### Idea

- Store all numbers in an array
- Sort the array whenever `findMedian()` is called
- Pick the middle element(s)

---

### Pseudocode

```
addNum(x):
    arr.push_back(x)

findMedian():
    sort(arr)
    n = arr.size()
    if n is odd:
        return arr[n/2]
    else:
        return (arr[n/2 - 1] + arr[n/2]) / 2
```

---

### Dry Run

Input stream:

```
5 → 15 → 1 → 3
```

Stored array before median:

```
[5, 15, 1, 3]
```

After sorting:

```
[1, 3, 5, 15]
```

Median:

```
(3 + 5) / 2 = 4
```

---

### Complexity

- `addNum` → **O(1)**
- `findMedian` → **O(N log N)** (sorting)
- Space → **O(N)**

---

### Why this fails

- Sorting is repeated unnecessarily
- Large input → Time Limit Exceeded (TLE)
- Not suitable for streaming data

---

## 2️⃣ Optimized Approach (Two Heaps – Streaming Median)

### Core Idea

Instead of sorting repeatedly, **maintain the data already split around the median**.

We use two heaps:

- **Max Heap (`smallHeap`)** → stores the smaller half of numbers
- **Min Heap (`largeHeap`)** → stores the larger half of numbers

---

### Heap Representation

```
smallHeap (max heap)      largeHeap (min heap)
[ smaller numbers ] | [ larger numbers ]
         ↑                     ↑
   largest of left      smallest of right
```

The median always lies **between these two tops**.

---

### Invariants (Must Always Hold)

1. `smallHeap.top() ≤ largeHeap.top()`
2. `| size(smallHeap) - size(largeHeap) | ≤ 1`

---

### Algorithm

#### addNum(num)

1. Insert `num` into `smallHeap`
2. If order breaks → move top from `smallHeap` to `largeHeap`
3. If size difference > 1 → rebalance heaps

Each operation costs at most `log N`.

---

#### findMedian()

- If both heaps have equal size → average of both tops
- Otherwise → top of the larger heap

---

## 🔍 Dry Run (Step-by-Step)

### Input stream

```
5, 15, 1, 3
```

---

### Insert 5

```
smallHeap = [5]
largeHeap = []
median = 5
```

---

### Insert 15

```
smallHeap = [15, 5]
→ rebalance

smallHeap = [5]
largeHeap = [15]

median = (5 + 15) / 2 = 10
```

---

### Insert 1

```
smallHeap = [5, 1]
largeHeap = [15]

median = 5
```

---

### Insert 3

```
smallHeap = [5, 3, 1]
→ rebalance

smallHeap = [3, 1]
largeHeap = [5, 15]

median = (3 + 5) / 2 = 4
```

---

## ⏱️ Complexity Analysis

### Time Complexity

- `addNum` → **O(log N)**
- `findMedian` → **O(1)** ✅

### Space Complexity

- **O(N)**

---

## 📊 Comparison Summary

| Approach      | addNum   | findMedian | Suitable for Streaming |
| ------------- | -------- | ---------- | ---------------------- |
| Sorting-based | O(1)     | O(N log N) | ❌                     |
| Two Heaps     | O(log N) | O(1)       | ✅                     |

---

## 🧩 Key Insight

> Don’t recompute order every time.
> Maintain the median boundary as data arrives.

This pattern is widely used in:

- Real-time analytics
- Sliding window median
- Online statistics systems

---

## 🏁 Conclusion

The two-heap solution transforms median finding from a repeated sorting problem into a **controlled balancing problem**.

Once the invariants are understood, the implementation becomes natural — and efficient enough for production-scale data streams.
