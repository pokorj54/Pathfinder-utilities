#include <string>

class Fraction
{
    public:
        Fraction(int numerator, int denominator = 1);
        std::string ToString() const;
        int ToInt() const;
        double ToDouble() const;
    private:
        int numerator;
        int denominator;
        Fraction Normalize();
    friend Fraction Add(const Fraction & f1, const Fraction & f2);
    friend Fraction Subtract(const Fraction & f1, const Fraction & f2);
    friend Fraction Multiply(const Fraction & f1, const Fraction & f2);
    friend Fraction Divide(const Fraction & f1, const Fraction & f2);
};