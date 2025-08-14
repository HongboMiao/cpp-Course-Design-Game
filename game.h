#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include "hero1.h"
#include "hero2.h"
#include "obstacle.h"
#include "scoreboard.h"
#include "background.h"
#include "tools.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class Game {
private:
    BaseHero* hero;          
    Background bg;          
    ObstacleMgr obstacleMgr; 
    ScoreBoard scoreBoard;   
    ToolHelper tool;         
    bool gameover;           
    bool win;                
    int timer;          
    DWORD t;                 // 时间变量，用于控制障碍物生成
    const int FRAME_DELAY;   // 帧延迟，控制游戏帧率

public:
    
    Game();
    ~Game();

    
    void run();

private:
    
    void init();

    void handleInput();

    void update();

    void render();

    void selectHero();

    void handleGameOver();

    void handleWin();
};

#endif 
