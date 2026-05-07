#include "../include/Zombie.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/InputManager.h"

Zombie::Zombie(GameObject& associated) 
    : Component(associated), hitpoins(100),hit(false),dead(false),hitSound("Recursos/audio/Hit0.wav"), deathSound("Recursos/audio/Dead.wav"){

        SpriteRenderer* sr = new SpriteRenderer(
                associated,
                "Recursos/img/Enemy.png",
                3, 2
                );

        associated.AddComponent(sr);

        //Animações Zombie
        Animator* anim = new Animator(associated);

        anim->AddAnimation("walking", Animation(0, 3, 0.2f));
        anim->AddAnimation("hit", Animation(4,4,0));
        anim->AddAnimation("dead", Animation(5, 5, 0));

        anim->SetAnimation("walking");

        associated.AddComponent(anim);
}

void Zombie::Damage(int damage) {

    hitpoins -= damage;

    if (hitpoins <= 0) {
        dead = true;

        deathSound.Play(1);

        deathTimer.Restart();

        Animator* anim =
            (Animator*) associated.GetComponent<Animator>();

        if (anim != nullptr) {
            anim->SetAnimation("dead");
        }
    }
    else {
        hit = true;

        hitSound.Play(1);

        hitTimer.Restart();

        Animator* anim =
            (Animator*) associated.GetComponent<Animator>();

        if (anim != nullptr) {
            anim->SetAnimation("hit");
        }
    }
}

void Zombie::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    hitTimer.Update(dt);
    deathTimer.Update(dt);

    //Deleta o Corpo do Zumbi depois de 5 segundos Morto
    if (dead) {
        if (deathTimer.Get() >= 5.0f) {
            associated.RequestDelete();
        }
        //Parada do loop
        return;
    }

    
    //Animação de Walking após 5 segundos do hit
    if (hit && !dead && hitTimer.Get() >= 0.5f) {
        hit = false;

        Animator* anim =
            (Animator*) associated.GetComponent<Animator>();
        if (anim != nullptr) {
            anim->SetAnimation("walking");
        }
    }

    //Dano ao Cliclar
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {

        int mouseX = input.GetMouseX();
        int mouseY = input.GetMouseY();

        if (associated.box.Contains(Vec2(mouseX, mouseY))) {
            Damage(20);
        }
    }
}

void Zombie::Render() {

}
