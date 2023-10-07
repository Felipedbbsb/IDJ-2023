#define SDL_MAIN_HANDLED
#include "Game.h"
#include "TitleState.h"

#include <iostream>
#include <exception>

int main(int argc, char** argv) {
    try {
        //======================== Game happens here ===============================
        Game& game = Game::GetInstance();


        TitleState* initialState = new TitleState();
    
        game.Push(initialState);


        game.Run();
        //==========================================================================
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1; // Retorna um código de erro não zero para indicar que ocorreu um erro.
    }

    return 0;
}
