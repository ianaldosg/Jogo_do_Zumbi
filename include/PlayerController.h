#pragma once
#include "SDL_include.h"
#include "Component.h"

class PlayerController : public Component {
    public:
        PlayerController(GameObject& associated);
        void Start();
        void Update(float dt);
        void Render();
};
