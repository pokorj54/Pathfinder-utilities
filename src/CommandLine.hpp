#include "dices.hpp"

#include <unordered_map>
#include <list>
#include <memory>
#include <iostream>

/**
 * @brief Gets commands from user and then returns answer
 * 
 */
class CommandLine
{
    private:
        /**
         * @brief Container for arguments of commands
         * 
         */
        class Arguments
        {
            private:
                std::list<std::string> arguments;
                int noArgs;
            public:
                Arguments();
                /**
                 * @brief Adds argument to the last position
                 * 
                 * @param argument 
                 */
                void PushBack(const std::string & argument);
                /**
                 * @brief Pops first argument and returns it
                 * 
                 * @return std::string first argument
                 * @throws InvalidNoArgumentsException - if it is empty
                 */
                std::string PopFirst();
                /**
                 * @brief Same as PopFirst but it will return empty string instead of throwing exception
                 * 
                 * @return std::string first argument or empty string
                 */
                std::string PopFirstIfNotEmpty();
                /**
                 * @brief Throws an exception if there are more arguments that they should be
                 * 
                 * @throws InvalidNoArgumentsException
                 */
                void ThrowIfNotEmpty();
                
                int GetNoArguments() const;
        };
        std::istream * input;
        std::ostream * output;
        DiceRoller diceRoller;
        typedef void (CommandLine::*HandleCmd)(Arguments & args);
        /**
         * @brief Static map with command names as keys and pointer to method that will 
         *  handle that command and description of the command
         * 
         */
        static std::unordered_map<std::string, std::pair<HandleCmd,std::string>> cmdTranslation;
        /**
         * @brief Static map with aliases to commands
         * 
         */
        static std::unordered_map<std::string, std::string> aliases;
        
        //methods that handles commands
        void HandleHelp(Arguments & args);
        void HandleRoll(Arguments & args);
        void HandleSacredGeometry(Arguments & args);
        void HandleArithmancy(Arguments & args);
        
    public:
        CommandLine();
        /**
         * @brief 
         * 
         * @return true on normal use
         * @return false if checking validity and error occurs
         */
        void HandleCommands();

    friend std::string _GetCommandAndArgument(std::string command, Arguments & outArguments);
};