#pragma once

#define PENGUINBODY_SPRITE "assets/img/penguin.png"
#define PENGUIN_DEATH "assets/img/penguindeath.png"
#define PENGUIN_DEATH_SOUND "assets/audio/boom.wav"

#define PENGUIN_ACC 0.025
#define SPEED_MAX 2.5
#define SPEED_ANG 1
#define PENGUIN_HP 100

#define PENGUIN_DEATH_FC 5.0
#define PENGUIN_DEATH_FT 0.5


#include <memory>

#include "Component.h"
#include "Vec2.h"
#include "Sound.h"
#include "Bullet.h"
#include "Sprite.h"
#include "GameObject.h"


//#include "Collider.h"



class PenguinBody : public Component{
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        static PenguinBody* player;
        void NotifyCollision(GameObject &other);
        Vec2 Pos();

    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
};