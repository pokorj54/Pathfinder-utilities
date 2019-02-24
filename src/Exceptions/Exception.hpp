#ifndef Exception_785a62ec3213411cb4e442ee734c00cb
#define Exception_785a62ec3213411cb4e442ee734c00cb

#include <iostream>

/**
 * @brief Abstract class providing genereal interface to exceptions
 * 
 */
class Exception: public std::exception
{
    public:
        /**
         * @brief Message that can be printed to the end user
         * 
         * @param[out] o here it will be printed
         */
        virtual void Message(std::ostream & o) const = 0;
};

#endif //Exception_785a62ec3213411cb4e442ee734c00cb