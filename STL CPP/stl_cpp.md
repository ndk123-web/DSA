### 1. STL Contains

- Algorithms
- Containers ( vector , list , Deque , Stack , Queue , Priority Queue , Set , Multi Set , Unorder Set , Map , Multi Map , Unorder Map
- Iterators

### 2. Pairs

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    
    // 1. pair 
    pair <int, int> p = {1,2};
    cout << p.first << " " << p.second;
    // 1 2
    
    cout << endl;
    
    pair <int , pair <int,int>> hyb = {1,{2,3}};
    cout << hyb.first << " " << hyb.second.first << " " << hyb.second.second;
    // 1 2 3
    
    cout << endl;
    
    pair <int , int> arr[] = { {1,2} , {3,4} };
    cout << arr[0].first << endl;
    // 1

    pair <string , int> map;
    map = {"ndk",1};
    
    cout << map.first << " " << map.second << endl;
    // ndk 1

    return 0;
}
```

### 3. Vectors ( Basics of Vector )

- Dynamic in Nature

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    
    // 1 Simple pushing methods
    vector<int> v;
    v.push_back(1);   // slower for big objects
    v.emplace_back(2); // faster for big objects

    for(auto i = 0 ; i < v.size(); i++){
        cout << v[i] << endl;
    }
    
    // 2 -> pair collboration 🤣
    vector<pair<int,int>> arr;
    arr.push_back({1,2});
    cout << arr[0].first << " " << arr[0].second << endl;
    
    // 3 -> 5 location of filled value 100
    vector<int> v2(5,100);
    for(auto i = 0 ; i < v2.size(); i++){
        cout << v2[i] << " ";
    }
    // {100,100,100,100,100}
    cout << endl;
    
    // 4 -> default value is 0
    vector <int> v3(5);
    // {0,0,0,0,0}
    
    // 5 -> Copy 
    vector <int> v4(5,20);
    vector <int> v5(v4);
    // v5 = v4

    return 0;
}
```

### 4. Vectors ( Iterators )

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    
   vector <int> v;
   v.push_back(1);
   v.push_back(2);
   v.push_back(3);
   
   // 1 -> This is Standard way 
   vector<int>::iterator it = v.begin(); // gives memory of first element
   for(vector<int>::iterator i = it ; i < v.end(); i++){
       cout <<  *i << " ";
   }
   cout << endl;
   
   // 2-> modern way (auto keyword) (here i is iterator)
   for (auto i =0 ; i < v.size(); i++){
       cout << v[i] << " ";
   }
   cout << endl;
   
   // 3-> for each loop (here i is int ) 
   for (auto i : v){
       cout << i << " ";
   }
   
   // 4-> erase
   v.erase(v.begin()+1); // remove 2nd element
   v.erase(v.begin()+2, v.begin()+4); // erase (2,3) location element
   
   // 5-> insert at some location 
   v.insert(v.begin() , 10); // insert 10 at beginning
   v.insert(v.begin()+1, 2, 10); // insert {10,10} from location 2nd
   
   // 6-> pop_back means pop last element
   v.pop_back();
   
   // 7-> swap 2 vectors
   vector <int> v1 = {10,20};
   vector <int> v2 = {30,40};
   v1.swap(v2); // swaps v1 <-> v2
   
   // 8-> clear all elements
   v.clear();
   
   // 9-> to check whether vector is empty
   v.empty() ? cout << "Empty" : cout << "Not Empty";
   
    return 0;
}
```

### 5. List

- Internal Implementation in “**Doubly LinkedList**”

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int main() {

    list<int> ls;
    
    ls.push_back(1);
    ls.emplace_back(2);
    
    ls.push_front(10);
    ls.emplace_front(20);
    
    // rest functions are same rend , rbegin , begin , end , swap , clear, ...
    
    return 0;
}
```

### 6. Deque

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

using namespace std;

