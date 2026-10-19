# C++ Fundamentals for DSA

A practical revision guide for the C++ features that should feel automatic before solving DSA problems.

## 1. Time Complexity and Amortized Analysis

| Complexity | Typical example |
|---|---|
| O(1) | Access `v[i]`, read `pq.top()` |
| O(log n) | Binary search, operations in `map` / `set` |
| O(n) | Scan an array |
| O(n log n) | Comparison sorting |
| O(n²) | Compare every pair with nested loops |

### What does amortized O(1) mean?

A single operation may occasionally cost O(n), but across a sequence of operations, the average cost per operation is O(1).

```cpp
vector<int> v;
for (int i = 0; i < n; ++i) {
    v.push_back(i);
}
```

Appending to a vector is **amortized O(1)**. Most appends are O(1); when capacity is exhausted, the vector may allocate a larger buffer and move/copy existing elements, making that particular append O(n).

`reserve(n)` can reduce reallocations when the expected size is known:

```cpp
vector<int> v;
v.reserve(n);
for (int i = 0; i < n; ++i) v.push_back(i);
```

## 2. Essential `std::string` Operations

Include `<string>` (or `<bits/stdc++.h>` in competitive programming).

```cpp
string s = "banana";

cout << s.size();             // 6
cout << s.empty();            // 0 (false)
cout << s[0];                 // 'b'
cout << s.front();            // 'b'
cout << s.back();             // 'a'

s.push_back('!');             // Append one character
s.pop_back();                 // Remove the last character
s += " tree";                 // Append another string

cout << s.substr(1, 3);       // "ana": start at index 1, take 3 chars

size_t pos = s.find("tree");
if (pos != string::npos) {
    cout << pos;              // Found: starting index
}

s.insert(0, "Hi ");           // Insert at index 0
s.erase(0, 3);                // Remove 3 characters from index 0

reverse(s.begin(), s.end());  // Reverse characters
sort(s.begin(), s.end());     // Sort characters
```

### Frequently used conversions

```cpp
int number = stoi("123");        // string -> int
long long big = stoll("12345678901"); // string -> long long
string text = to_string(456);    // number -> string
```

Notes:
- `size()` and `length()` are equivalent.
- `find()` returns `string::npos` when no match is found.
- `substr(start, length)` copies a substring.
- `sort(s.begin(), s.end())` sorts characters by their character values.
- `stoi` / `stoll` can throw exceptions for invalid or out-of-range input.

### Split a string

C++ `std::string` does **not** have a built-in `split()` method. Use `stringstream` for whitespace-separated tokens, or write a small helper for a specific delimiter.

Split by whitespace (consecutive spaces/tabs/newlines are treated as one separator):

```cpp
#include <sstream>

string s = "  learn   C++\nfor DSA ";
stringstream ss(s);
string word;

while (ss >> word) {
    cout << word << '\\n';
}
// learn
// C++
// for
// DSA
```

Split by a specific delimiter such as comma (this keeps empty fields between consecutive delimiters; a trailing empty field can also be handled explicitly if required):

```cpp
vector<string> split(const string& s, char delimiter) {
    vector<string> parts;
    string part;
    stringstream ss(s);

    while (getline(ss, part, delimiter)) {
        parts.push_back(part);
    }
    return parts;
}

// Example: split("red,green,blue", ',') -> {"red", "green", "blue"}
```

### Trim whitespace from both ends

C++ `std::string` does **not** have a built-in `trim()` method. This helper removes leading and trailing whitespace (spaces, tabs, newlines, etc.):

```cpp
#include <cctype>

string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() &&
           isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    size_t end = s.size();
    while (end > start &&
           isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }

    return s.substr(start, end - start);
}

// trim("  hello world  ") -> "hello world"
```

To remove leading whitespace only, use the first loop. To remove trailing whitespace only, use the second loop.

### Convert a string to lowercase or uppercase

