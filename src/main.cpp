#include "dices.hpp"

#include <iostream>

using namespace std;
int main(void)
{
    string cmd = "";
    DiceRoller diceRoller;
    cin >> cmd;
    while(cmd != "exit")
    {
        diceRoller.ParseDiceString(cmd).Print();
        cin >> cmd;
    }
    return 0;
}