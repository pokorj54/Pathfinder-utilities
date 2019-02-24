#include "InvalidCommandUseException.hpp"

#include <iostream>

void InvalidCommandUseException::Message(std::ostream & o) const 
{
    o << "You cannot use this command now" << std::endl;
}