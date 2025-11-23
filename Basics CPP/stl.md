# STL

---

Total :
vector , list , Deque , Stack , Queue , Priority Queue , Set , Multi Set , Unorder Set , Map , Multi Map , Unorder Map

---

---

✔ Vector → Reallocates = ❌ Unsafe
✔ Deque → Sometimes reallocate = ❌ Unsafe
✔ List → Never reallocate = ✔ Safe
✔ Map / Set (Tree) → Never reallocate = ✔ Safe
✔ Unordered (Hash) → Rehash = ❌ Unsafe

---

## Iterators

- Iterator means pointing to the some location (pointer)

```cpp
vector<int> v = {1,2,3};

// it means 1's location is in "it"
vector<int>::iterator it = v.begin();

// dereference to get the actual data inside that address
std::cout << *it
```

### Types of Iterators

```cpp
auto it = v.begin();   // first element
auto it2 = v.end();    // LAST element ke baad

auto it = v.rbegin(); // last element
auto it2 = v.rend();  // first se pehle

vector<int>::const_iterator it = v.begin();
*it = 50; // error

set<int> s = {10,20,30};
auto it = s.begin();
cout << *it;      // 10

map<int,int> mp;
mp[1] = 100;
mp[2] = 200;

auto it = mp.begin();
cout << it->first << " " << it->second;
```

## Iterators in Deep

- Types of Iterators
  | Container | Iterator Type |
  | ------------------- | ---------------------- |
  | vector | random access iterator |
  | deque | random access iterator |
  | list | bidirectional iterator |
  | map / set | bidirectional iterator |
  | unordered_map / set | forward iterator |

  | Iterator Type | Moves             | Random Access |
  | ------------- | ----------------- | ------------- |
  | Random access | it+1, it+5, it[i] | YES           |
  | Bidirectional | ++it, --it        | NO            |
  | Forward       | ++it only         | NO            |

## 1 Pair

- Normal Pair

```cpp
#include <iostream>

int main() {

    std::pair<int,int> p = {11,22};

    p.first = 10;
    p.second = 20;

    std::cout << p.first << " " << p.second;

    return 0;
}
```

- Array Pair

```cpp
#include <iostream>

int main() {

    std::pair<int,int> p[] = { {1,2} , {3,4} };

    p[0].first = 10;
    p[0].second = 20;

    std::cout << p[0].first << " " << p[0].second;

    return 0;
}
```

## 2 Vector

- Dynamic Array
- Resizing → memory changed → old iterator invalid

```cpp
auto it = v.begin();

// because push_back may trigger expand size and because of that memory might be shifted for the vector v
v.push_back(100); // resizing happened

cout << *it; // ❌ it is invalid now
```

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<int> v;

    v.push_back(1);

    for (auto i : v) {
        cout << i;
    }

    return 0;
}
```

## 3 List

- Doubly LinkeldList
- `No Random Access`
- `Doesn't Reallocate On Resize like Vector`

```bash
[ prev | data | next ]
```

| Feature               | vector          | list      |
| --------------------- | --------------- | --------- |
| Memory                | contiguous      | scattered |
| Random access         | ✔               | ❌        |
| Insert/delete middle  | ❌ O(n)         | ✔ O(1)    |
| push_back             | ✔               | ✔         |
| push_front            | slow            | ✔         |
| Iterator invalidation | break on resize | SAFE      |
| Sorting               | fast            | slow      |

- List recommended only when:
  - LRU Cache implementation
  - Doubly linked list problems
  - Big objects moving avoid karna
  - Very frequent insert/delete in between

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <list>

using namespace std;

