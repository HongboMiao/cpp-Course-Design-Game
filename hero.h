#pragma once
#include <graphics.h>
#include <vector>

class ObstacleMgr;  // 前向声明
class ScoreBoard;   // 前向声明

class Hero {
public:
    Hero();
    void init();
    void jump();
    void down();
    void shoot();
    void update();
    void render();
    void renderBlood();
    void checkHit(const ObstacleMgr& obstacleMgr);
    void checkBulletHit(ObstacleMgr& obstacleMgr, ScoreBoard& scoreBoard);
    void reset();
    bool isDead() const;

private:
    int x, y;
    int index;
    bool jumping;
    bool downing;
    int jumpOff;
    int jumpHeightMax;
    IMAGE runImgs[14];
    IMAGE downImgs[2];
    IMAGE bulletImg;
    bool bulletExist;
    int bulletX, bulletY;
    bool shootFlag;
    int blood;
};
