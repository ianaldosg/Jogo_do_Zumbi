#define INCLUDE_SDL

#pragma once
#include "SDL_include.h"
#include "Music.h"
#include "GameObject.h"
#include "Zombie.h"
#include "TileMap.h"
#include <vector>
#include <memory>

class StageState {
public:
    StageState();
    ~StageState();

    void LoadAssets();

    void Update(float dt);
    void Render(); 

    void Start();

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);



    bool QuitRequested();

private:
    Sprite bg;
    Music music;

    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;

    bool quitRequested;
};
