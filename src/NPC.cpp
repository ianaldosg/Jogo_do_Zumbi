#include "../include/GameObject.h"
#include "../include/NPC.h"
#include "../include/AIController.h"

int NPC::count = 0;

NPC::NPC(GameObject& associated, std::string sprite) 
    : Character(associated, sprite) {
        count ++;
    }

void NPC::Start() {
    Character::Start();
    associated.AddComponent(new AIController(associated));
}

NPC::~NPC() {
    count--;
}
