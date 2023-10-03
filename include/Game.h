#pragma once

#define INCLUDE_SDL

// Screen definition
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
#define SCREEN_TITLE "Felipe Dantas Borges - 202021749"


#include "SDL_include.h"
#include "State.h"
#include "InputManager.h"

//Class responsible for running main game loop
class Game {
    private:
        static Game* instance;
        Game(std::string title, int width, int height);

        bool InitializeSDL();
        bool InitializeIMG();
        bool InitializeMixer();
        bool CreateWindowAndRenderer(const std::string& title, int width, int height, int flags);

        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        int frameStart;
        float dt;
        void CalculateDeltaTime();

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
        float GetDeltaTime();
};