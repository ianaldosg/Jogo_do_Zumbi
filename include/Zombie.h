#include "SDL_include.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Animator.h"

class Zombie : public Component{
    public:
        Zombie(GameObject& associated);

        void Damage(int damage);

        void Update(float dt);
        void Render();

    private:
        int hitpoins;
};

