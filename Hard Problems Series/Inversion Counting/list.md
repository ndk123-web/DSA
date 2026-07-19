## Inversion Counting

1. Minimum Adjacent Swaps to partition arrays
- Trick -> 
    - If zoneA found in zoneC then need to traverse (zoneB + zoneC) , or if found in zoneB then need to traverse (zoneB) only 
    - If ZoneB found in zoneC then only need to traverse (zoneC)
    - If zoneC found in zoneB/zoneC then just increase the element count of zoneC 

```cpp
class Solution {
public:
    int minAdjacentSwaps(vector<int>& nums, int a, int b) {
        /*
            Input: nums = [1,3,2,4,5,6], a = 3, b = 4
        */
        long long zoneB = 0;
        long long zoneC = 0;
        long long res = 0;
        const int MOD = 1e9 + 7;

        for (int& num : nums) {
            if (num < a) {

                // if its zoneA in either of zoneB/zoneC then pass through both zones that many required adjacent swaps
                res += zoneB + zoneC;
            } else if (num >= a && num <= b) {

                // if its zoneB in zoneC then swap zoneC elements (logically swap)
                res += zoneC;
                zoneB++;
            } else {

                // if its zoneC then don't need to do anything just ++ , further condition 1,2 will do there work to count res
                zoneC++;
            }
        }

        return res % MOD;
    }
};
```