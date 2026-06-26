#pragma once

#include "State.h"
#include "Sprite.h"
#include "GameObject.h"

class TitleState : public State {
    public:
        TitleState();
        ~TitleState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};
