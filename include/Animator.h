#pragma once
#include "SDL_include.h"
#include "Component.h"
#include "Animation.h"
#include "GameObject.h"
#include <unordered_map>
#include <string>

class Animator : public Component{
    public:
        Animator(GameObject& associated);

        void Update(float dt);
        void Render();

        void SetAnimation(std::string name);

        void AddAnimation(std::string name,
                Animation anim);

    private:
        std::unordered_map<std::string, Animation> animations;

        int frameStart;
        int frameEnd;
        float frameTime;
        int currentFrame;
        float timeElapsed;
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
