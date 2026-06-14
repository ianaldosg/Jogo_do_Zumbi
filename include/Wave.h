#pragma once
#include "SDL_include.h"

class Wave {
    public:
        Wave(int zombies, float cooldown);
        int zombies;
        float cooldown;
};

