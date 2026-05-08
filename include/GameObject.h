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

        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);

        template <typename T>
        T* GetComponent();

        Rect box;

        bool IsDead() const;

    private:
        std::vector<Component*> components;
        bool isDead;
};
