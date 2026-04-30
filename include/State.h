#define INCLUDE_SDL

#pragma once
#include "SDL_include.h"
#include "Music.h"
#include "GameObject.h"
#include "Zombie.h"
#include "TileMap.h"
#include <vector>
#include <memory>

class State {
public:
    State();
    ~State();

    void LoadAssets();

    void Update(float dt);
    void Render(); 

    void AddObject(GameObject* go);

    bool QuitRequested();

private:
    Sprite bg;
    Music music;
    std::vector<std::unique_ptr<GameObject>> objectArray;

    bool quitRequested;
};
