//
// Created by Darren Tynan on 27/12/2022.
//

#ifndef EDITOR_LOGGER_H
#define EDITOR_LOGGER_H

#include <iostream>

class Logger
{
    public:
        static void Log(const std::string &message);
        static void Error(const std::string& message);
        static void Error2Arg(const std::string& message, const std::string& message2 );
};

#endif //EDITOR_LOGGER_H
