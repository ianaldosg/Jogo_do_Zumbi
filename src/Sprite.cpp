#include "../include/Sprite.h"
#include "../include/Game.h"

Sprite::Sprite() 
    : texture(nullptr), 
    width(0), 
    height(0), 
    frameCountW(1),
    frameCountH(1) {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) 
    : texture(nullptr), frameCountW(frameCountW), frameCountH(frameCountH) {
    Open(file);
}

Sprite::~Sprite(){
    if (texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file){
    if (texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()); 

    if (texture == nullptr) {
        std::cout << "Erro ao carregar texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width / frameCountW, height / frameCountH);

    SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h){
    SDL_Rect dstrect;

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = w;
    dstrect.h = h;

    SDL_RenderCopy(
        Game::GetInstance().GetRenderer(), 
        texture,
        &clipRect, 
        &dstrect
    );
}

int Sprite::GetWidth(){
    return width / frameCountW;
}

int Sprite::GetHeight(){
    return height / frameCountH;
}

void Sprite::SetFrame(int frame) {
    int frameWidth = width / frameCountW;
    int frameHeight = height / frameCountH;

    int frameX = frame % frameCountW;
    int frameY = frame / frameCountW;

    int x = frameX * frameWidth;
    int y = frameY * frameHeight;

    if (x + frameWidth > width || y + frameHeight > height) {
        return;
    }

    SetClip(x, y, frameWidth, frameHeight);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;

    int frameWidth = width / frameCountW;
    int frameHeight = height / frameCountH;
     
    SetClip(0, 0, frameWidth, frameHeight);
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}
