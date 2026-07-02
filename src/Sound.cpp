#include "../include/Sound.h"
#include "../include/Resources.h"

Sound::Sound() : chunk(nullptr), channel(-1) {}

Sound::Sound(std::string file) : Sound() {
    Open(file);
}

void Sound::Play(int times) {
    if (chunk != nullptr) {
        channel = Mix_PlayChannel(-1, chunk, times -1);
    }

    if (channel != -1) {
        Mix_Volume(channel, 3);
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
        chunk = nullptr;
    }
}
