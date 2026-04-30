#include "../include/Music.h"
#include "../include/Resources.h"

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
    music = Resources::GetMusic(file);

    if (music == nullptr) {
        printf("Erro ao carregar musica: %s\n", Mix_GetError());
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
