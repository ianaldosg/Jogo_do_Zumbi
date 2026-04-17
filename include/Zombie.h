#include "SDL_include.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

class Zombie : public Component{
    public:
        Zombie(GameObject& associated);

        void Damage(int damage);

        void Update(float dt);
        void Render();

    private:
        int hitpoins;
};

template <typename T>
T* GameObject::GetComponent() {
    for (auto it = components.begin(); it != components.end(); ++it) {
        T* result = dynamic_cast<T*>(*it);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}
