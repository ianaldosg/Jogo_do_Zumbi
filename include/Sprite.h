#pragma once
#define INCLUDE_SDL

#include "SDL_include.h"
#include <string>

class Sprite{
public:
    Sprite();
    Sprite(std::string file,
            int frameCountW = 1,
            int frameCountH = 1);
    ~Sprite();

    void Open(std::string file);

    void SetClip(int x, int y, int w, int h);

    void Render(int x, int y, int w, int h);

    int GetWidth();
    int GetHeight();

    void SetFrame(int Frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    bool IsOpen();

private:
    SDL_Texture* texture;
    SDL_Rect clipRect;

    int width;
    int height;

    int frameCountW;
    int frameCountH;
};
