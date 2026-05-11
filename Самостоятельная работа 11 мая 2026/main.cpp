#include "Function.h"
#include <iostream>
using namespace std;
int main() {

    // Hyperbola 
    Hyperbola hyp(2.0, 1.0);
    hyp.printInfo();
    hyp.printValue(1.0);
    cout << "Min [1,5]: " << hyp.findMin(1, 5) << std::endl;
    cout << "Max [1,5]: " << hyp.findMax(1, 5) << std::endl;
    cout << "Integral [1,3]: " << hyp.integrate(1, 3) << std::endl;
    cout << "Derivative at x=2: " << hyp.derivative(2.0) << std::endl << std::endl;

    // Parabola 
    Parabola par(-0.5, 2.0, 1.0);
    par.printInfo();
    par.printValue(2.0);
    cout << "Min [-2,4]: " << par.findMin(-2, 4) << std::endl;
    cout << "Max [-2,4]: " << par.findMax(-2, 4) << std::endl;
    cout << "Integral [0,2]: " << par.integrate(0, 2) << std::endl;
    cout << "Derivative at x=2: " << par.derivative(2.0) << std::endl << std::endl;

    // Exponent 
    Exponent exp(1.0, 0.7, 0.0);
    exp.printInfo();
    exp.printValue(1.0);
    cout << "Min [-1,3]: " << exp.findMin(-1, 3) << std::endl;
    cout << "Max [-1,3]: " << exp.findMax(-1, 3) << std::endl;
    cout << "Integral [0,2]: " << exp.integrate(0, 2) << std::endl;
    cout << "Derivative at x=1: " << exp.derivative(1.0) << std::endl << std::endl;

    // Polinom 
    Polinom poly({ 3, -2, 1 });   // 3 - 2x + x²
    poly.printInfo();
    poly.printValue(1.0);
    cout << "Min [0,2]: " << poly.findMin(0, 2) << std::endl;
    cout << "Max [0,2]: " << poly.findMax(0, 2) << std::endl;
    cout << "Integral [0,2]: " << poly.integrate(0, 2) << std::endl;
    cout << "Derivative at x=1: " << poly.derivative(1.0) << std::endl;

    return 0;
}
