//
// Created by Darren Tynan on 11/01/2025.
//

#ifndef EDITOR_PROJECTMENUDISPLAY_H
#define EDITOR_PROJECTMENUDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include "../libs/imgui_docking/misc/cpp/imgui_stdlib.h"
#include "../libs/nativefiledialog-extended/src/include/nfd.h"

namespace EDITOR
{
    class ProjectMenuDisplay : public IDisplay
    {
    public:
        std::string project_name;
        std::string file_path;
        int window_width;
        int window_height;
        std::string window_title;

        ProjectMenuDisplay();
        ~ProjectMenuDisplay() override = default;

        void Render() override;
    };
} // namespace EDITOR

#endif //EDITOR_PROJECTMENUDISPLAY_H
