#include "sacredGeometry.hpp"
#include "Helpers/fraction.hpp"

#include <string>
#include <cmath>

using namespace std;

const int PRIMECONSTANTS[9][3] = {
    {3, 5, 7},
    {11, 13, 17},
    {19, 23, 29},
    {31, 37, 41},
    {43, 47, 53},
    {59, 61, 67},
    {71, 73, 79},
    {83, 89, 97},
    {101, 103, 107},
};

class ExprAndValue
{
    public:
        ExprAndValue() = default;
        ExprAndValue(Fraction value, int index, bool canSubstract = true, bool canDivide = true): 
        value(value), expression(value.ToString()), canSubstract(canSubstract), canDivide(canDivide),
        pLowIndex(index), pHighIndex(index), mLowIndex(index), mHighIndex(index)
        {}
        Fraction value;
        string expression;
        bool canSubstract;
        bool canDivide;
        int pLowIndex, pHighIndex, mLowIndex, mHighIndex;
        typedef Fraction (*func)(const Fraction &, const Fraction &);
        ExprAndValue Combine(const ExprAndValue & that, func f, const string & funcRepresentation,
        bool canSubstract, bool canDivide, int index) const
        {
            ExprAndValue result = ExprAndValue(f(this->value, that.value),index, canSubstract, canDivide);
            result.expression = "(" + this->expression + funcRepresentation + that.expression + ")";
            return result;
        }
};
int GetHigherBound(int * values, int size)
{
    int res = 1;
    int ones = 0;
    int twos = 0;
    for(int i = 0; i < size; ++i)
    {
        if(values[i] == 1)
        {
            ++ones;
        }
        else if(values[i] == 2)
        {
            ++twos;
        }
        else
        {
            res *= values[i];
        }
        if(res > PRIMECONSTANTS[(sizeof(PRIMECONSTANTS)/sizeof(*PRIMECONSTANTS))-1][0])
        {
            return res;
        }
    }
    if(ones > twos)
    {
        res *= pow(3, twos+(ones-twos)/3)*2;
    }
    else
    {
        res *= pow(3, ones);
        res *= pow(2, twos-ones);
    }
    return res;
}
string CombineExpressions(int spellLevel, ExprAndValue * exprs, int size, int originalSize)
{
    if(size == 1)
    {
        for(int i : PRIMECONSTANTS[spellLevel - 1])
        {
            if((double)i == exprs[0].value.ToDouble())
            {
                return exprs[0].expression;
            }
        }
    }
    for(int i = 0; i < size; ++i)
    {
        ExprAndValue e1 = exprs[i];
        exprs[i] = exprs[size-1];
        for(int j = 0; j < size - 1; ++j)
        {
            ExprAndValue e2 = exprs[j];
            exprs[j] = exprs[size-2];
            string tmp;
            if(e1.pHighIndex < e2.pLowIndex && (e1.canSubstract || e2.canSubstract))
            {
                exprs[size-2] = e1.Combine(e2, Add, "+",e1.canSubstract && e2.canSubstract, true, 2*originalSize-size);
                exprs[size-2].pLowIndex = e1.pLowIndex;
                exprs[size-2].pHighIndex = e1.pHighIndex;
                tmp = CombineExpressions(spellLevel, exprs, size-1, originalSize);
                if(tmp != "")
                {
                    return tmp;
                }
            }
            if(e1.mHighIndex < e2.mLowIndex && (e1.canDivide || e2.canDivide) && (e1.value != Fraction(2) || e2.value != Fraction(2)) && (e1.value != Fraction(0) || e2.value != Fraction(0))) //2*2 == 2+2, 0*0=0+0
            {
                exprs[size-2] = e1.Combine(e2, Multiply, "*", true, e1.canDivide && e2.canDivide, 2*originalSize-size);
                exprs[size-2].mLowIndex = e1.mLowIndex;
                exprs[size-2].mHighIndex = e1.mHighIndex;
                tmp = CombineExpressions(spellLevel, exprs, size-1, originalSize);
                if(tmp != "")
                {
                    return tmp;
                }
            }
            exprs[size-2] = e1.Combine(e2, Subtract, "-", false, true, 2*originalSize-size);
            if(e2.canSubstract && exprs[size-2].value >= Fraction(0) && e1.value != exprs[size-2].value)//no point of using negative numbers, we already added 0
            {
                tmp = CombineExpressions(spellLevel, exprs, size-1, originalSize);
                if(tmp != "")
                {
                    return tmp;
                }
            }
            if(e2.canDivide && e2.value != Fraction(1) && e2.value != Fraction(0) && e1.value != Fraction(0) && (e1.value != Fraction(4) || e2.value != Fraction(2))) //we already multiplied by zero and substracted 2 from 4
            {
                exprs[size-2] = e1.Combine(e2, Divide, "/", true, false, 2*originalSize-size);
                tmp = CombineExpressions(spellLevel, exprs, size-1, originalSize);
                if(tmp != "")
                {
                    return tmp;
                }
            }
            exprs[size-2] = exprs[j];
            exprs[j] = e2;
        }
        exprs[size-1] = exprs[i];
        exprs[i] = e1;
    }
    return "";
}

string GetDesiredExpression(int spellLevel, int rolledDices[], int size)
{
    if(GetHigherBound(rolledDices, size) < PRIMECONSTANTS[spellLevel-1][0])
    {
         return "";
    }
    ExprAndValue * exprs = new ExprAndValue[size];
    for(int i = 0; i < size; ++i)
    {
        exprs[i] = ExprAndValue(Fraction(rolledDices[i]), i);
    }
    return CombineExpressions(spellLevel, exprs, size, size);
}