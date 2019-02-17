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
        void Print() const;
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
        void Print() const;
    private:
        std::list<DiceResult> diceResults;
        int result;
};

class DiceRoller
{
    public:
        DiceRoller();
        DiceResult RollDice(int sides);
        RollResult RollDices(const std::list<std::pair<int, int>> & dices);
        RollResult ParseDiceString(const std::string & diceString);
    private:
        std::default_random_engine generator;
};