There are no member functions named `s.lower()` or `s.upper()` in standard C++. Use `transform` with `tolower` / `toupper` from `<cctype>`.

```cpp
#include <algorithm>
#include <cctype>

string s = "HeLLo 123";

transform(s.begin(), s.end(), s.begin(),
          [](unsigned char c) { return static_cast<char>(tolower(c)); });
// s == "hello 123"

transform(s.begin(), s.end(), s.begin(),
          [](unsigned char c) { return static_cast<char>(toupper(c)); });
// s == "HELLO 123"
```

The `unsigned char` conversion avoids undefined behavior for negative `char` values when calling the C character-classification functions. These functions are intended for single-byte characters; Unicode case conversion needs a Unicode-aware library.

### Check character type: alphabetic, digit, or alphanumeric

Use functions from `<cctype>`. Pass the character as `unsigned char` to avoid undefined behavior for negative `char` values.

```cpp
#include <cctype>

char c = 'A';

bool isLetter = isalpha(static_cast<unsigned char>(c)); // true
bool isDigit  = isdigit(static_cast<unsigned char>(c));  // false
bool isAlphaNum = isalnum(static_cast<unsigned char>(c)); // true
bool isSpace = isspace(static_cast<unsigned char>(' '));  // true
bool isLower = islower(static_cast<unsigned char>(c)); // false
bool isUpper = isupper(static_cast<unsigned char>(c)); // true
```

| Function | Returns true when the character is... |
|---|---|
| `isalpha(c)` | An alphabetic letter |
| `isdigit(c)` | A decimal digit, `0`–`9` |
| `isalnum(c)` | A letter or a digit |
| `isspace(c)` | Whitespace, such as space, tab, or newline |
| `islower(c)` | A lowercase letter |
| `isupper(c)` | An uppercase letter |
| `ispunct(c)` | A punctuation character |
| `isxdigit(c)` | A hexadecimal digit, `0`–`9`, `a`–`f`, or `A`–`F` |

Remember: these are character functions, so call them with one character, for example `isalnum(s[i])`. In locale-dependent C++ character classification, letters beyond basic ASCII may depend on the active locale; these functions are not full Unicode character classifiers.

## 3. Printing Decimal Places

Use `fixed` with `setprecision` from `<iomanip>` to specify the number of digits after the decimal point.

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double x = 3.1415926535;

    cout << setprecision(4) << x << '\\n';       // 3.142 (4 significant digits)
    cout << fixed << setprecision(4) << x << '\\n'; // 3.1416 (4 digits after decimal)
}
```

- `setprecision(4)` alone sets **four significant digits** for the default floating-point format.
- `fixed << setprecision(4)` displays **four digits after the decimal point**.
- Formatting changes how a value is printed; it does not change the stored value.

## 4. Pass by Value, Reference, and Pointer

### Pass by value: a copy is passed

```cpp
void change(int x) {
    x = 100;
}

int main() {
    int a = 10;
    change(a);
    cout << a; // 10: original is unchanged
}
```

### Pass by reference: an alias to the original variable

```cpp
void change(int& x) {
    x = 100;
}

int main() {
    int a = 10;
    change(a);
    cout << a; // 100
}
```

Use `const T&` for large read-only objects to avoid copying while preventing modification:

```cpp
void printVector(const vector<int>& v) {
    for (int x : v) cout << x << ' ';
}
```

### Pass by pointer: explicitly pass an address

```cpp
void change(int* ptr) {
    if (ptr != nullptr) {
        *ptr = 100; // Dereference: access the value at the address
    }
}

int main() {
    int a = 10;
    change(&a); // &a means the address of a
    cout << a;  // 100
}
```

Remember:
- `&a` in an expression obtains the address of `a`.
- `int* ptr` declares a pointer to an integer.
- `*ptr` dereferences the pointer.
- `int& ref = a` declares a reference to `a`; use `ref` directly, without `*`.
- A pointer can be `nullptr`; a reference should refer to a valid object.

## 5. Sorting, Comparators, and Binary Search

### Sorting

```cpp
vector<int> v = {4, 1, 3, 2};

