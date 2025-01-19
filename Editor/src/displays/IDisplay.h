//
// Created by Darren Tynan on 11/01/2025.
//

//#ifndef EDITOR_DEBUG_H
//#define EDITOR_DEBUG_H
//
//#endif //EDITOR_DEBUG_H

#ifndef EDITOR_IDISPLAY_H
#define EDITOR_IDISPLAY_H

#include <vector>
#include <memory>
#include <typeindex>

namespace EDITOR
{
    class IDisplay
    {
    public:
        virtual ~IDisplay() = default;
        virtual void Draw() = 0;
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
