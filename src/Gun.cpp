#include "../include/Gun.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character) : Component(associated),
    shotSound("Recursos/audio/Range.wav"),
    reloadSound("Recursos/audio/PumpAction.mp3"),
    cooldownState(0),
    angle(0),
    character(character) {

        associated.AddComponent(new SpriteRenderer(associated, "Recursos/img/Gun.png", 3,2));
        
        Animator* anim = new Animator(associated);
        anim->AddAnimation("idle", Animation(0,0,0));
        anim->AddAnimation("reloading", Animation(1,5,0.2f));
        associated.AddComponent(anim);

    }
