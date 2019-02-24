#ifndef InvalidNoArgumentsException_da27936d2ece48ad873e4175b907dc5f
#define InvalidNoArgumentsException_da27936d2ece48ad873e4175b907dc5f

#include "Exception.hpp"

#include <iostream>

/**
 * @brief Exception signaling that number of argument that was given to command 
 *  was not compatible with the command need
 * 
 */
class InvalidNoArgumentsException: public Exception
{
    private:
        int noArgs;
        bool tooMuch;
    public:
        InvalidNoArgumentsException(int noArgs, bool tooMuch);
        void Message(std::ostream & o) const override;
};

#endif //InvalidNoArgumentsException_da27936d2ece48ad873e4175b907dc5f