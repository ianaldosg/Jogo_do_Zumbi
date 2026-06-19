#pragma once

#include "Character.h"

class NPC : public Character {
    public:
        NPC(GameObject& associated, std::string sprite);

        void Start();

        static int count;

        ~NPC();
};
