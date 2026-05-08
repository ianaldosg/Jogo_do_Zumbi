#include "../include/Camera.h"
#include "../include/InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

GameObject* Camera::GetFocus(){
    return focus;
}

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if (focus != nullptr) {
        pos.x = focus->box.x + focus->box.w/2 - 600;
        pos.y = focus->box.y + focus->box.h/2 - 450;
    }
    else {
        speed.x = 0;
        speed.y = 0;
        
        InputManager& input = InputManager::GetInstance();

        if (input.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x -= 500;
        }

        if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x += 500;
        }
        
        if (input.IsKeyDown(UP_ARROW_KEY)) {
            speed.y -= 500;
        }

        if (input.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y += 500;
        }

        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    }
}
