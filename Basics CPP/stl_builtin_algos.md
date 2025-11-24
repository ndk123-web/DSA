# CPP Built it Algorithms

1. Reverse

- `reverse(start_iterator, end_iterator)`
- Does not work on: forward_list (singly linked list)

```cpp
vector<int> v = {1,2,3,4,5};
reverse(v.begin(), v.end());
// 5 4 3 2 1

vector<int> v = {10,20,30,40,50};
reverse(v.begin()+1, v.begin()+4);
// reverse [20,30,40]
// final: 10, 40, 30, 20, 50

string s = "ndk";
reverse(s.begin(), s.end());
// "kdn"
```
