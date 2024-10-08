#pragma once

#define TITLE_IMAGE "assets/img/title.jpg"
#define TITLE_FONT "assets/font/Play-Regular.ttf"
#define FONT_COLOR {200, 200, 200, 0} // Red Green Blue Alpha
#define TITLE_TEXT "PRESS SPACEBAR TO PLAY"

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1024
#endif
#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 600
#endif

#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Component.h"
#include "StageState.h"
//#include "Text.h"

    class TitleState : public State
{
public:
    TitleState();
    ~TitleState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
};