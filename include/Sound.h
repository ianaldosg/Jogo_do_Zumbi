#pragma once
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <string>
#include <memory>

class Sound{
    public:
        Sound();
        Sound(std::string file);
        ~Sound();

        void Play(int times = 1);
        void Stop();

        void Open(std::string file);
        bool IsOpen();

    private:
        std::shared_ptr<Mix_Chunk> chunk;
        int channel;
};
