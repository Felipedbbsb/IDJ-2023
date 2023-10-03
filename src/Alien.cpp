#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Vec2.h"
#include "Game.h"
#include "Collider.h"
#include "Sound.h"
#include "PenguinBody.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions): Component::Component(associated),
    hp(ALIEN_VIDA),
    nMinions(nMinions),
    state(RESTING)
    {
    alienCount += 1;    
    Sprite* alien_sprite = new Sprite(associated, ALIEN_SPRITE);
    associated.AddComponent(std::shared_ptr<Sprite>(alien_sprite));

    Collider* alien_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)alien_collider);
}

void Alien::Start() {
    std::weak_ptr<GameObject> go_alien = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

    for (int i = 0; i < nMinions; i++) {
        GameObject* minion = new GameObject();
        int equally_dist = 360 / nMinions * i;
        Minion* minion_behaviour = new Minion(*minion, go_alien, equally_dist);
        minion->AddComponent(std::shared_ptr<Minion>(minion_behaviour));
        std::weak_ptr<GameObject> go_minion = Game::GetInstance().GetCurrentState().AddObject(minion);
        minionArray.push_back(go_minion);
    }
}

Alien::~Alien() {
    // Always remove from back to front
    alienCount -= 1;
    for (int i = minionArray.size() - 1; i >= 0; i--) {
        minionArray.erase(minionArray.begin() + i);
    }
}


    

void Alien::Update(float dt) {

    // Verifica morte
    if (hp <= 0){
        associated.RequestDelete();
 
        GameObject *alien_death = new GameObject();
    
        Sprite *explosion_sprite = new Sprite(*alien_death, ALIEN_DEATH_SPRITE, 
                                                            ALIEN_DEATH_SPRITE_FC, 
                                                            ALIEN_DEATH_SPRITE_FT / ALIEN_DEATH_SPRITE_FC  ,
                                                            ALIEN_DEATH_SPRITE_FT);


        explosion_sprite->SetFrameCount(ALIEN_DEATH_SPRITE_FC);                                               

        alien_death->AddComponent((std::shared_ptr<Sprite>)explosion_sprite);
        // Criando som da morte
        Sound *alienDeath_sound = new Sound(*alien_death, ALIEN_DEATH_SOUND_PATH);
        alien_death->AddComponent((std::shared_ptr<Sound>)alienDeath_sound);
        alien_death->box.DefineCenter(associated.box.GetCenter());
        Game::GetInstance().GetCurrentState().AddObject(alien_death);

        alienDeath_sound->Play();
    }
    



    // spin alien
    associated.angleDeg += dt * ALIEN_V_ANGULAR;


    // Get player's position
    Vec2 destination = (PenguinBody::player != nullptr) ? PenguinBody::player->Pos() : Vec2();

    switch (state) {
        case AlienState::MOVING: {
            float maxDistTarget = ALIEN_TARGET_MAX_DIST;
            float speed = ALIEN_VELOCIDADE * dt;

            Vec2 distance = Vec2::D2points(associated.box.GetCenter(), destination);
            float ToDest = distance.Hypotenuse();

            // If the distance is greater than a maxDistTarget, MOVE to the destination
            if (ToDest > maxDistTarget) {
                float step = std::min(speed, ToDest);

                float angle = distance.Angle();
                associated.box.x += step * cos(angle);
                associated.box.y += step * sin(angle);
            } else {
                std::shared_ptr<GameObject> minion = nullptr;
                float distToTarget = std::numeric_limits<float>::max();

                // Iterate through the minion vector to find the closest one to the target
                for (const auto& minionPtr : minionArray) {
                    if (!minionPtr.expired()) {
                        std::shared_ptr<GameObject> temp_minion = minionPtr.lock();
                        float closerMinion = Vec2::D2points(temp_minion->box.GetCenter(), destination).Hypotenuse();

                        if (closerMinion < distToTarget) {
                            distToTarget = closerMinion;
                            minion = temp_minion;
                        }
                    }
                }

                // If this minion exists
                if (minion != nullptr) {
                    Minion* real_minion = static_cast<Minion*>(minion->GetComponent("Minion").get());

                    // Fire
                    if (PenguinBody::player != nullptr) {
                        real_minion->Shoot(destination);
                    }
                } 
                else { 
                    std::cout << "No minion" << std::endl;
                } 

                // Reset the timer and change the state to RESTING
                restTimer.Restart();
                state = AlienState::RESTING;
            }
            break; 
        } 

        case AlienState::RESTING: {
            // If the timer has already "elapsed"
            if (restTimer.Get() >= ALIEN_MOV_TIMER ) {
                // Update the destination/target position and change the state to MOVING
                if (PenguinBody::player != nullptr) {
                    destination = PenguinBody::player->Pos();
                }
                state = AlienState::MOVING;
            } else {
                // Update the timer until it "elapses"
                restTimer.Update(dt);
            }
            break;
        }
    }

    
}

void Alien::Render(){}

bool Alien::Is(std::string type){
    if (type == "Alien"){return true;}
    else{return false;}
}


void Alien::NotifyCollision(GameObject &other){
    // Try to convert the component to a Bullet
    std::shared_ptr<Bullet> shared_Bullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet"));

    // Check if the component is a bullet and if it wasn't shot by the player
    if (shared_Bullet && !shared_Bullet->WhoIsShooter("Minion")){
        int d_alien = shared_Bullet->GetDamage();
        hp -= d_alien;
        std::cout << "ALIEN(HP) " << hp << std::endl;
    }
}