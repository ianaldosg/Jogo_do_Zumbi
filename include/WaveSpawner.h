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

        static WaveSpawner* spawner;

        bool IsDone() const { return wavesDone;}

    private:
        std::vector<Wave> waves;

        int zombieCounter;
        Timer zombieCooldownTimer;

        int npcCounter;
        Timer npcCooldownTimer;

        int currentWave;

        Vec2 GetRandomSpawnPosition();

        bool wavesDone = false;

};
