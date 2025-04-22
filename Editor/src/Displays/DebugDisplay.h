//
// Created by Darren Tynan on 18/01/2025.
//

#ifndef EDITOR_DEBUGDISPLAY_H
#define EDITOR_DEBUGDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include <iostream>
#include <mutex>
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR
{
    class DebugDisplay : public IDisplay
    {

    private:
        // Private constructor
        DebugDisplay() {};

        // Disable copy constructor and assignment operator
        DebugDisplay(const DebugDisplay&) = delete;
        DebugDisplay& operator=(const DebugDisplay&) = delete;

        // Private static instance
        static std::shared_ptr<DebugDisplay> instancePtr;

    public:
        // Public static method to get the instance
        static std::shared_ptr<DebugDisplay> GetInstance()
        {
            if (!DebugDisplay::instancePtr)
            {
                DebugDisplay::instancePtr = std::shared_ptr<DebugDisplay>();
            }
            return DebugDisplay::instancePtr;
        }

        void TestLog();

        void Render(std::shared_ptr<Registry>& registry) override;
        void Update() override {}

    };


} // end namespace

#endif //EDITOR_DEBUGDISPLAY_H
