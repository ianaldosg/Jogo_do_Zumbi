#include "../include/PlayerController.h"
#include "../include/InputManager.h"
#include "../include/Character.h"
#include "../include/Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Start() {}

void PlayerController::Render() {}

void PlayerController::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    Character* character = associated.GetComponent<Character>();
    if (!character) return;

    Vec2 dir(0,0);

    if (input.IsKeyDown(SDLK_w)) dir.y -= 1;
    if (input.IsKeyDown(SDLK_s)) dir.y += 1;
    if (input.IsKeyDown(SDLK_a)) dir.x -= 1;
    if (input.IsKeyDown(SDLK_d)) dir.x += 1;

    // Movimentação
    if (dir.x != 0 || dir.y != 0) {
        Vec2 currentPos(associated.box.x, associated.box.y);
        Vec2 target = currentPos + dir.Normalizar() * 10.0f;

        character->Issue(Character::Command(Character::Command::MOVE, target.x, target.y));
    }

    // Posição Mouse
    Vec2 mousePos(input.GetMouseX(), input.GetMouseY());
    Vec2 worldPos = mousePos + Camera::pos;

    // Atirar
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        character->Issue(Character::Command(Character::Command::SHOOT, worldPos.x, worldPos.y));
    }
}
