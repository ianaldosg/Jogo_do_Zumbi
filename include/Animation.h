#pragma once
#include "SDL_include.h"

class Animation{
    public:
        Animation(int frameStart,
                int frameEnd,
                float frameTime);

    private:
        int frameStart;
        int frameEnd;
        float frameTime;
};
