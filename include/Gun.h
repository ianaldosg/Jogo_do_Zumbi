#pragma once
#include "SDL_include.h"
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include "Sound.h"
#include <memory>

class Gun : public Component {
    public:
        Gun (GameObject& associated, std::weak_ptr<GameObject>);
        
        void Update(float dt);
        void Render();
        void Shoot(Vec2 target);

    private:
        Sound shotSound;
        Sound reloadSound;
        int cooldownState;
        Timer cdTimer;
        std::weak_ptr<GameObject> character;
        float angle;

};
