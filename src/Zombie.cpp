#include "../include/Zombie.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/Camera.h"
#include "../include/Collider.h"
#include "../include/Bullet.h"

int Zombie::count = 0;

Zombie::Zombie(GameObject& associated) 
    : Component(associated), hitSound("Recursos/audio/Hit0.wav"), deathSound("Recursos/audio/Dead.wav"), hitpoins(100), hit(false), left(false),dead(false){

        SpriteRenderer* sr = new SpriteRenderer(
                associated,
                "Recursos/img/Enemy.png",
                3, 2
                );

        associated.AddComponent(sr);

        //Animações Zombie
        Animator* anim = new Animator(associated);

        anim->AddAnimation("walking_right", Animation(0, 3, 0.2f));
        anim->AddAnimation("walking_left", Animation(0, 3, 0.2f, SDL_FLIP_HORIZONTAL));
        anim->AddAnimation("hit_right", Animation(4,4,0));
        anim->AddAnimation("hit_left", Animation(4,4,0, SDL_FLIP_HORIZONTAL));
        anim->AddAnimation("dead", Animation(5, 5, 0));

        anim->SetAnimation("walking_right");

        associated.AddComponent(anim);

        // Colisão
        associated.AddComponent(new Collider(associated));

        // Contador
        Zombie::count++;
}

void Zombie::Damage(int damage) {

    hitpoins -= damage;

    Animator* animator = associated.GetComponent<Animator>();
    //Animações Morto
    if (hitpoins <= 0) {
        dead = true;
        deathSound.Play(1);
        deathTimer.Restart();

        if (animator) {
            animator->SetAnimation("dead");
        }

        if (Collider* collider = associated.GetComponent<Collider>()) {
            collider->SetScale(Vec2(0.0f, 0.0f));
        }

        return;
    }

    // Animações de Dano
    hit = true;
    hitSound.Play(1);
    hitTimer.Restart();

    if (animator) {
        animator->SetAnimation(left ? "hit_left" : "hit_right");
    }
}

void Zombie::Update(float dt) {
    //Deleta o Corpo do Zumbi depois de 5 segundos Morto
    if (dead) {
        HandleDeath(dt);
        return;
    }

    // Atualiza Hit depois de tiro
    if (hit) {
        hitTimer.Update(dt);
    }

    // SortY para Zombie
    associated.sortY = associated.box.y + associated.box.h / 2;

    // Perseguição
    if (Character::player != nullptr && !Character::player->IsCharacterDead()) {
        ProcessMovementAndAnimations(dt);
    }

    //Limite do Mapa
    WorldBorder();

}

void Zombie::Render() {}

void Zombie::NotifyCollision(GameObject& other) {
    if (dead) return;

    Bullet* bullet = (Bullet*)other.GetComponent<Bullet>();
    if (bullet != nullptr) {
        if (bullet->targetsPlayer) {
            return;
        }

        Damage(bullet->GetDamage());
    }
}
Zombie::~Zombie() {
    Zombie::count--;
}

void Zombie::HandleDeath(float dt) {
    // Atualiza relogio de morte
    deathTimer.Update(dt);

    if (Camera::GetFocus() == &associated) {
        Camera::Unfollow();
    }

    if (deathTimer.Get() >= 5.0f) {
        associated.RequestDelete();
    }

}

void Zombie::ProcessMovementAndAnimations(float dt) {
    Animator* animator = associated.GetComponent<Animator>();
    if (!animator) return;

    // Calcula direção até Player
    Vec2 playerPos = Character::player->GetCenter();
    Vec2 myPos = associated.box.GetCentroRect();
    Vec2 direction = (playerPos - myPos).Normalizar();

    // Rotaciona Zombie
    associated.angleDeg = std::atan2(direction.y, direction.x);

    // Stun
    if (hit && hitTimer.Get() >= 0.5f) {
        hit = false;
    }

    // Verificação de Stun
    if(hit) return;

    // Movimentação
    const float speed = 50.0f;
    associated.box.x += direction.x * speed * dt;
    associated.box.y += direction.y * speed * dt;

    // Lado do Animation
    left = (direction.x < 0.0f);
    animator->SetAnimation(left ? "walking_left" : "walking_right");
}

void Zombie::WorldBorder() {
    // Limite de Mapa X
    if (associated.box.x < 640.0f) {
        associated.box.x = 640.0f;
    } else if (associated.box.x + associated.box.w > 1920.0f) {
        associated.box.x = 1920.0f - associated.box.w;
    }

    // Limite de Mapa Y
    if (associated.box.y < 512.0f) {
        associated.box.y = 512.0f;
    } else if (associated.box.y + associated.box.h > 2048.0f) {
        associated.box.y = 2048.0f - associated.box.h;
    }
}
