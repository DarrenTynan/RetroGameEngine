//
// Created by Darren Tynan on 19/01/2025.
//

#include "Logger.h"

namespace EDITOR_LOGGER
{
/**
 * even though I've defined the static member variable outside the class,
 * it remains inaccessible directly because it's still declared as private
 * within the class. The purpose of defining it outside the class is to
 * allocate memory for it, but its access is still controlled by the class's
 * access specifiers.
*/
    Logger* Logger::instancePtr = nullptr;

    void Logger::TestLog()
    {
        std::cout << "TestLog from Logger instance" << std::endl;
    }

} // namespace end
