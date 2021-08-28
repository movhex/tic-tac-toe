#include <iostream>

#include "game.h"


int main(void)
{
    Game game;

    switch (game.run()) {
    case Game::X_WIN:
        std::cout << "You win" << std::endl;
        break;
    case Game::O_WIN:
        std::cout << "Bot win" << std::endl;
        break;
    default:
        std::cout << "Draw" << std::endl;
    };

    return 0;
}
