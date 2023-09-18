#pragma once

#include <iostream>

#include "Component.h"
#include "Camera.h"
#include "GameObject.h"

class CameraFollower : public Component{
    public:
        CameraFollower(GameObject& associated);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};