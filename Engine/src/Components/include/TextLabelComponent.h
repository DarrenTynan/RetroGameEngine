//
// Created by Darren Tynan on 19/01/2023.
//

#ifndef RETRO_ENGINE_TEXTLABELCOMPONENT_H
#define RETRO_ENGINE_TEXTLABELCOMPONENT_H

#include <glm/glm.hpp>
#include <string>
#include <SDL2/SDL.h>

namespace RGE_Component
{

struct TextLabelComponent
{
    glm::vec2 position;
    std::string text;
    std::string assetId;
    SDL_Color color;
    bool isFixed;

    /**
     *
     * @param position
     * @param text
     * @param assetId
     * @param color
     * @param isFixed
     */
    TextLabelComponent(glm::vec2 position = glm::vec2(200,5), const std::string& text = "Text label", const std::string& assetId = "arial-font", const SDL_Color& color = {255,255,255}, bool isFixed = true) {
        this->position = position;
        this->text = text;
        this->assetId = assetId;
        this->color = color;
        this->isFixed = isFixed;
    }
};

} // end namespace
#endif //RETRO_ENGINE_TEXTLABELCOMPONENT_H
