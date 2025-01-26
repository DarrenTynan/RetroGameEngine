//
// Created by Darren Tynan on 15/01/2025.
//

#ifndef EDITOR_MAINMENUBAR_H
#define EDITOR_MAINMENUBAR_H

#include "IDisplay.h"
#include <imgui.h>
#include "../src/Logger/Logger.h"
#include "../src/FileSystem/include/FileDialogs.h"

namespace EDITOR
{
    class MainMenuBar : public IDisplay
    {
    public:
        MainMenuBar();
        ~MainMenuBar() = default;
        virtual void Render() override;
    };

} // namespace end
#endif //EDITOR_MAINMENUBAR_H
