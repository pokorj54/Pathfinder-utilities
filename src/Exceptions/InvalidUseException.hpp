#ifndef InvalidUseException_cc44027c01f64c4684ad73fedc9bccf9
#define InvalidUseException_cc44027c01f64c4684ad73fedc9bccf9


#include "Exception.hpp"

#include <iostream>

/**
 * @brief Exception signaling that user is trying to do something that does not make sense
 * 
 */
class InvalidUseException: public Exception
{
    public:
        InvalidUseException() = default;
        void Message(std::ostream & o) const override;
};

#endif //InvalidUseException_cc44027c01f64c4684ad73fedc9bccf9