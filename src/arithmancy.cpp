#include <string>

using namespace std;

const int LETTERVALUES[26] = {1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8};

int SumDigits(int n)
{
    while(n > 9)
    {
        int tmp = 0;
        while(n > 0)
        {
            tmp += n % 10;
            n /= 10;
        }
        n = tmp;
    }
    return n;
}

int GetDigitalRootOfSpell(const string & spellName)
{
    int root = 0;
    for(char c : spellName)
    {
        if(c >= 'a' && c <= 'z')
        {
            root += LETTERVALUES[c - 'a'];
        }
        else if(c >= 'A' && c <= 'Z')
        {
            root += LETTERVALUES[c - 'A'];
        }
    }
    return SumDigits(root);
}