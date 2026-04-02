#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "../include/Game.h"

Game* Game::instance = nullptr;

Game::Game() {
    std::cout << "Jogo inicializado." << std::endl;
}
Game& Game::GetInstance(){
    if (instance == nullptr){
        instance = new Game();
    }
    return *instance;
}

