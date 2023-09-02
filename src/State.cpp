#include "../include/State.h"

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_MUSIC_LOOP_TIMES -1 // -1 for infinite loop

State::State() {
    quitRequested = false;
    LoadAssets();
    music.Play(BACKGROUND_MUSIC_LOOP_TIMES);
}
//método que cuida de pré-carregar os assets dostate do jogo
void State::LoadAssets() {
    bg.Open(BACKGROUND_SPRITE_PATH);
    music.Open(BACKGROUND_MUSIC_PATH);
}

//atualização do estado das entidades, testes de
//colisões e a checagem relativa ao encerramento do jogo.
void State::Update(float dt) {
    if (SDL_QuitRequested() == true) {
        quitRequested = true;
    }
    SDL_Delay(dt);
}

//renderização do estado do jogo. Isso inclui entidades, cenários, HUD, entre outros.
void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}