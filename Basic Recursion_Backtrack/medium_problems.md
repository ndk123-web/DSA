
### 1. Subsequence

- Time Complexity -> O (2^ n)
- Space Complexity -> O (n)
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