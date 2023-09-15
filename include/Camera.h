#pragma once

#include "Vec2.h"
#include "GameObject.h"

#define CAMERA_SPEED 100 //movement speed

class Camera{
    public:
        static void Follow (GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);
        static Vec2 pos;
        static Vec2 speed;

    private:
        static GameObject* focus;
};