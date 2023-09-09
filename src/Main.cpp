
#define SDL_MAIN_HANDLED
#include "Game.h"

int main(int argc, char** argv) {
    std::cout << "Damage applied: "  << std::endl;
    Game& game = Game::GetInstance();
    game.Run();

    return 0;
}