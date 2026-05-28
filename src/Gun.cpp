#include "../include/Gun.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/Character.h"

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character) : Component(associated),
    shotSound("Recursos/audio/Range.wav"),
    reloadSound("Recursos/audio/PumpAction.mp3"),
    cooldownState(0),
    character(character),
    angle(0)
{
    associated.AddComponent(new SpriteRenderer(associated, "Recursos/img/Gun.png", 3,2));

    Animator* anim = new Animator(associated);
    anim->AddAnimation("idle", Animation(0,0,0));
    anim->AddAnimation("reloading", Animation(1,5,0.2f));
    associated.AddComponent(anim);
}

void Gun::Update(float dt) {
    //Morto?
    auto charPtr = character.lock();
    if (!charPtr) {
        associated.RequestDelete();
        return;
    }

    // Centraliza Arma
    Vec2 centroPersonagem = charPtr->box.GetCentroRect();
    associated.box.x = centroPersonagem.x - (associated.box.w / 2.0f);
    associated.box.y = centroPersonagem.y - (associated.box.h / 2.0f);

    // Esdados do cooldown
    float dist = 30.0f;
    associated.box.x += cos(angle) * dist;
    associated.box.y += sin(angle) * dist;

    cdTimer.Update(dt);

    if (cooldownState == 1 && cdTimer.Get() > 0.5f) {
        cooldownState = 2;
        cdTimer.Restart();
        reloadSound.Play();
        associated.GetComponent<Animator>()->SetAnimation("reloading");
    }
    else if (cooldownState == 2 && cdTimer.Get() > 0.5f) {
        cooldownState = 3;
        cdTimer.Restart();
        associated.GetComponent<Animator>()->SetAnimation("idle");
    }
    else if (cooldownState == 3 && cdTimer.Get() > 0.1f) {
        cooldownState = 0;
    }
}

void Gun::Shoot(Vec2 target) {
    if (cooldownState != 0) return;
    
    // Angulo alvo
    Vec2 origin = associated.box.GetCentroRect();
    Vec2 dir = target - origin;
    angle = atan2(dir.y, dir.x);

    // Inicia som
    shotSound.Play();
    cooldownState = 1;
    cdTimer.Restart();
}

void Gun::Render() {

}
