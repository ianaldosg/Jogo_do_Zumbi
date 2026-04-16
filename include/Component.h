#pragma once
#include "SDL_include.h"

class GameObject;

class Component{
    public:
        Component(GameObject& associated);
        virtual ~Component();

        virtual void Update(float dt) = 0;
        virtual void Render() = 0;

    protected:
        GameObject& associated;
};
