## 🧠 **C++ Cheatsheet — Vectors, Maps, Sets, Algorithms, and Core Concepts**

---

### **1️⃣ VECTORS (`std::vector`)**

Header:

```cpp
#include <vector>
using namespace std;
```

#### **Basic Syntax**

```cpp
vector<int> v;          // empty vector
vector<int> v(5);       // size 5, all 0
vector<int> v(5, 10);   // size 5, all 10
vector<int> v2 = {1,2,3,4};
```

#### **Main Methods**

| Operation              | Description                                | Example                            |
| ---------------------- | ------------------------------------------ | ---------------------------------- |
| `v.push_back(x)`       | Adds element at the end                    | `v.push_back(5);`                  |
| `v.emplace_back(x)`    | Adds element (faster, constructs in-place) | `v.emplace_back(5);`               |
| `v.pop_back()`         | Removes last element                       | `v.pop_back();`                    |
| `v.size()`             | Number of elements                         | `cout << v.size();`                |
| `v.empty()`            | Check if empty                             | `if(v.empty()) ...`                |
| `v.clear()`            | Removes all elements                       | `v.clear();`                       |
| `v.front() / v.back()` | Access first/last element                  | `v.back();`                        |
| `v[i]` or `v.at(i)`    | Access element at index                    | `v[2];`                            |
| `v.insert(pos, val)`   | Insert element at iterator                 | `v.insert(v.begin()+2, 10);`       |
| `v.erase(pos)`         | Remove one element                         | `v.erase(v.begin()+3);`            |
| `v.erase(start, end)`  | Remove range                               | `v.erase(v.begin(), v.begin()+3);` |
| `v.swap(v2)`           | Swap two vectors                           | `v.swap(v2);`                      |
| `v.begin(), v.end()`   | Iterators                                  | Used for loops & algorithms        |

> ⚙️ **Note**:
>
> * `push_back` makes a copy.
> * `emplace_back` constructs in place (no copy → faster).

---

### **2️⃣ MAPS (`std::map` and `std::unordered_map`)**

Header:

```cpp
#include <map>
#include <unordered_map>
using namespace std;
```

#### **Map = Sorted by key (Balanced BST)**

```cpp
map<int, string> m;
m[1] = "apple";
m.insert({2, "banana"});
```

#### **Unordered Map = Faster (Hash Table)**

```cpp
unordered_map<int, string> um;
um[3] = "cat";
```

#### **Main Methods**

| Operation            | Description              | Example                        |
| -------------------- | ------------------------ | ------------------------------ |
| `m[key]`             | Access or create key     | `m[5] = "dog";`                |
| `m.at(key)`          | Access existing key only | `cout << m.at(5);`             |
| `m.insert({k, v})`   | Insert pair              | `m.insert({3, "rat"});`        |
| `m.erase(key)`       | Erase key                | `m.erase(3);`                  |
| `m.find(key)`        | Returns iterator         | `if(m.find(5) != m.end()) ...` |
| `m.count(key)`       | 0 or 1 (presence check)  | `if(m.count(2)) ...`           |
| `m.size()`           | No. of pairs             | `m.size();`                    |
| `m.empty()`          | True if empty            | `if(m.empty()) ...`            |
| `m.clear()`          | Remove all               | `m.clear();`                   |
| `m.begin(), m.end()` | Iterators                | for traversing                 |

#### **Looping**

```cpp
for(auto &p : m)
    cout << p.first << " " << p.second << endl;
```

> ⚙️ `map` = O(log n)
> ⚙️ `unordered_map` = O(1) average

---

### **3️⃣ SETS (`std::set` and `std::unordered_set`)**

Header:

```cpp
#include <set>
#include <unordered_set>
```

#### **Set = Sorted Unique Elements**

```cpp
set<int> s = {1, 3, 5};
s.insert(2);
s.erase(3);
```

#### **Unordered Set = Faster (Hash Table)**

```cpp
unordered_set<int> us;
us.insert(10);
```

#### **Main Methods**

| Operation            | Description      | Example                        |
| -------------------- | ---------------- | ------------------------------ |
| `s.insert(x)`        | Add element      | `s.insert(4);`                 |
| `s.erase(x)`         | Remove           | `s.erase(2);`                  |
| `s.find(x)`          | Returns iterator | `if(s.find(3) != s.end()) ...` |
| `s.count(x)`         | 0 or 1           | `if(s.count(5)) ...`           |
| `s.size()`           | Count            | `s.size();`                    |
| `s.clear()`          | Clear all        | `s.clear();`                   |
| `s.empty()`          | Check empty      | `s.empty();`                   |
| `s.begin(), s.end()` | Iterators        | for looping                    |

