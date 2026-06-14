#include "../include/Wave.h"
#include "../include/WaveSpawner.h"
#include "../include/Camera.h"
#include "../include/GameObject.h"
#include "../include/Zombie.h"
#include "../include/Game.h"

WaveSpawner::WaveSpawner(GameObject& associated) 
    : Component(associated), 
      zombieCounter(0),
      currentWave(0) {
    // Waves
    waves.emplace_back(5, 2.0f); 
    waves.emplace_back(8, 1.5f); 
    waves.emplace_back(12, 1.0f); 
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);

    Wave& wave = waves[currentWave];

    if (zombieCounter < wave.zombies) {
        if (zombieCooldownTimer.Get() > wave.cooldown) {
            // Posiciona fora da tela aleatóriamente
            float angle = (rand() % 360) * M_PI / 180.0f;
            float distance = 1200.0f;
            Vec2 pos = {
                Camera::pos.x + distance * (float)cos(angle),
                Camera::pos.y + distance * (float)sin(angle),
            };
            // Cria Zombie
            GameObject* zombieGo = new GameObject();
            zombieGo->box.x = pos.x;
            zombieGo->box.y = pos.y;
            zombieGo->AddComponent(new Zombie(*zombieGo));
            Game::GetInstance().GetState().AddObject(zombieGo);

            zombieCounter ++;
            zombieCooldownTimer.Restart();
        }
    } else {
        // Todos os Zombies spawnados, esperar morrer
        if (Zombie::count == 0) {
            currentWave++;
            zombieCounter = 0;

            if (currentWave >= (int)waves.size()) {
                // Acabaram as Waves
                associated.RequestDelete();
            }
        }
    }
}

void WaveSpawner::Render() {}
