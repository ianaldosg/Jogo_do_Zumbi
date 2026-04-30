#include "../include/Sound.h"
#include "../include/Resources.h"

Sound::Sound() {
    chunk = nullptr;
}

Sound::Sound(std::string file) : Sound() {
    Open(file);
}

void Sound::Play(int times) {
    if (chunk != nullptr) {
        channel = Mix_PlayChannel(-1, chunk, times -1);
    }
}

void Sound::Stop() {
    if (chunk != nullptr && channel != -1) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);

    if (chunk == nullptr) {
        printf("Erro ao carregar som: %s\n", Mix_GetError());
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Stop();
        Mix_FreeChunk(chunk);
    }
}
