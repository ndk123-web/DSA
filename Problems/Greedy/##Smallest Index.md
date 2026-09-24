```cpp
class Solution {
public:

    long long sum_digits(int& num) {
        long long sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    int smallestIndex(vector<int>& nums) {

        for (int i = 0; i < nums.size(); i++) {
            if (sum_digits(nums[i]) == i) {
                return i;
            }
        }

        return -1;
    }
};
```
