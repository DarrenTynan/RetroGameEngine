//
// Created by Darren Tynan on 27/12/2022.
//

#include "TerminalLogger.h"

namespace LOGGER
{

void TerminalLogger::Log(const std::string &message)
{
    std::cout << "\x1B[32m" << message << "\033[0m" << std::endl;
}

void TerminalLogger::Error(const std::string &message, int i)
{
    std::cout << "\x1B[91m" << message << "\033[0m" << std::endl;
}

void TerminalLogger::Error2Arg(const std::string &message, const std::string &message2)
{
    std::cout << "\x1B[91m" << message << message2 << "\033[0m" << std::endl;
}

} // LOGGER END
