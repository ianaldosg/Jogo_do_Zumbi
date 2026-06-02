#include "../include/Bullet.h"
#include "../include/SpriteRenderer.h"

Bullet::Bullet(GameObject& associated,
                float angle,
                float speed,
                int damage,
                float maxDistance) : Component(associated) {
    // Calcula velocidade a partir do angulo
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;

    // Distancia máxima
    this->distanceLeft = maxDistance;

    // Dano
    this->damage = damage;

    // Imagem projétil
    auto* sr = new SpriteRenderer(associated, "Recursos/img/Bullet.png");
    associated.AddComponent(sr);
}

void Bullet::Update(float dt) {
    // Distancia percorrida
    Vec2 displacement = speed * dt;

    // Movimento da Bala
    associated.box.x += displacement.x;
    associated.box.y += displacement.y;

    // Distancia restante
    distanceLeft -= displacement.Magnitude();

    // Deletando
    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

int Bullet::GetDamage() {
    return damage;
}
