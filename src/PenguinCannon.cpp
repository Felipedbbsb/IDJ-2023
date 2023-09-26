#include "PenguinCannon.h"
#include "InputManager.h"
#include "Game.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> pbody) : Component::Component(associated),
pbody(pbody),
angle(0)
{

    Sprite* pengCannon_sprite = new Sprite(associated, PENGUINCANNON_SPRITE);
    associated.AddComponent((std::shared_ptr<Sprite>)pengCannon_sprite);
    

    //Collider *penguinCannon_collider = new Collider(associated);
    //associated.AddComponent((std::shared_ptr<Collider>)penguinCannon_collider);

    std::shared_ptr<GameObject> shared_body = pbody.lock();
    if (shared_body.get() != nullptr){
        associated.box.DefineCenter(shared_body.get()->box.GetCenter());
    }
    else{   
        associated.RequestDelete();
    }
}

void PenguinCannon::Update(float dt){  
     std::shared_ptr<GameObject> shared_body = pbody.lock();
    if (shared_body.get() != nullptr)
    {
        associated.box.DefineCenter(shared_body.get()->box.GetCenter());
    }
    else
    {
        associated.RequestDelete();
    } 
}

void PenguinCannon::Render()
{}

void PenguinCannon::Shoot()
{}

bool PenguinCannon::Is(std::string type)
{
    return (type == "PenguinCannon");
}

//void PenguinCannon::NotifyCollision(GameObject &other){}