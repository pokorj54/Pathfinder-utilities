#include "sacredGeometry.hpp"
#include "Helpers/fraction.hpp"

#include <string>

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
        ExprAndValue(Fraction value): value(value), expression(value.ToString()){}
        Fraction value;
        string expression;
        typedef Fraction (*func)(const Fraction &, const Fraction &);
        ExprAndValue Combine(const ExprAndValue & that, func f, const string & funcRepresentation) const
        {
            ExprAndValue result = ExprAndValue(f(this->value, that.value));
            result.expression = "(" + this->expression + funcRepresentation + that.expression + ")";
            return result;
        }
};

string CombineExpressions(int spellLevel, ExprAndValue * exprs, int size)
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
            exprs[size-2] = e1.Combine(e2, Add, "+");
            string tmp = CombineExpressions(spellLevel, exprs, size-1);
            if(tmp != "")
            {
                return tmp;    
            }
            exprs[size-2] = e1.Combine(e2, Subtract, "-");
            tmp = CombineExpressions(spellLevel, exprs, size-1);
            if(tmp != "")
            {
                return tmp;    
            }
            exprs[size-2] = e1.Combine(e2, Multiply, "*");
            tmp = CombineExpressions(spellLevel, exprs, size-1);
            if(tmp != "")
            {
                return tmp;    
            }
            if(e2.value.ToDouble() != (double)0)
            {
                exprs[size-2] = e1.Combine(e2, Divide, "/");
                tmp = CombineExpressions(spellLevel, exprs, size-1);
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
    ExprAndValue * exprs = new ExprAndValue[size];
    for(int i = 0; i < size; ++i)
    {
        exprs[i] = ExprAndValue(Fraction(rolledDices[i]));
    }
    return CombineExpressions(spellLevel, exprs, size);
}