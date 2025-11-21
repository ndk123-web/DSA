- Only Difference:

| Feature | struct | class |
| --- | --- | --- |
| Default access | public | private |
| Use-case | DSA nodes, simple models | Full OOP |

1. Struct 
- This is Storing in Stack
- We can also store this in Heap using **new** Keyword

```cpp
#include <iostream>

struct Node {
    int data;
    Node *left;
    Node *right;
    
    Node(int data){
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

int main() {
    
    Node node1 = Node(10);
    int val = node1.data;
    std::cout << val;
    
    return 0;
}
```

1. Class
- This is Storing in Stack
- We can also store this in Heap using **new** Keyword

```cpp
#include <iostream>

class Node {
    private:
        Node *left;
        Node *right;
    
    public:
        int data;
        
        Node(int data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }
};

int main() {
    
    Node node1 = Node(10);
    int val = node1.data;
    std::cout << val;
    
    return 0;
}
```