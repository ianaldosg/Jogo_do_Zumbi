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

    anim->AddAnimation("idle", Animation(6, 7, 0));
    anim->AddAnimation("walking_right", Animation(0, 5, 0.1f));
    anim->AddAnimation("walking_left", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    anim->AddAnimation("dead", Animation(10, 11, 0.15f));
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

void Character::Update(float dt) {
    speed = Vec2(0,0);

    // Fila de Comandos
    // VOLTAR AQUI NEVER NESTING!!!
    while (!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE) {
            Vec2 dir = task.pos - Vec2(associated.box.x, associated.box.y);

            if (dir.Magnitude() > 2.0f) {
                dir = dir.Normalizar();
                speed = dir * linearSpeed;
            }
        }
        if (task.type == Command::SHOOT) {
            auto gunPtr = gun.lock();
            if (gunPtr) {
                Gun* g = (Gun*)gunPtr->GetComponent<Gun>();
                if (g) g->Shoot(task.pos);
            }
        }
    }

    // Movimento
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    // Animações vivo
    if (hp > 0) {
        if (speed.Magnitude() > 0) {
            if (speed.x < 0) {
                associated.GetComponent<Animator>()->SetAnimation("walking_right");
            } else {
                associated.GetComponent<Animator>()->SetAnimation("walking_left");
            }
        }
        else {
            associated.GetComponent<Animator>()->SetAnimation("idle");
        }
    }

    // Morto?
    if (hp <= 0) {
        associated.GetComponent<Animator>()->SetAnimation("dead");
        deathTimer.Update(dt);
        if (deathTimer.Get() > 3.0f) {
            associated.RequestDelete();
        }
    }
}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

void Character::Render() {}

Character::Command::Command(CommandType type, float x, float y) : type(type), pos(x, y) {}
