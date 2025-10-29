### 1 Number of Subarray with xor k (Brute)

- Time -> N^2
- Space -> O(1)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {

    // 0 1 2 3  4
    // 4 6 8 14 18
    vector<int> arr = {4,2,2,6,4};
    // output :
                // 42
                // 42264
                // 226
                // 6

    // int xorans = 0;
    int i = 0 , j = 0;
    int cnt = 0;
    int target = 6;

    for (i = 0 ; i < arr.size(); i++){
        int xorans = 0;

        // i -> j
        for (j = i; j < arr.size(); j++){

            // calculate xorans i -> j
            xorans = xorans ^ arr[j];

            // if target == xorans
            if (target == xorans){
                cnt++;

                // print 1st subarray with target = 6
                for (int k = i ; k <= j; k++){
                    cout << arr[k];
                }

                // new line
                cout << endl;
            }
        }
    }
    cout << "Ans: " << cnt;
    return 0;
}
```

### 2 Number of Subarray with xor k (Optimize)

```cpp
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    int target = 6;

    int cnt = 0;
    vector<int> arr = {4,2,2,6,4};
    map<int,int> mpp;

    int xr = 0;
    mpp[xr]++;

    for (int i = 0 ; i < arr.size(); i++){

        // calculate xr
        xr = xr ^ arr[i];

        // calculate what we want
        int x = xr ^ target;

        // add if that is occures in map
        cnt = cnt + mpp[x];

        // increase xr value in map
        mpp[xr]++;
    }

    cout << "Cnt: " << cnt;

    return 0;
}
```
