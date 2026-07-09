#pragma once
#include "SDL_include.h"
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include "Sound.h"
#include <string>
#include <memory>
#include <queue>

class Character : public Component {
    public:
        static Character* player;

        Character(GameObject& associated, std::string sprite);
        virtual ~Character() override;

        void Start() override;
        void Update(float dt) override;
        void Render() override;

        class Command{
            public:
                enum CommandType {MOVE, SHOOT };

                CommandType type;
                Vec2 pos;

                Command(CommandType type, float x, float y);
        };

        void Issue(Command task);

        void NotifyCollision(GameObject& other) override;

        int GetHP();

        Vec2 GetCenter() const;

        bool IsCharacterDead() const { return dead; }
        
    private:
        std::weak_ptr<GameObject> gun;
        std::queue<Command> taskQueue;
        Vec2 speed;
        int hp;
        float linearSpeed;
        Timer deathTimer;
        Timer damageTimer;
        Sound hitSound;
        Sound deathSound;
        bool dead;

        // Funções de Refatoração
        void ProcessTasks();
        void UpdateAnimations();
        void HandleDeath();
        void WorldBorder();

};

class Zombie;
class Bullet;
