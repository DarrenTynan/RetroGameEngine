//
// Created by Darren Tynan on 14/01/2025.
//

#ifndef EDITOR_SCENEDISPLAY_H
#define EDITOR_SCENEDISPLAY_H

#include "IDisplay.h"
#include <imgui.h>

namespace EDITOR
{
    class SceneDisplay : public IDisplay
    {
    public:
        SceneDisplay();
        ~SceneDisplay() = default;

        virtual void Render() override;
    };
} // namespace EDITOR

#endif //EDITOR_SCENEDISPLAY_H
