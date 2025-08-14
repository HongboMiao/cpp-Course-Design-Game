#pragma once
#include "base_hero.h"

class Hero2 : public BaseHero {
public:
    Hero2();
    void init() override;
    void jump() override;
    void down() override;
    void shoot() override;
    void update() override;
    void render() override;
    void renderBlood() override;
    void checkHit(const ObstacleMgr& obstacleMgr) override;
    void checkBulletHit(ObstacleMgr& obstacleMgr, ScoreBoard& scoreBoard) override;
    void reset() override;
    bool isDead() const override;

private:
    IMAGE runImgs[12];  // Hero2跑步动画帧（12张，路径res/bark/）
    IMAGE downImgs[2];  // Hero2下蹲动画帧
};