#### **Loop**

```cpp
for(auto x : s)
    cout << x << " ";
```

> ⚙️ `set` = O(log n)
> ⚙️ `unordered_set` = O(1) average

---

### **4️⃣ BUILT-IN ALGORITHMS**

Header:

```cpp
#include <algorithm>
#include <numeric> // for accumulate
```

#### **Most Useful Ones**

| Algorithm                        | Description                                     | Example                                                       |
| -------------------------------- | ----------------------------------------------- | ------------------------------------------------------------- |
| `sort(begin, end)`               | Sort ascending                                  | `sort(v.begin(), v.end());`                                   |
| `sort(rbegin, rend)`             | Sort descending                                 | `sort(v.rbegin(), v.rend());`                                 |
| `reverse(begin, end)`            | Reverse order                                   | `reverse(v.begin(), v.end());`                                |
| `max_element(begin, end)`        | Get max iterator                                | `*max_element(v.begin(), v.end());`                           |
| `min_element(begin, end)`        | Get min iterator                                | `*min_element(v.begin(), v.end());`                           |
| `accumulate(begin, end, init)`   | Sum elements                                    | `accumulate(v.begin(), v.end(), 0);`                          |
| `count(begin, end, val)`         | Count occurrences                               | `count(v.begin(), v.end(), 3);`                               |
| `find(begin, end, val)`          | Find value                                      | `find(v.begin(), v.end(), 5);`                                |
| `binary_search(begin, end, val)` | True/False (sorted data)                        | `binary_search(v.begin(), v.end(), 3);`                       |
| `lower_bound(begin, end, val)`   | First ≥ val                                     | `auto it = lower_bound(v.begin(), v.end(), 5);`               |
| `upper_bound(begin, end, val)`   | First > val                                     | `auto it = upper_bound(v.begin(), v.end(), 5);`               |
| `unique(begin, end)`             | Removes consecutive duplicates (use after sort) | `auto it = unique(v.begin(), v.end()); v.erase(it, v.end());` |
| `next_permutation(begin, end)`   | Generate next lexicographic permutation         | `next_permutation(v.begin(), v.end());`                       |

---

### **5️⃣ SMALL BUT IMPORTANT CONCEPTS**

#### **endl vs '\n'**

| `endl`                                                       | `'\n'`            |
| ------------------------------------------------------------ | ----------------- |
| Adds newline **and flushes output buffer**                   | Only adds newline |
| Slower in loops                                              | Faster            |
| ✅ Use `'\n'` in competitive coding                           |                   |
| 💡 Use `endl` when you need to **flush output immediately**. |                   |

---

#### **Pass by Reference vs Value**

```cpp
void f(int &x) { x++; }  // changes original
void f(int x) { x++; }   // copies, doesn’t change original
```

---

#### **Cache Concept (CPU Level)**

* **Cache = fast memory** near CPU that stores recently accessed data.
* Locality of Reference matters:

  * **Temporal Locality:** recently used = likely reused soon.
  * **Spatial Locality:** nearby memory addresses = likely accessed soon.
* Example: Iterating **row-wise** in 2D array is faster than **column-wise** because of cache line memory layout.

---

#### **auto Keyword**

Automatically deduces type:

```cpp
auto x = 5;       // int
auto it = v.begin(); // vector<int>::iterator
```

---

#### **Range-based for loop**

```cpp
for(auto &x : v)
    cout << x << " ";
```

---

#### **Pair & Tuple**

```cpp
pair<int, string> p = {1, "abc"};
auto [id, name] = p; // structured binding (C++17)
```

---

#### **Lambda (Anonymous Function)**

```cpp
auto add = [](int a, int b){ return a + b; };
cout << add(2,3);
```

---

#### **Const correctness**

```cpp
void f(const int &x) { }  // prevents modification
```

---

#### **Fast I/O**

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

> Speeds up input/output — **must be used before any I/O**.

---

#### **Memory Optimization**

Use `reserve()` to pre-allocate memory:

```cpp
v.reserve(1000);  // avoids multiple reallocations
```

---

Would you like me to add **a printable PDF version** of this cheatsheet (formatted cleanly with syntax highlighting, page sections, and examples)?
It’s extremely handy for quick reference offline.
