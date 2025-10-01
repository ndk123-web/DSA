### 1. Pattern

```cpp

// * * * * * 
// * * * * * 
// * * * * * 
// * * * * * 
// * * * * * 

#include <iostream>

using namespace std;

int main() {
    
    for (int i = 0 ; i < 5; i++){
        for (int j = 0 ; j < 5; j++){
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}
```

### 2. Pattern

```cpp

// * 
// * * 
// * * * 
// * * * * 
// * * * * * 

#include <iostream>

using namespace std;

int main() {
    
    for (int i = 0 ; i < 5; i++){
        for (int j = 0 ; j <= i; j++){
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}
```

### 3. Pattern

```cpp
// * * * * * 
// * * * * 
// * * * 
// * * 
// * 

#include <iostream>

using namespace std;

int main() {
    
    for(int i = 0 ; i < 5; i++){
        for (int j = 4; j >=i ; j--){
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}
```

### 4. Pattern

```cpp
// 1 
// 1 2 
// 1 2 3 
// 1 2 3 4 
// 1 2 3 4 5 

#include <iostream>

using namespace std;

int main() {
    
    for (int i = 1; i <= 5; i++){
        for (int j=1 ; j<=i; j++){
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}
```

### 5. Pattern

```cpp
// 1 
// 2 2 
// 3 3 3 
// 4 4 4 4 
// 5 5 5 5 5 

#include <iostream>

using namespace std;

int main() {
    
    for (int i = 1; i <= 5; i++){
        for (int j=1 ; j<=i; j++){
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
```

### 6. Pattern

```cpp
//    *
//   ***
//  *****
// *******
//*********

#include <iostream>

using namespace std;

int main() {
    
    int r = 3;
    int c = 3;
    int space;
    int star;
    
    for (int i = 0 ; i < r ; i++){
        space = r - i - 1;
        for (int j = 0; j < space ; j++){
            cout << " ";
        }
        
        star = (2*i) + 1;
        for (int k = 0 ; k < star ; k++){
            cout << "*";
        }
        
        cout << endl;
    }

    return 0;
}
```

### 7. Pattern

```cpp
//    * 
//   ***
//  ***** 
// ******* 
//********* 
// ******* 
//  *****
//   ***
//    * 

#include <iostream>

using namespace std;

int main() {
    
    int r = 4;
    int c = 5;
    int space;
    int star;
    int opposite_r = r - 1;
    
    for (int i = 0 ; i < r ; i++){
        space = r - i - 1;
        for (int j = 0; j < space ; j++){
            cout << " ";
        }
        
        star = (2*i) + 1;
        for (int k = 0 ; k < star ; k++){
            cout << "*";
        }
        
        cout << endl;
    }
    
    for (int i = opposite_r - 1; i >= 0 ; i--){
        space = opposite_r - i;
        for (int j = 0 ; j < space; j++){
            cout << " ";
        }
        
        star = (2*i) + 1;
        for(int k = 0 ; k < star ; k++){
            cout << "*";
        }
        
        cout << endl;
    }

    return 0;
}
```

### 8. Pattern

```cpp
// * 
// * * 
// * * * 
// * * * * 
// * * * * * 
// * * * * 
// * * * 
// * * 
// *

#include <iostream>

using namespace std;

int main() {
    
    int r = 5;
    int c = 5;
    int opposite_r = r - 1;
    
    for (int i = 0 ; i < r; i++){
        for (int j = 0 ; j<=i ; j++){
            cout << "* ";
        }
        cout << endl;
    }
    
    for (int i = opposite_r; i > 0; i--){
        for (int j = 0; j < i; j++){
            cout << "* ";
        }    
        cout << endl;
    }
    return 0;
} 
```

### 9. Pattern

```cpp
// start -> even -> 0 , odd -> 1
// 0
// 10
// 010
// 1010
// 01010

#include <iostream>

using namespace std;

int main() {
    
    int r = 5;
    int c = 5;
    
    for (int i = 0 ; i < r ; i++ ){
        int start_with = i % 2 == 0 ? 1 : 0;
        for (int j = 0 ; j <= i ; j++){
            cout << start_with;
            start_with == 1 ? start_with-- : start_with++;
        }
        
        cout << endl;
    }

    return 0;
}
```

