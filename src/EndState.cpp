#include "EndState.h"
#include "GameData.h"
#include "Game.h"
#include "InputManager.h"
#include "Text.h"

EndState::EndState() : State::State(){   
}

EndState::~EndState(){
    bgEndMusic.Stop();
}

void EndState::LoadAssets() {
    // Determine text and colors based on player's victory
    std::string endText;
    SDL_Color endText_color;

    if (GameData::playerVictory) {
        endText = "YOU WIN!!!";
        endText_color = {0, 200, 0, 0}; // Green
        bgEndMusic.Open(W_MUSIC);
    } else {
        endText = "YOU LOSE";
        endText_color = {200, 0, 0, 0}; // Red
        bgEndMusic.Open(L_MUSIC);
    }

    // Create GameObjects
    GameObject* endState = new GameObject();
    GameObject* msg1 = new GameObject();
    GameObject* msg2 = new GameObject();

    // Create and add components
    Sprite* endState_spr = new Sprite(*endState, GameData::playerVictory ? W_SCREEN : L_SCREEN);
    Text* msg1Text = new Text(*msg1, TITLE_FONT, 50, Text::BLENDED, endText, endText_color, 2);
    Text* msg2Text = new Text(*msg2, TITLE_FONT, 50, Text::BLENDED, "ESC to exit the game or space to play again", endText_color, 2);

    endState->AddComponent(std::make_shared<Sprite>(*endState_spr));
    msg1->AddComponent(std::make_shared<Text>(*msg1Text));
    msg2->AddComponent(std::make_shared<Text>(*msg2Text));

    // Set positions
    msg1->box.DefineCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    msg2->box.DefineCenter(msg1->box.GetCenter() + Vec2(0, 50));

    // Add objects to the state
    AddObject(endState);
    AddObject(msg1);
    AddObject(msg2);
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