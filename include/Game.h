#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.h"
#include <iostream>
#include <string>

class Game {
private:
    Game(std::string title, int width, int height);
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

public:
    static Game& GetInstance(std::string title, int width, int height); 
    ~Game();
    State& GetState();
    SDL_Renderer* GetRenderer();
    void Run();
};
