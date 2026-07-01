#include "../include/Text.h"
#include "../include/Resources.h"
#include "../include/Camera.h"
#include "../include/GameObject.h"
#include "../include/Game.h"

Text::Text(GameObject& associated, std::string fontFile,
             int fontSize, TextStyle style,
             std::string text, SDL_Color color)
    : Component(associated),
      font(nullptr),
      texture(nullptr),
      text(text),
      style(style),
      fontFile(fontFile),
      fontSize(fontSize),
      color(color) {
          RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {}

void Text::RemakeTexture() {
    // Destroi textura antiga
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    // Busca Fonte nova
    font = Resources::GetFont(fontFile, fontSize);
    if (font == nullptr) return;

    // Renderiza
    SDL_Surface* surface = nullptr;
    switch (style) {
        case SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        case SHADED: {
            SDL_Color bg = {0, 0, 0, 255};
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, bg);
            break;
                     }
        case BLENDED:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
    }

    if (surface == nullptr) return;

    // Converte Surface
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

    // Atualiza tamanho da box
    associated.box.w = surface->w;
    associated.box.h = surface->h;

    SDL_FreeSurface(surface);
}

void Text::Render() {
    if (texture == nullptr) return;

    SDL_Rect clipRect = {0, 0, (int)associated.box.w, (int)associated.box.h};

    SDL_Rect dstRect = {
        (int) (associated.box.x - Camera::pos.x),
        (int) (associated.box.y - Camera::pos.y),
        (int) associated.box.w,
        (int) associated.box.h
    };

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
                     texture, 
                     &clipRect, 
                     &dstRect, 
                     0, 
                     nullptr, 
                     SDL_FLIP_NONE);
}

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontfile(std::string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}
