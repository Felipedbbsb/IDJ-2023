#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component::Component(associated),
speed(0, 0),
linearSpeed(0),
angle(0),
hp(PENGUIN_HP)
{
    player = this;

    Sprite* sp = new Sprite(associated, PENGUINBODY_SPRITE);
    associated.AddComponent((std::shared_ptr<Sprite>)sp);

    //Camera::Follow(&associated);

    //Collider *cl = new Collider(associated);
	//associated.AddComponent(cl);
}

PenguinBody::~PenguinBody()
{
    //Camera::Unfollow();
    player = nullptr;
}

void PenguinBody::Start() {
    //GameObject *go = new GameObject();
	//std::weak_ptr<GameObject> weak_ptr = Game::GetInstance().GetState().AddObject(go);
	//std::shared_ptr<GameObject> ptr = weak_ptr.lock();
	//pcannon = weak_ptr;

    //PenguinCannon* pcan = new PenguinCannon(*ptr, Game::GetInstance().GetState().GetObjectPtr(&associated));
	//ptr->box = associated.box;
	//ptr->AddComponent(pcan);
}

void PenguinBody::Update(float dt){   
    if (hp <= 0)
    {
        associated.RequestDelete();

        // Criando animação de morte
        GameObject* penguin_death = new GameObject();
        Sprite *explosion_anim = new Sprite(*penguin_death, PENGUIN_DEATH, PENGUIN_DEATH_FC, 
                                                       PENGUIN_DEATH_FT);
        penguin_death->AddComponent((std::shared_ptr<Sprite>)explosion_anim);
        // Criando som da morte
        Sound *explosion_sound = new Sound(*penguin_death, PENGUIN_DEATH_SOUND);
        penguin_death->AddComponent((std::shared_ptr<Sound>)explosion_sound);
        penguin_death->box.DefineCenter(associated.box.GetCenter());
        Game::GetInstance().GetState().AddObject(penguin_death);
        
        explosion_sound->Play();
    }

    if (InputManager::GetInstance().IsKeyDown(W_KEY))
    {
        if (linearSpeed < SPEED_MAX)
        {
            linearSpeed += PENGUIN_ACC;
        }
    }
    if (InputManager::GetInstance().IsKeyDown(S_KEY))
    {
        if (linearSpeed > -SPEED_MAX)
        {
            linearSpeed -= PENGUIN_ACC;
        }
    }

    if (InputManager::GetInstance().IsKeyDown(A_KEY))
    {
        associated.angleDeg -= SPEED_ANG;
    }
    if (InputManager::GetInstance().IsKeyDown(D_KEY))
    {
        associated.angleDeg += SPEED_ANG;
    }

    angle = associated.angleDeg / (180 / 3.14159265359);
    Vec2 desloc = Vec2(cos(angle) * linearSpeed, sin(angle) * linearSpeed);
    associated.box.DefineCenter(associated.box.GetCenter() + desloc);
}

void PenguinBody::Render(){}

bool PenguinBody::Is(std::string type)
{
    return (type == "PenguinBody");
}

Vec2 PenguinBody::Pos()
{   
    return associated.box.GetCenter();
}