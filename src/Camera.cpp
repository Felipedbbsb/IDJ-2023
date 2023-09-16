#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

GameObject* Camera::focus;

Vec2 Camera::pos;
Vec2 Camera::speed;


void Camera::Update(float dt){
    if (focus == nullptr) {
        InputManager& input = InputManager::GetInstance();
        //EIXO X

        if (input.IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x = CAMERA_SPEED;
        }
        else if (input.IsKeyDown(LEFT_ARROW_KEY)){
            speed.x =  CAMERA_SPEED * (-1) ;
        }
        else{
            speed.x = 0;
        }
             
        
        //EIXO Y
        if (input.IsKeyDown(UP_ARROW_KEY)){ // Também verificar se o eixo y está sendo pressionado ~ diagonais
            speed.y = CAMERA_SPEED * (-1) ;
        }
        else if (input.IsKeyDown(DOWN_ARROW_KEY)){
            speed.y = CAMERA_SPEED;
        }     
        else{
            speed.y = 0;
        }


        pos.x += dt * speed.x;
        pos.y += dt * speed.y;

    }
    else{
        // Se mudar o tamanho da tela tem que mudar aqui!!!
		pos.x = focus->box.x + focus->box.w - 1024/2;
		pos.y = focus->box.y + focus->box.h - 600/2;
    }
}

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

