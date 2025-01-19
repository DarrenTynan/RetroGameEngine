//
// Created by Darren Tynan on 19/01/2025.
//

#ifndef EDITOR_LOGGER_H
#define EDITOR_LOGGER_H

#include <iostream>
#include <imgui.h>

namespace EDITOR_LOGGER
{
    class Logger
    {
    private:
        // Private constructor to prevent direct instantiation
        Logger() {}

        // Disable copy constructor and assignment operator
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        // Private static instance
        static Logger* instancePtr;

    public:
        // Public static method to get instance
        static Logger* GetInstance()
        {
            if (instancePtr == nullptr)
            {
                instancePtr = new Logger();
            }
            return instancePtr;
        }

        void TestLog();
    };


} // namespace end
#endif //EDITOR_LOGGER_H
