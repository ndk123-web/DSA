## 1. Basic Program CPP

```cpp
#include <bits/stdc++.h> // it includes some basic group of libraries (iostream , string , math )

using namespace std;

int main(){
	cout << "Hi" << endl;
	return 0;
}
```

## 2. Data Types

- int
- long
- long long
- double
- float

## 3. Getline vs String

```cpp
#include <bits/stdc++.h> // it includes some basic group of libraries (iostream , string , math )
#include <string>

using namespace std;

int main(){
  string s1;
  cin >> "Hello I Am Ndk";
  cout << s1;  
  // only will print "Hello" 
  
  string s2;
  getline(cin,s2);
  cout << s2; 
  // will print "Hello I Am Ndk"
  
	return 0;
}
```

## 4. If Else

```cpp
#include <bits/stdc++.h> // it includes some basic group of libraries (iostream , string , math )

using namespace std;

int main(){

	int age = 10;
	
	if (age > 18) cout <<"Adult";
	else if(age < 0) cout <<"Something went wrong : Too Less";
	else if(age > 150) cout <<"Something went Wrong: Too Large";
	else cout << "Not Adult";

	return 0;
}
```

## 5. Array

```cpp
#include <bits/stdc++.h> // it includes some basic group of libraries (iostream , string , math )

using namespace std;

int main(){
	
	// 1D Array
	int arr1[2] = {1,2};
	
	for(auto i = 0 ; i < sizeof(arr1)/sizeof(arr1[0]); i++){
		cout << arr[i] << endl;
	}
	
	// 2D Array (2 -> row , 4-> col)
	int mat[2][4];
	
	return 0;
}
```

## 6. For Loop / while loop / do while loop

```cpp
#include <bits/stdc++.h> // it includes some basic group of libraries (iostream , string , math )

using namespace std;

int main(){
	
	int i;
	
	// For Loop
	for (i=0 ; i < 500 ; i++){
		cout << i << endl;
	}
	
	// While Loop
	while (i < 500){
		cout << i << endl;
		i++;
	}
	
	// Do While Loop
	do{
		cout << i << endl;
		i++;
	}
	while(i < 500);
	
	return 0;
}
```

## 7. Functions ( pass by ref / pass by value )

```cpp
#include <bits/stdc++.h> // it includes some basic group of libraries (iostream , string , math )

using namespace std;

void passByValue(int a){
	a = 10;
}

void passByRef(int *a){
	*a = 10;
}

int main(){
	
	int a = 20;
	
	passByValue(a);
	cout << a << endl; // 20 
	
	passByRef(&a);
	cout << a << endl; // 10 (changed because sent the address of a )
	
	return 0;
}
```

## 8. Alias / pointer

- **Only “Array” Always is Pass By Reference ( don’t need to write “&” )**

```cpp
#include <bits/stdc++.h> // it includes some basic group of libraries (iostream , string , math )

using namespace std;

void alias(int &a){
	a = 10;
}

void passByRef(int *a){
	*a = 10;
}

int main(){
	
	int a = 10;
	
	passByRef(&a);
	cout << a << endl;
	
	alias(a);
	cout << a << endl;
	
	// both is pass by reference
	// in case of alias the alias means giving another name to the same block
	
	return 0;
}
```