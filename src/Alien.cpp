#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Vec2.h"
#include "Game.h"

Alien::Action::Action(ActionType type, float x, float y)
    : type(type), pos(x, y) {}

Alien::Alien(GameObject& associated, int nMinions): Component::Component(associated),
    hp(ALIEN_VIDA),
    nMinions(nMinions) 
    {

    // Sprite do alien
    Sprite* alien_sprite = new Sprite(associated, ALIEN_SPRITE);
    associated.AddComponent(std::shared_ptr<Sprite>(alien_sprite));
}

void Alien::Start() {
    std::weak_ptr<GameObject> go_alien = Game::GetInstance().GetState().GetObjectPtr(&associated);

    for (int i = 0; i < nMinions; i++) {
        GameObject* minion = new GameObject();
        int equally_dist = 360 / nMinions * i;
        Minion* minion_behaviour = new Minion(*minion, go_alien, equally_dist);
        minion->AddComponent(std::shared_ptr<Minion>(minion_behaviour));
        std::weak_ptr<GameObject> go_minion = Game::GetInstance().GetState().AddObject(minion);
        minionArray.push_back(go_minion);
    }
}

Alien::~Alien() {
    // Always remove from back to front
    for (int i = minionArray.size() - 1; i >= 0; i--) {
        minionArray.erase(minionArray.begin() + i);
    }
}


    

void Alien::Update(float dt) {
    // Faz o alien girar
    associated.angleDeg += dt * ALIEN_V_ANGULAR;

    InputManager& input = InputManager::GetInstance();

    // get task de action, seta tipo e posicao
    if (input.MousePress(SDL_BUTTON_LEFT)) {
        taskQueue.emplace(Action(SHOOT, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y));
    }
    if (input.MousePress(SDL_BUTTON_RIGHT)) {
        taskQueue.emplace(Action(MOVE, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y));
        std::cout << "Alien moves queue to X:" << input.GetMouseX() - Camera::pos.x << " Y:" << input.GetMouseY() - Camera::pos.y << std::endl;
    }

    // Executa front queue, n usa while para n executar tudo de uma vez
    if (!taskQueue.empty()) {
        switch (taskQueue.front().type) {
            case MOVE: {
                float alienMoviment = dt * ALIEN_VELOCIDADE;

                // Calculo de velocidade e mudança de posição
                Vec2 centralized = Vec2(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2);
                Vec2 distance = Vec2::D2points(centralized, taskQueue.front().pos);

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

                //----aproxima x----
                bool xFinished = false;
                bool yFinished = false;

                if (fabsf(distance.x) > alienMoviment) {
                    associated.box.x += alienMoviment * cos(atan2(distance.y, distance.x));
                } else {
                    associated.box.x = taskQueue.front().pos.x - associated.box.w / 2;
                    xFinished = true;
                }

                //----aproxima y----
                if (fabsf(distance.y) > alienMoviment) {
                    associated.box.y += alienMoviment * sin(atan2(distance.y, distance.x));
                } else {
                    associated.box.y = taskQueue.front().pos.y - associated.box.h / 2;
                    yFinished = true;
                }

                // Valida se ja incremetou ate x e y
                if (yFinished == true && xFinished == true) {
                    taskQueue.pop();
                }
                break;
            }

            case SHOOT: {
                Vec2 target = taskQueue.front().pos;

                // Determine the closest minion using std::min_element and a lambda function
                auto closestMinion = std::min_element(minionArray.begin(), minionArray.end(), [&](const std::weak_ptr<GameObject>& minionA, const std::weak_ptr<GameObject>& minionB) {
                    if (minionA.expired() || minionB.expired()) return false;
                    
                    Vec2 centerA = minionA.lock()->box.GetCenter();
                    Vec2 centerB = minionB.lock()->box.GetCenter();

                    float distanceA = Vec2::D2points(centerA, target).Hypotenuse();
                    float distanceB = Vec2::D2points(centerB, target).Hypotenuse();
                    
                    return distanceA < distanceB;
                });

                if (closestMinion != minionArray.end() && !closestMinion->expired()) {
                    auto minion = closestMinion->lock();
                    Minion* MinionPtr = (Minion*)minion->GetComponent("Minion").get();
                    MinionPtr->Shoot(target);
                } 
                else {
                    std::cout << "minion = nullptr!" << std::endl;
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