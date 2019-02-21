#include "fraction.hpp"

#include <string>

using namespace std;

int gcd(int a, int b) 
{
    return b == 0 ? a : gcd(b, a % b);
}

Fraction::Fraction(int numerator, int denominator):numerator(numerator), denominator(denominator)
{
    Normalize();
}
std::string Fraction::ToString() const
{
    if(denominator == 1)
    {
        return to_string(numerator);
    }
    return to_string(numerator) + "/" + to_string(denominator);
}
int Fraction::ToInt() const
{
    return numerator/denominator;
}
double Fraction::ToDouble() const
{
    return (double)numerator/denominator;
}
Fraction Fraction::Normalize()
{
    int d = gcd(numerator, denominator);
    numerator /= d;
    denominator /= d;
    if(denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }
    return *this;
}
bool Fraction::operator < (const Fraction & other) const
{
    Fraction f = Divide(*this, other);
    return f.numerator < f.denominator;
}
bool Fraction::operator > (const Fraction & other) const
{
    return other < *this;
}
bool Fraction::operator <= (const Fraction & other) const
{
    return !(*this > other);
}
bool Fraction::operator >= (const Fraction & other) const
{
    return !(*this < other);
}
bool Fraction::operator != (const Fraction & other) const
{
    return *this < other || other < *this; 
}
bool Fraction::operator == (const Fraction & other) const
{
    return !(*this != other);
}
Fraction Add(const Fraction & f1, const Fraction & f2)
{
    return Fraction(f1.numerator * f2.denominator + f2.numerator*f1.denominator, f1.denominator * f2.denominator).Normalize();
}
Fraction Subtract(const Fraction & f1, const Fraction & f2)
{
    return Add(f1, Fraction(-f2.numerator, f2.denominator));
}
Fraction Multiply(const Fraction & f1, const Fraction & f2)
{
    return Fraction(f1.numerator * f2.numerator, f1.denominator * f2.denominator).Normalize();
}
Fraction Divide(const Fraction & f1, const Fraction & f2)
{
    return Multiply(f1, Fraction(f2.denominator, f2.numerator));
}
