#include "Face.h"

Face::Face(GameObject &associated) : Component::Component(associated){
    hitpoints = 30;
}
                                     

void Face::Damage(int damage){
    hitpoints -= damage;
    if (hitpoints <= 0)
    {
        Sound* tmp= (Sound *)associated.GetComponent("Sound").get();
        if (tmp != nullptr)
        {    
        tmp->Play();  
        }
        associated.RequestDelete();
    }
}

void Face::Update(float dt) {

}

void Face::Render() {

}

bool Face::Is(std::string type){
    if (type == "Face"){
        return true;
    }
    else{
        return false;
    }
}