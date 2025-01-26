//
// Created by Darren Tynan on 19/01/2025.
//

#ifndef EDITOR_LOGGER_H
#define EDITOR_LOGGER_H

#include <iostream>
#include <imgui.h>

#define EDITOR_LOG() EDITOR_LOGGER::Logger::GetInstance();

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

        ImGuiTextBuffer textBuffer = {};
        ImGuiTextFilter textFilter = {};
        ImVector<int> lineOffsets = {};     // Index to lines offset. We maintain this with AddLog() calls.
        bool AutoScroll{};                  // Keep scrolling if already at the bottom.

    public:
        [[nodiscard]] const ImGuiTextBuffer &getTextBuffer() const;
        [[nodiscard]] const ImGuiTextFilter &getTextFilter() const;
        [[nodiscard]] const ImVector<int> &getLineOffsets() const;
        [[nodiscard]] bool isAutoScroll() const;

        void AddLog(const char *fmt, ...);

        // Public static method to get instance
        static Logger* GetInstance()
        {
            if (instancePtr == nullptr)
            {
                instancePtr = new Logger();
            }
            return instancePtr;
        }

        static void TestLog();

        void Clear();
    };


} // namespace end
#endif //EDITOR_LOGGER_H
