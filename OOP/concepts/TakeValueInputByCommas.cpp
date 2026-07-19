#include <bits/stdc++.h>

using namespace std;

int main() {
    string s = "10,20,30,40";

    stringstream ss(s);
    string temp;

    // just change here (double, long long, float) to work 
    vector<int> v;

    int i = 0;
    while (getline(ss, temp, ',')) {
        v.push_back(stoi(temp));
        cout << v[i++] << " ";
    }

    // cin automatically return according to the type 
    int x;
    cin >> x;
    
    cout << x+1;

    return 1;
}