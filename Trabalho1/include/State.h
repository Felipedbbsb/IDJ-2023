#pragma once

#include "Sprite.h"
#include "Music.h"


//Class responsible for control of state
class State {
    public:
        State();

        bool QuitRequested();

        void LoadAssets();
        void Update(float dt);
        void Render();

    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};