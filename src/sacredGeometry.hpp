#include <string>

/**
 * @brief Gets expression that when calculaten gives you corresponding prime constant
 * 
 * @param spellLevel Prime constants relly on this, it is spell level with modification by metamagic feats
 * @param rolledDices Array with results of dices rolled
 * @param size Number of dices rolled
 * @return std::string Empty if no expression was found
 */
std::string GetDesiredExpression(int spellLevel, int rolledDices[], int size);