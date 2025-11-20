# include <iostream> 

using namespace std;

// Create Arrays 
void CreateArray() {
    int a[] = {1,2,3,4};
    cout << "Created Array" << "\n";
    return;
}

// Read Array
void ReadArray() {
    int a[] = {1,2,3,4};
    cout <<"Reading Array Elements" << "\n";
    cout << "Read: " << a[0] << "\n";
    return;
}

// Update the Array
void UpdateArray() {
    int a[] = {1,2,3,4};
    cout << "Updating Array Element" << "\n";
    cout << "Before: " << a[0] << "\n";
    a[0] = 10;
    cout << "After: " << a[0] << "\n";
}

// Delete the array
void DeleteArray() {
    int a[] = {1,2,3,4};
    int deleteIndex = 2; // 3 

    for (int i = deleteIndex; i < sizeof(a)/sizeof(a[0]) - 1; i++) {
        a[i] = a[i+1];
    }

    a[sizeof(a)/sizeof(a[0])] = 0;

    for (int i : a) {
        cout << i << "\n";
    }

    return;

}

int main () {

    CreateArray();
    ReadArray();
    UpdateArray();
    DeleteArray();

    return 0;
}