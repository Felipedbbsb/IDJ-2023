#pragma once

#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.h"
#include "InputManager.h"

//Class responsible for running main game loop
class Game {
    private:
        static Game* instance;
        Game(std::string title, int width, int height);
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