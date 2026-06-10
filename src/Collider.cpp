#include "../include/Collider.h"
#include "../include/Collision.h"
#include "../include/GameObject.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
    : Component(associated), scale(scale), offset(offset), box(0, 0, 0, 0) {}

void Collider::Update(float dt) {
    // Copia box
    box = associated.box;

    // Aplica escala
    box.w *= scale.x;
    box.h *= scale.y;

    // Centraliza
    Vec2 center = associated.box.GetCentroRect() + offset.Rotacao(associated.angleDeg);
    box.x = center.x - (box.w / 2.0f);
    box.y = center.y - (box.h / 2.0f);
}

void Collider::Render() {}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}
