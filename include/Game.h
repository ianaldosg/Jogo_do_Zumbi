#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#pragma once
#include "SDL_include.h"
#include "State.h"
#include <iostream>
#include <string>

class Game {
public:
    static Game& GetInstance(); 
    static Game& GetInstance(std::string title, int width, int height);

    float GetDeltaTime();

    State& GetState();

    SDL_Renderer* GetRenderer();

    ~Game();

    void Run();

private:
    Game(std::string title, int width, int height);

    static Game* instance;

    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    int frameStart;
    float dt;
    void CalculateDeltaTime();
};

