### 1 Factorial 

```cpp
#include <iostream>

using namespace std;

// Functional Recursion -> returns something
int print(int i){
    if (i==1){
        return 1;
    }
    return i*print(i-1);
}

int main() {
    
    int sum = print(5);
    cout << sum << endl;
    
    return 0;
}
```

### 2 Reverse Array using 2 pointers
```cpp
#include <iostream>
#include <vector>

using namespace std;

// Recursion -> Reverse Array using 2 pointers

void reverse(vector<int> &arr , int start , int end){
    if (start >= end){
        return;
    }
    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
}

int main() {
    
    vector<int> arr = {1,2,3,4,5};
    
    cout << "Before" << endl;
    for (auto i : arr){
        cout << i << " ";
    }
    cout << endl;
    
    reverse(arr,0,arr.size()-1);
    
    cout << "After" << endl;
    for (auto i : arr){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
```

### 3 Palidrome using Recursion
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Recursion -> Reverse Array using 2 pointers

bool palindrome(string value, int start , int end){
    if (start >= end){
        return true;
    }
    if (value[start] != value[end]){
        return false;
    }
    return palindrome(value,start+1,end-1);
}

int main() {
    
    string value = "nayan";
    
    palindrome(value, 0, value.size()-1) ? cout <<"Palindrome" : cout << "Not Palindrome";
    return 0;
}
```