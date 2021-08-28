#include <cstdlib>
#include <iostream>

#include "game.h"


Game::Game(void) : map(9, BLANK)
{

}

Game::Result Game::run(void)
{
    bool user = true;
 
    showMap();

    for (size_t i = 0; i < 9; i++) {

        while (user) {
            
            size_t move = getPlayerMove();

            if (map[move] != BLANK) {
                continue;
            }
 
            map[move] = PLAYER;
            break;
        }

        if (!user) {
            map[nextMove(BOT, 0)] = BOT;
        }
 
        showMap();

        if (CellValue win = checkWinner()) {
            if (win == PLAYER) {
                return X_WIN;
            }
            else {
                return O_WIN;
            }
        }
        user = !user;
    }

    return DRAW;
}


void Game::showMap(void) const
{
#if defined(_WIN32)
    std::system("cls");
#else
    std::system("clear");
#endif

    std::fprintf(stdout,
        " %c | %c | %c \n"
        "---+---+---\n"
        " %c | %c | %c \n"
        "---+---+---\n"
        " %c | %c | %c \n\n",
        getChar(0), getChar(1), getChar(2),
        getChar(3), getChar(4), getChar(5),
        getChar(6), getChar(7), getChar(8)
    );
}


size_t Game::nextMove(int8_t who, int depth)
{
    int best = -1;
    int changed = 0;
 
    int score = checkWinner();

    if (score) {
        return (score == who) ? PLAYER : BOT;
    }
 
    for (size_t i = 0; i < 9; ++i) {
        if (map[i]) {
            continue;
        }

        changed = who;
        map[i] = static_cast<CellValue>(who);
        score = -nextMove(-who, depth + 1);
        map[i] = BLANK;
 
        if (score <= best) {
            continue;
        }
        if (!depth) {
            return i;
        }

        best = score;
    }
 
    return changed ? best : 0;
}


Game::CellValue Game::checkWinner(void) const
{
    for (size_t i = 0; i < 3; ++i) {
        if (map[toLinearIndex(i, 0)] &&
            map[toLinearIndex(i, 1)] == map[toLinearIndex(i, 0)] &&
            map[toLinearIndex(i, 2)] == map[toLinearIndex(i, 0)])
        {
            return map[toLinearIndex(i, 0)];
        }
        if (map[toLinearIndex(0, i)] &&
            map[toLinearIndex(1, i)] == map[toLinearIndex(0, i)] &&
            map[toLinearIndex(2, i)] == map[toLinearIndex(0, i)])
        {
            return map[toLinearIndex(0, i)];
        }
    }
    if (!map[toLinearIndex(1, 1)]) {
        return BLANK;
    }
 
    if (map[toLinearIndex(1, 1)] == map[toLinearIndex(0, 0)] &&
        map[toLinearIndex(2, 2)] == map[toLinearIndex(0, 0)])
    {
        return map[toLinearIndex(0, 0)];
    }
    if (map[toLinearIndex(1, 1)] == map[toLinearIndex(2, 0)] &&
        map[toLinearIndex(0, 2)] == map[toLinearIndex(1, 1)])
    {
        return map[toLinearIndex(1, 1)];
    }
 
    return BLANK;
}

char Game::getChar(size_t pos) const
{
    if (map[pos] == 1) {
        return 'X';
    }
    if (map[pos] == -1) {
        return 'O';
    }
    return 0x31 + pos;
}


size_t Game::toLinearIndex(size_t i, size_t j) const
{
    return i * 3 + j;
}


size_t Game::getPlayerMove(void) const
{
    size_t move;

    do {
        std::cout << "Your turn" << std::endl;
        std::cin >> move;
        move -= 1;
    } while (move >= 9);

    return move;
}
