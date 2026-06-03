## CPP Hidden Conceptss


1. min, max always should use the same data type 
```cpp
min(long long, int) // not allowed
min(long long, 1LL * int) // allowerd (not both same data type but both are long long)
```

2. unordered_map for the pair and vector and other data types that are not hashable by default
    1. unordered_map<pair<int, int>, int, hash_pair> mp; // for pair
    ```cpp
    struct hash_pair{
        size_t operator()(const pair<int, int>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };

    unordered_map<pair<int, int>, int, hash_pair> mp; // for pair
    ```

    2. unordered_map<vector<int>, int, hash_vector> mp; // for vector
    ```cpp
    struct hash_vector {
        size_t operator()(const vector<int>& v) const {
            size_t hash_value = 0;
            for (const auto& num : v) {
                hash_value ^= hash<int>()(num) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            }
            return hash_value;
        }
    };

    unordered_map<vector<int>, int, hash_vector> mp; // for vector 
    ```

    - Componenet:
        1. size_t operator()(const T& key) const {} 
            - size_t is return type of operator() function  
            - operator() is operator overloading for "()" so that we can call the object of the struct as a function 
            ```cpp
            struct hash_vector {
                size_t operator()(const vector<int>& v) const {
                    size_t hash_value = 0;
                    for (const auto& num : v) {
                        hash_value ^= hash<int>()(num) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
                    }
                    return hash_value;
                }
            };

            hash_vector hv; // create an object of the struct
            vector<int> v = {1, 2, 3};
            size_t hash_value = hv(v); // call the object as a function to get the hash value of the vector
            ```