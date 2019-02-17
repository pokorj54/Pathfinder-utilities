#include "dices.hpp"

#include <list>
#include <string>
#include <random>
#include <utility>
#include <sstream>
#include <iostream>

using namespace std;

DiceResult::DiceResult(int sides, int roll):sides(sides), roll(roll)
{}

int DiceResult::GetDiceSides() const
{
    return sides;
}
int DiceResult::GetRoll() const
{
    return roll;
}

void DiceResult::Print() const
{
    cout << roll << "\t(" << sides << ")" << endl;    
}
 
RollResult::RollResult():result(0)
{}

void RollResult::AddDiceResult(const DiceResult & diceResult)
{
    diceResults.push_back(diceResult);
    result += diceResult.GetRoll();
}

void RollResult::AddModifier(int modifier)
{
    result += modifier;
}
const std::list<DiceResult> & RollResult::GetDiceResults() const
{
    return diceResults;
}
int RollResult::GetResult() const
{
    return result;
}
void RollResult::Print() const
{
    for(DiceResult dr : diceResults)
    {
        dr.Print();
    }
    cout << "result: " << result << endl;
}

DiceRoller::DiceRoller()
{
    random_device rd;
    generator = default_random_engine(rd());
}
DiceResult DiceRoller::RollDice(int sides)
{
    uniform_int_distribution<int> dis(1, sides);
    int rnd = dis(generator);
    return DiceResult(sides, rnd);
}
RollResult DiceRoller::RollDices(const list<pair<int, int>> & dices)
{
    RollResult rollResult;
    for(pair<int, int> group : dices)
    {
        for(int i = 0; i < group.first; ++i)
        {
            rollResult.AddDiceResult(RollDice(group.second));
        }
    }
    return rollResult;
}
RollResult DiceRoller::ParseDiceString(const std::string & diceString)
{
    RollResult rollResult;
    stringstream ss(diceString);
    int amount, sides;
    ss >> amount;
    while(!ss.fail())
    {
        char c = 0;
        ss >> c;
        if(c == 'd')
        {
            ss >> sides;
            for(int i = 0; i < amount; ++i)
            {
                rollResult.AddDiceResult(RollDice(sides));
            }
            ss >> c;
        }
        else
        {
            rollResult.AddModifier(amount);
        }
        ss >> amount;
    }
    return rollResult;
}