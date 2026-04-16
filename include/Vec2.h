#include "SDL_include.h"

class Vec2{
public:
    float x,y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(float esacalar) const;

    float Magnitude() const;

    Vec2 Normalizar() const;

    float Distancia(const Vec2& v) const;

    float Angulo() const;
    float Angulo(const Vec2& v) const;

    Vec2 Rotacao(float angulo) const;
};
