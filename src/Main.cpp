#define SDL_MAIN_HANDLED
#include "Game.h"
#include "StageState.h"

#include <iostream>
#include <exception>

int main(int argc, char** argv) {
    try {
        //Game happens here
        Game& game = Game::GetInstance();


        StageState* stagelState = new StageState();
    
        game.Push(stagelState);


        game.Run();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1; // Retorna um código de erro não zero para indicar que ocorreu um erro.
    }

    return 0;
}
