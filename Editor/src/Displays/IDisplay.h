//
// Created by Darren Tynan on 11/01/2025.
//

#ifndef EDITOR_IDISPLAY_H
#define EDITOR_IDISPLAY_H

#include <vector>
#include <memory>
#include <typeindex>
#include <SDL_rect.h>
#include "../../Engine/src/ECS/include/ECS.h"

using namespace RGE_ECS;

namespace EDITOR_DISPLAY
{
    class IDisplay : public System
    {
    public:
        std::string name = "null";
        virtual ~IDisplay() = default;
        virtual void Render(std::shared_ptr<Registry>& registry) = 0;
        virtual void Update() {}

    protected:
        virtual void DrawToolbar() {}
    };


    struct DisplayHolder
    {
        std::vector<std::unique_ptr<IDisplay>> displays;
    };

}

#endif // EDITOR_IDISPLAY_H
