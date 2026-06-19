#include "../include/AIController.h"
#include "../include/Character.h"
#include "../include/GameObject.h"

AIController::AIController(GameObject& associated) : Component(associated) {
    state = RESTING;
    restTimer.Restart();
}

void AIController::Update(float dt) {
    if (Character::player == nullptr) {
        return;
    }

    Character* character = associated.GetComponent<Character>();
    if (character != nullptr && character->GetHP() <= 0) {
        return;
    }


    Vec2 playerPos = Character::player->GetCenter();

    switch (state) {
        case RESTING: {
                          restTimer.Update(dt);
                          if (restTimer.Get() > 2.0f) {
                              state = MOVING;
                              destination = playerPos;
                          }
                          break;
                      }
        case MOVING: {
                         Character* character = associated.GetComponent<Character>();

                         Vec2 myCorner(associated.box.x, associated.box.y);
                         Vec2 direction = destination - myCorner;
                         float distance = direction.Magnitude();

                         if (distance > 10) {
                             if (character != nullptr) {
                                character->Issue(Character::Command(Character::Command::MOVE,
                                                                    destination.x, 
                                                                    destination.y));
                             }
                         } else {
                             destination = playerPos;

                             if (character != nullptr) {
                                character->Issue(Character::Command(Character::Command::SHOOT, 
                                        playerPos.x, 
                                        playerPos.y));
                             }

                             restTimer.Restart();
                             state = RESTING;
                         }
                         break;
                     }
    }
}

void AIController::Render() {}
