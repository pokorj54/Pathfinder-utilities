#include "InvalidArgumentException.hpp"

InvalidArgumentException::InvalidArgumentException(const std::string & arg, int n): arg(arg), position(n)
{}

void InvalidArgumentException::Message(std::ostream & o) const
{
    o << "Argument " << arg << " on position " << position << " isn't valid" << std::endl;
}