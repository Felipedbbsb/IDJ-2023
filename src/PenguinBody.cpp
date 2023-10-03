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

    Camera::Follow(&associated);

    Collider *cl = new Collider(associated);
	associated.AddComponent((std::shared_ptr<Collider>)cl);
}

PenguinBody::~PenguinBody(){
    Camera::Unfollow();
    player = nullptr;
}
 
void PenguinBody::Start() {

    std::weak_ptr<GameObject> weak_pcan = Game::GetInstance().GetState().GetObjectPtr(&associated);
    GameObject *pcan = new GameObject();
    PenguinCannon* pcan_behaviour = new PenguinCannon(*pcan, weak_pcan);
    std::shared_ptr<PenguinCannon> pcan_shared = std::make_shared<PenguinCannon>(*pcan_behaviour);
    pcan->AddComponent(pcan_shared);
    Game::GetInstance().GetState().AddObject(pcan);
	
}

void PenguinBody::Update(float dt) {
    
     if (hp <= 0){
        associated.RequestDelete();

        // Criando animação de morte
        GameObject* penguin_death = new GameObject();
        Sprite *explosion_sprite = new Sprite(*penguin_death, PENGUIN_DEATH, PENGUIN_DEATH_FC, PENGUIN_DEATH_FT/PENGUIN_DEATH_FC, 
                                                       PENGUIN_DEATH_FT);


        explosion_sprite->SetFrameCount(PENGUIN_DEATH_FC);   

        penguin_death->AddComponent((std::shared_ptr<Sprite>)explosion_sprite);
        // Criando som da morte
        Sound *explosion_sound = new Sound(*penguin_death, PENGUIN_DEATH_SOUND);
        penguin_death->AddComponent((std::shared_ptr<Sound>)explosion_sound);
        penguin_death->box.DefineCenter(associated.box.GetCenter());
        Game::GetInstance().GetState().AddObject(penguin_death);
        
        explosion_sound->Play();
    }
    // Mapeamento das teclas para o movimento
    std::unordered_map<int, Vec2> keyMovementMap = {
        {W_KEY, Vec2(0, PENGUIN_ACC)},
        {S_KEY, Vec2(0, -PENGUIN_ACC)},
        {A_KEY, Vec2(-SPEED_ANG, 0)},
        {D_KEY, Vec2(SPEED_ANG, 0)}
    };

    for (const auto& keyVecPair : keyMovementMap) {
        if (InputManager::GetInstance().IsKeyDown(keyVecPair.first)) {
            linearSpeed = std::min(std::max(linearSpeed + keyVecPair.second.y, -static_cast<float>(SPEED_MAX)), static_cast<float>(SPEED_MAX));
            associated.angleDeg += keyVecPair.second.x;
        }
    }

    angle = associated.angleDeg * (3.14159265359 / 180.0);
    Vec2 movement = Vec2(cos(angle) * linearSpeed, sin(angle) * linearSpeed);
    associated.box.DefineCenter(associated.box.GetCenter() + movement);
}

void PenguinBody::Render() {}

bool PenguinBody::Is(std::string type) {
    return (type == "PenguinBody");
}

Vec2 PenguinBody::Pos() {
    return associated.box.GetCenter();
}
 
  
void PenguinBody::NotifyCollision(GameObject &other) {
    // Try to convert the component to a Bullet
    std::shared_ptr<Bullet> shared_Bullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet"));

    // Check if the component is a bullet and if it wasn't shot by the player
    if (shared_Bullet && !shared_Bullet->WhoIsShooter("Penguin"))
    {
        int d_penguin = shared_Bullet->GetDamage();
        hp -= d_penguin;
        std::cout << "PENGUIN(HP): " << hp << std::endl;
    }
}
