#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    const int i = n;
    cout << "i = " << i << endl; 

    int *ptr_i = const_cast<int*>(&i);
    *ptr_i = 5; 

    cout << "i = " << i << endl;

    return 0;
}