sort(v.begin(), v.end());                  // 1, 2, 3, 4
sort(v.begin(), v.end(), greater<int>());  // 4, 3, 2, 1
```

Custom comparator for pairs, sorted by second value ascending:

```cpp
vector<pair<int, int>> v = {{1, 30}, {2, 10}, {3, 20}};

sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;
});
```

A comparator should define a **strict weak ordering**. Do not use `<=` or `>=` as the comparator condition.

### `lower_bound` and `upper_bound`

The input range must already be sorted.

```cpp
vector<int> v = {1, 2, 2, 2, 5, 8};

auto lo = lower_bound(v.begin(), v.end(), 2); // First element >= 2
auto hi = upper_bound(v.begin(), v.end(), 2); // First element > 2

cout << (lo - v.begin()); // 1
cout << (hi - v.begin()); // 4
cout << (hi - lo);        // 3 occurrences of 2
```

Each binary-search operation takes O(log n) comparisons on a vector's random-access iterators.

## 6. Ordered vs. Unordered Associative Containers

| Container | Ordering | Typical lookup | Use when |
|---|---|---:|---|
| `map<K,V>` | Keys sorted | O(log n) | Need sorted keys or ordered traversal |
| `set<T>` | Values sorted | O(log n) | Need unique sorted values |
| `unordered_map<K,V>` | No sorted order | O(1) average, O(n) worst case | Need fast key lookup |
| `unordered_set<T>` | No sorted order | O(1) average, O(n) worst case | Need fast membership checks |

```cpp
unordered_map<string, int> frequency;
frequency["apple"]++;

unordered_set<int> seen;
seen.insert(10);
if (seen.count(10)) cout << "Found";
```

### Custom types in unordered containers

Hash-based containers need a hash function and an equality comparison for the key type. Standard C++ does not provide a portable built-in `std::hash<pair<int,int>>` in C++17, so provide one yourself when using a pair as an unordered key.

```cpp
using P = pair<int, int>;

