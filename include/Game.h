#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <memory>

class Game {
public:
    ~Game();


    static Game& GetInstance(); 
    static Game& GetInstance(std::string title, int width, int height);
    State& GetCurrentState();

    void Push(State* state);

    void Run();

    float GetDeltaTime();

    SDL_Renderer* GetRenderer();

    // Proteção contra copy de Game
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
private:
    Game(std::string title, int width, int height);

    void CalculateDeltaTime();
    float dt;

    static Game* instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::stack<std::unique_ptr<State>> stateStack;

    int frameStart;
};
