#include "../include/Wave.h"
#include "../include/WaveSpawner.h"
#include "../include/Camera.h"
#include "../include/GameObject.h"
#include "../include/Zombie.h"
#include "../include/NPC.h"
#include "../include/Game.h"

WaveSpawner::WaveSpawner(GameObject& associated) 
    : Component(associated), 
      zombieCounter(0),
      npcCounter(0),
      currentWave(0) {
    // Waves
    waves.emplace_back(5, 1, 2.0f); 
    waves.emplace_back(8, 3, 1.5f); 
    waves.emplace_back(12, 5, 1.0f); 
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);
    npcCooldownTimer.Update(dt);

    Wave& wave = waves[currentWave];

    // Gerenciador de Zombies
    if (zombieCounter < wave.zombies) {
        if (zombieCooldownTimer.Get() > wave.cooldown) {
            // Posiciona fora da tela aleatóriamente
            Vec2 pos = GetRandomSpawnPosition();
            // Cria Zombie
            GameObject* zombieGo = new GameObject();
            zombieGo->box.x = pos.x;
            zombieGo->box.y = pos.y;
            zombieGo->AddComponent(new Zombie(*zombieGo));
            Game::GetInstance().GetState().AddObject(zombieGo);

            zombieCounter ++;
            zombieCooldownTimer.Restart();
        }
    } 

    // Gerenciador de NPC's
    if (npcCounter < wave.npcs) {
        if (npcCooldownTimer.Get() > wave.cooldown) {
            // Posiciona fora da tela aleatóriamente
            Vec2 pos = GetRandomSpawnPosition();
            // Cria NPC
            GameObject* npcGo = new GameObject();
            npcGo->box.x = pos.x;
            npcGo->box.y = pos.y;
            npcGo->AddComponent(new NPC(*npcGo, "Recursos/img/NPC.png"));
            Game::GetInstance().GetState().AddObject(npcGo);

            npcCounter++;
            npcCooldownTimer.Restart();
        }
    } 

    // Controlador de Fim de Wave
    if (zombieCounter >= wave.zombies && npcCounter >= wave.npcs) {
        if (Zombie::count == 0 && NPC::count == 0) {
            currentWave++;
            zombieCounter = 0;
            npcCounter = 0;

            // Reset Timer
            zombieCooldownTimer.Restart();
            npcCooldownTimer.Restart();

            // Acabaram Waves
            if (currentWave >= (int)waves.size()) {
                associated.RequestDelete();
            }
        }
    }
}

void WaveSpawner::Render() {}

Vec2 WaveSpawner::GetRandomSpawnPosition() {
    float angle = (rand() % 360) * M_PI / 180.0f;
    float distance = 1200.0f;
    return Vec2 (
        Camera::pos.x + distance * (float)cos(angle),
        Camera::pos.y + distance * (float)sin(angle)
        );
}
