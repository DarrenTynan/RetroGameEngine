//
// Created by Darren Tynan on 24/01/2025.
//

#ifndef EDITOR_FILEDISPLAY_H
#define EDITOR_FILEDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include "../../Editor/src/FileSystem/include/FileDialogs.h"
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR_DISPLAY
{
    class FileDisplay : public IDisplay
    {
    public:
        FileDisplay();
        ~FileDisplay() override = default;

        void Render(std::shared_ptr<Registry>& registry) override;

        std::vector<std::string> nodes;

        void GetFolderTree();
        void NodeTree();
    };
} // namespace EDITOR

#endif //EDITOR_FILEDISPLAY_H
