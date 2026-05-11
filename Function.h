#pragma once
#include <vector>
#include <iostream>
#include <cmath>

class Function {
public:
    virtual ~Function() = default;
    virtual double calculate(double x) const = 0;
    virtual void printValue(double x) const;
    virtual double findMin(double a, double b, int steps = 1000) const;
    virtual double findMax(double a, double b, int steps = 1000) const;
    virtual double integrate(double a, double b, int steps = 1000) const;
    virtual double derivative(double x, double h = 1e-5) const;
    virtual void printInfo() const = 0;
};

class Hyperbola : public Function {
private:
    double a, b;
public:
    Hyperbola(double a = 1.0, double b = 0.0);
    double calculate(double x) const override;
    void printInfo() const override;
};

class Parabola : public Function {
private:
    double a, b, c;
public:
    Parabola(double a = 1.0, double b = 0.0, double c = 0.0);
    double calculate(double x) const override;
    void printInfo() const override;
};

class Exponent : public Function {
private:
    double a, b, c;
public:
    Exponent(double a = 1.0, double b = 1.0, double c = 0.0);
    double calculate(double x) const override;
    void printInfo() const override;
};

class Polinom : public Function {
private:
    std::vector<double> coeffs;
public:
    Polinom(const std::vector<double>& coefficients);
    double calculate(double x) const override;
    void printInfo() const override;
};


