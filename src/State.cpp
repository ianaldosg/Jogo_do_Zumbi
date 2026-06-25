#include "../include/State.h"
#include "../include/GameObject.h"

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object) {
    std::shared_ptr<GameObject> sharedObject(object);
    objectArray.push_back(sharedObject);
    if (started) {
        sharedObject->Start();
    }
    return std::weak_ptr<GameObject>(sharedObject);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object) {
    for (auto& sharedObject : objectArray) {
        if (sharedObject.get() == object) {
            return std::weak_ptr<GameObject>(sharedObject);
        }
    }
    return std::weak_ptr<GameObject>();
}

bool State::PopRequested(){
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt) {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}
