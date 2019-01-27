#include <string>

/**
 * @brief Gets the digital root of spell as described in feat Arithmancy
 * 
 * @param spellName Name of the spell, doesn't matter if it is uppercase or not, also special characters and order does nto matter
 * @return int Digital root - number from 1 to 9
 */
int GetDigitalRootOfSpell(const std::string & spellName);