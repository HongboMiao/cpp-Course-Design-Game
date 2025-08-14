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
    DWORD t;                 // ʱ����������ڿ����ϰ�������
    const int FRAME_DELAY;   // ֡�ӳ٣�������Ϸ֡��

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
