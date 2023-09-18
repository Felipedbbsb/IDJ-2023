#include "InputManager.h"



//Meyers’ Singleton.
InputManager &InputManager::GetInstance(){
    static InputManager ins;
    return ins;
}

InputManager::InputManager() : 
mouseState{false, false, false, false, false, false},
mouseUpdate{0, 0, 0, 0, 0, 0},
quitRequested(false),
updateCounter(0),
mouseX(0),
mouseY(0){}

InputManager::~InputManager(){}

void InputManager::Update(){
    SDL_Event event;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    updateCounter ++;//Atualiza o updateCounter
    quitRequested = false;
    

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)){   
        // Para saber se o evento é repetidos
        //std::cout << "Tecla: " << event.key.keysym.sym << std::endl;
        //std::cout << "Botao: " << event.button.button << std::endl;
        //std::cout << "MouseXY: X" << GetMouseX() << " Y" << GetMouseY() << std::endl;
        if (event.key.repeat != true) {   
            
            // Switch melhor que if nessa situacao
            switch (event.type){

                //Para os eventos de key, podemos saber qual o keycode via --event.key.keysym.sym--
                // Para eventos de botao event.button.button 
                // Pressionamento de tecla
                case SDL_KEYDOWN:
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

                // Uma tecla foi solta
                case SDL_KEYUP:
                    keyState[event.key.keysym.sym] = false;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

                // Pressionamento de botão do mouse
                case SDL_MOUSEBUTTONDOWN:
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                // Botão do mouse foi solto
                case SDL_MOUSEBUTTONUP:
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                // Clique no X, Alt+F4, etc.(mudar depois)
                case SDL_QUIT:
                    quitRequested = true;
                    break;
            }
        }
    }
}

bool InputManager::QuitRequested(){return quitRequested;}

int InputManager::GetMouseX(){return mouseX;}

int InputManager::GetMouseY(){return mouseY;}


//Para proximas funcoes 

//      ___Press e ___Release estão interessadas no pressionamento ocorrido
//      naquele frame, e só devem retornar true nesse caso. Use os vetores
//      ___Update e o updateCounter para saber. Is___Down retorna se o botão/tecla
//      está pressionado, independente de quando isso ocorreu.


bool InputManager::KeyPress(int key){
    if ((keyState[key] == true) && (keyUpdate[key] == updateCounter)){
        return true;
    }
    else{return false;}
}

bool InputManager::KeyRelease(int key){
    if ((keyState[key] == false) && (keyUpdate[key] == updateCounter)){
        return true;
    }
    else{return false;}
}

bool InputManager::IsKeyDown(int key){ 
    if (keyState[key] == true){
        return true;
    }
    else{return false;}
}

bool InputManager::MousePress(int button){
    if ((mouseState[button] == true)&&(mouseUpdate[button] == updateCounter)){
        return true;
    }
    else{return false;}
}

bool InputManager::MouseRelease(int button){
    if ((mouseState[button] == false) && (mouseUpdate[button] == updateCounter)){
        return true;
    }
    else{return false;}
}

bool InputManager::IsMouseDown(int button){
    if (mouseState[button] == true){
        return true;
    }
    else{return false;}
}