struct PairHash {
    size_t operator()(const P& p) const {
        size_t h1 = hash<int>{}(p.first);
        size_t h2 = hash<int>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

int main() {
    unordered_set<P, PairHash> points;
    points.insert({1, 2});
    points.insert({3, 4});
    points.insert({1, 2});
    cout << points.size(); // 2
}
```

For a custom struct, define equality and a compatible hash:

```cpp
struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        size_t h1 = hash<int>{}(p.x);
        size_t h2 = hash<int>{}(p.y);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

unordered_set<Point, PointHash> points;
```

Hash collisions are allowed: unequal keys may have the same hash. Equality is used to distinguish keys. Equal keys must always produce equal hashes.

## 7. Stack, Queue, Deque, and Priority Queue

```cpp
stack<int> st; // LIFO: last in, first out
st.push(1);
st.top();
st.pop();

queue<int> q; // FIFO: first in, first out
q.push(1);
q.front();
q.pop();

deque<int> dq; // Efficient insertion/removal at both ends
dq.push_front(1);
dq.push_back(2);
dq.pop_front();
dq.pop_back();
```

Typical complexities:
- `stack`: `push`, `top`, `pop` are O(1).
- `queue`: `push`, `front`, `pop` are O(1).
- `deque`: insertion/removal at either end is O(1).
- Always check `empty()` before accessing or removing from a possibly empty container.

## 8. Priority Queue and Custom Comparators

A default `priority_queue` is a **max-heap**: the largest element is at the top.

```cpp
priority_queue<int> maxHeap;
maxHeap.push(10);
maxHeap.push(30);
maxHeap.push(20);
cout << maxHeap.top(); // 30
```

A min-heap:

```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;
minHeap.push(10);
minHeap.push(30);
minHeap.push(20);
cout << minHeap.top(); // 10
```

Custom struct: process the task with the smallest priority number first.

```cpp
struct Task {
    string name;
    int priority;
};

struct TaskCompare {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority > b.priority;
    }
};

int main() {
    priority_queue<Task, vector<Task>, TaskCompare> pq;
    pq.push({"Email", 3});
    pq.push({"Bug fix", 1});
    pq.push({"Meeting", 2});

    while (!pq.empty()) {
        cout << pq.top().name << ' ' << pq.top().priority << '\\n';
        pq.pop();
    }
    // Bug fix 1, Meeting 2, Email 3
}
```

For a priority queue, if `Compare(a, b)` returns true, `a` is ordered behind `b`. Thus `a.priority > b.priority` makes the smaller priority number appear first.

Tie-break by name:

```cpp
struct TaskCompare {
    bool operator()(const Task& a, const Task& b) const {
        if (a.priority != b.priority)
            return a.priority > b.priority; // Smaller number first
        return a.name > b.name;             // Alphabetically smaller first
    }
};
```

Comparator rules:
- Default `priority_queue<T>`: max-heap.
- `priority_queue<T, vector<T>, greater<T>>`: min-heap.
- Custom comparator: define the desired ordering explicitly.
- `top()` reads the element; `pop()` removes it. `pop()` does not return the element.
- `push()` / `pop()` are O(log n); `top()` is O(1).

## 9. Pair, Tuple, and Structured Bindings

```cpp
pair<int, string> p = {1, "Alice"};
cout << p.first << ' ' << p.second;

tuple<int, string, double> t = {1, "Alice", 9.5};
cout << get<0>(t) << ' ' << get<1>(t);

auto [id, name, score] = t; // C++17 structured binding
```

Use structured bindings to make code easier to read. For map iteration, avoid unnecessary copies:

```cpp
unordered_map<string, int> freq = {{"apple", 2}, {"pear", 1}};

for (const auto& [word, count] : freq) {
    cout << word << ": " << count << '\\n';
}
```

## 10. Recursion, Integer Overflow, and `long long`

Every recursive function should have a base case and make progress toward it.

```cpp
long long factorial(int n) {
    if (n <= 1) return 1;
    return 1LL * n * factorial(n - 1);
}
```

Notes:
- Recursion uses call-stack space; a deep recursion can cause stack overflow.
- `long long` has a larger range than `int`, but it can still overflow.
- Use `1LL * a * b` when the multiplication must happen in 64-bit integer arithmetic; assigning an already-overflowed `int` result to `long long` does not fix it.
- For triangular numbers: `1LL * n * (n + 1) / 2`.

## 11. Quick Complexity Checklist

Before submitting a solution, ask:
1. How many times does each loop run?
2. Are loops nested, or do they run sequentially?
3. Is a sorting step present? Usually O(n log n).
4. Is a hash operation average O(1), with a possible O(n) worst case?
5. Does recursion branch? Estimate the number of calls and recursion depth.
6. Is integer overflow possible for values, products, or sums?
7. Are the container operations appropriate for the required ordering?

## Final Cheat Sheet

- Need sorted keys or values: `map` / `set`.
- Need average fast lookup: `unordered_map` / `unordered_set`.
- Need smallest element repeatedly: min-heap.
- Need largest element repeatedly: default max-heap.
- Need a large read-only parameter without copying: `const T&`.
- Need to modify the caller's variable: reference or pointer, depending on the API.
- Need fixed decimal digits: `fixed << setprecision(k)`.
- Need first value >= x: `lower_bound`; first value > x: `upper_bound`.
- Need substring: `substr`; search substring: `find`; check against `string::npos`.
- Need split: use `stringstream` or `getline` with a delimiter; `std::string` has no built-in `split()`.
- Need trim: write a helper using `isspace`; `std::string` has no built-in `trim()`.
- Need change case: `transform` with `tolower` or `toupper`.
- Need classify a character: `isalpha`, `isdigit`, `isalnum`, `isspace`, `islower`, or `isupper`.
