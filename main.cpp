
 // aviad40l@gmail.com

#include "SquareMat.h"
#include <iostream>

using namespace matrix;
using std::cout, std::endl;

int main() {
    SquareMat m(4);
    m = 6;
    cout << m << endl;

    cout << SquareMat::identity(3) << endl;
    cout << SquareMat::diagonal(2, 5) << endl;

    SquareMat a(3), b(3);
    a = 12;
    a[2][2] = 1;
    b = -3;
    b[0][0] = .5f;
    b[2][1] = 12.0f;
    b[1][0] = -3.3f;
    b[2][2] = 5.5f;
    b[2][0] = 0;

    cout << "a:\n" << a << "b:\n" << b;
    cout << endl;

    cout << "3*a:\n" << 3 * a;
    cout << "b%2:\n" << b % 2;
    cout << "a*b\n" << a * b;
    cout << endl;

    cout << "det(-b):\n" << !(-b) << "\n";

    cout << "trace (a): " << a() << "\n";

    return 0;
}