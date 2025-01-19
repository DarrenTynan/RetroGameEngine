//
// Created by Darren Tynan on 15/01/2025.
//

#ifndef EDITOR_LOGDISPLAY_H
#define EDITOR_LOGDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include <iostream>

namespace EDITOR
{
    class LogDisplay : public IDisplay
    {
    private:
        ImGuiTextBuffer textBuffer;
        ImGuiTextFilter textFilter;
        ImVector<int> lineOffsets;  // Index to lines offset. We maintain this with AddLog() calls.
        bool AutoScroll{};          // Keep scrolling if already at the bottom.

    public:
        [[nodiscard]] const ImGuiTextBuffer &getTextBuffer() const;

        ~LogDisplay() override = default;

        void Clear();
        void Draw() override;
        void AddLog(const char *fmt, ...);

    };

} // end namespace
#endif //EDITOR_LOGDISPLAY_H
