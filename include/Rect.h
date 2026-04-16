#include "SDL_include.h"
#include "Vec2.h"

class Rect{
public:
    float x,y,w,h;

    Rect( float x,float y,float w,float h);
    
    Rect operator+(const Vec2& v) const;

    Vec2 GetCentroRect() const;
    float DistanciaCentro(const Rect& other) const;
    bool Contains(const Vec2& point) const;

};
