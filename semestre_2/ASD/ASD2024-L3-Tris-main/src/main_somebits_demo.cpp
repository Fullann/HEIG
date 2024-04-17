#include <iostream>
#include <limits>
#include "some_bits.h"

using namespace std;
using ui = unsigned int;

int main() {

    ui n; cin >> n;

    for(unsigned nbits : { 1u, 2u, 4u, 8u, 16u }) {
        cout << nbits << " : ";
        for (unsigned i = 0; i < numeric_limits<ui>::digits / nbits ; ++i ) {
            auto fn = SomeBits<unsigned long long>(nbits, i);
            cout << fn(n) << " ";
        }
        cout << endl;
    }
}