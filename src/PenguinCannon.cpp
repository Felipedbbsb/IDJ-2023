#include "PenguinCannon.h"
#include "InputManager.h"
#include "Game.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> pbody)
    : Component::Component(associated),
      pbody(pbody),
      angle(0){

    Sprite* pengCannon_sprite = new Sprite(associated, PENGUINCANNON_SPRITE);
    associated.AddComponent(std::shared_ptr<Sprite>(pengCannon_sprite));

    Collider *penguinCannon_cl = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)penguinCannon_cl);
    
    std::shared_ptr<GameObject> penguin_body = pbody.lock();

    // Check if the shared pointer is valid
    if (penguin_body){
        associated.box.DefineCenter(penguin_body->box.GetCenter());
    }
    else{
        associated.RequestDelete(); 
    }
}
 
void PenguinCannon::Update(float dt) {
    if (auto penguin_body = pbody.lock()) {
        // Update the position of the cannon's box to match the penguin's box center
        associated.box.DefineCenter(penguin_body->box.GetCenter());
        shootTimer.Update(dt);
        // Calculate the angle in degrees
        Vec2 mousePos(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);
        angle = Vec2::D2points(associated.box.GetCenter(), mousePos).Angle();
        associated.angleDeg = angle * (180.0 / 3.1415);

        // Check for left mouse button press and shoot if cooldown is ready
        if (shootTimer.Get() >= PENGUIN_BULLET_CD) {
            if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
                Shoot();
                shootTimer.Restart();
            }
        }    
    } else {
        // Penguin body is no longer valid, request deletion of the cannon
        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {}

void PenguinCannon::Shoot() {
    // Calcula a posição da bala
    Vec2 bulletOffset = Vec2(associated.box.w * PENGUIN_BULLET_WIDTH_FACTOR, 0);
    bulletOffset.Rotate(angle);
    Vec2 bulletPosition = associated.box.GetCenter() + bulletOffset;

    // Cria a bala
    GameObject *bullet = new GameObject(bulletPosition);
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, PENGUIN_BULLET_SPEED, PENGUIN_BULLET_DAMAGE, PENGUIN_BULLET_DISTANCE, PENGUIN_BULLET_SPRITE, "Penguin");
    bullet->AddComponent((std::shared_ptr<Bullet>)bullet_behaviour);

     std::weak_ptr<GameObject> weakbullet = Game::GetInstance().GetState().AddObject(bullet);
    // Configura a sprite da bala se o componente existir
    if ( Sprite *bulletSprite = (Sprite *)weakbullet.lock()->GetComponent("Sprite").get()) {
        bulletSprite->SetFrameCount(PENGUINCANNON_FC);
        bulletSprite->SetFrameTime(PENGUINCANNON_FT);
    }
} 

bool PenguinCannon::Is(std::string type){return (type == "PenguinCannon");}

void PenguinCannon::NotifyCollision(GameObject &other)
{}