#include <iostream>
#include "rational.h"
#include <cmath> 

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Rational a(1, 2), b(-1, 6);
    cout << "a=" << a << " b=" << b << " a+b=" << a + b << endl;

    cout << "a(" << a << ") += b(" << b << ")" << endl;
    a += b;

    cout << "a=" << a << " b=" << b << " a-b=" << a - b << endl;

    Rational c = 3;
    cout << "b=" << b << " c=" << c << " b+c=" << b + c << endl;

    Rational e(7, 8), f(5, 12);
    cout << "e=" << e << " f=" << f << " e+f=?" << endl;
    cout << "Enter the result g=m/n in the format: m n" << endl;

    Rational g;
    cin >> g;

    if (e + f != g)
        cout << "Wrong! e+f=" << e + f << endl;
    else
        cout << "Right!" << endl;

    return 0;
}