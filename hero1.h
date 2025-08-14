#pragma once
#include "base_hero.h"

class Hero1 : public BaseHero {
public:
    Hero1();
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
    IMAGE runImgs[14];  // Hero1跑步动画帧（14张）
    IMAGE downImgs[2];  // Hero1下蹲动画帧
};