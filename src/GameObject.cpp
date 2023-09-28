#include "GameObject.h"
#include <iostream>
#include <stdexcept>

GameObject::GameObject() : box(0, 0, 0, 0){
    isDead = false;
    started = false;
    angleDeg = 0;
}

GameObject::GameObject(int posX, int posY) : GameObject(){
    this->box.DefineCenter(Vec2(posX, posY));
}

GameObject::GameObject(Vec2 pos) : GameObject(){
    this->box.DefineCenter(pos);
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt){
    try {
        for (int i = components.size() - 1; i >= 0; --i){
            components[i]->Update(dt);
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during GameObject update: " << e.what() << std::endl;
        throw; // Re-throw a exceção para encerrar o jogo ou realizar um tratamento superior.
    }
}

void GameObject::Render(){
    try {
        for (int i = components.size() - 1; i >= 0; --i){
            components[i]->Render();
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during GameObject rendering: " << e.what() << std::endl;
        throw; // Re-throw a exceção para encerrar o jogo ou realizar um tratamento superior.
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt){
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(std::shared_ptr<Component> cpt){
    for (int i = components.size() - 1; i >= 0; i--){
        if (components[i] == cpt){
            components.erase(components.begin()+i);
        }
    }
}

std::shared_ptr<Component> GameObject::GetComponent(std::string type){
    for (int i = components.size() - 1; i >= 0; i--){
        if (components[i]->Is(type)){
            return components[i];
        }
    }
    return nullptr;
}

void GameObject::Start(){
    try {
        for (int i = 0; i < (int)components.size(); i++){
            components[i]->Start();
        }
        started = true;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during GameObject start: " << e.what() << std::endl;
        throw; // Re-throw a exceção para encerrar o jogo ou realizar um tratamento superior.
    }
}
