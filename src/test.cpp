#include "arithmancy.hpp"
#include "sacredGeometry.hpp"
#include "Helpers/fraction.hpp"

#include <assert.h>
#include <iostream>

using namespace std;

int main(void)
{
    //Arithmancy
    assert(GetDigitalRootOfSpell("") == 0);
    assert(GetDigitalRootOfSpell("a") == 1);
    assert(GetDigitalRootOfSpell("N") == 5);
    assert(GetDigitalRootOfSpell(",.=-") == 0);
    assert(GetDigitalRootOfSpell("Daze") == 9);
    assert(GetDigitalRootOfSpell("Fireball") == 2);
    assert(GetDigitalRootOfSpell("Warding Weapon") == 6);

    //Fractions
    assert(Fraction(4,2).ToString() == "2");
    assert(Fraction(5,3).ToString() == "5/3");
    assert(Add(Fraction(3,-4), Fraction(2)).ToString() == "5/4");
    assert(Multiply(Fraction(1,4), Fraction(2)).ToDouble() == 0.5);
    assert(Subtract(Fraction(3,4), Fraction(1,2)).ToString() == "1/4");
    assert(Divide(Fraction(1,2), Fraction(1,4)).ToDouble() == 2);

    Fraction f1 = Fraction(1,2), f2 = 2;
    assert(f1 < f2);
    assert(!(f2 < f1));
    assert(!(f1 < f1));
    assert(f2 > f1);
    assert(!(f1 > f2));
    assert(!(f2 > f2));
    assert(f1 <= f2);
    assert(!(f2 <= f1));
    assert(f1 <= f1);
    assert(f2 >= f1);
    assert(!(f1 >= f2));
    assert(f2 >= f2);
    assert(f1 != f2);
    assert(f2 != f1);
    assert(!(f1 != f1));
    assert(f1 == f1);
    assert(!(f1 == f2));
    assert(!(f2 == f1));
    
    //SacredGeometry
    int a[] = {3};
    assert(GetDesiredExpression(1, a, (sizeof(a)/sizeof(int))) == "3");
    assert(GetDesiredExpression(2, a, (sizeof(a)/sizeof(int))) == "");
    int b[] = {1,1,2,5};
    assert(GetDesiredExpression(2, b, (sizeof(b)/sizeof(int))) != "");
    assert(GetDesiredExpression(3, b, (sizeof(b)/sizeof(int))) == "");
    return 0;
}