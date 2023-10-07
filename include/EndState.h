#pragma once

#define W_SCREEN "assets/img/win.jpg"
#define L_SCREEN "assets/img/lose.jpg"

#define W_MUSIC "assets/audio/endStateWin.ogg"
#define L_MUSIC "assets/audio/endStateLose.ogg"

#define TITLE_FONT "assets/font/Call me maybe.ttf"

#include "State.h"
#include "Music.h"
#include "GameObject.h"
#include "Sprite.h"
//#include "Text.h"
#include "TitleState.h"
#include "StageState.h"

class EndState : public State{
    public:
        EndState();
        ~EndState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
    private:
        Music bgEndMusic;
};