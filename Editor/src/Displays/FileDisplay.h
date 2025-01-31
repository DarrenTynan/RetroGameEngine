//
// Created by Darren Tynan on 24/01/2025.
//

#ifndef EDITOR_FILEDISPLAY_H
#define EDITOR_FILEDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include "../src/FileSystem/include/FileDialogs.h"

namespace EDITOR
{
    class FileDisplay : public IDisplay
    {
    public:
        FileDisplay();
        ~FileDisplay() = default;

        virtual void Render() override;

        std::vector<std::string> nodes;

        void GetFolderTree();
        void NodeTree();
    };
} // namespace EDITOR

#endif //EDITOR_FILEDISPLAY_H
