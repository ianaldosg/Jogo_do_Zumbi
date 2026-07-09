#include "../include/Character.h"
#include "../include/Game.h"
#include "../include/SpriteRenderer.h"
#include "../include/Animator.h"
#include "../include/Gun.h"
#include "../include/Bullet.h"
#include "../include/Zombie.h"
#include "../include/Collider.h"
#include "../include/Camera.h"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite) : Component(associated), 
    hp(100), 
    linearSpeed(100.0f),
    hitSound("Recursos/audio/Hit1.wav"),
    deathSound("Recursos/audio/Dead.wav"),
    dead(false){

    speed = Vec2(0, 0);

    SpriteRenderer* sr = new SpriteRenderer(
            associated,
            sprite,
            3, 4
            );

    associated.AddComponent(sr);

    Animator* anim = new Animator(associated);

    anim->AddAnimation("idle", Animation(6, 7, 0));
    anim->AddAnimation("walking_right", Animation(0, 5, 0.1f));
    anim->AddAnimation("walking_left", Animation(0, 5, 0.1f, SDL_FLIP_HORIZONTAL));
    anim->AddAnimation("dead", Animation(10, 11, 0.15f));
    associated.AddComponent(anim);

    // Colisão
    associated.AddComponent(new Collider(associated));

}

Character::~Character() {
    if (player == this) { player = nullptr; }
}

void Character::Start() {
    // Criando Gun
    GameObject* gunGo = new GameObject();
    gunGo->AddComponent(new Gun(*gunGo, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated)));

    gun = Game::GetInstance().GetCurrentState().AddObject(gunGo);
}

void Character::Update(float dt) {
    speed = Vec2(0,0);

    // Fila de Comandos
    ProcessTasks();

    // Movimento
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    // Animações vivo
    UpdateAnimations();

    if (hp<= 0) {
        // Morto?
        if (!dead) {
            HandleDeath();
        }
        // Contador de Delete
        deathTimer.Update(dt);
        if (deathTimer.Get() > 3.0f) {
            associated.RequestDelete();
        }
    }

    damageTimer.Update(dt);

    // Sort Y de Character
    associated.sortY = associated.box.y + associated.box.h / 2;

    //Limite do Mapa
    WorldBorder();
}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

void Character::Render() {}

Character::Command::Command(CommandType type, float x, float y) : type(type), pos(x, y) {}

void Character::NotifyCollision(GameObject& other) {
    // Se Character estiver morto deixa de colidir
    if (this->hp <= 0 || this->dead) {
        return;
    }

    // Colisão com Zombie
    if (Zombie* zombie = other.GetComponent<Zombie>()) {
        // Condições de Dano
        if (zombie->IsDead() || this != Character::player || damageTimer.Get() < 1.0f) {
            return;
        }

        hp -= 20;
        damageTimer.Restart();

        if (hp > 0) hitSound.Play(1);
    }

    // Colisão com Bullet
    if (Bullet* bullet = other.GetComponent<Bullet>()) {
        bool isPlayer = (this == Character::player);

        // Friendly fire
        if (bullet->targetsPlayer && !isPlayer)  return;
        if (!bullet->targetsPlayer && isPlayer)  return;

        // Toma dano
        hp -= bullet->GetDamage();

        // Som dano
        if (hp > 0) hitSound.Play(1);
    }
}

int Character::GetHP() {
    return hp;
}

Vec2 Character::GetCenter() const {
    return Vec2(associated.box.x + (associated.box.w / 2.0f), associated.box.y + (associated.box.h / 2.0f));
}

void Character::ProcessTasks(){
    // Fila de Comandos
    while (!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();
        switch (task.type) {
            case Command::MOVE: 
                {
                    Vec2 currentPos(associated.box.x, associated.box.y);
                    Vec2 dir = task.pos - currentPos;

                    if (dir.Magnitude() > 2.0f) {
                        speed = dir.Normalizar() * linearSpeed;
                    }
                    break;
                }
            case Command::SHOOT:
                {
                    if (auto gunPtr = gun.lock()) {
                        if (Gun* g = gunPtr->GetComponent<Gun>()) {
                            g->Shoot(task.pos);
                        }
                    }
                    break;
                }

                default:
                    break;
        }
    }
}

void Character::UpdateAnimations(){
    // Animações vivo
    if (hp <= 0) return;

    auto* animator = associated.GetComponent<Animator>();
    if (!animator) return;

    if (speed.Magnitude() > 0) {
        animator->SetAnimation(speed.x < 0.0f ? "walking_left" : "walking_right");
    } else {
        animator->SetAnimation("idle");
    }
}

void Character::HandleDeath() {
    // Morto?
    dead = true;

    associated.GetComponent<Animator>()->SetAnimation("dead");

    //Som de Morte
    deathSound.Play(1);

    //Camera
    if (this == Character::player) {
        Camera::Unfollow();
    }

    // Deleta Gun ao morrer
    auto gunPtr = gun.lock();
    if (gunPtr) { gunPtr->RequestDelete(); }

    // Para de se mover após morrer
    while (!taskQueue.empty()) {
        taskQueue.pop();
    }
}

void Character::WorldBorder() {
    // Limite de Mapa X
    if (associated.box.x < 640.0f) {
        associated.box.x = 640.0f;
    } else if (associated.box.x + associated.box.w > 1920.0f) {
        associated.box.x = 1920.0f - associated.box.w;
    }

    // Limite de Mapa Y
    if (associated.box.y < 512.0f) {
        associated.box.y = 512.0f;
    } else if (associated.box.y + associated.box.h > 2048.0f) {
        associated.box.y = 2048.0f - associated.box.h;
    }
}
