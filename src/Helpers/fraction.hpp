#include <string>

class Fraction
{
    public:
        Fraction() = default;
        Fraction(int numerator, int denominator = 1);
        std::string ToString() const;
        int ToInt() const;
        double ToDouble() const;
        bool operator < (const Fraction & other) const; 
        bool operator != (const Fraction & other) const; 
    private:
        int numerator;
        int denominator;
        Fraction Normalize();
    friend Fraction Add(const Fraction & f1, const Fraction & f2);
    friend Fraction Subtract(const Fraction & f1, const Fraction & f2);
    friend Fraction Multiply(const Fraction & f1, const Fraction & f2);
    friend Fraction Divide(const Fraction & f1, const Fraction & f2);
};
Fraction Add(const Fraction & f1, const Fraction & f2);
Fraction Subtract(const Fraction & f1, const Fraction & f2);
Fraction Multiply(const Fraction & f1, const Fraction & f2);
Fraction Divide(const Fraction & f1, const Fraction & f2);