### 10. Pattern

```cpp
// 1        1
// 12      21
// 123    321
// 1234  4321
// 1234554321

#include <iostream>

using namespace std;

int main() {
    
    int r = 5;
    int c = 5;
    int space = 0;
    int start_space = 2*r - 1;
    
    for (int i = 1; i <= r; i++){
        
        // numbers
        for (int j = 1; j<=i; j++){
            cout << j;
        }
        
        // space -> find initially space then decrease by 2 
        for (int k = 1; k <= start_space; k++){
            cout << " ";
        }
        
        // reverse numbers
        for (int l=1 ; l <= i; l++){
            cout << i - l + 1;
        }
        
        start_space = start_space - 2;
        cout << endl;
    }

    return 0;
}
```

### 11. Pattern

```cpp
// A
// AB
// ABC
// ABCD
// ABCDE

#include <iostream>

using namespace std;

int main() {
    
    int r = 5;
    int c = 5;
    
    for (int i = 0 ; i < r ; i++){
        for (char j = 'A'; j <= 'A' + i ; j++){
            cout << j;
        }
        cout << endl;
    }
    
    return 0;
}

// ABCDE
// ABCD
// ABC
// AB
// A
#include <iostream>

using namespace std;

int main() {
    
    int r = 5;
    int c = 5;
    
    for (int i = r ; i > 0 ; i--){
       for (char j = 'A' ; j < 'A' + i ; j++){
           cout << j;
       }
       cout << endl;
    }
    
    return 0;
}

// A
// BB
// CCC
// DDDD
// EEEEE

#include <iostream>

using namespace std;

int main() {
    
    int r = 5;
    int c = 5;
    
    for (int i = 0 ; i < r; i++){
        for (char j = 'A'; j <= 'A' + i; j++){
            char print_tobe = 'A' + i;
            cout << print_tobe;
        } 
        
        cout << endl;
    }
    
    return 0;
}
```

### 12. Pattern

```cpp
// *        *
// **      **
// ***    ***
// ****  ****
// **********
// ****  ****
// ***    ***
// **      **
// *        *

#include <iostream>

using namespace std;

int main() {
    
    int r = 5;
    int c = 5;
    int intial_space = r - 1;
    int opposite_r = r - 1;
    
    // upper part
    for (int i = 1; i <= r; i++){
        
        for (int j=1; j<=i; j++){
            cout << "*";
        }
        
        for (int k = 1 ; k <= intial_space; k++){
            cout << " ";
        }
        
        for (int k = 1 ; k <= intial_space; k++){
            cout << " ";
        }
        
        for (int l=1; l<=i; l++){
            cout << "*";
        }
        
        intial_space=intial_space-1;
        cout << endl;
    }
    
    // lower part
    intial_space = 2;
    for (int i = opposite_r; i >=0 ; i--){
        
        for (int j = 1 ; j <= i; j++){
            cout << "*";
        }
        
        for (int k = 1; k <= intial_space; k++){
            cout << " ";
        }
        
        for (int j = 1 ; j <= i; j++){
            cout << "*";
        }
        
        intial_space = intial_space + 2;
        cout << endl;
    }
    
}
```

### 13. Pattern

```cpp
// *********
// *       *
// *       *
// *       *
// *       *
// *       *
// *       *
// *       *
// *       *
// *********

#include <iostream>

using namespace std;

int main() {
    
    int r = 10;
    int c = 5;

    for (int i = 1; i <= r; i++){
        if (r == i || i == 1){
            for (int j = 1; j < r ; j++){
                cout << "*";
            }   
        }else{
            cout << "*";
            for (int j = 1; j < r - 2 ; j++){
                cout << " ";
            }   
            cout << "*";
        }
        
        cout << endl;
    }
    return 0;
}
```