//
// Created by Darren Tynan on 11/01/2025.
//

#ifndef EDITOR_TESTDISPLAYB_H
#define EDITOR_TESTDISPLAYB_H

#include "IDisplay.h"
#include <imgui.h>

namespace EDITOR
{
    class TestDisplayB : public IDisplay
    {
    public:
        TestDisplayB();
        ~TestDisplayB() = default;

        virtual void Draw() override;
    };
} // namespace EDITOR

#endif //EDITOR_TESTDISPLAYB_H
