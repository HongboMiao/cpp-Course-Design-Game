#pragma once
#include <graphics.h>

class ScoreBoard {
public:
    ScoreBoard();
    void load();
    void reset();
    void increase();
    void render();
    int get() const;
    bool win() const;

private:
    int score;
    IMAGE digits[10];
    const int WIN_SCORE = 6;
};
