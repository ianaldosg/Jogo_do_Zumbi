#include "../include/Music.h"

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    Open(file);
}

void Music::Play(int times){
    if (music == nullptr) {
        std::cout << " Erro: musica não carregada!" << std::endl;
    }
    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        std::cout << "Erro ao abrir musica: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen(){
    return music != nullptr;
}

Music::~Music(){
    if (music != nullptr) {
        Stop(0);
        Mix_FreeMusic(music);
        music = nullptr;
    }
}
