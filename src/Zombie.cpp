#include "../include/Zombie.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/InputManager.h"

Zombie::Zombie(GameObject& associated) 
    : Component(associated), hitpoins(100),hitSound("Recursos/audio/Hit0.wav"), deathSound("Recursos/audio/Dead.wav"){

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
    //Parada do loop
    if (hitpoins <= 0) return;

    hitpoins -= damage;

    hitSound.Play(1);

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
    InputManager& input = InputManager::GetInstance();

    //Dano ao Cliclar
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {

        int mouseX = input.GetMouseX();
        int mouseY = input.GetMouseY();

        if (associated.box.Contains(Vec2(mouseX, mouseY))) {
            Damage(1);
        }
    }
}

void Zombie::Render() {

}
