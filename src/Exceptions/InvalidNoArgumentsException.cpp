#include "InvalidNoArgumentsException.hpp"

InvalidNoArgumentsException::InvalidNoArgumentsException(int noArgs, bool tooMuch): noArgs(noArgs), tooMuch(tooMuch)
{}
void InvalidNoArgumentsException::Message(std::ostream & o) const 
{
    o << "You have entered " << noArgs << " arguments for the last command, which is ";
    if(tooMuch)
    {
        o << "too much";
    }
    else
    {
        o << "not enough";
    }
    o << std::endl;
}