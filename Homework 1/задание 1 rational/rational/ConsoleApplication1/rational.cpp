#include "rational.h"
#include <cmath> 

Rational::Rational()
{
    numer = 0;
    denom = 1;
}

Rational::Rational(int number)
{
    numer = number;
    denom = 1;
}

Rational::Rational(int n, int d)
{
    numer = n;
    denom = d;
}

void Rational::simplify()
{
    if (denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }
    for (int i = 2; i <= abs(denom) && i <= abs(numer); i++)
    {
        if (numer % i == 0 && denom % i == 0)
        {
            numer /= i;
            denom /= i;
            i--;
        }
    }
}

Rational& Rational::operator +=(const Rational& r)
{
    numer = (numer * r.denom + denom * r.numer);
    denom *= r.denom;
    simplify(); 
    return *this;
}

Rational Rational::operator +(const Rational& r) const
{
    Rational res(*this); 
    return res += r;     
}

Rational Rational::operator -() const
{
    Rational r(-numer, denom);
    return r;
}

Rational& Rational::operator -=(const Rational& r)
{
    return (*this += (-r));
}

Rational& Rational::operator ++()
{
    numer += denom;
    return *this;
}

Rational Rational::operator ++(int)
{
    Rational r(*this);
    numer += denom;
    return r;
}

bool Rational::operator ==(const Rational& r) const
{
    return (numer == r.numer) && (denom == r.denom);
}

bool Rational::operator !=(const Rational& r) const
{
    return !(*this == r);
}

Rational::operator int() const
{
    return numer / denom;
}

Rational::operator double() const
{
    return ((double)numer) / denom;
}

istream& operator >>(istream& in, Rational& r)
{
    in >> r.numer >> r.denom;
    return in;
}

ostream& operator <<(ostream& out, const Rational& r)
{
    out << r.numer << "/" << r.denom;
    return out;
}

Rational Rational::operator -(const Rational& r) const
{
    return *this + (-r);
}

int main(){
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
    cout << "Введите результат g=m/n в формате: m n" << endl;

    Rational g;
    cin >> g;

    if (e + f != g)
        cout << "Неправильно! e+f=" << e + f << endl;
    else
        cout << "Правильно!" << endl;

    return 0;
}