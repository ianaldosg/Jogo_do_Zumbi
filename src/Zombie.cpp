#include "../include/Zombie.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"

Zombie::Zombie(GameObject& associated) 
    : Component(associated), hitpoins(100), deathSound("Recursos/audio/Dead.wav"){

        SpriteRenderer* sr = new SpriteRenderer(
                associated,
                "Recursos/img/Enemy.png",
                3, 2
                );

        associated.AddComponent(sr);

        //Animações Zombie
        Animator* anim = new Animator(associated);

        anim->AddAnimation("walking", Animation(0, 3, 0.1));
        anim->AddAnimation("dead", Animation(5, 5, 0));

        anim->SetAnimation("walking");

        associated.AddComponent(anim);
}

void Zombie::Damage(int damage) {
    if (hitpoins <= 0) return;

    hitpoins -= damage;

    if (hitpoins <= 0) {
        Animator* anim =
            (Animator*) associated.GetComponent<Animator>();

        if (anim != nullptr) {
            anim->SetAnimation("dead");
        }

        deathSound.Play(1);
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {

}
