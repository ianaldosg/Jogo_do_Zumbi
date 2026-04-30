#include "../include/State.h"

State::State() : quitRequested(false) {
    LoadAssets();

    //Criando Imagem
    GameObject* bg = new GameObject();
    bg->AddComponent(
            new SpriteRenderer(*bg, "Recursos/img/Background.png")
                );
    AddObject(bg);

    //Criando Musica
    music.Play(-1);

    //Criando Zumbi
    GameObject* zombie = new GameObject();
    
    zombie->box.x = 600;
    zombie->box.y = 450;

    zombie->AddComponent(new Zombie(*zombie));

    AddObject(zombie);

    //Criando TileMap
    GameObject* mapObject = new GameObject();

    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");

    TileMap* tileMap = new TileMap(*mapObject, "Recursos/map/map.txt", tileSet);

    mapObject-> AddComponent(tileMap);

    mapObject->box.x = 0;
    mapObject->box.y = 0;

    AddObject(mapObject);
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
    //bg.Render(0,0);
    
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
