#pragma once
#include "SDL_include.h"
#include "Component.h"
#include "Rect.h"
#include <vector>

class GameObject{
    public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();

        void RequestDelete();

        void Start();
        bool started;

        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);

        template <typename T>
            T* GetComponent() {
                for (auto& component : components) {
                    T* casted = dynamic_cast<T*>(component);
                    if (casted != nullptr) {
                        return casted;
                    }
                }
                return nullptr;
            };

        Rect box;

        bool IsDead() const;

        double angleDeg;

        float sortY = -1;

    private:
        std::vector<Component*> components;
        bool isDead;
};
