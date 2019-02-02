#include "dices.hpp"

#include <list>
#include <string>
#include <random>
#include <utility>

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

DiceThrower::DiceThrower()
{
    random_device rd;
    generator = default_random_engine(rd());
}
DiceResult DiceThrower::RollDice(int sides)
{
    uniform_int_distribution<int> dis(1, sides);
    int rnd = dis(generator);
    return DiceResult(sides, rnd);
}
RollResult DiceThrower::RollDices(const list<pair<int, int>> & dices)
{
    RollResult rollResult;
    for(pair<int, int> group : dices)
    {
        for(int i = 0; i < group.second; ++i)
        {
            rollResult.AddDiceResult(RollDice(group.first));
        }
    }
    return rollResult;
}