#include "../include/State.h"

State::State() : bg(), quitRequested(false) {
}

void State::LoadAssets(){
    bg.Open("../Recursos/img/Background.png");
}

void State::Update(float dt){
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render(){
    bg.Render(0,0);
}

bool State::QuitRequested(){
    return quitRequested;
}
