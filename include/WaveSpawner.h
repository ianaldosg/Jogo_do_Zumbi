#pragma once
#include "SDL_include.h"
#include "GameObject.h"
#include "Component.h"
#include "Wave.h"
#include "Timer.h"
#include <vector>
#include <cmath>
#include <cstdlib>
    
class WaveSpawner : public Component{
    public:
        WaveSpawner(GameObject& associated);
        void Update(float dt);
        void Render();

    private:
        int zombieCounter;
        std::vector<Wave> waves;
        Timer zombieCooldownTimer;
        int currentWave;
};
