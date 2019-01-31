#include "sacredGeometry.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

const int maxSpellLevel = 9;
const int maxDices = 20;
const int maxDiceValue = 8;
const int limitedDiceValue = 6;
const bool showIntermedietResults = false;
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
            int possibleCombinations = 0, successfullCombinations = 0, possibleLimitedCombinations = 0, succesfullLimitedCombinations = 0;
            diceDelimiters[1] = -1;
            for(int k = 2; k < maxDiceValue; ++k)
            {
                diceDelimiters[k] = 0;
            }
            while(diceDelimiters[maxDiceValue-1] < currentNoDices)
            {
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
                    ++successfullCombinations;
                    if(dices[currentNoDices-1] <= limitedDiceValue)
                    {
                        ++succesfullLimitedCombinations;
                    }
                }
                ++possibleCombinations;
                if(dices[currentNoDices-1] <= limitedDiceValue)
                {
                    ++possibleLimitedCombinations;
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