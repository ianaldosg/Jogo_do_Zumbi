#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Character.h"
#include "../include/PlayerController.h"
#include "../include/Collision.h"
#include "../include/Collider.h"
#include "../include/WaveSpawner.h"
#include <algorithm>
#include <vector>

State::State() : started(false), quitRequested(false) {}

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

    // Camera Update
    Camera::Update(dt);

    // Atualiza Objetos
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    // Loop Colisão
    for (size_t i = 0; i < objectArray.size(); i++) {
        for (size_t j = i + 1; j < objectArray.size(); j++) {
            auto& goA = *objectArray[i];
            auto& goB = *objectArray[j];

            auto* colA = (Collider*)goA.GetComponent<Collider>();
            auto* colB = (Collider*)goB.GetComponent<Collider>();

            if (colA == nullptr || colB == nullptr) continue;

            // Colisão?
            if (Collision::IsColliding(colA->box, colB->box, goA.angleDeg, goB.angleDeg)) {
                goA.NotifyCollision(goB);
                goB.NotifyCollision(goA);
            }
        }
    }

    // Remove quem Morreu
    size_t i = objectArray.size();
    while (i > 0) {
        i--;
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render(){
    std::vector<GameObject*> renderOrder;
    for (auto& obj : objectArray) {
        renderOrder.push_back(obj.get());
    }

    // Ordena pelo centro de Y da box
    std::sort(renderOrder.begin(), renderOrder.end(),
        [](GameObject* a, GameObject* b) {
            float ya = (a->sortY >= 0) ? a->sortY : (a->box.y + a->box.h / 2);
            float yb = (b->sortY >= 0) ? b->sortY : (b->box.y + b->box.h / 2);
            return ya < yb;
        });

    for (GameObject* obj : renderOrder) {
        obj->Render();
    }
}

void State::Start() {
    // Mídia Básica
    LoadAssets();

    //Criando TileMap
    GameObject* mapObject = new GameObject();

    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");

    TileMap* tileMap = new TileMap(*mapObject, "Recursos/map/map.txt", tileSet);

    //Setando Camadas Parallax
    tileMap->SetParallax(0, 0.2f);
    tileMap->SetParallax(1, 1.0f);

    mapObject-> AddComponent(tileMap);

    mapObject->box.x = 0;
    mapObject->box.y = 0;

    AddObject(mapObject);

    //Criando Musica
    music.Play(-1);
    
    // Criando Player
    GameObject* playerGo = new GameObject();
    playerGo->AddComponent(new Character(*playerGo, "Recursos/img/Player.png"));
    // PlayerController
    playerGo->AddComponent(new PlayerController(*playerGo));

    // Ponteiro estático
    Character::player = (Character*)playerGo->GetComponent<Character>();

    // Posiciona Player no centro do mapa
    playerGo->box.x = 1280;
    playerGo->box.y = 1280;

    // Estado
    AddObject(playerGo);

    // Foco da Camera no Player
    Camera::Follow(playerGo);

    // WaveSpawner
    GameObject* spawnerGo = new GameObject();
    spawnerGo->AddComponent(new WaveSpawner(*spawnerGo));
    AddObject(spawnerGo);

    // Roda tudo
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
