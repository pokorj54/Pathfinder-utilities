#ifndef InvalidCommandUseException_c19ae71d86744fa4961020b11969130e
#define InvalidCommandUseException_c19ae71d86744fa4961020b11969130e

#include "Exception.hpp"

#include <iostream>

/**
 * @brief Exception signailing use of command when there are not the right resources for it
 * 
 */
class InvalidCommandUseException: public Exception
{
    public:
        InvalidCommandUseException() = default;
        void Message(std::ostream & o) const override;
};

#endif //InvalidCommandUseException_c19ae71d86744fa4961020b11969130e