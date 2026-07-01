#include "../include/TitleState.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/StageState.h"
#include "../include/SpriteRenderer.h"
#include "../include/Camera.h"

TitleState::TitleState() : State() {
    // Título
    GameObject* titleGo = new GameObject();
    titleGo->AddComponent(new SpriteRenderer(*titleGo, "Recursos/img/Title.png"));
    AddObject(titleGo);

    // Text
    GameObject* promptGo = new GameObject();
    SDL_Color white = {255, 255, 255, 255};
    Text* text = new Text(*promptGo, "Recursos/font/neodgm.ttf", 28,
                        Text::BLENDED, "Pressione espaco para continuar", white);
    promptGo->AddComponent(text);
    promptGo->box.x = 380;
    promptGo->box.y = 750;
    promptText = text;
    AddObject(promptGo);

    showPrompt = true;
    blinkTimer.Restart();
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

    blinkTimer.Update(dt);

    // ESC ou Fechar janela Game morre
    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    // Espaço Inicia StageState
    if (input.KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }

    // Pisca pisca Text
    if (blinkTimer.Get() > 0.5f) {
        showPrompt = !showPrompt;
        promptText->SetText(showPrompt ? "Pressione espaco para continuar" : "");
        blinkTimer.Restart();
    }
    
    UpdateArray(dt);
}

void TitleState::Render() {
    RenderArray();
}
