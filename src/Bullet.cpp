#include "../include/Bullet.h"
#include "../include/SpriteRenderer.h"
#include "../include/Collider.h"
#include "../include/Character.h"

Bullet::Bullet(GameObject& associated,
                float angle,
                float speed,
                int damage,
                float maxDistance,
                Character* shooter) : Component(associated) {
    // Imagem projétil
    auto* sr = new SpriteRenderer(associated, "Recursos/img/Bullet.png");
    // Ajuste de Tamanho
    sr->SetScale(0.5f, 0.5f);
    associated.AddComponent(sr);

    // Calcula velocidade a partir do angulo
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;

    // Distancia máxima
    this->distanceLeft = maxDistance;

    // Dano
    this->damage = damage;

    // Angulação do objeto
    associated.angleDeg = angle * (180.0 / M_PI) + 90.0;

    // Mira no player
    targetsPlayer = (shooter != Character::player);

    // Colisão
    associated.AddComponent(new Collider(associated));
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

void Bullet::NotifyCollision(GameObject& other) {
    // Balas não se destroem
    Bullet* otherBullet = (Bullet*)other.GetComponent<Bullet>();
    if (otherBullet != nullptr) {
        return;
    }

    // Checagem de friendly fire
    Character* character = (Character*)other.GetComponent<Character>();
    if (character != nullptr) {
        printf("[Bullet] -> Era Character! targetsPlayer=%d, ehPlayer=%d\n",
                targetsPlayer, character == Character::player);
        if (targetsPlayer && character != Character::player) return;
        if (!targetsPlayer && character == Character::player) return;

    }

    associated.RequestDelete();
}
