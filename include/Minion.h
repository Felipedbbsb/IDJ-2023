#pragma once

#define MINION_SPRITE "assets/img/minion.png"
#define MINION_V_ANGULAR -100
#define MINION_V_BULLET 200.0
#define BULLET_DAMAGE 10.0
#define BULLET_SPRITE "assets/img/minionbullet2.png"
#define BULLET_FC 3
#define BULLET_FT 0.5
#define MINION_BULLET_DISTANCE 1000

#define MINION_DEATH_SPRITE "assets/img/miniondeath.png"
#define MINION_DEATH_SPRITE_FT 1.0
#define MINION_DEATH_SPRITE_FC 4.0
#define MINION_DEATH_SOUND "assets/audio/boom.wav"
#define MINION_VIDA 15

#include <iostream>
#include <memory>
#include <math.h>

#include "Sprite.h"
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Bullet.h"

class Minion : public Component{
public:
    Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);
    void NotifyCollision(GameObject &other);

private:
    Vec2 radius;
    std::weak_ptr<GameObject> alienCenter;
    float arc;
    int hp;
};