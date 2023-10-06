#pragma once

#include <iostream>
#include <queue>
#include <math.h>
#include <limits>

#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"
#include "Minion.h"
#include "Rect.h"

#include <algorithm> 

#define ALIEN_SPRITE "assets/img/alien.png"
#define ALIEN_VELOCIDADE 100
#define ALIEN_VIDA 50
#define ALIEN_V_ANGULAR 20 // degree/frame
#define MIN_DIST 5

#define ALIEN_DEATH_SPRITE "assets/img/aliendeath.png"
#define ALIEN_DEATH_SPRITE_FC 4.0
#define ALIEN_DEATH_SPRITE_FT 1.0
#define ALIEN_DEATH_SOUND "assets/audio/boom.wav"

#define ALIEN_MOV_TIMER 0.5 + (rand() % 2)
#define ALIEN_TARGET_MAX_DIST 300 




//Class responsible for control of state
class Alien : public Component{
    public:
        Alien(GameObject &associated, int nMinions);
        ~Alien();
        void Start();                                    
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision(GameObject &other);
        static int alienCount;

    private:
        enum AlienState{MOVING, RESTING};
        Vec2 speed;
        int hp;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        int nMinions;

        AlienState state;
        Timer restTimer;
        Vec2 destination;

};

