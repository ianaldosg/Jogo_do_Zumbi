#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component{
    public:
        Zombie(GameObject& associated);

        void Damage(int damage);

        Timer hitTimer;
        Timer deathTimer;

        bool hit;
        bool dead;

        void Update(float dt);
        void Render();

        Sound deathSound;
        Sound hitSound;

    private:
        int hitpoins;
};

