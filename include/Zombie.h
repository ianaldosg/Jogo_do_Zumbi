#pragma once
#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component{
    public:
        Zombie(GameObject& associated);

        ~Zombie();

        void Damage(int damage);

        Timer hitTimer;
        Timer deathTimer;


        void Update(float dt);
        void Render();

        Sound hitSound;
        Sound deathSound;

        void NotifyCollision(GameObject& other);

        static int count;

    private:
        int hitpoins;
        bool hit;
        bool left;
        bool dead;
};

