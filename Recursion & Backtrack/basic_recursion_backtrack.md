- Function Calling itself
- There will be always **“Base Condition”**
- Issue → **Stack Overflow**

### 1. Recursion

- In this example Complexity
- Time Complexity → O(N)
- Space Complexity → O(N)

```cpp
#include <iostream>

using namespace std;

void print(int i){
    if (i==10) {
      cout << i << " ";
      return;
	  }
    
    cout << i << " ";
    print(i+1);
}

int main() {
    
    print(1);
    
    return 0;
}
```

### 2. Backtrack ( N to 1 )

```cpp
#include <bits/stdc++.h>

using namespace std;

void print(int num){
    if (num == 10){
        cout << num << " ";
        return;
    }
    
    // first call fn then cout will performs
    print(num+1);
    
    cout << num << " ";
}

int main() {
    
    // 1. Backtrack Intro (number from 10 -> 1)
    
    print(1);
    
    return 0;
}
```

### 3. Backtrack ( 1 to N )

```cpp
#include <iostream>

using namespace std;

// 1 to N (backtrack)
void print(int i){
    if (i==0){
        return;
    }

    // first call fn then cout will performs
    print(i-1);
    cout << i << " ";
}

int main() {
    
    print(10);
    
    return 0;
}
```

### 4. Parameterized vs Functional Recursion

| Type | Carries Data | Returns Data | Example Use |
| --- | --- | --- | --- |
| **Parameterized Recursion** | Through parameters | Usually `void` | Printing, Accumulating sums |
| **Functional Recursion** | No extra parameter | Returns computed value | Mathematical return-based functions |

```cpp
// Parameterized Recursion -> returns void 
#include <iostream>

using namespace std;

void print(int i, int sum){
    if (i == 0){
        cout << "Sum: " << sum << endl;
        return;
    }
    print(i-1,sum+i);
}

int main() {
    
    print(10,0);
    
    return 0;
}
```

```cpp
#include <iostream>

using namespace std;

// Functional Recursion -> returns something
int print(int i){
    if (i==1){
        return 1;
    }
    return i + print(i-1);
}

int main() {
    
    int sum = print(10);
    cout << sum << endl;
    
    return 0;
}
```