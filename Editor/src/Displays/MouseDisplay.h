//
// Created by Darren Tynan on 14/01/2025.
//

#ifndef EDITOR_MOUSEDISPLAY_H
#define EDITOR_MOUSEDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR
{
    class MouseDisplay : public IDisplay
    {
    public:
        MouseDisplay();
        ~MouseDisplay() override = default;

        void Render(std::shared_ptr<Registry>& registry) override;
        void MousePressed(std::shared_ptr<Registry>& registry);
    };
} // namespace EDITOR

#endif //EDITOR_MOUSEDISPLAY_H
