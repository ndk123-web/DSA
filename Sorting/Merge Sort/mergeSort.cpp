#include <iostream>
#include <vector>

using namespace std;

void sort(vector<int> &arr , vector<int> &left , vector<int> &right){
    int i = 0 , j= 0 , k=0;
    
    while (i < left.size() && j < right.size()){
        if (left[i] > right[j]){
            arr[k++] = right[j++];
        }else{
            arr[k++] = left[i++];
        }
    }
    
    while (i < left.size()){
        arr[k++] = left[i++];
    }
    
    while (j < right.size()){
        arr[k++] = right[j++];
    }
    
}

void merge(vector<int> &arr){
    
    if (arr.size() == 1){
        return;
    }
    
    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());
    
    merge(left);  // return left side 
    merge(right); // return right side 
    
    sort(arr,left,right);
}

int main() {
    
    vector<int> arr = {5,42,6,2,1};
    
    merge(arr);
    
    for (auto i : arr){
        cout << i << " ";
    }
    
    return 0;
}