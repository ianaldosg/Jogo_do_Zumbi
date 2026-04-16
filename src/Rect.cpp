#include "../include/Rect.h"

Rect Rect::operator+(const Vec2& v) const {
    return Rect(x + v.x, y + v.y, w, h);
}

Vec2 Rect::GetCentroRect() const {
    return Vec2(x + w / 2, y + h / 2);
}

float Rect::DistanciaCentro(const Rect& other) const {
    return GetCentroRect().Distancia(other.GetCentroRect());
}

bool Rect::Contains(const Vec2& point) const {
    return (point.x >= x &&
            point.x <= x + w &&
            point.y >= y &&
            point.y <= y + h
           );
}
