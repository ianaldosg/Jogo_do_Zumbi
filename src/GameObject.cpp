#include "../include/GameObject.h"

GameObject::GameObject()
    : box(0, 0, 0, 0), isDead(false) {}

GameObject::~GameObject(){
    for (int i = components.size() - 1; i >= 0; i--){
        delete components[i];
    }
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

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    for (std::size_t i = 0; i < components.size(); i++){
        if (components[i] == cpt) {
            delete components[i];
            components[i] = nullptr;
            components.erase(components.begin() + i);
            return;
        }
    }
}
