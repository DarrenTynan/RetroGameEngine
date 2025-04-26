//
// Created by Darren Tynan on 11/01/2025.
//

#ifndef EDITOR_TESTDISPLAYA_H
#define EDITOR_TESTDISPLAYA_H

#include "IDisplay.h"
#include <imgui.h>
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR_DISPLAY
{
    class TestDisplayA : public IDisplay
    {
    public:
        TestDisplayA();
        ~TestDisplayA() override = default;

        void Render(std::shared_ptr<Registry>& registry) override;
    };
} // end namespace

#endif //EDITOR_TESTDISPLAYA_H
