#pragma once
#include <graphics.h>
#include <string>
#include "hero1.h"
#include "hero2.h"
#include "obstacle.h"
#include "scoreboard.h"
#include "background.h"

class ToolHelper {
public:
    // 获取延迟时间
    int getDelay();

    // PNG透明绘图相关函数
    void putimagePNG(int x, int y, IMAGE* picture);
    void putimagePNG2(int x, int y, IMAGE* picture);
    void putimagePNG2(int x, int y, int widthLimit, IMAGE* picture);

    // 绘制血条
    void drawBloodBar(int x, int y, int width, int height, int border,
        COLORREF borderColor, COLORREF bgColor, COLORREF fgColor, float percent);

    // 碰撞检测（矩形相交）
    bool rectIntersect(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2);

    // 音效相关函数
    void preLoadSound(const char* filename);
    void playSound(const char* filename);

private:
    // 静态成员变量用于记录时间（替代原全局静态变量）
    static unsigned long long lastTime;
};