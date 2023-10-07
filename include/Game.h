#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF 

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#include "SDL_include.h"
#include "State.h"
#include "InputManager.h"



#include <stack>
#include <iostream>
#include <string>
#include <memory>


class State;


//Class responsible for running main game loop
class Game {
    public:
        Game(std::string title, int width, int height);
        ~Game();
        static Game& GetInstance();
        SDL_Renderer *GetRenderer();
        State& GetCurrentState();
        void Push(State* state);
        void Run();
        float GetDeltaTime();

    private:
        void CalculateDeltaTime();
        int frameStart;
        float dt;
        static Game* instance;

        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;

        std::stack<std::unique_ptr<State>> stateStack;

        bool InitializeSDL();
        bool InitializeIMG();
        bool InitializeMixer();
        bool InitializeTTF();
        bool CreateWindowAndRenderer(const std::string& title, int width, int height, int flags);

};