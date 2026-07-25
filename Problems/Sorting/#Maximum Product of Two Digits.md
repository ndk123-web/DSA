## solutions


### 1
```cpp
class Solution {
public:
    int maxProduct(int n) {
        string s = to_string(n);

        // to check whether is there duplication or not
        // {location, value}
        pair<long long, long long> res1 = {-1, 0};
        pair<long long, long long> res2 = {-1, 0};

        // find the first max 
        for (int i = 0; i < s.size(); i++) {
            if (res1.second < s[i] - '0') {
                res1 = {i, s[i] - '0'};
            }
        }

        // find the second max 
        for (int i = 0; i < s.size(); i++) {
            if (res1.first == i)
                continue;
            
            if (res2.second < s[i] - '0' && res2.second <= res1.second) {
                res2 = {i, s[i] - '0'};
            }
        }

        return (res1.second * res2.second);
    }
};
```


### 2
```cpp
class Solution {
public:
    int maxProduct(int n) {
        string s = to_string(n);
        long long res = 0;
        priority_queue<int> pq;

        for (int i = 0; i < s.size(); i++) {
            pq.push(s[i] - '0');
        }

        long long res1 = 0;
        if (!pq.empty()) {
            res1 = pq.top();
            pq.pop();
        }
        long long res2 = 0;
        if (!pq.empty()) {
            res2 = pq.top();
            pq.pop();
        }

        return max(res, (res1 * res2));
    }
};
```