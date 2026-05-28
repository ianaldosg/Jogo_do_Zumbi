#include "../include/State.h"
//#include "../include/SpriteRenderer.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Character.h"

State::State() : quitRequested(false) {
    LoadAssets();

    //Criando TileMap
    GameObject* mapObject = new GameObject();

    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");

    TileMap* tileMap = new TileMap(*mapObject, "Recursos/map/map.txt", tileSet);

    //Setando Camadas Parallax
    tileMap->SetParallax(0, 0.2f);
    tileMap->SetParallax(1, 1.0f);
    //tileMap->SetParallax(2, 0.2f);

    mapObject-> AddComponent(tileMap);

    mapObject->box.x = 0;
    mapObject->box.y = 0;

    AddObject(mapObject);

    //Criando Musica
    music.Play(-1);
    
    // Criando Player
    GameObject* playerGo = new GameObject();
    Character* ch = new Character(*playerGo, "Recursos/img/Player.png");
    playerGo->AddComponent(ch);

    // Ponteiro estático
    Character::player = ch;

    // Posiciona Player no centro do mapa
    playerGo->box.x = 1280;
    playerGo->box.y = 1280;

    // Estado
    AddObject(playerGo);

    // Foco da Camera no Player
    Camera::Follow(playerGo);
    
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

    //Camera Update
    Camera::Update(dt);

    //Criando Zumbi
    if (input.KeyPress(SDLK_SPACE)) {
        GameObject* zombieGO = new GameObject();

        Zombie* zombie = new Zombie(*zombieGO);
        zombieGO->AddComponent(zombie);

        zombieGO->box.x = input.GetMouseX() + Camera::pos.x - (zombieGO->box.w /2);
        zombieGO->box.y = input.GetMouseY() + Camera::pos.y - (zombieGO->box.h /2);

        AddObject(zombieGO);
    }

    //Atualiza Objetos
    for (std::size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    //Remoção de Objetos Motos
    for (int i = objectArray.size() - 1; i >= 0; i--){
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render(){
    for (auto& obj : objectArray) {
        obj->Render();
    }
}

void State::Start() {
    LoadAssets();
    for (auto& go : objectArray) {
        go->Start();
    }
    started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> sharedGo(go);
    objectArray.push_back(sharedGo);
    if (started) {
        sharedGo->Start();
    }
    return std::weak_ptr<GameObject>(sharedGo);
}

std::weak_ptr<GameObject> State::GameObjectPtr(GameObject* go) {
    for (auto& sharedGo : objectArray) {
        if (sharedGo.get() == go) {
            return std::weak_ptr<GameObject>(sharedGo);
        }
    }
    return std::weak_ptr<GameObject>();
}

bool State::QuitRequested(){
    return quitRequested;
}
