#include "GameObject.h"

GameObject::GameObject() : box(0, 0, 0, 0){
    isDead = false;
    started = false;
    angleDeg = 0;
    
    
}

GameObject::~GameObject(){
    components.clear();
}

void GameObject::Update(float dt){   
    for (int i = components.size() - 1; i >= 0; --i){
        components[i]->Update(dt);
    }
}

void GameObject::Render(){   
    for (int i = components.size() -1; i >= 0; --i){   
        components[i]->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

/// ----------------
void GameObject::AddComponent(std::shared_ptr<Component> cpt){
    components.emplace_back(cpt);
}
/// ----------------
void GameObject::RemoveComponent(std::shared_ptr<Component> cpt){
    for (int i = components.size() - 1; i >= 0; i--){   
        if (components[i] == cpt){
            components.erase(components.begin()+i);
        }
    }
}
/// ----------------
//Retorna nullptr caso esse componente não exista.
std::shared_ptr<Component> GameObject::GetComponent(std::string type){
    for (int i = components.size() - 1; i >= 0; i--){
        if (components[i]->Is(type)){
            return components[i];
        }
    }
    return nullptr;
}

void GameObject::Start(){
    for (int i = 0; i < (int)components.size(); i++){
        components[i]->Start();
    }
        started = true;
}