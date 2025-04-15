//
// Created by Darren Tynan on 15/01/2025.
//

#ifndef EDITOR_LOGDISPLAY_H
#define EDITOR_LOGDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>
#include <iostream>
#include "../../Editor/src/Logger/include/Logger.h"

namespace EDITOR
{
    class LogDisplay : public IDisplay
    {
    public:
        ~LogDisplay() override = default;

        void Render() override;
    };

} // end namespace
#endif //EDITOR_LOGDISPLAY_H
