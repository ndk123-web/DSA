### 1 Rotate Array By K Elements
- Time Complexity -> O (k*n)
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

### 2 Rotate Array Most Efficient Way
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