#define INCLUDE_SDL

#include "SDL_include.h"
#include <iostream>
#include <string>

class Game {
private:
    Game();
    static Game* instance;

public:
    static Game& GetInstance(); 
};
