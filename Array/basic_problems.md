### 1 Intersection Of 2 Sorted Arrays

- Worst Case -> O (N1 + N2)
- Space -> O (1)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {

    // intersection between 2 sorted array
    vector<int> arr1 = {1,2,2,3,3,4,5};
    vector<int> arr2 = {2,3,3,5,6,6,7};
    vector<int> inters;

    int i=0,j=0;

    while (i < arr1.size() && j < arr2.size()){
        if (arr1[i] < arr2[j]){
            i++;
        }else if(arr1[i] == arr2[j]){
            inters.push_back(arr1[i]);
            i++;
            j++;
        }else{
            j++;
        }
    }

    for (auto i : inters){
        cout << i << " ";
    }

    return 0;
}
```

### 2 Rotate Array By K Elements

- Time Complexity -> O (k\*n)
- Space Complexity -> O(n) (including arr)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {

    int arr[] = {1,2,3,4,5};
    int n = 5;
    int k = 6;
    int temp;

    for (auto i: arr){
        cout << i << " ";
    }
    cout << endl;

    int optimized_k = k % n;

    for (int i = 0 ; i < optimized_k; i++){
        temp = arr[0];
        for (int j=0 ; j < n; j++){
            arr[j-1] = arr[j];
        }
        arr[n-1] = temp;
        for (auto i: arr){
            cout << i << " ";
        }
        cout << endl;
    }


    return 0;
}
```

### 3 Rotate Array Most Efficient Way

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {

        int len = nums.size();
        int optimized_k = k % len;
        int temp;

        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + optimized_k);
        reverse(nums.begin() + optimized_k, nums.end());
    }
};
```

### Subarray Sum Equals K

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int total = 0;
        int cnt = 0;
        unordered_map<int,int> mapp;

        mapp[0] = 1;

        for (int i=0; i < nums.size();i++){
            total = total + nums[i];

            // it means find returns iterator/not found
            // end() means returns always iterators
            if (mapp.find(total-k) != mapp.end()){
                cnt = cnt + mapp[total-k];
            }

            mapp[total]++; // if key not exist then key:0 ++ means key:1
        }

        return cnt;
    }
};
```
