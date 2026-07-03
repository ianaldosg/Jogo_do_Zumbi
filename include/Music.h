#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <iostream>
#include <string>
#include <memory>

class Music{
public:
    Music();
    Music(std::string file);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen();

private:
    std::shared_ptr<Mix_Music> music;
};
