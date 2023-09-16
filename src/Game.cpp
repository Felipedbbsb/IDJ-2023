#include <string>
#include <iostream>
#include "Resources.h"
#include "Game.h"
#include "InputManager.h"

#define AUDIO_CHUNKSIZE 1024
#define AUDIO_FREQUENCY MIX_DEFAULT_FREQUENCY
#define AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS MIX_DEFAULT_CHANNELS
#define SOUND_RESOLUTION 32

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
#define SCREEN_TITLE "Felipe Dantas Borges - 202021749"

#define WINDOW_FLAGS 0 // Ex.: SDL_WINDOW_FULLSCREEN

// Static class member initialization
Game *Game::instance = nullptr;


Game::Game (std::string title, int width, int height) : frameStart(0),
                                                       dt(0.0){
    int SDL_ERROR;
    int IMG_ERROR;
    int MSC_ERROR;

    if (Game::instance != nullptr) {
        std::cout << "Something's Wrong!";
    } else {
        Game::instance = this;
    }

    //Inicializacao da biblioteca SDL
    SDL_ERROR = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (SDL_ERROR != 0) { 
        std::cout << "SDL_Init Failed";
    } else {
        std::cout << "SDL_Init started" << std::endl;


        //Inicializacao de loader de IMG_INIT
        IMG_ERROR = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        if (IMG_ERROR == 0){
            std::cout << "IMG_Init failed";
        } else {
            std::cout << "IMG_Init started" << std::endl;

            //Inicializacao de bibliotecas de som via mixer
            MSC_ERROR = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3);
            if (MSC_ERROR == 0) {
                std::cout << "No loader was loaded";
            } else {
                std::cout << "Mix_Init started correctly" << std::endl;

                //Inicializacao de canais de áudio
                Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE);
                Mix_AllocateChannels(SOUND_RESOLUTION);

                //Criação de janela
                window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAGS);
                if (window == nullptr) {
                    std::cout << "Window creation failed" <<std::endl;
                } else {
                    std::cout << "Window successfully created!" << std::endl;
                }
                //Criação de render
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //Use SDL_RENDERER_ACCELERATED, para requisitar o uso de OpenGL ouDirect3D.
                if (renderer == nullptr) {
                    std::cout << "Failed to create renderer" << std::endl;
                } else {
                    std::cout << "Renderer successfully created!" << std::endl;
                }
            }
        }
    } // End of initialization routine
    state = new State();
}

//É utilizado para impedir que uma classe possua mais de uma instância.
Game& Game::GetInstance() {
    std::string title = "Felipe Dantas Borges - 202021749";
    //std::string title = SCREEN_TITLE;
    // dimensoes da janela do jogo
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;

    if (Game::instance != nullptr) {
        return *Game::instance;
    } else {
        Game::instance = new Game(title, width, height);
        return *Game::instance;
    }
}


//A ordem importa! Faça na ordem inversa da inizialização
Game::~Game() {
    Mix_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

State& Game::GetState () {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}



//GAME LOOP

void Game::Run() {
    while (state->QuitRequested()!=true) {
         CalculateDeltaTime();
        InputManager::GetInstance().Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(Game::GetInstance().GetRenderer());
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}



void Game::CalculateDeltaTime(){
    int time_delta  = SDL_GetTicks();
    //std::cout << "frameStart: " << frameStart << std::endl;
    //std::cout << "time_delta: " << time_delta << std::endl;

    dt = (time_delta - frameStart) / 1000.0; // converting time from miliseconds to seconds
    //std::cout << "dt: " << dt << std::endl;
    //std::cout << "Frames = " << 1000/dt <<std::endl; 
    frameStart = time_delta;
}

float Game::GetDeltaTime(){return dt;}