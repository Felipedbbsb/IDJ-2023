#pragma once

#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "GameObject.h"



//Class responsible for control of state
class State {
    public:
        State();
        ~State();
        bool QuitRequested();                                       

        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        GameObject background;
        Sprite *bg_sprite;
        Music music;
        bool quitRequested;
        void Input();
        void AddObject(int mouseX, int mouseY);
        std::vector<std::shared_ptr<GameObject>> objectArray;
};