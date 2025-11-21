## Reference

- It means Alias
- It means We are pointing to same location but has different names
- It is not **Reassignable**

```cpp
#include <iostream>

int main() {
    int a = 11;
    int &ref = a; // alias (ref and a) = 11 
    
    std::cout << a << "\n";
        
    ref = 10; // ref changes a also changes
    
    std::cout << ref << "\n";
    std::cout << a << "\n";

    return 0;
}
```

## Pointer

- Its another way to pass the reference / address
- It is Reassignable

```cpp
#include <iostream>

int main() {
    int a = 11;
    int *ref = &a; // alias (ref and a) = 11 
    
    std::cout << a << "\n";
        
    *ref = 10; // ref changes a also changes
    
    std::cout << *ref << "\n";
    std::cout << a << "\n";

    return 0;
}
```