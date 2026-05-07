#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
    if (instance == nullptr){
        instance = new Game("Ian Aldo SerwY Gonzale 242039176",1200,900);
    }
    return *instance;
}

Game::Game(std::string title, int width, int height) {
    
    frameStart = SDL_GetTicks();
    dt = 0;

    if (instance != nullptr){
        std::cout << "Erro: Game já instaciado!" << std::endl;
        exit(1);
    }

    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << "Erro SDL_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Erro IMG_Init: " << IMG_GetError() << std::endl;
        exit(1);
    }

    int mixFlags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD;

    if (!(Mix_Init(mixFlags) & mixFlags)) {
        std::cout << "Erro Mix_Init: " << Mix_GetError() << std::endl;
        exit(1);
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cout << "Erro Mix_OpenAudio: " << Mix_GetError() << std::endl;
        exit(1);
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, 
        height, 
        0
    );
    if (window == nullptr) {
        std::cout << "Erro SDL_CreateWindow: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );
    if (renderer == nullptr) {
        std::cout << "Erro SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(1);
    }

    state = new State();

}

void Game::CalculateDeltaTime(){
    int currentTime = SDL_GetTicks();

    dt = (currentTime - frameStart) / 1000.0f;

    frameStart = currentTime;
}

float Game::GetDeltaTime(){
    return dt;
}

Game::~Game(){
    delete state;

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    Mix_CloseAudio();

    Mix_Quit();

    IMG_Quit();

    SDL_Quit();

    std::cout << "Jogo Encerrado!" << std::endl;
}


State& Game::GetState(){
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run(){

    while (!state->QuitRequested()){
        CalculateDeltaTime();

        InputManager::GetInstance().Update();

        state->Update(0);

        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    Resources::ClearImages();
    Resources::ClearMusic();
    Resources::ClearSounds();
}


