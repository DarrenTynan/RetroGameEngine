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

namespace RGE_Component
{
    /**
      * @brief A small struct to hold the vars for the animation frames.
      */
    struct FramePointers
    {
        std::string textureAssetID;
        int width;
        int height;
        int z_index;
        bool fixed;
        int srcRectX;
        int srcRectY;
        int numFrames;
        int frameSpeedRate;
        bool isLoop;

    explicit FramePointers( std::string _textureAssetID, int _width, int _height, int _z_index, bool _fixed, int _srcRectX, int _srcRectY, int _numFrames, int _frameSpeedRate, bool _isLoop )
    {
        this->textureAssetID = _textureAssetID;
        this->width = _width;
        this->height = _height;
        this->z_index = _z_index;
        this->fixed = _fixed;
        this->srcRectX = _srcRectX;
        this->srcRectY = _srcRectY;
        this->numFrames = _numFrames;
        this->frameSpeedRate = _frameSpeedRate;
        this->isLoop = _isLoop;
    }

    };

    struct SpritesheetComponent
    {
        // Pointer to hold the instance.
        std::vector<std::shared_ptr<FramePointers>> m_pointers;

        // Look-up table.
        std::map<std::string, std::shared_ptr<FramePointers>> states;

        SpritesheetComponent() {}

        void AddToSheet( int _index, std::string _textureAssetID, int _width, int _height, int _z_index, bool _fixed, int _srcRectX, int _srcRectY, int _numFrames, int _frameSpeedRate, bool _isLoop )
        {
            m_pointers.push_back(std::make_shared<FramePointers>(_textureAssetID, _width, _height, _z_index, _fixed, _srcRectX, _srcRectY, _numFrames, _frameSpeedRate, _isLoop));
            states.insert(make_pair(_textureAssetID, m_pointers[_index]));

        }

    };

} // end namespace

#endif //RETROGAMEENGINE_SPRITESHEETCOMPONENT_H
