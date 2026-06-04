#pragma once
#define INCLUDE_SDL

#include "SDL_include.h"
#include "Vec2.h"
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

    void Render(int x, int y, float angle = 0.0f);
    void Render(int x, int y,int w, int h, float angle = 0.0f);

    int GetWidth();
    int GetHeight();

    void SetFrame(int Frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    bool IsOpen();

    void SetCameraFollower(bool cameraFollower);

    void SetParallax(float factor);

    SDL_Texture* GetTexture() {return texture;}

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();

    void SetFlip(SDL_RendererFlip flip);

private:
    SDL_Texture* texture;
    SDL_Rect clipRect;

    int width;
    int height;

    int frameCountW;
    int frameCountH;

    bool cameraFollower;

    float parallaxFactor;

    SDL_RendererFlip flip;

    Vec2 scale;
};
