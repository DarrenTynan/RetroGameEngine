//
// Created by Darren Tynan on 14/01/2025.
//

#ifndef EDITOR_SCENEDISPLAY_H
#define EDITOR_SCENEDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR_DISPLAY
{
    class SceneDisplay : public IDisplay
    {
    public:
        SceneDisplay();
        ~SceneDisplay() override = default;

        void Render(std::shared_ptr<Registry>& registry) override;
    };
} // namespace EDITOR

#endif //EDITOR_SCENEDISPLAY_H
