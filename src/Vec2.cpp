#include "../include/Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0){}

Vec2::Vec2(float x, float y): x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& v){
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v){
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(float escalar){
    return Vec2(x * escalar, y * escalar);
}

float Vec2::Magnitude(){
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::Normalizar() {
    float mag = Magnitude();
    if (mag == 0) return Vec2(0,0);
    return Vec2(x/mag, y/mag);
}
