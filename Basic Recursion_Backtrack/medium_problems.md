### 1. Subsequence

- Time Complexity -> O (2^ n)
- Space Complexity -> O (n)
```bash
                   []
             /                 \
          [3]                 []
       /        \           /       \
   [3,1]       [3]      [1]         []
   /   \       /  \      /  \        /  \
[3,1,2][3,1] [3,2][3] [1,2][1]    [2]  []

```
```cpp
#include <iostream>
#include <vector>

using namespace std; 

void subseq(vector<int> &ans, vector<int> &arr, int index, int size){
   
   if (index >= size){
       if (ans.empty()){
            cout << "[]" << endl;
       } 
       cout << "[";
       for (auto i : ans){
           cout << i << " ";
       }
       cout << "]" << endl;
       return;
   }
   
   // take it
   ans.push_back(arr[index]);
   subseq(ans,arr,index+1,size);
   
   // after take it remove it (backtrack)
   ans.erase(ans.begin()+index);
   subseq(ans,arr,index+1,size);
}

int main() {
    
    vector<int> arr = {3,1,2};
    vector<int> ans = {};
    
    subseq(ans,arr,0,arr.size());
    
    return 0;
}
```

### 2. Subsequence Sum

```cpp
#include <iostream>
#include <vector>

using namespace std; 

void subseq(vector<int> &ans, vector<int> &arr, int index, int size, int k , int sum){
   
   if (index >= size){
       if(sum == k){
           for(auto i : ans){
               cout << i << " ";
           }
           cout << endl;
       }
       return;
   }
   
   // take it
   ans.push_back(arr[index]);
   sum+=arr[index];
   
   subseq(ans,arr,index+1,size,k,sum);
   
   // after take it remove it (backtrack)
   ans.erase(ans.begin()+index);
   sum-=arr[index];
   subseq(ans,arr,index+1,size,k,sum);
}

int main() {
    
    vector<int> arr = {3,1,2};
    vector<int> ans = {};
    int k = 3;
    
    subseq(ans,arr,0,arr.size(),k,0);
    
    return 0;
}
```