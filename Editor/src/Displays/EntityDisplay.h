//
// Created by Darren Tynan on 11/01/2025.
//

#ifndef EDITOR_TESTDISPLAYB_H
#define EDITOR_TESTDISPLAYB_H

#include "IDisplay.h"
#include <imgui.h>
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR
{
    class EntityDisplay : public IDisplay
    {
    public:
        EntityDisplay();
        ~EntityDisplay() override = default;

        void Render(std::shared_ptr<Registry>& registry) override;
    };
} // namespace EDITOR

#endif //EDITOR_TESTDISPLAYB_H
