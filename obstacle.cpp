#include "obstacle.h"
#include "tools.h"
#include "scoreboard.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

ObstacleMgr::ObstacleMgr() {
    reset();
}

void ObstacleMgr::load() {
    char name[64];
    std::vector<IMAGE> tmp;
    IMAGE img;

    const char* paths[] = {
        "res/t1.png", "res/t2.png", "res/t3.png", "res/fd.png"
    };

    for (auto path : paths) {
        int width = 50;
        int height = 50;
        if (strcmp(path, "res/fd.png") == 0) {
            height = 25; 
        }
        loadimage(&img, path, 50, height, true);
        tmp.clear();
        tmp.push_back(img);
        obstacleImgs.push_back(tmp);
        obstacleImgHeights.push_back(img.getheight()); 
    }

    std::vector<IMAGE> lionImgs;
    for (int i = 0; i < 6; i++) {
        sprintf_s(name, "res/p%d.png", i + 1);
        loadimage(&img, name,50,50,true);
        lionImgs.push_back(img);
    }
    obstacleImgs.push_back(lionImgs);
    obstacleImgHeights.push_back(lionImgs[0].getheight()); 

    for (int i = 0; i < 4; i++) {
        std::vector<IMAGE> hookImgs;
        sprintf_s(name, "res/h%d.png", i + 1);
        loadimage(&img, name, 63, 260, true);
        hookImgs.push_back(img);
        obstacleImgs.push_back(hookImgs);
        obstacleImgHeights.push_back(img.getheight()); 
    }
    
}

void ObstacleMgr::reset() {
    for (int i = 0; i < 9; i++)
        obstacles[i].exist = false;
    lastObstacleIndex = -1;
}

void ObstacleMgr::create() {
    int slotIndex = -1;
    for (int i = 0; i < 9; ++i) {
        if (!obstacles[i].exist) {
            slotIndex = i;
            break;
        }
    }
    if (slotIndex == -1) return;

    obstacle& o = obstacles[slotIndex];
    o.exist = true;
    o.hited = false;
    o.imgIndex = 0;
    o.passed = false;

    o.type = rand() % 9;

    if (o.type == 5) {
        o.type += rand() % 3 + 1;  
        if (o.type > 8) o.type = 8;  
    }

    if (lastObstacleIndex != -1) {
        obstacle& last = obstacles[lastObstacleIndex];
        if (last.exist && last.type >= 6 && last.type <= 9
            && o.type == 4 && last.x > 512) {
            o.type = 0;
        }
    }
    lastObstacleIndex = slotIndex;

    o.x = 1012;
    int windowHeight = 396;

    int imgHeight = 100;
    if (o.type >= 0 && o.type < obstacleImgHeights.size()) {
        imgHeight = obstacleImgHeights[o.type];
    }

    o.y = 345 + 5 - imgHeight;

    if (o.type == 3) {
        int maxY = windowHeight - imgHeight;
        if (maxY < 0) maxY = 0;
        o.y = rand() % (maxY + 1);
    }
    else if (o.type >= 6 && o.type <= 9) {
        o.y = 0;
    }

    o.speed = (o.type == 4) ? 4 : 0;
    o.power = 15 + (o.type % 3) * 5;

    //std::cout << "type: " << o.type
    //    << " x: " << o.x << " y: " << o.y
    //    << " imgH: " << imgHeight
    //    << " screenH: " << windowHeight << std::endl;
}

void ObstacleMgr::update() {
    for (int i = 0; i < 9; i++) {
        if (obstacles[i].exist) {
            obstacle& o = obstacles[i];
            o.x -= o.speed + 16;
            if (o.x < -obstacleImgs[o.type][0].getwidth() * 2)
                o.exist = false;
            int len = obstacleImgs[o.type].size();
            o.imgIndex = (o.imgIndex + 1) % len;
        }
    }
}

void ObstacleMgr::render() {
    for (int i = 0; i < 9; i++) {
        if (obstacles[i].exist) {
            ToolHelper tool;
            tool.putimagePNG2(obstacles[i].x, obstacles[i].y, 1012,
                &obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);
            //putimage(obstacles[i].x, obstacles[i].y, &obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);

        }
    }
}

bool ObstacleMgr::checkHeroCollision(int heroX, int heroY, int heroIndex, bool isDown, IMAGE& runImg, IMAGE& downImg, int& blood) const {
    ToolHelper tool;
    for (int i = 0; i < 9; i++) {
        if (obstacles[i].exist && !obstacles[i].hited) {
            const obstacle& o = obstacles[i];
            int off = 30;
            int a1x = heroX + off;
            int a1y = isDown ? 345 - downImg.getwidth() / 2 : heroY + off;
            int a2x = heroX + (isDown ? downImg.getwidth() : runImg.getwidth()) - off;
            int a2y = isDown ? 345 : heroY + runImg.getheight();

            //std::cout << "人物矩形 - 右下角: (" << a1x << ", " << a1y
            //    << "), 左上角: (" << a2x << ", " << a2y << ")" << std::endl;
            IMAGE img = obstacleImgs[o.type][o.imgIndex];
            int b1x = o.x + off;
            int b1y = o.y + off;
            int b2x = o.x + img.getwidth() - off;
            int b2y = o.y + img.getheight() - 10;
            //std::cout << "障碍物[type=" << o.type << "]矩形 - 右下角: (" << b1x << ", " << b1y
             //  << "), 左上角: (" << b2x << ", " << b2y << ")" << std::endl;

            if (tool.rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)) {
                blood -= o.power;
                obstacles[i].hited = true;
                return true;
            }
        }
    }
    return false;
}

bool ObstacleMgr::checkBulletCollision(int bx, int by) {
    //std::cout << "===== 子弹坐标: (" << bx << ", " << by << ") =====" << std::endl;

    for (int i = 0; i < 9; i++) {
       // std::cout << "障碍物[" << i << "] - ";

        if (obstacles[i].exist && !obstacles[i].hited) {
            obstacle& o = obstacles[i];
            IMAGE& img = obstacleImgs[o.type][o.imgIndex];
                      //  std::cout << "存在, type=" << o.type 
                      //<< ", 坐标: (" << o.x << ", " << o.y 
                      //<< "), 宽度: " << img.getwidth() 
                      //<< ", 高度: " << img.getheight();
            int off = 5;
            //int a1x = bx + 30;
            //int a1y = by + 90 + off;
            //int a2x = bx + 10 - off;
            //int a2y = by + 90 - 10;
            //int b1x = o.x + off;
            //int b1y = o.y + off;
            //int b2x = o.x + img.getwidth() - off;
            //int b2y = o.y + img.getheight() - 10;//钩子0+260，狮子300+50；
            int a1x = bx - 20;    
            int a2x = bx + 70;    
           
            int a1y = by - 50;    
            int a2y = by + 100;   

            
            int b1x = o.x + off;          
            int b1y = o.y + off;       
            int b2x = o.x + img.getwidth() - off;  
            int b2y = o.y + img.getheight() - off;
            ToolHelper tool;
            if (tool.rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)) {
                o.exist = false;
                o.x = 0;
                return true;
            }
        }
    }
    return false;
}

void ObstacleMgr::checkPass(int heroX, ScoreBoard& scoreBoard) {
    for (int i = 0; i < 9; i++) {
        obstacle& o = obstacles[i];
        if (o.exist && !o.hited && !o.passed &&
            o.x + obstacleImgs[o.type][0].getwidth() < heroX) {
            scoreBoard.increase();
            o.passed = true;
        }
    }
}
