//
// Created by Darren Tynan on 11/01/2025.
//

#ifndef EDITOR_TESTDISPLAYA_H
#define EDITOR_TESTDISPLAYA_H

#include "IDisplay.h"
#include <imgui.h>

namespace EDITOR
{
    class TestDisplayA : public IDisplay
    {
    public:
        TestDisplayA();
        ~TestDisplayA() = default;

        virtual void Render() override;
    };
} // namespace EDITOR

#endif //EDITOR_TESTDISPLAYA_H
