#pragma once

#include <iostream>
#include <queue>
#include <math.h>
#include <limits>

#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"


#define ALIEN_SPRITE "assets/img/alien.png"
#define ALIEN_HP 50
#define ALIEN_VELOCITY 150
#define ALIEN_ANG_VEL 2 // degree/frame
#define MIN_DIST 5

enum ActionType{MOVE, SHOOT};  



//Class responsible for control of state
class Alien : public Component{
    public:
        Alien(GameObject &associated, int nMinions);
        ~Alien();
        void Start();                                    
        void Update(float dt);
        void Render();

        bool Is(std::string type);

    private:
        class Action{
            public:
                Action(ActionType type, float x, float y);
                  
                ActionType type;
                Vec2 pos;
            };

        Vec2 speed;
        int hp;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        int nMinions;
};

