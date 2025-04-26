//
// Created by Darren Tynan on 15/01/2025.
//

#ifndef EDITOR_MAINMENUBAR_H
#define EDITOR_MAINMENUBAR_H

#include "IDisplay.h"
#include <imgui.h>
#include "../../Editor/src/Logger/include/Logger.h"
#include "../../Editor/src/FileSystem/include/FileDialogs.h"
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR_DISPLAY
{
    class MainMenuBar : public IDisplay
    {
    public:
        MainMenuBar();
        ~MainMenuBar() override = default;
        void Render(std::shared_ptr<Registry>& registry) override;
    };

} // namespace end
#endif //EDITOR_MAINMENUBAR_H
