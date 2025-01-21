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


    /**
     * @brief Add a new log entry
     *
     * @param fmt
     * @param ...
     */
    void Logger::AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
//        auto logger = EDITOR_LOGGER::Logger::GetInstance();
//        auto textBuffer = logger->getTextBuffer();
//        auto lineOffsets = logger->getLineOffsets();

        int old_size = textBuffer.size();
        va_list args;
        va_start(args, fmt);

        textBuffer.appendfv(fmt, args);

        va_end(args);
        for (int new_size = textBuffer.size(); old_size < new_size; old_size++)
        {
            if (textBuffer[old_size] == '\n')
                lineOffsets.push_back(old_size + 1);

        }

    }


    /**
     * @brief Clear the arrays.
    */
    void Logger::Clear()
    {
        textBuffer.clear();
        lineOffsets.clear();
        lineOffsets.push_back(0);
    }

    const ImGuiTextBuffer &Logger::getTextBuffer() const
    {
        return textBuffer;
    }

    const ImGuiTextFilter &Logger::getTextFilter() const
    {
        return textFilter;
    }

    const ImVector<int> &Logger::getLineOffsets() const
    {
        return lineOffsets;
    }

    bool Logger::isAutoScroll() const
    {
        return AutoScroll;
    }

} // namespace end
