#pragma once

#define PENGUINCANNON_SPRITE "assets/img/cubngun.png"
#define PENGUIN_BULLET_SPRITE "assets/img/penguinbullet.png"

#define PENGUIN_BULLET_SPEED 200.0
#define PENGUIN_BULLET_DAMAGE 30.0
#define PENGUIN_BULLET_DISTANCE 2000
#define PENGUIN_BULLET_WIDTH_FACTOR 0.75
#define PENGUIN_BULLET_CD 0.25

#define PENGUINCANNON_FC 4
#define PENGUINCANNON_FT 0.2

#include <iostream>
#include <memory>


#include "Sprite.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Component.h"
#include "GameObject.h"

//#include "Timer.h"
//#include "Collider.h"
class PenguinCannon : public Component
{
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();
        //void NotifyCollision(GameObject &other);

    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        //Timer shootCooldown;
};