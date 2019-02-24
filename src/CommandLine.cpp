#include "CommandLine.hpp"

#include "Exceptions/Exception.hpp"
#include "Exceptions/InvalidNoArgumentsException.hpp"

#include "sacredGeometry.hpp"
#include "arithmancy.hpp"

#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

/**
 * @brief Initialization of commands
 * 
 */
unordered_map<string, std::pair<CommandLine::HandleCmd,std::string>> CommandLine::cmdTranslation =
{
    {"help", make_pair(&CommandLine::HandleHelp, "0: shows all commands and their description, 1 - command: shows description for command")},
    {"roll", make_pair(&CommandLine::HandleRoll, "1 - roll string: string representing roll")},
    {"sacredGeometry", make_pair(&CommandLine::HandleSacredGeometry, "2+ - spell level: from 1 to 9, dices: any number of integers")},
    {"arithmancy", make_pair(&CommandLine::HandleArithmancy, "1 - spell name: name of spell without metamagic")},
};

CommandLine::CommandLine(): input(&cin), output(&cout)
{}

CommandLine::Arguments::Arguments(): noArgs(0)
{}
void CommandLine::Arguments::PushBack(const string & argument)
{
    ++noArgs;
    arguments.push_back(argument);
}
string CommandLine::Arguments::PopFirst()
{
    if(arguments.empty())
    {
        throw InvalidNoArgumentsException(noArgs, false);
    }
    string res = arguments.front();
    arguments.pop_front();
    return res;
}
string CommandLine::Arguments::PopFirstIfNotEmpty()
{
    if(arguments.empty())
    {
        return "";
    }
    string res = arguments.front();
    arguments.pop_front();
    return res;
}
void CommandLine::Arguments::ThrowIfNotEmpty()
{
    if(!arguments.empty())
    {
        throw InvalidNoArgumentsException(noArgs, true);
    }
}
int CommandLine::Arguments::GetNoArguments() const
{
    return arguments.size();
}

string _GetCommandAndArgument(string command, CommandLine::Arguments & outArguments)
{
    size_t pos = command.find(" ");
    if(pos == string::npos)
    {   
        return command;
    }
    string result = command.substr(0, pos);
    command = command.substr(pos +1, command.length());
    
    list<string> tmp;

    pos = command.find("\"");
    bool qmark = 0;
    while(pos != string::npos)
    {
        tmp.push_back(command.substr(0, pos));
        command = command.substr(pos, command.length());
        qmark = !qmark;
        pos = command.find("\"", qmark) + qmark;
    }
    tmp.push_back(command);

    for(string & s : tmp)
    {
        if(s == "")
        {
            continue;
        }
        else if(s[0] == '"')
        {
            outArguments.PushBack(s.substr(1, s.length() - 2));
        }
        else
        {
            pos = s.find(" ");
            while(pos != string::npos)
            {
                string tmpstring = s.substr(0, pos);
                if(tmpstring.find_first_not_of(' ') != string::npos)
                {
                    outArguments.PushBack(tmpstring);
                }
                s = s.substr(pos + 1, s.length());
                pos = s.find(" ");
            }
            if(s.find_first_not_of(' ') != string::npos)
            {
                outArguments.PushBack(s);
            }
        }
    }
    return result;
}

void CommandLine::HandleCommands()
{
    while(!input->eof() && !input->fail())
    {
        string fullCommand;
        getline(*input, fullCommand);
        if(fullCommand.find_first_not_of(" \t") == string::npos)
        {
            continue; //no command given
        }
        else if(count(fullCommand.begin(), fullCommand.end(), '"') % 2 == 1)
        {
            *output << "Invalid command - odd number of \"" << endl;
            continue;
        }

        Arguments arguments;
        string cmdName = _GetCommandAndArgument(fullCommand, arguments);

        if(cmdName == "exit") //it's the only command that can affect the command cycle 
        {
            break;
        }

        HandleCmd method;
        try
        {
            method = cmdTranslation.at(cmdName).first;
        }
        catch(const out_of_range & e)
        {
            *output << "Unknown command" << endl;
            continue;
        }

        try
        {
            ((*this).*method)(arguments);
        }
        catch(const Exception & e)
        {
            e.Message(*output);
        }
    }
}

void CommandLine::HandleHelp(Arguments & args)
{
    string cmd = args.PopFirstIfNotEmpty();
    args.ThrowIfNotEmpty();
    if(cmd == "")
    {
        vector<pair<string, string>> commands;
        for(const pair<string, pair<CommandLine::HandleCmd, string>> & c : cmdTranslation)
        {
            commands.push_back(make_pair(c.first, c.second.second));
        }
        sort(commands.begin(), commands.end());
        for(const pair<string,string> p : commands)
        {
            *output << p.first << " - " << p.second << endl;
        }
        return;
    }
    try
    {
        *output << cmdTranslation.at(cmd).second << endl;
    }
    catch(const out_of_range & e)
    {
        *output << "Unknown command" << endl;
    }
}

void CommandLine::HandleRoll(Arguments & args)
{
    string rollString = args.PopFirst();
    args.ThrowIfNotEmpty();
    diceRoller.ParseDiceString(rollString).Print();
}

void CommandLine::HandleSacredGeometry(Arguments & args)
{
    int spellLevel = stoi(args.PopFirst());
    int size = args.GetNoArguments();
    int * dices = new int[size];
    for(int i = 0; i < size; ++i)
    {
        dices[i] = stoi(args.PopFirst());
    }
    string expression = GetDesiredExpression(spellLevel, dices, size);
    if(expression == "")
    {
        expression = "none";
    }
    (*output) << "Expression: " << expression << endl;
}

void CommandLine::HandleArithmancy(Arguments & args)
{
    string spellName = args.PopFirst();
    args.ThrowIfNotEmpty();
    (*output) << "Digital root: " << GetDigitalRootOfSpell(spellName) << endl;
}