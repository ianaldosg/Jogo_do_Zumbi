#pragma once
#include "SDL_include.h"

class Animation{
    public:
        Animation();
        Animation(int frameStart,
                int frameEnd,
                float frameTime);

        int frameStart;
        int frameEnd;
        float frameTime;
};
