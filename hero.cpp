#include "hero.h"
#include "tools.h"
#include "obstacle.h"
#include "scoreboard.h"

Hero::Hero() { init(); }

void Hero::init() {
    char name[64];
    for (int i = 0; i < 14; i++) {
        sprintf_s(name, "res/hero%d.png", i + 1);
        loadimage(&runImgs[i], name);
    }
    loadimage(&downImgs[0], "res/d1.png");
    loadimage(&downImgs[1], "res/d2.png");
    loadimage(&bulletImg, "res/zd.png");
    x = 1012 * 0.3 - runImgs[0].getwidth() / 2;
    y = 345 - runImgs[0].getheight();
    jumpHeightMax = y - 120;
    index = 0;
    jumpOff = -4;
    jumping = downing = shootFlag = bulletExist = false;
    bulletX = x;
    bulletY = y;
    blood = 100;
    ToolHelper tool;
    tool.preLoadSound("res/hit.mp3");
}

void Hero::jump() {
    if (!jumping && !downing)
        jumping = true;
}

void Hero::down() {
    if (!jumping) {
        downing = true;
        index = 0;
    }
}

void Hero::shoot() {
    if (!bulletExist) shootFlag = true;
}

void Hero::update() {
    if (jumping) {
        if (y < jumpHeightMax) jumpOff = 10;
        y += jumpOff;
        if (y > 345 - runImgs[0].getheight()) {
            jumping = false;
            jumpOff = -10;
        }
    }
    else if (downing) {
        static int count = 0;
        int delays[2] = { 4, 14 };
        count++;
        if (count >= delays[index]) {
            count = 0;
            index++;
            if (index >= 2) {
                index = 0;
                downing = false;
            }
        }
    }
    else {
        index = (index + 1) % 12;
    }

    if (shootFlag) {
        bulletExist = true;
        shootFlag = false;
        bulletX = x;
        bulletY = y;
    }
    if (bulletExist && bulletX < 1012)
        bulletX += 50;
}

void Hero::render() {
    ToolHelper tool;
    if (!downing) {
        tool.putimagePNG2(x, y, &runImgs[index]);
    }
    else {
        int dy = 345 - downImgs[index].getheight();
        tool.putimagePNG2(x, dy, &downImgs[index]);
    }

    if (bulletExist) {
        tool.putimagePNG2(bulletX, bulletY + 70, 1012, &bulletImg);
    }
}

void Hero::renderBlood() {
    ToolHelper tool;
    tool.drawBloodBar(10, 10, 200, 10, 2, BLUE, DARKGRAY, RED, blood / 100.0f);
}

bool Hero::isDead() const {
    return blood <= 0;
}

void Hero::reset() {
    blood = 100;
    bulletExist = false;
    bulletX = x;
}

void Hero::checkHit(const ObstacleMgr& obstacleMgr) {
    if (obstacleMgr.checkHeroCollision(x, y, index, downing, runImgs[index], downImgs[index], blood)) {
        ToolHelper tool;
        tool.playSound("res/hit.mp3");
    }
}

void Hero::checkBulletHit(ObstacleMgr& obstacleMgr, ScoreBoard& scoreBoard) {
    if (bulletExist && obstacleMgr.checkBulletCollision(bulletX, bulletY)) {
        bulletExist = false;
        bulletX = x;
        scoreBoard.increase();
    }

    if (bulletX > 1012) {
        bulletExist = false;
        bulletX = x;
    }
}
