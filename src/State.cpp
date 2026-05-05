#include "../include/State.h"
#include "../include/SpriteRenderer.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"

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

    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    //Criando Zumbi
    if (input.KeyPress(SDLK_SPACE)) {
        GameObject* zombieGO = new GameObject();

        Zombie* zombie = new Zombie(*zombieGO);
        zombieGO->AddComponent(zombie);

        zombieGO->box.x = input.GetMouseX();
        zombieGO->box.y = input.GetMouseY();

        AddObject(zombieGO);
    }

    //Atualiza Objetos
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (int i = objectArray.size() - 1; i >= 0; i--){
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
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
