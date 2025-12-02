#include <iostream>
#include <vector>

using namespace std;

// Cycle Sort
// has O(N) Time and O(1) Space
// Only Can use when Number are in Range 

int main() {

    // we know its in range of N 
    vector<int> nums = {3,1,2,4};

    int n = nums.size();
    int i = 0;

    cout << "Before: ";
    for (auto& num : nums) {
        cout << num;
    } 
    cout << "\n";

    while (i < n) {

        // means the last biggest number will be n 
        if (nums[i] <= 0 || nums[i] > n) {
            i++;
            continue;
        }

        // if 1 then idx = 0 , if 2 then idx = 1 
        int idx = nums[i] - 1;  

        // if idx at values are not same just swap it else i++
        if (nums[i] != nums[idx]) {
            swap(nums[i],nums[idx]);
        }else {
            i++;
        }
    }
    cout << "After : ";
    for (auto& num : nums) {
        cout << num;
    } 
    cout << "\n";
    
    return 0;
}