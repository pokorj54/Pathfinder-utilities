#include "sacredGeometry.hpp"

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cmath>

using namespace std;

const int maxSpellLevel = 9;
const int maxDices = 20;
const int maxDiceValue = 8;
const int limitedDiceValue = 6;
const bool showIntermedietResults = false;

int64_t factorial(int n)
{
    int64_t values[] = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000};
    return values[n];
}

int main(void)
{
    int diceDelimiters[maxDiceValue+1];
    diceDelimiters[maxDiceValue] = 0;
    
    for(int currentNoDices = 1; currentNoDices < maxDices; ++currentNoDices)
    {
        int * dices = new int[currentNoDices];
        diceDelimiters[0] = currentNoDices;
        for(int currentSpellLevel = 1; currentSpellLevel <= maxSpellLevel; ++currentSpellLevel)
        {
            int64_t possibleCombinations = pow(maxDiceValue, currentNoDices), successfullCombinations = 0;
            int64_t possibleLimitedCombinations = pow(limitedDiceValue, currentNoDices), succesfullLimitedCombinations = 0;
            diceDelimiters[1] = -1;
            for(int k = 2; k < maxDiceValue; ++k)
            {
                diceDelimiters[k] = 0;
            }
            while(diceDelimiters[maxDiceValue-1] < currentNoDices)
            {
                int64_t permutations = factorial(currentNoDices);
                if(diceDelimiters[1] < currentNoDices)
                {
                    diceDelimiters[1] += 1;
                }
                else
                {
                    int l = 1;
                    while(diceDelimiters[l] == currentNoDices)
                        ++l;
                    int m = diceDelimiters[l] + 1;
                    for(;l >= 1; --l)
                        diceDelimiters[l] = m;
                }
                int currentPosition = 0;
                for(int n = 1; n <= maxDiceValue; ++n)
                {
                    int difference = diceDelimiters[n-1] - diceDelimiters[n];
                    permutations /= factorial(difference);
                    for(int o = 0; o < difference; ++o)
                    {
                        dices[currentPosition] = n;
                        ++currentPosition;
                    }
                }
                string tmp = GetDesiredExpression(currentSpellLevel, dices, currentNoDices);
                if(showIntermedietResults)
                {
                    cout << currentSpellLevel << '\t';
                    for(int p = 0; p < currentNoDices; ++p)
                    {
                        cout << dices[p] << " ";
                    }
                    
                    cout << '\t' << tmp << endl;
                }
                if(tmp != "")
                {
                    successfullCombinations += permutations;
                    if(dices[currentNoDices-1] <= limitedDiceValue)
                    {
                        succesfullLimitedCombinations += permutations;
                    }
                }
            }
            cout << setprecision(5)  << "NoD: " << currentNoDices << ", SL: " << currentSpellLevel<< " = PC: "
            << possibleCombinations << ", SC: " << successfullCombinations << ", PLC: " << possibleLimitedCombinations 
            << ", SLC: " << succesfullLimitedCombinations << " -> Rate: "
            << (double)successfullCombinations/possibleCombinations << "(" << (double)succesfullLimitedCombinations/possibleLimitedCombinations 
            << ")" << endl;
        }
        delete [] dices;
    }
}