//
// Created by Darren Tynan on 15/01/2025.
//

#ifndef EDITOR_MAINMENUBAR_H
#define EDITOR_MAINMENUBAR_H

#include "IDisplay.h"
#include <imgui.h>
#include "../libs/nativefiledialog-extended/src/include/nfd.h"

namespace EDITOR
{
    class MainMenuBar : public IDisplay
    {
    public:
        MainMenuBar();
        ~MainMenuBar() = default;
        virtual void Draw() override;
        void FileLoader();
    };

} // namespace end
#endif //EDITOR_MAINMENUBAR_H
