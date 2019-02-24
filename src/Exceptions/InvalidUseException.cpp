#include "InvalidUseException.hpp"

void InvalidUseException::Message(std::ostream & o) const 
{
    o << "The thing you are trying to do doesn't really make sense" << std::endl;
}