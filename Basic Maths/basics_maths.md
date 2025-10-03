### 1. Digit Concept

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 82823;
    
    while (a > 0) {
        int lastDigit = a % 10;  // extract last digit
        cout << lastDigit << endl;
        a = a / 10;              // reduce number
    }
    
    return 0;
}
```

### 2. Count Digit

```cpp
#include <bits/stdc++.h>
using namespace std;

// log10(100) = ?
// 10^2 = 100
// log10(100)=2

int main(){
	int a = 142424;
	
	int digits = (int)(log10(a) + 1);
	cout << digits;
	
	return 0;
}
```

### 3. Reverse Number

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){

    int num = 7654;
    int rev = 0;
    
    while (num > 0){
        rev = rev * 10 + (num % 10);
        num = num / 10;
    }
    
    cout << rev;
	
	return 0;
}
```

### 4. Print All Divisions

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){

    // print all divisions
    int num = 36;
    vector <int> nums;
    
    for (int i = 1 ; i <= sqrt(num); i++){
        if(num%i == 0){
            nums.emplace_back(i);
            if (num / i != i){ // for preventing double 6 
                nums.emplace_back(num/i);
            }
        }
    }
    
    sort(nums.begin(),nums.end());
    
    for (auto i : nums){
        cout << i << " ";
    }
    
    // 1 36 2 18 3 12 4 9 6 
	
	return 0;
}
```

### 4. Prime

- Prime Means number which has exactly 2 factors

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){

    int num = 34;
    int cnt = 0;
 
    for (int i = 1 ; i <= sqrt(num) ; i++){
        if (num % i == 0){
            cnt++;
            if (num/i != i){ // it means include 36 also (36/1) = 36
                cnt++;
            }
        }
        
    }
    
    cnt == 2 ? cout << "Prime" : cout <<"Not Prime";
	return 0;
}
```

### 5. GCD ( Euclidian Distance )

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){

	 // Euclidian Distance
   // gcd(a,b) = gcd(a-b,b) where a > b
   
   int a = 10;
   int b = 22;
   
   while (a>0 && b>0){
       if (a > b) a = a % b;
       else b = b % a;
   }
   
   a == 0 ? cout << b : cout << a;

   return 0;
}
```