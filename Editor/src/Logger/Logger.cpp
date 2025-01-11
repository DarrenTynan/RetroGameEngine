//
// Created by Darren Tynan on 27/12/2022.
//

#include "Logger.h"

namespace LOGGER
{

void Logger::Log(const std::string &message)
{
    std::cout << "\x1B[32m" << message << "\033[0m" << std::endl;
}

void Logger::Error(const std::string &message)
{
    std::cout << "\x1B[91m" << message << "\033[0m" << std::endl;
}

void Logger::Error2Arg(const std::string &message, const std::string &message2)
{
    std::cout << "\x1B[91m" << message << message2 << "\033[0m" << std::endl;
}

} // LOGGER END
