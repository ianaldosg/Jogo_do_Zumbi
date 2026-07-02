#include "../include/EndState.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/TitleState.h"
#include "../include/SpriteRenderer.h"
#include "../include/Text.h"
#include "../include/GameData.h"
#include "../include/StageState.h"

EndState::EndState() {
    // Imagem e Som de Derrota/Vitória
    GameObject* bgGo = new GameObject();

    if (GameData::playerVictory) {
        bgGo->AddComponent(new SpriteRenderer(*bgGo, "Recursos/img/Win.png"));
        backgroundMusic.Open("Recursos/audio/endStateWin.ogg");
    } else {
        bgGo->AddComponent(new SpriteRenderer(*bgGo, "Recursos/img/Lose.png"));
        backgroundMusic.Open("Recursos/audio/endStateLose.ogg");
    }
    AddObject(bgGo);

    // Instrução na tela
    GameObject* instructionGo = new GameObject();
    SDL_Color white = {255, 255, 255, 255};
    instructionGo->AddComponent(new Text(*instructionGo,
                "Recursos/font/neodgm.ttf", 24, Text::BLENDED,
                "ESC para sair ou ESPACO para tentar novamente", white));
    instructionGo->box.x = 330;
    instructionGo->box.y = 750;
    AddObject(instructionGo);
}

EndState::~EndState() {}

void EndState::LoadAssets() {}

void EndState::Start() {
    backgroundMusic.Play(-1);
    StartArray();
}

void EndState::Pause() {}

void EndState::Resume() {}

void EndState::Render() {
    RenderArray();
}

void EndState::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.QuitRequested()) {
        quitRequested = true;
    }
    
    // ESC volta pro Menu
    if (input.KeyPress(ESCAPE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }

    // Espaço Inicia StageState
    if (input.KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }

    UpdateArray(dt);

}