int main() {

    list<int> ls;

    ls.push_back(20);
    ls.push_front(10);

    auto it = ls.begin();
    advance(it,1); // it is now in location 1 which is 20

    ls.insert(it,100); // in location 1 put 100

    for (auto i : ls) {
        cout << i << " ";
    }

    cout << "\n";

    ls.erase(it); // erase location 1 which it was pointing to the 20 but now 100 is in 1th location but it was before the insert so that 20 will remove

    for (auto i : ls) {
        cout << i << " ";
    }

    return 0;
}
```

## 4 Deque

- It internally uses blocks , not like vector which is uses contiguous memory
- When Resizing Happens then vector iterators will be invalid because vector get shifted so old iterators get invalid
- In Deque it just add new `Block` and because of that old data will be persist in memory unlike vectors who shifts entire vector memory

- ✔ front se push = O(1)
- ✔ back se push = O(1)
- ✔ random access = O(1)

- When To Use:
  - ✔ Sliding Window Maximum
  - ✔ Monotonic Queue
  - ✔ BFS (when you need both ends)
  - ✔ 0-1 BFS
  - ✔ Tasks needing push/pop front + random access

| Feature       | Vector     | Deque  | List      |
| ------------- | ---------- | ------ | --------- |
| Random access | ✔          | ✔      | ❌        |
| push_back     | ✔          | ✔      | ✔         |
| push_front    | slow       | ✔      | ✔         |
| Middle insert | slow       | slow   | ✔         |
| Memory        | contiguous | blocks | scattered |

| Operation     | deque | vector         |
| ------------- | ----- | -------------- |
| push_back     | O(1)  | O(1) amortized |
| push_front    | O(1)  | O(N)           |
| pop_back      | O(1)  | O(1)           |
| pop_front     | O(1)  | O(N)           |
| random access | O(1)  | O(1)           |

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <deque>

using namespace std;

int main() {

    deque<int> dq;

    dq.push_back(10);
    dq.push_front(20);

    // can access random variable
    cout << dq[0] << "\n";

    dq.pop_front();
    dq.pop_back();

    return 0;
}
```

## 5 Stack

- Simple LIFO (Last In First Out)

- Operations:

  - push(x)
  - pop()
  - top()
  - empty()
  - size()

- `It Internally Uses Deque because of fast push/pop both ends`
- `No Shifting Like Vector`

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <stack>

using namespace std;

int main() {

    stack<int> st;

    st.push(10);    // push 10
    st.push(20);    // push 20

    int t = st.top();   // get top element also can modify
    cout << "Top: " << t << "\n";

    st.pop(); // pop top element

    return 0;
}
```

## 6 Queue

2. WHAT is queue?

- Operations:

  - push(x) → end me add
  - pop() → front se remove
  - front() → first element
  - back() → last element
  - empty()
  - size()

- `It also Uses Internally Deque for fast push/pop operations`

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <queue>

using namespace std;

int main() {

    queue<int> q;

    q.push(10);
    q.push(20);

    cout << "Front: " << q.front() << "\n";
    cout << "Back: " << q.back() << "\n";

    q.pop(); // remove front element

    return 0;
}
```

## 7 Priority Queue (Min Heap / Max Heap / Custom Heap)

- It uses Vector and Conceptual Binary Tree
- We Get the Binary tree data using Maths Formulas

```bash
parent = (i-1)/2
left child = 2*i + 1
right child = 2*i + 2
```

- Always gives `Highest Priority Element First`
- In CPP By Default MAX HEAP , means `top() is always Greater Element`
  | Operation | Complexity |
  | --------- | ---------- |
  | push() | O(log n) |
  | pop() | O(log n) |
  | top() | O(1) |
  | empty() | O(1) |
  | size() | O(1) |

- It always Compares Child and Parent
- Child is a(first element) and Parent is b(second element) in comparator

- `true` means send child down
- `false` means send parent down and child become parent

```bash
1️⃣ return a > b
If child > parent → TRUE → child down
meaning big element niche → small top
→ MIN HEAP

2️⃣ return a < b
If child < parent → TRUE → child down
meaning small element niche → big top
→ MAX HEAP
```

## 8 Set

- C++ set = balanced BST (red-black tree).
- All Operation -> O(Log N)

- sorted (always increasing order)
- unique (no duplicate)
- internally tree
- `No random access`
- iterators are stable

| Operation         | Complexity |
| ----------------- | ---------- |
| insert            | log(N)     |
| erase             | log(N)     |
| find              | log(N)     |
| lower_bound       | log(N)     |
| upper_bound       | log(N)     |
| iterate whole set | O(N)       |

