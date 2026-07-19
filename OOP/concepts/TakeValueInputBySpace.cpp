#include <bits/stdc++.h>

using namespace std;

int main() {
    string s = "10 20 30 40";

    // its like cin for string s 
    stringstream ss(s);

    // just change here (double, long long, float) to work 
    vector<int> v;
    // just change here (double, long long, float) to work 
    int x;

    // >> this has delimiter as space thats why its working
    while (ss >> x) {
        v.push_back(x);
    }

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";


    return 1;
}