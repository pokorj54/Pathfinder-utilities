#ifndef InvalidArgumentException_dff04bfead7b429e930d968816650564
#define InvalidArgumentException_dff04bfead7b429e930d968816650564

#include "Exception.hpp"

#include <iostream>

/**
 * @brief Exception signaling invalid argument given to command
 * 
 */
class InvalidArgumentException: public Exception
{
    private:
        std::string arg;
        int position;
    public:
        InvalidArgumentException(const std::string & arg, int n);
        void Message(std::ostream & o) const override;
};

#endif //InvalidArgumentException_dff04bfead7b429e930d968816650564