#include "../include/GameObject.h"

GameObject::GameObject()
    : started(false), box(0, 0, 0, 0), isDead(false) {}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt) {
    for (Component* c : components) {
        c->Update(dt);
    }
}

void GameObject::Render() {
    for (Component* c : components){
        c->Render();
    }
}

bool GameObject::IsDead() const{
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::Start() {
    for (auto& c : components) {
        c->Start();
    }
    started = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);

    if (started) {
        components.back()->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    for (std::size_t i = 0; i < components.size(); i++){
        if (components[i] == cpt) {
            components.erase(components.begin() + i);
            return;
        }
    }
}
