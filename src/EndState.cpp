#include "EndState.h"
#include "GameData.h"
#include "Game.h"
#include "InputManager.h"


EndState::EndState() : State::State(){   
}

EndState::~EndState(){
    bgEndMusic.Stop();
}

void EndState::LoadAssets(){
    
    GameObject* endState = new GameObject();
    GameObject* firstMsg = new GameObject();

    Sprite* endStateSprite;
    //Text* firstMsgText;

    //SDL_Color endTextColor;
    //std::string conditinalText;

    if (GameData::playerVictory){
        endStateSprite = new Sprite(*endState, W_SCREEN);
        //conditinalText = "CONGRATULATIONS!!! You have won!";
        //endTextColor = {0, 200, 0, 0}; // Green
        bgEndMusic.Open(W_MUSIC);
    }
    else{
        endStateSprite = new Sprite(*endState, L_SCREEN);
        //conditinalText = "Oh no! You have lost!";
        //endTextColor = {200, 0, 0, 0}; // Red
        bgEndMusic.Open(L_MUSIC);
    }
    //std::string text = conditinalText;
    //firstMsgText = new Text(*firstMsg, TITLE_FONT, 50, Text::BLENDED, text, endTextColor, 2);

    endState->AddComponent((std::shared_ptr<Component>)endStateSprite);
    //firstMsg->AddComponent((std::shared_ptr<Component>)firstMsgText);
    //firstMsg->box.DefineCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    AddObject(endState);
    std::weak_ptr<GameObject> weak_firstMsg = AddObject(firstMsg);

    //GameObject* secondMsg = new GameObject();
    //Text *secondMsgText = new Text(*secondMsg, TITLE_FONT, 40, Text::BLENDED, "Press ESC to go to Menu or SPACEBAR to play again", endTextColor, 2);
    //secondMsg->AddComponent((std::shared_ptr<Component>)secondMsgText);
    //secondMsg->box.DefineCenter(weak_firstMsg.lock()->box.GetCenter() + Vec2(0, 50));
    //AddObject(secondMsg);
}

void EndState::Update(float dt) 
{
    InputManager& input = InputManager::GetInstance();

    // If the event is quit, set the termination flag
    if ((input.KeyPress(ESCAPE_KEY)) || input.QuitRequested()){ 
        quitRequested = true;
    }
    
    
    // If space, changes to StageState
    if (input.KeyPress(SPACEBAR_KEY)){   
        TitleState* title = new TitleState();
        Game::GetInstance().Push(title);
        popRequested = true;
    }

    //============================ Checks whether to delete objects and updates ========================================
    UpdateArray(dt);
}
void EndState::Render(){
    RenderArray();
}

void EndState::Start(){
    LoadAssets();
    StartArray();
    started = true;
    bgEndMusic.Play();
}

void EndState::Pause(){
    bgEndMusic.Stop(0);
}

void EndState::Resume(){ 
    bgEndMusic.Play();
}