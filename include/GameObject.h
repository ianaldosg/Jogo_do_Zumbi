#pragma once
#include "SDL_include.h"
#include <vector>
#include "Component.h"
#include "Rect.h"

class GameObject{
    public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();

        bool IsDead() const;

        void RequestDelete();

        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);

        template <typename T>
        T* GetComponent();

        Rect box;

    private:
        std::vector<Component*> components;
        bool isDead;
};
