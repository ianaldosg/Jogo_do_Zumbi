#include "../include/TitleState.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/StageState.h"
#include "../include/SpriteRenderer.h"
#include "../include/Camera.h"

TitleState::TitleState() : State() {
    GameObject* titleGo = new GameObject();
    titleGo->AddComponent(new SpriteRenderer(*titleGo, "Recursos/img/Title.png"));
    AddObject(titleGo);
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {}

void TitleState::Start() {
    // Camera fica Centralizada no Title
    Camera::Unfollow();
    Camera::pos = {0.0f, 0.0f};

    StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume() {
    Camera::Unfollow();
    Camera::pos = {0.0f, 0.0f};
}

void TitleState::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    // ESC ou Fechar janela Game morre
    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    // Espaço Inicia StageState
    if (input.KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }
    
    UpdateArray(dt);
}

void TitleState::Render() {
    RenderArray();
}
