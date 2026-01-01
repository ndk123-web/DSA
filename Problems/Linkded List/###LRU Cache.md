# 🧠 LRU Cache (Least Recently Used) — Explained with Code

## 🔹 Core Idea (1 line)

> **Jo key recently use hui ho (get / put), wo “most recently used (MRU)” ban jaati hai.
> Capacity full ho jaaye to “least recently used (LRU)” key remove hoti hai.**

---

## 🔹 Data Structures Used

```cpp
unordered_map<int, pair<int, list<int>::iterator>> cache;
list<int> latest;
int size;
```

### Why this combo?

| Structure       | Kaam                  |
| --------------- | --------------------- |
| `unordered_map` | O(1) lookup           |
| `list`          | Maintain usage order  |
| `iterator`      | O(1) delete from list |

---

## 🔹 Meaning of This Line (Important Doubt)

```cpp
unordered_map<int, pair<int, list<int>::iterator>> cache;
```

### Actual meaning:

```
key → { value , iterator_to_key_in_list }
```

👉 **Har key ke saath sirf ek iterator store hota hai**,
jo `latest` list ke **exact node** ko point karta hai.

---

## ✅ Complete Code (With Comments)

```cpp
class LRUCache {
private:
    // key -> { value , iterator to position in list }
    unordered_map<int, pair<int, list<int>::iterator>> cache;

    // Usage order: front = LRU, back = MRU
    list<int> latest;

    int size;

public:
    // Constructor
    LRUCache(int capacity) {
        this->size = capacity;
    }

    // GET operation
    int get(int key) {
        // Key not present
        if (cache.find(key) == cache.end())
            return -1;

        // Remove key from its old position in list
        latest.erase(cache[key].second);

        // Move key to back (MRU)
        latest.push_back(key);

        // Update iterator in map
        cache[key].second = --latest.end();

        // Return value
        return cache[key].first;
    }

    // PUT operation
    void put(int key, int value) {

        // Case 1: Key already exists
        if (cache.find(key) != cache.end()) {
            // Remove old position
            latest.erase(cache[key].second);
        }

        // Case 2: Key does not exist & cache is full
        else if (cache.size() == size) {
            // Identify LRU key (front of list)
            int oldKey = latest.front();

            // Remove LRU key from list
            latest.erase(cache[oldKey].second);

            // Remove LRU key from map
            cache.erase(oldKey);
        }

        // Insert key as MRU
        latest.push_back(key);

        // Store value and iterator to list node
        cache[key] = {value, --latest.end()};
    }
};
```

---

## 🔹 What Does `--latest.end()` Mean?

```cpp
latest.end()      // points AFTER last element
--latest.end()    // points TO last element
```

So:

```cpp
cache[key].second = --latest.end();
```

👉 means
**“iss key ka iterator list ke last (MRU) node pe set kar do”**

---

## 🔹 DRY RUN (Step-by-Step)

### Capacity = 2

---

### ▶ put(1, 10)

```
latest = [1]
cache  = {1 → (10)}
```

---

### ▶ put(2, 20)

```
latest = [1, 2]
cache  = {1, 2}
```

---

### ▶ get(1)

- 1 accessed → MRU

```
latest = [2, 1]
return 10
```

---

### ▶ put(3, 30) (cache full)

- LRU = 2 → remove

```
latest = [1, 3]
cache  = {1, 3}
```

---

### ▶ get(2)

```
return -1
```

---

## 🔹 Exact Rules (Tumhara Doubt Clear)

| Operation | Key present?  | Action                  |
| --------- | ------------- | ----------------------- |
| get       | ❌            | return -1               |
| get       | ✅            | MRU bana do             |
| put       | ❌ & full     | LRU remove → insert MRU |
| put       | ❌ & not full | insert MRU              |
| put       | ✅            | value update + MRU      |

👉 **Har get / put = MRU update**

---

## 🔹 Why This Works in O(1)

| Operation        | Why O(1)      |
| ---------------- | ------------- |
| map lookup       | unordered_map |
| delete from list | iterator      |
| move to MRU      | push_back     |
| remove LRU       | pop_front     |

---

## 🔹 One-Line Mental Model (Lock This)

> **Map data rakhta hai, list order rakhti hai, iterator dono ko jodta hai.**
