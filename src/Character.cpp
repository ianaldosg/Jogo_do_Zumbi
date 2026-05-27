#include "../include/Character.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite) : Component(associated){

    hp = 10;
    linearSpeed = 100.0f;
    speed = Vec2(0, 0);

    associated.AddComponent(new SpriteRenderer(associated, sprite));

    Animator* anim = new Animator(associated);

    anim->AddAnimation("idle", );
    anim->AddAnimation("walking", );
    anim->AddAnimation("dead", );

}
