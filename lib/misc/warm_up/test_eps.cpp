#include <bits/stdc++.h>
using namespace std;

template <class T>
int calc_bits() {
    int bit = 0;
    for (T delta = 1; true; delta /= 2, bit++) {
        volatile T tot = T(1) + delta;
        if (tot - T(1) != delta) break;
    }
    return bit;
}

int main() {
    /*
        digit2 -> digit10
        53        15
        64        18
        113       33
    */

    cout << "double:      " << calc_bits<double>() << '\n';
    cout << "long double: " << calc_bits<long double>() << '\n';
    cout << "__float128:  " << calc_bits<__float128>() << '\n';

    assert( calc_bits<double>() == 53 );
    assert( calc_bits<long double>() == 64 );
    assert( calc_bits<__float128>() == 113 );

    return 0;
}