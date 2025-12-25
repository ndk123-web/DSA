# ⏱️ Time Based Key-Value Store – Explanation & Mistakes

## Problem Recap (One Line)

Har key ke multiple values hote hain with timestamps.
`get(key, t)` → **latest value jiska timestamp ≤ t ho**.

---

## ✅ Solution 1 (Binary Search – Optimized)

```cpp
class TimeMap {
    map<string, vector<pair<string, int>>> mapp;

public:
    void set(string key, string value, int timestamp) {
        mapp[key].push_back({value, timestamp});
    }

    string get(string key, int timestamp) {
        string res;
        vector<pair<string,int>>& v = mapp[key]; // reference, no copy

        int l = 0, r = v.size() - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;
            if (v[m].second <= timestamp) {
                res = v[m].first;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return res;
    }
};
```

### ⏱️ Time Complexity

- `set()` → **O(1)**
- `get()` → **O(log n)**

### ✅ Ye sahi approach hai

---

## ❌ Solution 2 (Linear Scan – Slow but Passes)

```cpp
class TimeMap {
    map<string,vector<pair<string,int>>> mapp;

public:
    void set(string key, string value, int timestamp) {
        mapp[key].push_back({value,timestamp});
    }

    string get(string key, int timestamp) {
        vector<pair<string,int>> v = mapp[key]; // COPY
        string res;

        for (auto& obj : v) {
            if (obj.second <= timestamp) {
                res = obj.first;
            }
        }
        return res;
    }
};
```

### ⏱️ Time Complexity

- `get()` → **O(n)**

### ⚠️ Ye brute force hai, interview-grade nahi

---

## ❌ Teri Asli Mistakes (Important)

### ❌ Mistake 1: Vector COPY in optimized solution (pehle version mein)

```cpp
vector<pair<string,int>> v = mapp[key];
```

🔴 Problem:

- Har `get()` pe **poora vector copy**
- Binary search ka fayda hi khatam

✔️ Fix:

```cpp
vector<pair<string,int>>& v = mapp[key];
```

---

### ❌ Mistake 2: `map` instead of `unordered_map`

```cpp
map<string, ...> mapp;
```

- `map` → O(log n)
- `unordered_map` → O(1)

⚠️ LeetCode ke constraints ke liye:

```cpp
unordered_map<string, vector<pair<int,string>>>
```

best hota hai.

---

### ❌ Mistake 3: Data order (style issue)

Tu store kar raha hai:

```cpp
pair<string, int> // value, timestamp
```

Binary search hamesha **timestamp pe hota hai**, so better:

```cpp
pair<int, string> // timestamp, value
```

Cleaner, safer, readable.

---

## ✅ Best Possible Version (Industry Standard)

```cpp
class TimeMap {
    unordered_map<string, vector<pair<int,string>>> mp;

public:
    void set(string key, string value, int timestamp) {
        mp[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (!mp.count(key)) return "";

        auto& v = mp[key];
        int l = 0, r = v.size() - 1;
        string res = "";

        while (l <= r) {
            int m = l + (r - l) / 2;
            if (v[m].first <= timestamp) {
                res = v[m].second;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return res;
    }
};
```

---

## 🧠 Core Learnings (Exam + Interview)

1. **Binary search tabhi fast hota hai jab data copy na ho**
2. **Reference vs Copy** = TLE vs Accepted
3. `unordered_map` > `map` for lookup problems
4. Always binary search on the **sorted field**

---

## 🧾 One-Line Interview Answer

> We store values per key in timestamp order and binary search for the largest timestamp ≤ query time.
