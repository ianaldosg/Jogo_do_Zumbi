#pragma once
#include "SDL_include.h"
#include "Component.h" 
#include "Vec2.h"
#include "Character.h"

class Bullet : public Component{
    public:
        Bullet (GameObject& associated,
                float angle,
                float speed,
                int damage,
                float maxDistance,
                Character* shooter);

        void Update(float dt);
        void Render();
        
        int GetDamage();

        bool targetsPlayer;

        void NotifyCollision(GameObject& other); 

    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};