int main() {

    deque<int> ls;
    
    ls.push_back(1);
    ls.emplace_back(2);
    
    ls.push_front(10);
    ls.emplace_front(20);
    
    // rest functions are same rend , rbegin , begin , end , swap , clear, ...
    
    return 0;
}
```

### Difference Between Vector , List , Deque

| Container | Internally | Random Access | Insert/Delete Middle | Insert/Delete Ends |
| --- | --- | --- | --- | --- |
| **vector** | Dynamic array | ✅ O(1) | ❌ O(n) | End = O(1), Front = O(n) |
| **list** | Doubly linked list | ❌ O(n) | ✅ O(1) (if iterator known) | ✅ O(1) (both ends) |
| **deque** | Block-based dynamic array | ✅ O(1) | ❌ O(n) | ✅ O(1) (both ends) |
- `vector` = best for **random access + end insert**
- `list` = best for **frequent insert/delete in middle**
- `deque` = best for **front & back operations + random access**

### 7. Stack

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>

using namespace std;

int main() {
    
    stack<int> st;
    
    // push 
    st.push(1);
    st.push(2);
    st.push(3);
    st.emplace(4); // faster for big objects
    
    // pop 
    st.pop();
    
    // get top element
    int last = st.top();
    
    // get size
    int size = st.size();
    
    // is Emtpy 
    int isEmpty = st.empty();
    
    return 0;
}
```

### 8. Queue

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>

using namespace std;

int main() {
    
    queue<int> q;
    
    // push 
    q.push(1);
    q.push(2);
    q.push(3);
    q.emplace(4); // faster for big objects
    
    q.back() = q.back() + 5; 
    
    // pop 
    q.pop();
    
    // get top element
    int front_element = q.front();
    
    // get size
    int size = q.size();
    
    // is Emtpy 
    int isEmpty = q.empty();
    
    // swap
    queue <int> q1;
    queue <int> q2;
    q1.swap(q2);
    
    return 0;
}
```

### 9. Priority Queue

- Inside it uses **Tree**
- Push , Pop → Log(N)
- Top → O(1)

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    
    // default maximum heap
    priority_queue<int> pq;
    
    pq.push(2);   // {2}
    pq.push(10);  // {10,2}
    pq.push(8);   // {10,8,2}
    pq.emplace(100);   // {100,10,8,2}
    
    pq.top(); // 10
    
    pq.pop(); // pops 10
    
    for (auto i = 0 ; i < pq.size(); i++){
        cout << pq[i] << " ";
    }
    
    // minimum heap syntax
    priority_queue<int , vector<int>, greater<int>> pq;
    pq.push(2);   // {2}
    pq.push(10);  // {2,10}
    pq.push(8);   // {2,8,10}
    pq.emplace(100);   // {2,8,10,100}
    
    pq.top() // 2 
    
    pq.pop() // pops 2
    
    return 0;
}
```

### 10. Set

- Stores In Sorted Order
- No Duplication Allowed
- Internally Tree is Maintained

```cpp
#include <iostream>
#include <set>

using namespace std;

int main() {
    
    set<int> s;
    
    s.insert(1);
    s.emplace(2);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    
    //1-> returns iterator which points to the value 3
    auto it = s.find(3); // it presents 
    auto it = s.find(10); // if not then after end + 1 iterator returns
    
    cout << *it << endl;
    
    //2-> erase
    s.erase(3);
    
    //3-> if element is in set or not
    int ans = s.count(1) // if 1 is in s the 1 else 0 
    return 0;
}
```

### 11. Multiset

- Sorted But Not Unique

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<int> ms;
    
    ms.insert(1);
    ms.emplace(2);
    ms.insert(2);
    ms.insert(3);
    ms.insert(4);
    
    // Erase all 2s
    ms.erase(2);
    
    // Insert again for demo
    ms.insert(2);
    ms.insert(2);

    // Find 2 and erase only one occurrence
    auto it = ms.find(2);      // iterator to first "2"
    if (it != ms.end()) {
        ms.erase(it, next(it)); // erase just one 2
    }

    // Print elements
    for (int x : ms) cout << x << " ";
    cout << endl;
    
    // Count how many times "1" appears
    int ans = ms.count(1);
    cout << "1 occurs " << ans << " time(s)" << endl;

    return 0;
}

```

### 12. Unorder Set

- Internally Hash Buckets Used
- Unique But Not Sorted ( Randomness )
- Average Complexity For All Operations → O(1)

```cpp
unordered_set<int> us = {10, 11, 20};

Hash function (mod 5):
10 % 5 = 0 → bucket 0
11 % 5 = 1 → bucket 1
20 % 5 = 0 → bucket 0 (collision)

Buckets:
0 → [10, 20]   (linked list)
1 → [11]
2 → [ ]
3 → [ ]
4 → [ ]

us.find(10) → bucket 0 → Hash fn 10 % 5 = 0 → bucket 0 -> found ✅
us.find(20) → bucket 0 → Hash fn 20 % 5 = 0 → bucket 0 → found ✅
us.find(11) → bucket 1 → Hash fn 11 % 5 = 1 -> bucket 1 -> found ✅

