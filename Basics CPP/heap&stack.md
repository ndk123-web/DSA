1. When Program Runs , OS Allocated Virtual Address Space to the Program
2. OS Creates Virtual Address Space ( Includes Stack , and all default segments)
3. Heap is managed by **runtime library**
4. Runtime library (**not compiler**) takes extra memory from **OS** via **system calls** (`brk`, `sbrk`, `mmap`)
5. Compiler / Runtime manage how your program uses that Space

6. Stack

- Used For
  - Local Variables
  - Function parameters
  - Recursion Function Call Frames
- Pros And Cons
  - Fast and Auto Cleanup
  - **Small in Size**

```cpp
#include <iostream>

void fn(int a, int b) {      // fn store in stack
    int c = a + b;
    std::cout << "Sum: " << c;

    fn(c,a);       // unlimited recursion fn frames stored in stack
}

int main(){

	int a = 10;    // store in stack
	fn(10,20);     // store in stack

	return 0;
}
```

1. Heap

- Used For
  - Dynamically Allocated Memory
  - Large Data Structures
  - **Memory U Want to Control Manually**
- Pros and Cons
  - Big And Flexible
  - **Slow** and Must free memory else then **Issue of Memory Leak**

```cpp
#include <iostream>

int main(){

  int *p = new int(10);  // store in heap

  delete p;   // my responsiblitiy to clean the memory from heap

	return 0;
}
```

- Summary

| Feature  | Stack                 | Heap                |
| -------- | --------------------- | ------------------- |
| Speed    | Very Fast             | Slower              |
| Size     | Limited               | Big                 |
| Cleanup  | Automatic             | Manual              |
| Used for | Local vars, recursion | dynamic memory, STL |
| Errors   | stack overflow        | memory leak         |
