# STL

---

Total :
vector , list , Deque , Stack , Queue , Priority Queue , Set , Multi Set , Unorder Set , Map , Multi Map , Unorder Map

---

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