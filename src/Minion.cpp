#include "Minion.h"
#include "Game.h"
#include "Sprite.h"
#include "Collider.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg): Component::Component(associated),
    alienCenter(alienCenter),
    arc(arcOffsetDeg),
    hp(MINION_VIDA)
{
    // Inicializa com sprite fixo
    Sprite* minion_spr = new Sprite(associated, MINION_SPRITE);

    float zoom = ((rand() % 50) / 100.0) + 1;
    minion_spr->SetScale(zoom, zoom);
    associated.AddComponent(std::shared_ptr<Sprite>(minion_spr));

    // Adicionando Collider 
    Collider* minion_collider = new Collider(associated);
    associated.AddComponent((std::shared_ptr<Collider>)minion_collider);

    if (auto reference_center = alienCenter.lock()) {
        radius.x = (reference_center->box.w / 2) * 1.5;
        radius.y = (reference_center->box.h / 2) * 1.5;

        radius.RotateAngle(arc);
        Vec2 pos = radius + Vec2(reference_center->box.x + reference_center->box.w / 2, reference_center->box.y + reference_center->box.h / 2);
        associated.box.DefineCenter(pos.x, pos.y);
        //Minions sempre com a parte de baixo do Sprite virada para o Alien
        // Calculate the vector from the minion to the center
        Vec2 toCenter = reference_center->box.GetCenter() - associated.box.GetCenter();

        // Calculate the angle to face the center
        float angleToCenter = atan2(toCenter.y, toCenter.x);

        // Convert the angle from radians to degrees and set it as the rotation angle
        associated.angleDeg = angleToCenter * 180.0f / 3.14159265359;

    } else {
        associated.RequestDelete();
        std::cout << "No alien reference was found." << std::endl;
    }

    
}

void Minion::Update(float dt) {
    if (hp <= 0){

        associated.RequestDelete();
        GameObject *minion_death = new GameObject();
    
        Sprite *explosion_sprite_minion = new Sprite(*minion_death,MINION_DEATH_SPRITE, 
                                                           MINION_DEATH_SPRITE_FC, 
                                                           MINION_DEATH_SPRITE_FT / MINION_DEATH_SPRITE_FC  ,
                                                           MINION_DEATH_SPRITE_FT);


        explosion_sprite_minion->SetFrameCount(MINION_DEATH_SPRITE_FC);                                               
        minion_death->AddComponent((std::shared_ptr<Sprite>)explosion_sprite_minion);
        // Criando som da morte
        //Sound *explosion_sound_minion = new Sound(*minion_death,MINION_DEATH_SOUND);
        //minion_death->AddComponent((std::shared_ptr<Sound>)explosion_sound_minion);
        minion_death->box.DefineCenter(associated.box.GetCenter());
        Game::GetInstance().GetState().AddObject(minion_death);

        //explosion_sound_minion->Play();
    }


    float angleMovement = dt * MINION_V_ANGULAR;
    associated.angleDeg += angleMovement; // faz girar

    if (auto center = alienCenter.lock()) {
        radius.RotateAngle(angleMovement);
        Vec2 newRef = radius + Vec2(center->box.x + center->box.w / 2, center->box.y + center->box.h / 2);
        associated.box.DefineCenter(newRef.x, newRef.y);
    } else {
        associated.RequestDelete();
    }
}

void Minion::Render()
{}

bool Minion::Is(std::string type)
{
    if (type == "Minion"){return true;}
    else{return false;}
}

void Minion::Shoot(Vec2 target)
{
    Vec2 path = target - associated.box.GetCenter();
    float angle = atan2(path.y, path.x);

    // Criando um bullet
    GameObject* bullet = new GameObject();
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, MINION_V_BULLET, BULLET_DAMAGE, MINION_BULLET_DISTANCE, BULLET_SPRITE, "Minion");
    bullet->AddComponent((std::shared_ptr<Bullet>)bullet_behaviour);

    bullet->box.DefineCenter(associated.box.GetCenter());
 
     
    Game::GetInstance().GetState().AddObject(bullet);

    std::weak_ptr<GameObject> weak_bullet = Game::GetInstance().GetState().AddObject(bullet);
    Sprite* bulletSprite = (Sprite*)weak_bullet.lock()->GetComponent("Sprite").get();
    bulletSprite->SetFrameCount(BULLET_FC);
    bulletSprite->SetFrameTime(BULLET_FT );

    std::cout << "Shoot to target: X"  << target.x << " Y" << target.y  <<  std::endl;
}

void Minion::NotifyCollision(GameObject &other){
    // Try to convert the component to a Bullet
    std::shared_ptr<Bullet> shared_Bullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet"));

    // Check if the component is a bullet and if it wasn't shot by the player
    if (shared_Bullet && !shared_Bullet->WhoIsShooter("Minion")){
        int m_alien = shared_Bullet->GetDamage();
        hp -= m_alien;
        std::cout << "MINION(HP) " << hp << std::endl;
    }       
}