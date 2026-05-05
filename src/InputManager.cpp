#include "../include/InputManager.h"

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

InputManager::InputManager(){
    for (int i = 0; i < 0; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }

    updateCounter = 0;
    quitRequested = false;
    mouseX = 0;
    mouseY = 0;
}

void InputManager::Update(){
    updateCounter++;

    quitRequested = false;

    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.repeat == 0) {
                int key = event.key.keysym.sym;
                keyState[key] = true;
                keyUpdate[key] = updateCounter;
            }
        }
        else if (event.type == SDL_KEYUP) {
            int key = event.key.keysym.sym;
            keyState[key] = false;
            keyUpdate[key] = updateCounter;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int button = event.button.button;
            mouseState[button] = true;
            mouseUpdate[button] = updateCounter;
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            int button = event.button.button;
            mouseState[button] = false;
            mouseUpdate[button] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key){
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key){
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key){
    return keyState[key];
}

bool InputManager::MousePress(int button){
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button){
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button){
    return mouseState[button];
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}

InputManager::~InputManager(){
}
