#include "../include/Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0){}

Vec2::Vec2(float x, float y): x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& v) const{
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const{
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(float escalar) const{
    return Vec2(x * escalar, y * escalar);
}

float Vec2::Magnitude() const{
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::Normalizar() const {
    float mag = Magnitude();
    if (mag == 0) return Vec2(0,0);
    return Vec2(x/mag, y/mag);
}

float Vec2::Distancia(const Vec2& v) const{
    return (*this - v).Magnitude();
}

float Vec2::Angulo() const{
    return atan2(y, x);
}

float Vec2::Angulo(const Vec2& v) const{
    Vec2 diferença = v - *this;
    return atan2(diferença.y, diferença.x);
}

Vec2 Vec2::Rotacao(float angulo) const{
    float cosA = cos(angulo);
    float sinA = sin(angulo);

    return Vec2(
            x * cosA - y * sinA,
            y * cosA + x * sinA
            );
}

Vec2& Vec2::operator+=(const Vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}
