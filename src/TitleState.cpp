#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"

  

TitleState::TitleState() : State::State(){
} 

TitleState::~TitleState(){} 

void TitleState::Update(float dt){   
    InputManager& input = InputManager::GetInstance();

    // If the event is quit, set the termination flag
    if ((input.KeyPress(ESCAPE_KEY)) || input.QuitRequested()){
        quitRequested = true;
    }

    // If space, changes to StageState
    if (input.KeyPress(SPACEBAR_KEY)){
        StageState* new_stage = new StageState();
        Game::GetInstance().Push(new_stage); 
        popRequested = true;
    }

    //============================ Checks whether to delete objects and updates ========================================
    UpdateArray(dt);
    
}

void TitleState::LoadAssets(){
    GameObject *menu = new GameObject();
    Sprite* menuSprite= new Sprite(*menu, TITLE_IMAGE);
    menu->AddComponent((std::shared_ptr<Component>)menuSprite);

    //Na transicao de Stage para Title pode ocorrer de descentralizar com a camera, para evitar coloca o componente de camera
    CameraFollower* cameraMenu = new CameraFollower(*menu);
    menu->AddComponent((std::shared_ptr<Component>)cameraMenu);
    AddObject(menu);

    GameObject *title = new GameObject();
    Text *titleText = new Text(*title, TITLE_FONT, 50, Text::BLENDED, TITLE_TEXT, FONT_COLOR, 2);
    title->AddComponent((std::shared_ptr<Component>)titleText);
    title->box.DefineCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    AddObject(title);
}

void TitleState::Render(){
    RenderArray();
}

void TitleState::Start(){
    LoadAssets();
    StartArray();
    started = true;
}

void TitleState::Pause(){}

void TitleState::Resume(){

}