#include <string>
#include <iostream>
#include "Resources.h"
#include "Game.h"
#include "InputManager.h"

#define AUDIO_CHUNKSIZE 1024
#define AUDIO_FREQUENCY MIX_DEFAULT_FREQUENCY
#define AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS MIX_DEFAULT_CHANNELS
#define SOUND_RESOLUTION 64



#define WINDOW_FLAGS 0 // Ex.: SDL_WINDOW_FULLSCREEN

#include <stdexcept> // Para usar exceções

// Static class member initialization
Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) : frameStart(0), dt(0.0) {
    if (Game::instance != nullptr) {
        throw std::runtime_error("Something's Wrong!");
    } else {
        Game::instance = this;
    }

    try {
        if (!InitializeSDL() || !InitializeIMG() || !InitializeMixer() || !CreateWindowAndRenderer(title, width, height, WINDOW_FLAGS)) {
            // Tratar falhas de inicialização aqui, se necessário.
            throw std::runtime_error("Initialization failed");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        // Faça o tratamento de erro adequado aqui, como sair do jogo.
        // Você pode até mesmo lançar uma exceção aqui para indicar que a inicialização do jogo falhou.
    }

    state = new State();
}

bool Game::InitializeSDL() {
    int SDL_FAIL = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (SDL_FAIL != 0) {
        throw std::runtime_error("SDL_Init Failed");
    }
    return true;
}

bool Game::InitializeIMG() {
    int IMG_FAIL = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    if (IMG_FAIL == 0) {
        throw std::runtime_error("IMG_Init Failed");
    }
    return true;
}

bool Game::InitializeMixer() {
    int MSC_FAIL = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3);
    if (MSC_FAIL == 0) {
        throw std::runtime_error("No loader was loaded");
    }

    Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE);
    Mix_AllocateChannels(SOUND_RESOLUTION);

    return true;
}

bool Game::CreateWindowAndRenderer(const std::string& title, int width, int height, int flags) {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (window == nullptr) {
        throw std::runtime_error("Window creation failed");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
        throw std::runtime_error("Failed to create renderer");
    }

    return true;
}

//É utilizado para impedir que uma classe possua mais de uma instância.
Game& Game::GetInstance() {
    //std::string title = "Felipe Dantas Borges - 202021749";
    std::string title = SCREEN_TITLE;
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
    state->Start();
    while (state->QuitRequested()!=true) {
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(Game::GetInstance().GetRenderer());
        //SDL_Delay(10* dt);//por enquanto, depois será criado controle de frame
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}



void Game::CalculateDeltaTime(){
    int time_delta  = SDL_GetTicks();


    dt = (time_delta - frameStart) / 1000.0; // converting time from miliseconds to seconds
    //std::cout << "Frames = " << 1000/dt <<std::endl; 
    frameStart = time_delta;
}

float Game::GetDeltaTime(){return dt;}