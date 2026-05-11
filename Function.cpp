#include "Function.h"
#include <iomanip>
void Function::printValue(double x) const {
    std::cout << "f(" << x << ") = " << calculate(x) << std::endl;
}

double Function::findMin(double a, double b, int steps) const {
    if (a > b) std::swap(a, b);
    double minVal = calculate(a);
    double step = (b - a) / steps;
    // Используем целый счетчик для избежания накопления ошибки double
    for (int i = 0; i <= steps; ++i) {
        double x = a + i * step;
        double val = calculate(x);
        if (val < minVal) minVal = val;
    }
    return minVal;
}

double Function::findMax(double a, double b, int steps) const {
    if (a > b) std::swap(a, b);
    double maxVal = calculate(a);
    double step = (b - a) / steps;
    for (int i = 0; i <= steps; ++i) {
        double x = a + i * step;
        double val = calculate(x);
        if (val > maxVal) maxVal = val;
    }
    return maxVal;
}

double Function::integrate(double a, double b, int steps) const {
    double h = (b - a) / steps;
    double sum = 0.5 * (calculate(a) + calculate(b));
    for (int i = 1; i < steps; ++i) {
        sum += calculate(a + i * h);
    }
    return sum * h;
}

double Function::derivative(double x, double h) const {
    return (calculate(x + h) - calculate(x - h)) / (2 * h);
}

// Реализации 

Hyperbola::Hyperbola(double a, double b) : a(a), b(b) {}

double Hyperbola::calculate(double x) const {
    if (std::abs(x) < 1e-9) {
        // Возвращаем NaN (Not a Number) при делении на ноль
        return std::numeric_limits<double>::quiet_NaN();
    }
    return a / x + b;
}

void Hyperbola::printInfo() const {
    std::cout << "Hyperbola: y = " << a << "/x + " << b << std::endl;
}

Parabola::Parabola(double a, double b, double c) : a(a), b(b), c(c) {}

double Parabola::calculate(double x) const {
    return a * x * x + b * x + c;
}

void Parabola::printInfo() const {
    std::cout << "Parabola: y = " << a << "x^2 + " << b << "x + " << c << std::endl;
}

Exponent::Exponent(double a, double b, double c) : a(a), b(b), c(c) {}

double Exponent::calculate(double x) const {
    return a * std::exp(b * x) + c;
}

void Exponent::printInfo() const {
    std::cout << "Exponent: y = " << a << " * exp(" << b << "x) + " << c << std::endl;
}

Polinom::Polinom(const std::vector<double>& coefficients) : coeffs(coefficients) {}

double Polinom::calculate(double x) const {
    if (coeffs.empty()) return 0.0;
    double result = 0.0;
    double power = 1.0;
    for (double coef : coeffs) {
        result += coef * power;
        power *= x;
    }
    return result;
}

void Polinom::printInfo() const {
    std::cout << "Polynomial degree " << (coeffs.size() > 0 ? coeffs.size() - 1 : 0) << ": ";
    bool first = true;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        if (coeffs[i] == 0 && coeffs.size() > 1) continue; // Пропускаем нулевые коэфф.

        if (!first && coeffs[i] >= 0) std::cout << " + ";
        else if (!first && coeffs[i] < 0) std::cout << " - ";
        else if (first && coeffs[i] < 0) std::cout << "-";

        std::cout << std::abs(coeffs[i]);
        if (i > 0) std::cout << "x^" << i;
        first = false;
    }
    std::cout << std::endl;
}

