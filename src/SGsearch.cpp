#include "sacredGeometry.hpp"

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cmath>
#include <thread>

using namespace std;

const int maxSpellLevel = 9;
const int maxDices = 20;
const int maxDiceValue = 8;
const int limitedDiceValue = 6;
const bool showIntermedietResults = false;
const int maxThreads = 6;

int64_t factorial(int n)
{
    int64_t values[] = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000};
    return values[n];
}


class SGCategory
{
    public:
        SGCategory(){}
        SGCategory(int noDices, int spellLevel): noDices(noDices), spellLevel(spellLevel),
        successfulCombinations(),successfulLimitedCombinations(0),
        successfulVariations(0), successfulLimitedVariations(0)
        {}
        void Print() const;
        static void Execute(SGCategory & sgc);
    private:
        int noDices;
        int spellLevel;
        int successfulCombinations;
        int successfulLimitedCombinations;
        int64_t successfulVariations;
        int64_t successfulLimitedVariations;
        void TryAllCombinations();
};

void SGCategory::TryAllCombinations()
{
    int diceDelimiters[maxDiceValue+1];
    diceDelimiters[maxDiceValue] = 0;
    diceDelimiters[0] = noDices;
    diceDelimiters[1] = -1;
    int * dices = new int[noDices];
    for(int k = 2; k < maxDiceValue; ++k)
    {
        diceDelimiters[k] = 0;
    }
    while(diceDelimiters[maxDiceValue-1] < noDices)
    {
        int64_t permutations = factorial(noDices);
        if(diceDelimiters[1] < noDices)
        {
            diceDelimiters[1] += 1;
        }
        else
        {
            int l = 1;
            while(diceDelimiters[l] == noDices)
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
        string tmp = GetDesiredExpression(spellLevel, dices, noDices);
        if(showIntermedietResults)
        {
            cout << spellLevel << '\t';
            for(int p = 0; p < noDices; ++p)
            {
                cout << dices[p] << " ";
            }
            
            cout << '\t' << tmp << endl;
        }
        if(tmp != "")
        {
            successfulVariations += permutations;
            ++successfulCombinations;
            if(dices[noDices-1] <= limitedDiceValue)
            {
                successfulLimitedVariations += permutations;
                ++successfulLimitedCombinations;
            }
        }
    }
    delete [] dices;
}

void SGCategory::Print() const
{
    int64_t possibleVariations = pow(maxDiceValue, noDices);
    int64_t possibleLimitedVariations = pow(limitedDiceValue, noDices);
    cout << setprecision(5)  << "NoD: " << noDices << ", SL: " << spellLevel<< " = PC: "
        << possibleVariations << ", SC: " << successfulVariations << ", PLC: " << possibleLimitedVariations 
        << ", SLC: " << successfulLimitedVariations << " -> Rate: "
        << (double)successfulVariations/possibleVariations << "(" << (double)successfulLimitedVariations/possibleLimitedVariations 
        << ")" << endl;
}

void SGCategory::Execute(SGCategory & sgc)
{
    sgc.TryAllCombinations();
}

int main(void)
{
    for(int currentNoDices = 1; currentNoDices <= maxDices; ++currentNoDices)
    {   
        SGCategory s1 = SGCategory(currentNoDices, 1);
        SGCategory s2 = SGCategory(currentNoDices, 2);
        SGCategory s3 = SGCategory(currentNoDices, 3);
        SGCategory s4 = SGCategory(currentNoDices, 4);
        SGCategory s5 = SGCategory(currentNoDices, 5);
        SGCategory s6 = SGCategory(currentNoDices, 6);
        SGCategory s7 = SGCategory(currentNoDices, 7);
        SGCategory s8 = SGCategory(currentNoDices, 8);
        SGCategory s9 = SGCategory(currentNoDices, 9);
        thread t1 = thread(SGCategory::Execute, ref(s1));
        thread t2 = thread(SGCategory::Execute, ref(s2));
        thread t3 = thread(SGCategory::Execute, ref(s3));
        thread t4 = thread(SGCategory::Execute, ref(s4));
        thread t5 = thread(SGCategory::Execute, ref(s5));
        thread t6 = thread(SGCategory::Execute, ref(s6));
        thread t7 = thread(SGCategory::Execute, ref(s7));
        thread t8 = thread(SGCategory::Execute, ref(s8));
        thread t9 = thread(SGCategory::Execute, ref(s9));
        t1.join();
        s1.Print();
        t2.join();
        s2.Print();
        t3.join();
        s3.Print();
        t4.join();
        s4.Print();
        t5.join();
        s5.Print();
        t6.join();
        s6.Print();
        t7.join();
        s7.Print();
        t8.join();
        s8.Print();
        t9.join();
        s9.Print();
    }
}