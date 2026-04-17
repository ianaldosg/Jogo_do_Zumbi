#include "../include/Zombie.h"

Zombie::Zombie(GameObject& associated) 
    : Component(associated), hitpoins(100){

        SpriteRenderer* sr = new SpriteRenderer(
                associated,
                "Recursos/img/Enemy.png",
                3, 2
                );

        sr->SetFrame(1);

        associated.AddComponent(sr);
}

void Zombie::Damage(int damage) {
    hitpoins -= damage;

    if (hitpoins <= 0) {
        SpriteRenderer* sr = 
            (SpriteRenderer*) associated.GetComponent<SpriteRenderer>();
        if (sr != nullptr) {
            sr->SetFrame(5);
        }
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {

}
