# C++ Fundamentals for DSA

A practical revision guide for the C++ features that should feel automatic before solving DSA problems.


## Table of Contents

- [1. Time Complexity and Amortized Analysis](#1-time-complexity-and-amortized-analysis)
- [2. Essential `std::string` Operations](#2-essential-stdstring-operations)
  - [Frequently Used Conversions](#frequently-used-conversions)
  - [Split a String](#split-a-string)
  - [Trim Whitespace](#trim-whitespace-from-both-ends)
  - [Lowercase and Uppercase](#convert-a-string-to-lowercase-or-uppercase)
  - [Character Classification](#check-character-type-alphabetic-digit-or-alphanumeric)
  - [Type Casting: `static_cast`](#type-casting-with-static_cast)
  - [`transform()`](#transform-apply-an-operation-to-every-element)
  - [Lambda Functions](#lambda-functions-parameters--body-)
  - [`size_t` and `string::npos`](#size_t-container-sizes-and-stringnpos)
- [3. Character Processing: Filtering and Palindromes](#3-character-processing-filtering-and-palindromes)
  - [Lowercase Conversion](#31-lowercase-conversion)
  - [Character Filtering](#32-character-filtering-js-filter-vs-c)
  - [Two-Pointer Palindrome Check](#33-two-pointer-palindrome-check)
  - [Complete Alphanumeric Palindrome Solution](#34-complete-alphanumeric-palindrome-solution)
- [4. Printing Decimal Places](#4-printing-decimal-places)
- [5. Pass by Value, Reference, and Pointer](#5-pass-by-value-reference-and-pointer)
- [6. Sorting, Comparators, and Binary Search](#6-sorting-comparators-and-binary-search)
- [7. Ordered vs. Unordered Associative Containers](#7-ordered-vs-unordered-associative-containers)
- [8. Stack, Queue, Deque, and Priority Queue](#8-stack-queue-deque-and-priority-queue)
- [9. Priority Queue and Custom Comparators](#9-priority-queue-and-custom-comparators)
- [10. Pair, Tuple, and Structured Bindings](#10-pair-tuple-and-structured-bindings)
- [11. Recursion, Integer Overflow, and `long long`](#11-recursion-integer-overflow-and-long-long)
- [12. Quick Complexity Checklist](#12-quick-complexity-checklist)
- [Final Cheat Sheet](#final-cheat-sheet)

---

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

### Type casting with `static_cast`

Use `static_cast<T>(expression)` to explicitly convert an expression to type `T` when the conversion is supported by C++.

```cpp
int a = 5, b = 2;

cout << a / b << '\\n'; // 2: integer division
cout << static_cast<double>(a) / b << '\\n'; // 2.5: floating-point division

double value = 3.9;
int whole = static_cast<int>(value); // 3: fractional part is discarded
```

Why use it?
- It makes a conversion visible and intentional to readers.
- It can prevent surprises caused by implicit conversions.
- It does not guarantee that a conversion preserves all information: converting `3.9` to `int` loses the fractional part.
- It is not a universal cast for every type; the requested conversion must be allowed by C++.

A common safe-use pattern with functions from `<cctype>` is:

```cpp
char c = s[i];
bool letter = isalpha(static_cast<unsigned char>(c));
```

The conversion to `unsigned char` avoids undefined behavior when a plain `char` has a negative value and is passed to C character-classification functions.

### `transform()`: apply an operation to every element

`std::transform` is an algorithm from `<algorithm>`. It applies an operation to each element in an input range and writes the results to a destination range.

General syntax:

```cpp
transform(first, last, destination, operation);
```

- `first`, `last`: input range `[first, last)`; `last` is excluded.
- `destination`: where results are written.
- `operation`: function or callable that receives each input element and returns its result.

Convert a string to lowercase in place:

```cpp
#include <algorithm>
#include <cctype>

string s = "HeLLo 123";

transform(s.begin(), s.end(), s.begin(),
          [](unsigned char c) {
              return static_cast<char>(tolower(c));
          });
// s == "hello 123"
```

Convert to uppercase by changing `tolower` to `toupper`:

```cpp
transform(s.begin(), s.end(), s.begin(),
          [](unsigned char c) {
              return static_cast<char>(toupper(c));
          });
// s == "HELLO 123"
```

The third argument is `s.begin()`, so each transformed character overwrites the corresponding character in the same string. The input and output ranges may overlap when used this way.

It also works with numbers:

```cpp
vector<int> nums = {1, 2, 3, 4};

transform(nums.begin(), nums.end(), nums.begin(),
          [](int x) { return x * x; });
// nums == {1, 4, 9, 16}
```

### Lambda functions: `[](parameters) { body }`

A lambda is an anonymous callable, often used to provide a short operation to algorithms such as `transform`, `sort`, and `count_if`.

```cpp
[](int x) {
    return x + 1;
}
```

Parts:
- `[]`: capture list; empty means no outside local variables are captured.
- `(int x)`: parameter list.
- `{ return x + 1; }`: body and returned result.

Example with `transform`:

```cpp
vector<int> v = {2, 3, 4};
transform(v.begin(), v.end(), v.begin(),
          [](int x) { return x + 1; });
// v == {3, 4, 5}
```

A lambda can capture a local variable when needed:

```cpp
int add = 10;
vector<int> v = {1, 2, 3};

transform(v.begin(), v.end(), v.begin(),
          [add](int x) { return x + add; });
// v == {11, 12, 13}
```

Here `[add]` captures `add` by value. `[&add]` captures it by reference. Be careful not to return or store a lambda that refers to local variables whose lifetimes have ended.

### `size_t`, container sizes, and `string::npos`

`size_t` is an unsigned integer type used to represent object sizes and container sizes. For example, `string::size()` and `vector::size()` return `size_t`.

```cpp
string s = "hello";
size_t n = s.size(); // 5
```

Because `size_t` is unsigned, it cannot represent negative values. Converting `-1` to `size_t` produces a large unsigned value, so avoid checks such as `i >= 0` in a loop where `i` is `size_t`: that condition never becomes false.

Safe reverse traversal:

```cpp
for (size_t i = s.size(); i > 0; --i) {
    cout << s[i - 1];
}
```

This also handles an empty string because the loop does not execute when `s.size() == 0`.

`string::npos` is a special `size_t` value used by string-search operations to mean “not found”.

```cpp
string s = "hello";
size_t pos = s.find("ll");

if (pos != string::npos) {
    cout << pos; // 2
}

if (s.find("xyz") == string::npos) {
    cout << "Not found";
}
```

Do not test a search result with `pos >= 0`; `size_t` is unsigned. Compare it with `string::npos` instead.


## 3. Character Processing: Filtering and Palindromes

This section connects the exact tools used in a common DSA problem: **Valid Palindrome**. The goal is to normalize the text, discard characters that should not participate, and compare the remaining characters.

### 3.1 Lowercase Conversion

**What:** Convert uppercase letters to lowercase. Digits and punctuation remain unchanged.

**Why:** A palindrome check should often ignore letter case. For example, `A` and `a` should compare equal.

**Syntax:**

```cpp
transform(s.begin(), s.end(), s.begin(), [](unsigned char ch) {
    return static_cast<char>(tolower(ch));
});
```

**Input:** `"A1,Bc!"`

**Output:** `"a1,bc!"`

**Logic, step by step:**
1. `s.begin()` points to the first character.
2. `s.end()` marks the end of the range (it is excluded).
3. The third argument, `s.begin()`, says to write each result back into the same string.
4. The lambda receives one character at a time.
5. `tolower(ch)` changes uppercase letters to lowercase; digits and punctuation are unchanged.
6. `static_cast<char>` converts the result back to the string's character type.

Use `unsigned char` as the lambda parameter when passing characters to `tolower` or other `<cctype>` functions. This avoids undefined behavior for negative plain-`char` values.

### 3.2 Character Filtering: JavaScript `.filter()` vs C++

**What:** Filtering means keeping only the elements that satisfy a condition and excluding all others.

**Why:** In a valid-palindrome problem, spaces and punctuation should not be compared. We want to keep only letters and digits.

In JavaScript, you might write:

```javascript
const filtered = [...s].filter(ch => /[a-z0-9]/i.test(ch));
```

Standard C++ `std::string` has no built-in `.filter()` method. There are two common approaches.

**Option A — build a new string (conceptually closest to JS `.filter()`):**

```cpp
string filtered;

for (unsigned char ch : s) {
    if (isalnum(ch)) {
        filtered += static_cast<char>(ch);
    }
}
```

**Input:** `"a,b!2 C"`

**Output:** `"ab2C"`

**Logic:**
1. Start with an empty string named `filtered`.
2. Visit each input character.
3. `isalnum(ch)` returns true only for an alphabetic character or a decimal digit.
4. Append the character only when the condition is true.
5. Characters like comma, exclamation mark, and spaces are never appended.

**Option B — filter in place (space-efficient for DSA):**

```cpp
int idx = 0;

for (int i = 0; i < static_cast<int>(s.size()); ++i) {
    unsigned char ch = static_cast<unsigned char>(s[i]);

    if (isalnum(ch)) {
        s[idx] = s[i];
        ++idx;
    }
}

s.resize(idx);
```

**Input:** `"a,b!2 C"`

**Output after filtering:** `"ab2C"`

**Logic with an index trace:**

| Character read | Is alphanumeric? | Action | `idx` after action |
|---|---|---|---:|
| `a` | Yes | Write `a` at `s[0]` | 1 |
| `,` | No | Skip it | 1 |
| `b` | Yes | Write `b` at `s[1]` | 2 |
| `!` | No | Skip it | 2 |
| `2` | Yes | Write `2` at `s[2]` | 3 |
| space | No | Skip it | 3 |
| `C` | Yes | Write `C` at `s[3]` | 4 |

Here, `idx` is the next write position and also the count of characters kept. After the loop, the valid characters occupy indices `0` through `idx - 1`. The original string can still contain stale characters after that point, so `s.resize(idx)` is essential: it changes the actual string length.

**Which should you use?**
- Use a new string when readability and a separate result are more important.
- Use in-place filtering when you want (O(1)) auxiliary space and can safely overwrite the original string.
- Both approaches take (O(n)) time. The new-string approach uses (O(n)) extra space; the in-place approach uses (O(1)) auxiliary space, excluding the input string.

### 3.3 Two-Pointer Palindrome Check

**What:** A palindrome reads the same from left to right and right to left.

**Why:** Comparing both ends lets us check the string without creating a reversed copy.

**Syntax:**

```cpp
bool palindrome(const string& s) {
    int l = 0;
    int r = static_cast<int>(s.size()) - 1;

    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l;
        --r;
    }

    return true;
}
```

**Input:** `"level"`

**Output:** `true`

**Counterexample:** `"hello"` → `false`, because the first and last characters (`h` and `o`) differ.

**Logic:**
1. Set `l` to the first index and `r` to the last index.
2. Compare `s[l]` and `s[r]`.
3. If they differ, the string cannot be a palindrome; return `false` immediately.
4. Otherwise move `l` one step right and `r` one step left.
5. If the pointers meet or cross, every required pair matched, so return `true`.

**Why `while (l < r)`?** Each comparison checks a pair. The middle character in an odd-length string does not need a partner, so it is not compared with itself.

**Empty-string note:** For an empty string, `s.size()` is zero. Converting `s.size()` to `int` before subtracting one gives `r = -1`; the loop is skipped and the function returns `true`. This avoids unsigned underflow from directly writing `int r = s.size() - 1`.

**Complexity:** (O(n)) time and (O(1)) auxiliary space.

### 3.4 Complete Alphanumeric Palindrome Solution

This version follows the common Valid Palindrome rule: ignore non-alphanumeric characters and compare letters case-insensitively.

```cpp
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        // Step 1: Normalize letter case.
        transform(s.begin(), s.end(), s.begin(),
                  [](unsigned char ch) {
                      return static_cast<char>(tolower(ch));
                  });

        // Step 2: Keep only letters and digits.
        int idx = 0;
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            unsigned char ch = static_cast<unsigned char>(s[i]);

            if (isalnum(ch)) {
                s[idx++] = s[i];
            }
        }
        s.resize(idx);

        // Step 3: Compare the cleaned string from both ends.
        int l = 0;
        int r = static_cast<int>(s.size()) - 1;

        while (l < r) {
            if (s[l] != s[r]) return false;
            ++l;
            --r;
        }

        return true;
    }
};
```

**Example A**

- **Input:** `"A man, a plan, a canal: Panama"`
- **After lowercase conversion:** `"a man, a plan, a canal: panama"`
- **After filtering:** `"amanaplanacanalpanama"`
- **Output:** `true`

**Example B**

- **Input:** `"race a car"`
- **After lowercase conversion:** `"race a car"`
- **After filtering:** `"raceacar"`
- **Output:** `false`

**Example C**

- **Input:** `"123, 21"`
- **After lowercase conversion:** `"123, 21"`
- **After filtering:** `"12321"`
- **Output:** `true`

**Why this order?**
1. Lowercase conversion makes comparisons case-insensitive.
2. Filtering removes characters that the problem says to ignore.
3. The two-pointer scan verifies the cleaned sequence.

**Overall complexity:** (O(n)) time. The in-place filtering uses (O(1)) auxiliary space, but the function receives `string s` by value, so the parameter itself is a copy of the caller's string.

---

## 4. Printing Decimal Places

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

## 5. Pass by Value, Reference, and Pointer

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

## 6. Sorting, Comparators, and Binary Search

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

## 7. Ordered vs. Unordered Associative Containers

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

## 8. Stack, Queue, Deque, and Priority Queue

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

## 9. Priority Queue and Custom Comparators

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

## 10. Pair, Tuple, and Structured Bindings

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

## 11. Recursion, Integer Overflow, and `long long`

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

## 12. Quick Complexity Checklist

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
