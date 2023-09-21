#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Vec2.h"
#include "Game.h"

Alien::Action::Action(ActionType type, float x, float y){
    this ->type = type;
    pos.x = x;
    pos.y = y;

}

Alien::Alien(GameObject &associated, int nMinions) : Component::Component(associated){   
    hp = ALIEN_HP;
    this ->nMinions = nMinions;

    //sprite do alien
    Sprite *alien_sprite = new Sprite(associated, ALIEN_SPRITE);
    associated.AddComponent((std::shared_ptr<Sprite>)alien_sprite);
}





void Alien::Start(){
    std::weak_ptr<GameObject> go_alien  = Game::GetInstance().GetState().GetObjectPtr(&associated);
    for (int i = 0; i < nMinions; i++){
        GameObject *minion = new GameObject();
        int equally_dist = 360/nMinions * i;
        Minion *minion_behaviour = new Minion(*minion, go_alien , equally_dist);
        minion->AddComponent((std::shared_ptr<Minion>)minion_behaviour);

        std::weak_ptr<GameObject> go_minion = Game::GetInstance().GetState().AddObject(minion);
        minionArray.push_back(go_minion);
    }
    
}

Alien::~Alien(){
    //sempre remover de tras pra frente
    for (int i = minionArray.size() - 1; i >= 0; i--){
        minionArray.erase(minionArray.begin() + i);
    }
}

void Alien::Update(float dt){
    
    // Faz o alien girar
    //associated.angleDeg += dt * ALIEN_ANG_VEL;

    InputManager& input = InputManager::GetInstance();
    // get task de action, seta tipo e posicao
    if (input.MousePress(SDL_BUTTON_LEFT)){
        taskQueue.emplace(Action(SHOOT, input.GetMouseX() , input.GetMouseY() ));
        
    }
    if (input.MousePress(SDL_BUTTON_RIGHT)){
        taskQueue.emplace(Action(MOVE, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y));
        std::cout <<"Alien moves queue to X:" << input.GetMouseX() - Camera::pos.x << " Y:" <<input.GetMouseY() - Camera::pos.y <<std::endl;
    }

    // Executa front queue, n usa while para n executar tudo de uma vez
    if (!taskQueue.empty()){
        switch (taskQueue.front().type){
            case MOVE:{
                float step = dt * ALIEN_VELOCITY;

                // Calculo de velocidade e mudança de posição
                //             w
                //      --------------
                //     |              |
                //     |              |
                //     |       C      |  h     Center(C) = Vec2(w/2 , h/2)
                //     |              |
                //     |              |
                //      --------------
                //

                Vec2 centralized = Vec2(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2);
                Vec2 distance = Vec2::D2points(centralized, taskQueue.front().pos);


                //----aproxima x----
                bool xFinished = false;
                bool yFinished = false;
                std::cout << fabsf(distance.x) <<" " << fabsf(distance.y) << " "<< step<<std::endl;

                if (fabsf(distance.x) > step){
                    associated.box.x += step * cos(atan2(distance.y, distance.x));
                }
                else{
                    associated.box.x = taskQueue.front().pos.x- associated.box.w / 2; 
                    xFinished = true;
                }
                
                //----aproxima y----
                 if (fabsf(distance.y) > step){
                    associated.box.y += step * sin(atan2(distance.y, distance.x));
                }
                else{
                    associated.box.y = taskQueue.front().pos.y- associated.box.h / 2;
                    yFinished = true;
                }

                //Valida se ja incremetou ate x e y
                if(yFinished == true && xFinished == true){taskQueue.pop();}
                break;
            }

            case SHOOT:
            {   
                std::shared_ptr<GameObject> minion;
                Vec2 target = taskQueue.front().pos;
                
                float distToTarget = std::numeric_limits<float>::max();

                // Percorre o vector de minions procurando pelo mais próximo do target
                if (!minionArray.empty())
                {   
                    for (int i = 0; i < (int)minionArray.size(); i++)
                    {   
                        if (!minionArray[i].expired())
                        {
                            std::shared_ptr<GameObject> temp_minion = minionArray[i].lock();
                            float closerMinionDistance = Vec2::D2points(temp_minion->box.GetCenter(), target).Magnitude();

                            if (closerMinionDistance < distToTarget)
                            {
                                distToTarget = closerMinionDistance;
                                minion = temp_minion;
                            }
                        }
                    }
                }
                

                if (minion != nullptr)
                {   
                    //Minion* realPtrMinion = (Minion *)minion->GetComponent("Minion").get();
                    //realPtrMinion->Shoot(target);
                }
                else
                {
                    std::cout << "ERRO: minion é um nullptr!" << std::endl;
                }

                taskQueue.pop();
                break;
            }
        }
    }
}   
    



void Alien::Render(){}

bool Alien::Is(std::string type){
    if (type == "Alien"){return true;}
    else{return false;}
}