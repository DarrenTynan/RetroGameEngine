//
// Created by Darren Tynan on 01/04/2025.
//

#ifndef RETROGAMEENGINE_SPRITESHEETCOMPONENT_H
#define RETROGAMEENGINE_SPRITESHEETCOMPONENT_H

#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sol.hpp>
#include <rapidjson/document.h>

namespace RGE_Component
{
    /**
      * @brief A small struct to hold the vars for the individual animation frames.
      */
    struct FramePointers
    {
        std::string textureAssetID;
        int width;
        int height;
        int z_index;
        bool isFixed;
        SDL_Rect srcRect;
        int numFrames;
        int fps;
        bool isLoop;

        void setSrcRect(const SDL_Rect &_srcRect)
        {
            FramePointers::srcRect = _srcRect;
        }


    /**
     *
     * @param _textureAssetID
     * @param _width
     * @param _height
     * @param _z_index
     * @param _fixed
     * @param _srcRectX
     * @param _srcRectY
     * @param _numFrames
     * @param _fps
     * @param _isLoop
     */
    explicit FramePointers( std::string _textureAssetID, int _width, int _height, int _z_index, bool _fixed, int _srcRectX, int _srcRectY, int _numFrames, int _frameSpeedRate, bool _isLoop )
    {
        this->textureAssetID = _textureAssetID;
        this->width = _width;
        this->height = _height;
        this->z_index = _z_index;
        this->isFixed = _fixed;
        this->srcRect = {_srcRectX, _srcRectY, _width, _height};
        this->numFrames = _numFrames;
        this->fps = _frameSpeedRate;
        this->isLoop = _isLoop;
    }

    };

    struct SpritesheetComponent
    {
        // Pointer to hold the instance.
        std::vector<std::shared_ptr<FramePointers>> m_pointers;

        // Look-up table.
        std::map<std::string, std::shared_ptr<FramePointers>> states;

        SpritesheetComponent() = default;

        void AddToSheet( int _index, const std::string& _textureAssetID, int _width, int _height, int _z_index, bool _fixed, int _srcRectX, int _srcRectY, int _numFrames, int _frameSpeedRate, bool _isLoop )
        {
            m_pointers.push_back(std::make_shared<FramePointers>(_textureAssetID, _width, _height, _z_index, _fixed, _srcRectX, _srcRectY, _numFrames, _frameSpeedRate, _isLoop));
            states.insert(make_pair(_textureAssetID, m_pointers[_index]));
            std::cout << "SpritesheetComponent" << std::endl;
        }


    };

} // end namespace

#endif //RETROGAMEENGINE_SPRITESHEETCOMPONENT_H
