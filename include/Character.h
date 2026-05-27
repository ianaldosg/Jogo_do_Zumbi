#pragma once
#include "SDL_include.h"
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include <string>
#include <memory>
#include <queue>

class Character : public Component {
    public:
        static Character* player;

        Character(GameObject& associated, std::string sprite);
        ~Character();

        void Start();
        void Update(float dt);
        void Render();

        class Command{
            public:
                enum CommandType {MOVE, SHOOT };

                CommandType type;
                Vec2 pos;

                Command(CommandType type, float x, float y);
        };
        void Issue(Command task);

    private:
        std::weak_ptr<GameObject> gun;
        std::queue<Command> taskQueue;
        Vec2 speed;
        float linearSpeed;
        int hp;
        Timer deathTimer;

};
