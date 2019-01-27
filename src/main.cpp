#include "arithmancy.hpp"

#include <assert.h>

using namespace std;

int main(void)
{
    //GetDigitalRootOfSpell
    assert(GetDigitalRootOfSpell("") == 0);
    assert(GetDigitalRootOfSpell("a") == 1);
    assert(GetDigitalRootOfSpell("N") == 5);
    assert(GetDigitalRootOfSpell(",.=-") == 0);
    assert(GetDigitalRootOfSpell("Daze") == 9);
    assert(GetDigitalRootOfSpell("Fireball") == 2);
    assert(GetDigitalRootOfSpell("Warding Weapon") == 6);

    return 0;
}