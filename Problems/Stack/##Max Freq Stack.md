# 📦 FreqStack — All 4 Approaches Explained (From Brute to Optimal)

---

## 🧠 Common Concepts Used

* **Frequency Map** → how many times a value appears
* **Recency** → latest pushed element wins ties
* **Stacks / Heap** → to maintain ordering efficiently

---

# 1️⃣ Solution 1 — Vector + Map (Brute Force)

### 💡 Idea

* Store all pushed values in a vector
* Track frequency using a map
* On pop:

  * Find maximum frequency
  * Scan vector from right to left to find latest value with that frequency

---

### 💻 Code (Short Comments)

```cpp
class FreqStack {
private:
    vector<int> stack;                // stores all pushed values
    unordered_map<int,int> mapp;      // frequency map
public:
    void push(int val) {
        stack.push_back(val);
        mapp[val]++;
    }
    
    int pop() {
        int mxCnt = 0;
        for (auto& [_, freq] : mapp) {
            mxCnt = max(mxCnt, freq);
        }

        int i = stack.size() - 1;
        while (mapp[stack[i]] != mxCnt) {
            i--;
        }

        int val = stack[i];
        stack.erase(stack.begin() + i);
        mapp[val]--;
        return val;
    }
};
```

---

### ⏱️ Complexity

| Operation | Time |
| --------- | ---- |
| push      | O(1) |
| pop       | O(n) |
| space     | O(n) |

❌ **Too slow for large input**

---

# 2️⃣ Solution 2 — Max Heap (Priority Queue)

### 💡 Idea

* Use a **max heap** ordered by:

  1. frequency
  2. index (recency)
* Store `{freq, index, value}`

---

### 💻 Code (Short Comments)

```cpp
class FreqStack {
private:
    priority_queue<vector<int>> heap; // {freq, index, value}
    unordered_map<int,int> mapp;
    int index = 0;
public:
    void push(int val) {
        mapp[val]++;
        heap.push({mapp[val], index++, val});
    }
    
    int pop() {
        auto top = heap.top();
        heap.pop();
        mapp[top[2]]--;
        return top[2];
    }
};
```

---

### ⏱️ Complexity

| Operation | Time     |
| --------- | -------- |
| push      | O(log n) |
| pop       | O(log n) |
| space     | O(n)     |

✅ Correct but **not optimal**

---

# 3️⃣ Solution 3 — HashMap + Stack Buckets

### 💡 Idea

* Group values by frequency
* Each frequency has its own stack
* Track `maxCnt`

---

### 💻 Code (Short Comments)

```cpp
class FreqStack {
private:
    unordered_map<int,int> cntMap;         // value -> frequency
    unordered_map<int, stack<int>> stacks; // freq -> stack of values
    int maxCnt = 0;
public:
    void push(int val) {
        int freq = ++cntMap[val];
        maxCnt = max(maxCnt, freq);
        stacks[freq].push(val);
    }
    
    int pop() {
        int val = stacks[maxCnt].top();
        stacks[maxCnt].pop();
        cntMap[val]--;
        if (stacks[maxCnt].empty()) maxCnt--;
        return val;
    }
};
```

---

### ⏱️ Complexity

| Operation | Time |
| --------- | ---- |
| push      | O(1) |
| pop       | O(1) |
| space     | O(n) |

✅ **Optimal logic** (hash-based)

---

# 4️⃣ Solution 4 — Vector of Stacks (Best & Cleanest)

### 💡 Idea

* Frequency = index in vector
* `stacks[f]` holds values with frequency `f`
* Vector size grows dynamically

---

### 💻 Code (Short Comments)

```cpp
class FreqStack {
private:
    unordered_map<int,int> cntMap;    // value -> frequency
    vector<stack<int>> stacks;        // index = frequency
    int maxCnt = 0;
public:
    FreqStack() {
        stacks.push_back(stack<int>()); // dummy index 0
    }
    
    void push(int val) {
        int freq = ++cntMap[val];
        if (freq == stacks.size()) {
            stacks.push_back(stack<int>());
        }
        maxCnt = max(maxCnt, freq);
        stacks[freq].push(val);
    }
    
    int pop() {
        int val = stacks[maxCnt].top();
        stacks[maxCnt].pop();
        cntMap[val]--;
        if (stacks[maxCnt].empty()) {
            stacks.pop_back();
            maxCnt--;
        }
        return val;
    }
};
```

---

### ⏱️ Complexity

| Operation | Time |
| --------- | ---- |
| push      | O(1) |
| pop       | O(1) |
| space     | O(n) |

⭐ **Best practical solution** (clean + fast)

---

## 🧠 Final Comparison Table

| Approach         | Push     | Pop      | Notes           |
| ---------------- | -------- | -------- | --------------- |
| Vector + Map     | O(1)     | O(n)     | Brute force     |
| Max Heap         | O(log n) | O(log n) | Easy but slower |
| HashMap + Stack  | O(1)     | O(1)     | Optimal         |
| Vector of Stacks | O(1)     | O(1)     | Best & clean    |

---

## 🔒 Mental Model (Lock This)

> **Frequency = bucket index**
> **Each bucket is a stack for recency**
> **Always pop from highest non-empty bucket**

---