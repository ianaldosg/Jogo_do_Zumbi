#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

class GameObject;

class AIController : public Component{
    public:
        AIController(GameObject& associated);

        void Update(float dt);
        void Render();

    private:
        enum AIState { MOVING, RESTING };

        AIState state;
        Timer restTimer;
        Vec2 destination;
};
