#include "SDL_include.h"

class Vec2{
public:
    float x,y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2& v);
    Vec2 operator-(const Vec2& v);
    Vec2 operator*(float esacalar);

    float Magnitude();
    Vec2 Normalizar();
};
