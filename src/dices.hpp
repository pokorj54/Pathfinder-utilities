#include <list>
#include <string>
#include <random>
#include <utility>

class DiceResult
{
    public:
        DiceResult(int sides, int roll);
        int GetDiceSides() const;
        int GetRoll() const;
    private:
        int sides;
        int roll;
};

class RollResult
{
    public:
        RollResult();
        void AddDiceResult(const DiceResult & diceResult);
        void AddModifier(int modifier);
        const std::list<DiceResult> & GetDiceResults() const;
        int GetResult() const;
    private:
        std::list<DiceResult> diceResults;
        int result;
};

class DiceThrower
{
    public:
        DiceThrower();
        DiceResult RollDice(int sides);
        RollResult RollDices(const std::list<std::pair<int, int>> & dices);
    private:
        std::default_random_engine generator;
};
