//
// Created by Darren Tynan on 18/01/2025.
//

#include "DebugDisplay.h"

namespace EDITOR
{
    std::shared_ptr<DebugDisplay> DebugDisplay::instancePtr = nullptr;

    void DebugDisplay::TestLog()
    {
        std::cout << "TestLog from DebugDisplay instance" << std::endl;
    }

    void Draw() {};
    void Update() {}


} // namespace end