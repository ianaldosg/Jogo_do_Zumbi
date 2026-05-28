#include "../include/Character.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/Gun.h"
#include "../include/Game.h"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite) : Component(associated), 
    hp(100), 
    linearSpeed(100.0f) {

    speed = Vec2(0, 0);

    //associated.AddComponent(new SpriteRenderer(associated, sprite));
    SpriteRenderer* sr = new SpriteRenderer(
            associated,
            "Recursos/img/Player.png",
            3, 4
            );

    associated.AddComponent(sr);

    Animator* anim = new Animator(associated);

    anim->AddAnimation("idle", Animation(6, 7, 0.2f));
    anim->AddAnimation("walking", Animation(0, 5, 0.2f));
    anim->AddAnimation("dead", Animation(10, 11, 0.2f));
    associated.AddComponent(anim);
}

Character::~Character() {
    if (player == this) {
        player = nullptr;
    }
}

void Character::Start() {
    GameObject* gunGo = new GameObject();
    gunGo->AddComponent(new Gun(*gunGo, Game::GetInstance().GetState().GameObjectPtr(&associated)));

    gun = Game::GetInstance().GetState().AddObject(gunGo);
}
