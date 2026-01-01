# LFU Cache — Complete Explanation (O(1) get & put)

## Problem Recap

Design an **LFU (Least Frequently Used) Cache** with:

- `get(key)` → return value or `-1`
- `put(key, value)` → insert or update
- When full:

  - Remove **least frequently used** key
  - If tie → remove **least recently used among them**

- **Both operations must be O(1)**

---

## Core Rule (MOST IMPORTANT)

> **LFU eviction priority**
>
> 1. Lowest **frequency**
> 2. If tie → **LRU inside that frequency**

So LFU = **Frequency first, Recency second**

---

## Data Structures Used

```cpp
unordered_map<int, pair<int, int>> valFreq;
unordered_map<int, list<int>> freqList;
unordered_map<int, list<int>::iterator> pos;

int size;
int minFreq;
```

---

## What Each Structure Does

### 1️⃣ `valFreq`

```cpp
key → { value , frequency }
```

Example:

```
1 → {10, 2}
```

Fast access to:

- value
- current frequency

---

### 2️⃣ `freqList`

```cpp
frequency → list of keys (LRU order)
```

Example:

```
freqList[1] = [2, 4]
freqList[2] = [1]
```

Meaning:

- Keys with same frequency are ordered by **recency**
- Front = LRU
- Back = MRU

---

### 3️⃣ `pos`

```cpp
key → iterator to its node in freqList[freq]
```

Why?

- `list.erase(iterator)` = **O(1)**
- Without iterator → O(n) ❌

---

### 4️⃣ `minFreq`

Tracks:

```
Current minimum frequency in cache
```

This avoids scanning all frequencies during eviction.

---

## Constructor

```cpp
LFUCache(int capacity) {
    this->size = capacity;
    this->minFreq = 0;
}
```

- `size` = max capacity
- `minFreq` starts empty

---

## `get(int key)` — Logic

```cpp
int get(int key) {
    if (!valFreq.count(key)) return -1;
```

### Step 1: Key not present

- Return `-1`

---

```cpp
int freq = valFreq[key].second;
freqList[freq].erase(pos[key]);
```

### Step 2: Key is used

- Remove key from its **old frequency list**

---

```cpp
if (freqList[freq].empty() && minFreq == freq) {
    minFreq++;
}
```

### Step 3: Update `minFreq`

- If old frequency bucket is empty
- And that frequency was the minimum
- Increase `minFreq`

---

```cpp
freq++;
freqList[freq].push_back(key);
pos[key] = --freqList[freq].end();
valFreq[key].second = freq;
```

### Step 4: Increase frequency

- Move key to next frequency bucket
- Insert as **MRU**
- Update iterator and frequency

---

```cpp
return valFreq[key].first;
```

### Step 5: Return value

---

## Key Insight (Your Doubt)

> **`get` also increases frequency**

Because:

- LFU counts **usage**
- Usage = `get` OR `put`

---

## `put(int key, int value)` — Logic

```cpp
if (size == 0) return;
```

### Edge case

- Capacity zero → do nothing

---

### Case 1️⃣ Key already exists

```cpp
if (valFreq.count(key)) {
    valFreq[key].first = value;
    get(key);
    return;
}
```

- Update value
- Reuse `get(key)` to:

  - Increase frequency
  - Update recency

---

### Case 2️⃣ Cache is full

```cpp
if (size == valFreq.size()) {
    int lruKey = freqList[minFreq].front();
    freqList[minFreq].pop_front();
    pos.erase(lruKey);
    valFreq.erase(lruKey);
}
```

Eviction logic:

- Use `minFreq`
- Evict **LRU inside minFreq bucket**
- Remove from all structures

---

### Case 3️⃣ Insert new key

```cpp
valFreq[key] = {value, 1};
freqList[1].push_back(key);
pos[key] = --freqList[1].end();
minFreq = 1;
```

- New key starts with frequency `1`
- Becomes MRU in `freqList[1]`
- Reset `minFreq = 1`

---

## Complete Dry Run (Quick)

### Capacity = 2

### `put(1,1)`

```
valFreq: 1 → (1,1)
freqList: 1 → [1]
minFreq = 1
```

---

### `put(2,2)`

```
freqList: 1 → [1,2]
```

---

### `get(1)`

```
freqList:
1 → [2]
2 → [1]

minFreq = 1
```

---

### `put(3,3)` (full)

- Evict `2` (freq=1, LRU)

```
freqList:
1 → [3]
2 → [1]

minFreq = 1
```

---

## Why This is O(1)

| Operation      | Why              |
| -------------- | ---------------- |
| Map lookup     | unordered_map    |
| Frequency move | list + iterator  |
| Eviction       | minFreq shortcut |
| LRU tie-break  | list.front()     |

No loops. No scans.

---

## Final Mental Model (LOCK THIS 🔒)

> **LRU = one list** > **LFU = list of lists** > **minFreq = eviction shortcut**
