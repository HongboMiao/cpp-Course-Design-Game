#pragma once
#include <graphics.h>

// Ç°ÏòÉùÃ÷
class ObstacleMgr;
class ScoreBoard;

class BaseHero {
public:
    
    virtual void init() = 0;
    virtual void jump() = 0;
    virtual void down() = 0;
    virtual void shoot() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void renderBlood() = 0;
    virtual void checkHit(const ObstacleMgr& obstacleMgr) = 0;
    virtual void checkBulletHit(ObstacleMgr& obstacleMgr, ScoreBoard& scoreBoard) = 0;
    virtual void reset() = 0;
    virtual bool isDead() const = 0;

    
    virtual ~BaseHero() = default;

protected:
    
    int x, y;               
    int index;              
    bool jumping;           
    bool downing;         
    int jumpOff;          
    int jumpHeightMax;      
    IMAGE bulletImg;        
    bool bulletExist;       
    int bulletX, bulletY;   
    bool shootFlag;         
    int blood;              
};