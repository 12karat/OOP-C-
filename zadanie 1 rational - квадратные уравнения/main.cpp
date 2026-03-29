#include <iostream>
#include "rational.h"
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Rational a, b, c;
    
    // тут вообщем ввод дроби они хранятся уже как rational
    
    cout << "(Enter the coefficients a, b, c (in the format: numerator denominator)\n";
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "c: ";
    cin >> c;

    // переводим в double ( используется мой оператор Rational::operator double() )
    double da = (double)a;
    double db = (double)b;
    double dc = (double)c;

    double D = db * db - 4 * da * dc;

    cout << "Discriminant D = " << D << endl;

    if (D > 0) {
        double x1 = (-db + sqrt(D)) / (2 * da);
        double x2 = (-db - sqrt(D)) / (2 * da);

        cout << "Two roots:\n";
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
    else if (D == 0) {
        double x = -db / (2 * da);
        cout << "One roots:\n";
        cout << "x = " << x << endl;
    }
    else {
        cout << "There are no roots (D < 0)\n";
    }

    return 0;
}