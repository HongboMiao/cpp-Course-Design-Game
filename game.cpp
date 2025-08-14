#include "game.h"


Game::Game() :
    hero(nullptr),
    gameover(false),
    win(false),
    timer(0),
    t(0),
    FRAME_DELAY(16) {
}

Game::~Game() {
    if (hero != nullptr) {
        delete hero;
        hero = nullptr;
    }
    closegraph();
}

void Game::run() {
    init();          
    selectHero();    

    while (true) {
        handleInput(); 
        update();     
        render();    

     
        if (gameover) {
            handleGameOver();
        }
        else if (win) {
            handleWin();
        }

        Sleep(FRAME_DELAY);
    }
}

void Game::init() {
    initgraph(1012, 396, EW_SHOWCONSOLE);
    loadimage(0, "res/log.jpg");
    system("pause");


    loadimage(0, "res/over1.png");
    system("pause");
    loadimage(0, "res/over2.png");
    Sleep(400);


    bg.load();
    obstacleMgr.load();
    scoreBoard.load();


    mciSendString("play res/bg.mp3 repeat", 0, 0, 0);

    t = GetTickCount();
}


void Game::handleInput() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'w' || ch == 'W') hero->jump();
        if (ch == 's' || ch == 'S') hero->down();
        if (ch == 'a' || ch == 'A') hero->shoot();
    }
}


void Game::update() {
    if (!gameover && !win) {
        
        timer += tool.getDelay();
        if (timer > 30) {
            timer = 0;
            bg.update();
        }

        if (GetTickCount() - t >= 1500) {
            t = GetTickCount();
            obstacleMgr.create();
        }

        
        obstacleMgr.update();
        hero->update();
        hero->checkHit(obstacleMgr);
        hero->checkBulletHit(obstacleMgr, scoreBoard);
        obstacleMgr.checkPass(300, scoreBoard);

        
        if (hero->isDead()) gameover = true;
        if (scoreBoard.win()) win = true;
    }
}


void Game::render() {
    BeginBatchDraw();
    cleardevice();

    bg.render();
    obstacleMgr.render();
    hero->render();
    hero->renderBlood();
    scoreBoard.render();

    if (gameover) {
        loadimage(0, "res/lose_cha.png");
    }
    else if (win) {
        loadimage(0, "res/vic_cha.png");
    }

    FlushBatchDraw();
    EndBatchDraw();
}

void Game::selectHero() {
    bool selected = false;

    while (!selected) {
        cleardevice();
     
        settextcolor(WHITE);
        loadimage(0, "res/start.png");
        settextstyle(24, 0, "SimHei");
        outtextxy(350, 150, "按 P 选择 Hero1");
        outtextxy(350, 200, "按 L 选择 Hero2");
        outtextxy(350, 250, "等待输入...");
        FlushBatchDraw();

        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'p' || ch == 'P') {
                hero = new Hero1(); 
                selected = true;
            }
            else if (ch == 'l' || ch == 'L') {
                hero = new Hero2();  
                selected = true;
            }
        }
        Sleep(50);  
    }

    hero->init(); 
}


void Game::handleGameOver() {
    mciSendString("stop res/bg.mp3", 0, 0, 0);

    char ch = _getch();
    if (ch == 'r' || ch == 'R') {
        gameover = false;
        loadimage(0, "res/log.jpg");
        system("pause");
        loadimage(0, "res/over2.png");
        hero->init();
        scoreBoard.reset();
        mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
    }
    else if (ch == 'e' || ch == 'E') {
       
        mciSendString("stop res/bg.mp3", 0, 0, 0);
        delete hero;
        hero = nullptr;
        closegraph();
        exit(0);
    }
}


void Game::handleWin() {
    mciSendString("stop res/bg.mp3", 0, 0, 0);

    char ch = _getch();
    if (ch == 'r' || ch == 'R') {
        win = false;
        loadimage(0, "res/log.jpg");
        system("pause");
        loadimage(0, "res/over2.png");
        hero->init();
        scoreBoard.reset();
        mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
    }
    else if (ch == 'e' || ch == 'E') {
       
        mciSendString("stop res/bg.mp3", 0, 0, 0);
        delete hero;
        hero = nullptr;
        closegraph();
        exit(0);
    }
}
