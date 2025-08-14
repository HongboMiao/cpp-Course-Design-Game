#include "scoreboard.h"
#include "tools.h"
#include <cstdio>

ScoreBoard::ScoreBoard() : score(0) {}

void ScoreBoard::load() {
    char name[64];
    for (int i = 0; i < 10; i++) {
        sprintf_s(name, "res/sz/%d.png", i);
        loadimage(&digits[i], name);
    }
}

void ScoreBoard::reset() {
    score = 0;
}

void ScoreBoard::increase() {
    score++;
    printf("score: %d\n", score);
}

void ScoreBoard::render() {
    char str[8];
    sprintf_s(str, "%d", score);
    int x = 20;
    int y = 25;
    for (int i = 0; str[i]; i++) {
        int d = str[i] - '0';
        ToolHelper tool;
        tool.putimagePNG(x, y, &digits[d]);
        x += digits[d].getwidth() + 5;
    }
}

int ScoreBoard::get() const {
    return score;
}

bool ScoreBoard::win() const {
    return score >= WIN_SCORE;
}
