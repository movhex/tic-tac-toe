#ifndef GAME_H
#define GAME_H

#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <vector>

class Game {
public:
    enum Result : uint8_t;
public:
    Game(void);
    Result run(void);
private:
    enum CellValue : int8_t;
private:
    void showMap(void) const;
    size_t nextMove(int8_t who, int depth);
    CellValue checkWinner(void) const;
    char getChar(size_t pos) const;
    size_t toLinearIndex(size_t i, size_t j) const;
    size_t getPlayerMove(void) const;
private:
    std::vector<CellValue> map;
}; // End of class


enum Game::Result : uint8_t {
    X_WIN,
    O_WIN,
    DRAW,
};


enum Game::CellValue : int8_t {
    BLANK = 0,
    PLAYER = 1,
    BOT = -1
};

#endif // GAME_H
