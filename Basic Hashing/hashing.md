### Time Complexity Of Map
- `It Sorted Keys`
- `Log N` for   Worst , Best , Average Case 
- `In Map Key Would be anything , like pair , int , char and all` 

### Time Complexity of Unorder Map
- `It doesn't Sort`
- `O(1)` for Best, Average Case (Uses Buckets)
- `O(N)` for Worst Case (All contents are in One Bucket) and (internal collisions)
- `In UnorderMap key would not be pair , it only store one type` 
```bash
Buckets:  0   1   2   3   4
           |   |   |   |   |
           A   -   -   B   C   ← Good distribution ✅
```
```bash
Buckets:  0   1   2   3   4
           |   |   |   |   |
           A→B→C→D→E        ← All collided 😬(all in bucket 0 which is collisions)
```

### Hashing Methods
1. Division Method
2. Folding Method
3. Mid Square Method

### 1 Basic Hash Code for( int array )
- You Can't declare array size `10^6` inside `main`, above this it will throw error (Segmentation Fault)
- In Global Declration it might go till `10^7`
```cpp 
#include <iostream>
#include <vector>

using namespace std;

int main() {

    int arr[5] = {1,3,2,1,3};
    int query[5] = {1,4,2,3,12}; // maximum is 12
    int hash[13] = {0}; // depening on highest value + 1 of size

    // precompute
    for (int i = 0 ; i < sizeof(arr)/sizeof(arr[0]); i++){
        hash[arr[i]]+=1;
    }

    // now query
    for (int i = 0 ; i < sizeof(query)/sizeof(query[0]);i++){
        cout << hash[query[i]] << endl;
    }

    return 0;
}
```

### 2 Basic hash Code for (character)
```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    int hash[27] = {0}; // a-z (only for small)
    string input = "abcabget";
    string query = "abfgoer";
    
    // precompute
    for (int i = 0 ; i < input.size(); i++){
        hash[input[i] - 'a']+=1;
    }
    
    // query
    for (int i = 0 ; i < query.size(); i++){
        cout << query[i] << ": " << hash[query[i]-'a'] << endl;
    }
    
    return 0;
}
```

