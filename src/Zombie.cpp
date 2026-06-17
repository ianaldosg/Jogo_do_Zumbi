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
        count++;
}

void Zombie::Damage(int damage) {

    hitpoins -= damage;

    //Animações Morto
    if (hitpoins <= 0) {
        dead = true;

        deathSound.Play(1);

        deathTimer.Restart();

        Animator* anim =
            (Animator*) associated.GetComponent<Animator>();

        if (anim != nullptr) {
            anim->SetAnimation("dead");
        }

        associated.RemoveComponent(associated.GetComponent<Collider>());
    }
    // Animações de Dano
    else {
        hit = true;

        hitSound.Play(1);

        hitTimer.Restart();

        Animator* anim =
            (Animator*) associated.GetComponent<Animator>();

        if (anim != nullptr) {
            if (left) {
                anim->SetAnimation("hit_left");
            } else {
                anim->SetAnimation("hit_right");
            }
        }
    }
}

void Zombie::Update(float dt) {
    hitTimer.Update(dt);
    deathTimer.Update(dt);

    //Deleta o Corpo do Zumbi depois de 5 segundos Morto
    if (dead) {
        if (Camera::GetFocus() == &associated) {
            Camera::Unfollow();
        }
        if (deathTimer.Get() >= 5.0f) {
            associated.RequestDelete();
        }
        //Parada do loop
        return;
    }
    

    // SortY para Zombie
    associated.sortY = associated.box.y + associated.box.h / 2;

    // ARRUMAR ESSA BAGUNÇA
    // Perseguição
    if (Character::player != nullptr) {
        Vec2 playerPos = Character::player->GetCenter();
        Vec2 myPos = associated.box.GetCentroRect();
        Vec2 direction = playerPos - myPos;
        direction = direction.Normalizar();
        //Animação de Walking após 5 segundos do hit
        if (!dead) {
            Animator* anim =
                (Animator*) associated.GetComponent<Animator>();
            if (anim != nullptr) {
                if (!hit) {
                    // Velocidade Constante
                    float speed = 50.f; // ajuste de velocidade
                    associated.box.x += direction.x * speed * dt;
                    associated.box.y += direction.y * speed * dt;

                    if (direction.x < 0) {
                        left = true;
                        anim->SetAnimation("walking_left");
                    } else {
                        left = false;
                        anim->SetAnimation("walking_right");
                    }
                }
                else if (hitTimer.Get() >= 0.5f) {
                    hit = false;
                    if (direction.x < 0) {
                        anim->SetAnimation("walking_left");
                    } else {
                        anim->SetAnimation("walking_right");
                    }
                }
            }
        }

        // Rotaciona para Player
        associated.angleDeg = atan2(direction.y, direction.x);
    }
}

void Zombie::Render() {}

void Zombie::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent<Bullet>();
    if (bullet == nullptr) return;

    Damage(bullet->GetDamage());
}

Zombie::~Zombie() {
    count--;
}
