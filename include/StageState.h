#define INCLUDE_SDL

#pragma once
#include "SDL_include.h"
#include "State.h"
#include "Music.h"
#include "GameObject.h"
#include "Zombie.h"
#include "TileMap.h"
#include <vector>
#include <memory>

class StageState : public State {
public:
    StageState();
    ~StageState();


    void LoadAssets();
    void Update(float dt);
    void Render(); 

    void Start();
    void Pause();
    void Resume();

private:
    TileSet* tileSet;
    Sprite bg;
    Music music;
};
