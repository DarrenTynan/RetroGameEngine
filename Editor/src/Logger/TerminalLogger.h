//
// Created by Darren Tynan on 27/12/2022.
//

#ifndef EDITOR_TERMINALLOGGER_H
#define EDITOR_TERMINALLOGGER_H

#include <iostream>

namespace LOGGER
{
    class TerminalLogger
    {
    public:
        static void Log(const std::string &message);
        static void Error(const std::string &message, int i);
        static void Error2Arg(const std::string& message, const std::string& message2 );
    };
}

#endif //EDITOR_TERMINALLOGGER_H
