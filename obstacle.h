#pragma once
#include <graphics.h>
#include <vector>

struct obstacle {
    int type, imgIndex, x, y, speed, power;
    bool exist, passed;
    mutable bool hited;
};

class ObstacleMgr {
public:
    ObstacleMgr();
    void load();
    void update();
    void render();
    void create();
    void reset();
    bool checkHeroCollision(int heroX, int heroY, int heroIndex, bool isDown, IMAGE& runImg, IMAGE& downImg, int& blood) const;
    bool checkBulletCollision(int bx, int by);
    void checkPass(int heroX, class ScoreBoard& scoreBoard);

private:
    std::vector<std::vector<IMAGE>> obstacleImgs;
    std::vector<int> obstacleImgHeights;
    obstacle obstacles[9];
    int lastObstacleIndex;
};
