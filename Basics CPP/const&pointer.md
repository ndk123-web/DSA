- `begin()` vs `cbegin()`
- iterator vs const_iterator
- pass-by-const-reference
- map keys are always const
- functions with const correctness
- strings passed as `const string&`
- prevent accidental modification

### Its Normal That Once Variable Initialize with value then it can not be change and because of this speed increases

1. Can not Re initialize

```cpp
#include <iostream>

int main() {
    
    const int a = 10;
    a = 100;  // gives error can't re-initialize
    std::cout << a;

    return 0;
}
```

| Code | Meaning |
| --- | --- |
| `const int* p` | int is const → *p cannot modify value* |
| `int* const p` | pointer const → p cannot move |
| `const int* const p` | both locked |
| `int const* p` | same as `const int* p` |

1. const int *p
- Here **Value Locked**

```cpp
#include <iostream>

int main() {
    
    int a = 10;
    const int *p = &a;  // * is for variable so value cant change

    int b = 11;
    p = &b;

    std::cout << *p;

    return 0;
}
```

1. int *const p
- Here **Pointer Locked**

```cpp
#include <iostream>

int main() {
    
    int a = 10;
    int *const p = &a;  // * touches const means pointer cant change 

    *p = 11;

    std::cout << *p;

    return 0;
}
```

3. const int *const p

- Both **Value And Pointer Locked**

```cpp
#include <iostream>

int main() {
    
    int a = 10;
    const int *const p = &a;  // here * touches const as well as const to int so value as well as pointer cant be change

    return 0;
}
```