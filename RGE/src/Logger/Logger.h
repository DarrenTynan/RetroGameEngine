//
// Created by Darren Tynan on 27/12/2022.
//

#ifndef RETROGAMEENGINE_LOGGER_H
#define RETROGAMEENGINE_LOGGER_H

#include <iostream>

class Logger {
    public:
        static void Log(const std::string &message);
        static void Error(const std::string& message);
};

#endif //RETROGAMEENGINE_LOGGER_H
