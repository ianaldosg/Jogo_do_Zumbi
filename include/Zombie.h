#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

class Zombie : public Component{
    public:
        Zombie(GameObject& associated);

        void Damage(int damage);

        void Update(float dt);
        void Render();

        Sound deathSound;

    private:
        int hitpoins;
};