WORST CASE ( All are in 1 buckets ) -> O ( N )
0 → [10, 20, 30]   (linked list)
1 → []
2 → [ ]
3 → [ ]
4 → [ ]
```

```cpp
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> us;

    us.insert(10); // hash(10) -> suppose bucket 2
    us.insert(20); // hash(20) -> suppose bucket 7
    us.insert(30); // hash(30) -> suppose bucket 4

    // Find operation
    if (us.find(20) != us.end()) {
        cout << "20 found" << endl;
    }
}

```

### 13. Map

- Map Stored Unique Keys in Sorted Order

| Feature | pair | map |
| --- | --- | --- |
| Stores | 1 key-value pair | Multiple key-value pairs |
| Access | `.first` and `.second` | By key (`mp[key]`) |
| Sorted | N/A | Yes (sorted by key) |
| Unique key | N/A | Yes (no duplicate keys) |
| Container? | No | Yes |

```cpp
#include <iostream>
#include <map>

using namespace std;

int main() {
    
    map<int,int> mp;
    
    // 1-> insert With Key 
    mp[1] = 1;
    mp[2] = 2;
    
    // 2-> Insert and emplace
    mp.insert({3,3});  // insert pair
    mp.emplace(4,4);   // construct pair directly
   
    for (auto it: mp){
        cout << it.first << " " << it.second << endl;
    }
    return 0;
}
```

### 14. Algorithms

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for sort, find, count, max_element, etc.
#include <numeric>   // for accumulate
using namespace std;

int main() {
    // -------------------------
    // 1️⃣ Sorting
    // -------------------------
    vector<int> v1 = {4, 1, 3, 2};

    // Ascending sort
    sort(v1.begin(), v1.end());
    cout << "Ascending: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // Descending sort
    sort(v1.rbegin(), v1.rend());
    cout << "Descending: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // -------------------------
    // 2️⃣ Search
    // -------------------------
    auto it = find(v1.begin(), v1.end(), 3); // linear search
    if (it != v1.end()) 
        cout << "Found " << *it << endl;

    // -------------------------
    // 3️⃣ Counting occurrences
    // -------------------------
    vector<int> v2 = {1, 2, 2, 3, 2, 4};
    int cnt = count(v2.begin(), v2.end(), 2); // counts how many times 2 appears
    cout << "Count of 2: " << cnt << endl;

    // -------------------------
    // 4️⃣ Min and Max
    // -------------------------
    int a = 5, b = 10;
    cout << "Max(a,b): " << max(a,b) << endl;
    cout << "Min(a,b): " << min(a,b) << endl;

    vector<int> v3 = {4, 1, 9, 3};
    cout << "Max element in v3: " << *max_element(v3.begin(), v3.end()) << endl;
    cout << "Min element in v3: " << *min_element(v3.begin(), v3.end()) << endl;

    // -------------------------
    // 5️⃣ Accumulate / Sum
    // -------------------------
    vector<int> v4 = {1, 2, 3, 4};
    int sum = accumulate(v4.begin(), v4.end(), 0); // sum = 10
    cout << "Sum of v4: " << sum << endl;

    // -------------------------
    // 6️⃣ Any_of / All_of / None_of
    // -------------------------
    vector<int> v5 = {1, 2, 3, 4};
    bool anyEven = any_of(v5.begin(), v5.end(), [](int x){ return x % 2 == 0; });
    bool allPositive = all_of(v5.begin(), v5.end(), [](int x){ return x > 0; });
    bool noneNegative = none_of(v5.begin(), v5.end(), [](int x){ return x < 0; });

    cout << "Any even? " << anyEven << endl;
    cout << "All positive? " << allPositive << endl;
    cout << "None negative? " << noneNegative << endl;

    // -------------------------
    // 7️⃣ Remove elements
    // -------------------------`
    vector<int> v6 = {1, 2, 2, 3, 2, 4};

    // Remove all 2s (returns iterator to new end)
    v6.erase(remove(v6.begin(), v6.end(), 2), v6.end());
    cout << "After removing 2s: ";
    for(int x : v6) cout << x << " ";
    cout << endl;

    // -------------------------
    // 8️⃣ Remove duplicates (needs sorted vector)
    // -------------------------
    vector<int> v7 = {1, 2, 2, 3, 2, 4};
    sort(v7.begin(), v7.end());                  // Sort first
    v7.erase(unique(v7.begin(), v7.end()), v7.end()); // Remove duplicates
    cout << "After removing duplicates: ";
    for(int x : v7) cout << x << " ";
    cout << endl;

    return 0;
}

```