# 📘 Single-Threaded CPU (Heap Scheduling)

## 1️⃣ Problem recap (very short)

Har task ke paas:

```
[enqueueTime, processingTime]
```

CPU rules:

- Sirf wahi tasks le sakta hai jinka `enqueueTime <= currentTime`
- Available tasks mein se:

  - smallest `processingTime`
  - tie → smallest `index`

- CPU idle ho to time jump karega

---

## Core idea (lock this)

> **Sort by enqueueTime + Min-Heap by (processingTime, index)**

---

## 2️⃣ Solution using `pair<int,int>`

### Why pair?

Because we want:

```
(first = processingTime, second = index)
```

### Code (pair version)

```cpp
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();

        // attach original index
        for (int i = 0; i < n; i++) {
            tasks[i].push_back(i);
        }

        // sort by enqueueTime
        sort(tasks.begin(), tasks.end());

        vector<int> res;

        // min-heap: {processingTime, index}
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > minHeap;

        long long time = tasks[0][0];
        int i = 0;

        while (i < n || !minHeap.empty()) {

            // push all available tasks
            while (i < n && tasks[i][0] <= time) {
                minHeap.push({tasks[i][1], tasks[i][2]});
                i++;
            }

            if (minHeap.empty()) {
                // CPU idle → jump time
                time = tasks[i][0];
            } else {
                auto [procTime, idx] = minHeap.top();
                minHeap.pop();
                time += procTime;
                res.push_back(idx);
            }
        }

        return res;
    }
};
```

---

## 3️⃣ Solution using `array<int,2>`

### Why array?

Because:

```
array<int,2> = fixed-size container
```

It behaves like:

```
{processingTime, index}
```

### Code (array version)

```cpp
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();

        // attach original index
        for (int i = 0; i < n; ++i) {
            tasks[i].push_back(i);
        }

        // sort by enqueueTime
        sort(tasks.begin(), tasks.end());

        vector<int> res;

        // min-heap: {processingTime, index}
        priority_queue<
            array<int,2>,
            vector<array<int,2>>,
            greater<>
        > minHeap;

        long long time = tasks[0][0];
        int i = 0;

        while (!minHeap.empty() || i < n) {

            // push all tasks that have arrived
            while (i < n && tasks[i][0] <= time) {
                minHeap.push({tasks[i][1], tasks[i][2]});
                i++;
            }

            if (minHeap.empty()) {
                time = tasks[i][0];
            } else {
                auto [procTime, index] = minHeap.top();
                minHeap.pop();
                time += procTime;
                res.push_back(index);
            }
        }

        return res;
    }
};
```

---

## 4️⃣ IMPORTANT EXPLANATION (this is what you asked)

### ❓ `array<int,2>` kya hota hai?

```cpp
array<int,2> a = {x, y};
```

Means:

- fixed size container
- contiguous memory
- no pointers
- behaves like tuple: `{a[0], a[1]}`

So:

```
a[0] → processingTime
a[1] → index
```

---

### ❓ `pair<int,int>` vs `array<int,2>`

| Feature        | pair                | array          |
| -------------- | ------------------- | -------------- |
| Named members  | `.first`, `.second` | `a[0]`, `a[1]` |
| Size           | fixed (2)           | fixed (2)      |
| STL comparison | lexicographic       | lexicographic  |
| Destructuring  | yes                 | yes            |
| Performance    | same                | same           |

So both are **equally valid**.

---

### ❓ `greater<>` EMPTY kyu likhte hain?

This is the **key modern C++ concept**.

#### With `pair`

```cpp
greater<pair<int,int>>
```

You must specify the type explicitly.

#### With `array`

```cpp
greater<>
```

Because:

- `array<int,2>` already has `operator<`
- `greater<>` is a **transparent comparator**
- Compiler infers type automatically

Internally it does:

```
compare element[0]
if tie → compare element[1]
```

Exactly what we want:

```
processingTime ↑
index ↑
```

---

### ❓ So when can we use `greater<>`?

You can use `greater<>` when:

- Type supports `<` operator
- You want lexicographic comparison
- You don’t want to repeat type

That’s why `array<int,2>` + `greater<>` looks cleaner.

---

## 🧠 Mental model (lock this)

> **Heap element = what you want to compare by** > **Comparator = how you want it ordered**

Here:

```
{processingTime, index}
```

→ heap automatically does correct scheduling.

---

## Final takeaway (important)

- `pair` = explicit, beginner-friendly
- `array<int,2>` = clean, modern C++
- `greater<>` works because array has built-in ordering
