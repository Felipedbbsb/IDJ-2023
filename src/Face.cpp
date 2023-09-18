#include "Face.h"
#include "InputManager.h"
#include "Camera.h"

Face::Face(GameObject &associated) : Component::Component(associated){
    hitpoints = 30;
}
                                     

void Face::Damage(int damage){
    hitpoints -= damage;
    if (hitpoints <= 0)
    {
        Sound* tmp= (Sound *)associated.GetComponent("Sound").get();
        if (tmp != nullptr){    
        tmp->Play();  
        }
        associated.RequestDelete();
    }
}

void Face::Update(float dt) {
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {
        if (associated.box.Contains(InputManager::GetInstance().GetMouseX() - Camera::pos.x,
                                    InputManager::GetInstance().GetMouseY() - Camera::pos.y))
        {
            int damage = std::rand() % 10 + 10;
            std::cout << "Damage applied: " << damage << std::endl;
           
            Damage(damage); //ataque
            
        }
    }
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