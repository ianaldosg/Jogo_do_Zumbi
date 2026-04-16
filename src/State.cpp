#include "../include/State.h"

State::State() : quitRequested(false) {
    LoadAssets();

    GameObject* bg = new GameObject();
    AddObject(bg);

    music.Play(-1);
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets(){
    bg.Open("Recursos/img/Background.png");
    music.Open("Recursos/audio/BGM.wav");
}

void State::Update(float dt){
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (int i = objectArray.size() - 1; i >= 0; i--){
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }

    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render(){
    bg.Render(0,0);
    
    for (auto& obj : objectArray) {
        obj->Render();
    }
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}

bool State::QuitRequested(){
    return quitRequested;
}
