#include "arithmancy.hpp"
#include "sacredGeometry.hpp"

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

    //SacredGeometry
    int a[] = {3};
    assert(GetDesiredExpression(1, a, (sizeof(a)/sizeof(int))) == "3");
    assert(GetDesiredExpression(2, a, (sizeof(a)/sizeof(int))) == "");
    int b[] = {1,1,2,5};
    assert(GetDesiredExpression(2, b, (sizeof(b)/sizeof(int))) != "");
    assert(GetDesiredExpression(3, b, (sizeof(b)/sizeof(int))) == "");
    return 0;
}