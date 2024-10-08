#pragma once

#define BULLET_SPRITE_PATH "assets/img/minionbullet1"
#include <iostream>

#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "math.h"
#include "Vec2.h"

class Bullet : public Component{
    public:
        Bullet(GameObject &associated, 
                float angle, 
                float speed, 
                int damage, 
                float maxDistance,
                std::string sprite, 
                std::string WhoShooter = "" );

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
        void NotifyCollision(GameObject &other);
        bool WhoIsShooter(std::string WhoShooter);

    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
        std::string WhoShooter;
};