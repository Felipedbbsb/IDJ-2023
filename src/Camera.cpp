#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

GameObject* Camera::focus;

Vec2 Camera::pos;
Vec2 Camera::speed;


void Camera::Update(float dt){
    if (focus == nullptr) {
        //EIXO X
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x = SPEED;
        }
        else if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
            speed.x =  CAMERA_SPEED * (-1) ;
        }
        else{
            speed.x = 0;
        }
             
        
        
        //EIXO Y
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_EY)){ // Também verificar se o eixo y está sendo pressionado ~ diagonais
            speed.y = CAMERA_SPEED * (-1) ;
        }
        else if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
            speed.y = CAMERA_SPEED;
        }     
        else{
            speed.y = 0;
        }

        

        pos.x += dt * speed.x;
        pos.y += dt * speed.y;
    }
}

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

