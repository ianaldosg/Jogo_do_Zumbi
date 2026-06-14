#include "../include/Gun.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
// Testando
//#include "../include/InputManager.h"
//#include "../include/Camera.h"

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
    // Um pouco mais abaixo
    associated.box.y += 15.0f;

    // Angulação da arma
    float dist = 20.0f;
    associated.box.x += cos(angle) * dist;
    associated.box.y += sin(angle) * dist;

    // Esdados do cooldown
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

    float angleDegrees = angle * (180.0f / M_PI);
    associated.angleDeg = angleDegrees;

    // Espelhamento
    auto* sr = associated.GetComponent<SpriteRenderer>();
    if (sr != nullptr) {
        SDL_RendererFlip flip = (angleDegrees > 90.0f || angleDegrees < -90.0f) 
            ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
        sr->SetFlip(flip);

        if (cooldownState == 0) {
            sr->SetFrame(0, flip);
        }
    }

    // Gun tem Y = ao de Character
    float characterSortY = (charPtr->sortY >= 0)
        ? charPtr->sortY : (charPtr->box.y + charPtr->box.h /2);
    associated.sortY = characterSortY;
}

void Gun::Shoot(Vec2 target) {
    if (cooldownState != 0) return;

    // Angulo alvo
    Vec2 origin = associated.box.GetCentroRect();
    Vec2 dir = target - origin;
    angle = atan2(dir.y, dir.x);

    // Desloca para o cano da arma
    float canoOffset = associated.box.w / 2.0f;
    origin.x += cos(angle) * canoOffset;
    origin.y += sin(angle) * canoOffset;

    // Inicia som
    shotSound.Play();

    // Cooldown
    cooldownState = 1;
    cdTimer.Restart();

    // Criando bala
    auto* bulletGO = new GameObject();

    // Bala sai da ponta do cano
    bulletGO->box.x = origin.x - bulletGO->box.w / 2.0f;
    bulletGO->box.y = origin.y - bulletGO->box.h / 2.0f;

    // Atirador
    Character* shooter = nullptr;
    auto charPtr = character.lock();
    if (charPtr) {
        shooter = (Character*) charPtr->GetComponent<Character>();
    }

    // Adiciona Component
    auto* bullet = new Bullet(*bulletGO, angle, 400.0f, 10, 500.0f, shooter);
    bulletGO->AddComponent(bullet);

    // Estado Atual
    Game::GetInstance().GetState().AddObject(bulletGO);
}

void Gun::Render() {}
