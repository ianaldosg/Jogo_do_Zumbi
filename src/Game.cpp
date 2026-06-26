#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
    // Gerador aleatório
    srand(time(NULL));
    if (instance == nullptr){
        instance = new Game("Ian Aldo Serwy Gonzales 242039176",1200,900);
    }
    return *instance;
}

Game::Game(std::string title, int width, int height)  : storedState(nullptr) {

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
    if (storedState!= nullptr) {
        delete storedState;
        storedState = nullptr;
    }

    while (!stateStack.empty()) {
        stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearMusic();
    Resources::ClearSounds();

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


State& Game::GetCurrentState(){
    return *stateStack.top();
}

void Game::Push(State* state) {
    storedState = state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    // Estado Inicial
    if (storedState != nullptr) {
        stateStack.emplace(storedState);
        storedState = nullptr;
        stateStack.top()->Start();
    }

    // Loop de pilha vazia ou quit
    while (!stateStack.empty() && !stateStack.top()->QuitRequested()) {
        CalculateDeltaTime();

        // Gerenciamento de Pilha
        // Estado atual removido?
        if (stateStack.top()->PopRequested()) {
            stateStack.pop();
            if (!stateStack.empty()) {
                stateStack.top()->Resume();
            }
            continue;
        }

        // Novo Estado
        if (storedState != nullptr) {
            if (!stateStack.empty()) {
                stateStack.top()->Pause();
            }
            stateStack.emplace(storedState);
            storedState = nullptr;
            stateStack.top()->Start();
            continue;
        }

        // Loop normal do Game
        InputManager::GetInstance().Update();

        stateStack.top()->Update(dt);

        SDL_RenderClear(renderer);
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    // Limpa storedState residual
    if (storedState != nullptr) {
        delete storedState;
        storedState = nullptr;
    }

    // Esvazia Pilha antes de sair de Run
    while (!stateStack.empty()) {
        stateStack.pop();
    }
}
