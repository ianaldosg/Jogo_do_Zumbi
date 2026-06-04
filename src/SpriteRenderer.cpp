#include "../include/SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) 
    : Component(associated), sprite() {
        SetFrame(0);
    }

SpriteRenderer::SpriteRenderer(
        GameObject& associated,
        std::string file,
        int frameCountW,
        int frameCountH
        ) 
    : Component(associated), 
    sprite(file, frameCountW, frameCountH) {

    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();

    SetFrame(0);
    }

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);

    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();

    SetFrame(0);
}

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float dt) {
}

void SpriteRenderer::Render() {
    sprite.Render(
            associated.box.x,
            associated.box.y,
            associated.box.w,
            associated.box.h,
            associated.angleDeg
            );
}

void SpriteRenderer::SetCameraFollower(bool cameraFollower){
    sprite.SetCameraFollower(cameraFollower);
}

void SpriteRenderer::SetParallax(float factor){
    sprite.SetParallax(factor);
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    // Mantém centro e ajusta largura e altura
    sprite.SetScale(scaleX, scaleY);
    associated.box.w = sprite.GetWidth(); 
    associated.box.h = sprite.GetHeight(); 
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}