- lower_bound(x) (Here only equal is extra with Greater)
  → first element >= x

- upper_bound(x) (Here must be Greater)
  → first element > x

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <set>

using namespace std;

int main() {

    set<int> s;

    s.insert(10);
    s.insert(20);
    s.insert(30);

    auto it = s.find(110);
    if (it == s.end()) {
        cout << "Not Found Element 20";
        return 0;
    }
    cout << *it;

    // erase value 10
    s.erase(10);

    // erase iterator
    s.erase(it);

    return 0;
}
```

## 9 MultiSet

- Same as Set But (Duplicates Allowed)
- lower_bound / upper_bound also work same as Set

```cpp
multiset<int> ms = {10,10,20,30};

ms.erase(5) // removes all occurences of 5

auto it = ms.find(10); // first 10
ms.erase(it);          // removes ONLY that one

// ms = {10,20,30}
```

## 10 Unordered Set

- Its Build By using Hashing and Buckets
- Each Bucket is Linked List
- Features
  ✔ Hash table
  ✔ Unique elements
  ✔ Not sorted
  ✔ Average O(1)
  ✔ Worst O(N) (rare)

| Operation | Average | Worst |
| --------- | ------- | ----- |
| insert    | O(1)    | O(N)  |
| find      | O(1)    | O(N)  |
| count     | O(1)    | O(N)  |
| erase     | O(1)    | O(N)  |

```cpp
unordered_set<int> us;

us.insert(10);
us.insert(20);
us.insert(20); // ignored
us.insert(30);

cout << us.count(20); // 1
us.erase(10);
```

## 11 Map

- C++ map = balanced BST (red-black tree).
- Its Tree Inside Like Set but In map this tree is for the Key

- Properties:
  - keys unique
  - sorted by key
  - O(log N) insert/find/erase
  - values stored with keys
  - supports iterators
  - supports lower_bound, upper_bound

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <map>

using namespace std;

int main() {

    map<int,int> mp;

    mp[2] = 200;
    mp[3] = 300;
    mp[1] = 100;


    for (auto i : mp){
        cout << i.first << " " << i.second << "\n";
    }

    return 0;
}
```

### 12 MultiMap (Same as Map But Duplicate Keys)

- ✔ Exactly like map
- ✔ BUT keys can be duplicated
- ✔ Still sorted
- ✔ Still uses red-black tree

| Operation | Time |
| --------- | ---- |
| insert    | logN |
| find      | logN |
| erase     | logN |
| iterate   | O(N) |

```cpp

```

## Unordered Map

- unordered_map hashing use karta → O(1) average

- ✔ Hash table
- ✔ Key–value pairs
- ✔ Unique keys
- ✔ NOT sorted
- ✔ Average O(1) ops
- ✔ Worst case O(N) (rare)
  | Feature | unordered_map | map |
  | -------------- | ------------- | -------------- |
  | Speed | O(1) avg | O(log N) |
  | Order | random | sorted |
  | Internal | hash table | red-black tree |
  | lower_bound | ❌ | ✔ |
  | duplicate keys | ❌ | ❌ |
  | best for | fast lookup | ordered lookup |

```cpp
unordered_map<string,int> mp;

mp["ndk"] = 1;
mp["coder"] = 2;
mp["ndk"] += 5;

for(auto &p : mp){
    cout << p.first << " " << p.second << endl;
}
```

## Unordered MultiMap

- Same as unordered_map BUT :
  ✔ Duplicate keys allowed
  ✔ Internally hash table
  ✔ No order
  ✔ fast operations O(1) avg

```cpp
unordered_multimap<int,string> umm;

umm.insert({10, "apple"});
umm.insert({10, "banana"});
umm.insert({20, "carrot"});

// l point to first 10 "apple"
// r point to last 10's aafter object which is 20 "carrot"
auto [l, r] = umm.equal_range(10);

for(auto it = l; it != r; it++){
    cout << it->first << " -> " << it->second << "\n";
}
```
