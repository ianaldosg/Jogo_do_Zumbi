#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF

#include "Component.h"
#include "SDL_include.h"
#include <string>

class Text : public Component {
    public:
        enum TextStyle {SOLID, SHADED, BLENDED};

        Text(GameObject& associated, std::string fontFile,
             int fontSize, TextStyle style,
             std::string text, SDL_Color color);
        ~Text();

        void Update(float dt);
        void Render();

        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontfile(std::string fontFile);
        void SetFontSize(int fontSize);

    private:
        void RemakeTexture();

        TTF_Font* font;
        SDL_Texture* texture;

        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;
};
