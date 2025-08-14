#include "tools.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <graphics.h>

// 初始化静态成员变量
unsigned long long ToolHelper::lastTime = 0;

int ToolHelper::getDelay() {
    unsigned long long currentTime = GetTickCount();
    if (lastTime == 0) {
        lastTime = currentTime;
        return 0;
    }
    else {
        int ret = currentTime - lastTime;
        lastTime = currentTime;
        return ret;
    }
}

// PNG透明绘图实现
void ToolHelper::putimagePNG(int x, int y, IMAGE* picture) {
    DWORD* dstBuffer = GetImageBuffer();   // 目标缓冲区（屏幕）
    DWORD* srcBuffer = GetImageBuffer(picture); // 源缓冲区
    int picW = picture->getwidth();
    int picH = picture->getheight();
    int screenW = getwidth();
    int screenH = getheight();

    for (int iY = 0; iY < picH; iY++) {
        for (int iX = 0; iX < picW; iX++) {
            int dstX = x + iX;
            int dstY = y + iY;

            if (dstX < 0 || dstX >= screenW || dstY < 0 || dstY >= screenH) {
                continue;
            }

            DWORD srcPixel = srcBuffer[iY * picW + iX];
            int dstIndex = dstY * screenW + dstX;
            DWORD dstPixel = dstBuffer[dstIndex];

            BYTE alpha = (srcPixel & 0xff000000) >> 24;
            if (alpha == 0) {
                continue;
            }
            else if (alpha == 255) {
                dstBuffer[dstIndex] = srcPixel;
                continue;
            }

            int srcR = (srcPixel & 0xff0000) >> 16;
            int srcG = (srcPixel & 0xff00) >> 8;
            int srcB = srcPixel & 0xff;

            int dstR = (dstPixel & 0xff0000) >> 16;
            int dstG = (dstPixel & 0xff00) >> 8;
            int dstB = dstPixel & 0xff;

            float alphaRatio = alpha / 255.0f;
            int finalR = (int)(srcR * alphaRatio + dstR * (1 - alphaRatio));
            int finalG = (int)(srcG * alphaRatio + dstG * (1 - alphaRatio));
            int finalB = (int)(srcB * alphaRatio + dstB * (1 - alphaRatio));

            dstBuffer[dstIndex] =
                (finalR << 16) | (finalG << 8) | finalB | (alpha << 24);
        }
    }
}

void ToolHelper::putimagePNG2(int x, int y, IMAGE* picture) {
    IMAGE imgTmp;
    if (y < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, -y,
            picture->getwidth(), picture->getheight() + y);
        SetWorkingImage();
        y = 0;
        picture = &imgTmp;
    }

    if (x < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, -x, 0, picture->getwidth() + x, picture->getheight());
        SetWorkingImage();
        x = 0;
        picture = &imgTmp;
    }

    putimagePNG(x, y, picture);
}

void ToolHelper::putimagePNG2(int x, int y, int winWidth, IMAGE* picture) {
    IMAGE imgTmp;
    int picW = picture->getwidth();
    int picH = picture->getheight();
    int winH = getheight();

    
    if (x + picW < 0 || x > winWidth || y + picH < 0 || y > winH) {
        return;
    }

    putimagePNG(x, y, picture);
}

void ToolHelper::drawBloodBar(int x, int y, int width, int height, int border,
    COLORREF borderColor, COLORREF bgColor, COLORREF fgColor,
    float percent) {
    setlinecolor(borderColor);
    rectangle(x, y, x + width, y + height);

    setfillcolor(bgColor);
    solidrectangle(x + border, y + border, x + width - border, y + height - border);

    int fillWidth = static_cast<int>((width - 2 * border) * percent);
    setfillcolor(fgColor);
    solidrectangle(x + border, y + border, x + border + fillWidth, y + height - border);
}

bool ToolHelper::rectIntersect(int x01, int y01, int x02, int y02,
    int x11, int y11, int x12, int y12) {
    int zx = abs(x01 + x02 - x11 - x12);
    int x = abs(x01 - x02) + abs(x11 - x12);
    int zy = abs(y01 + y02 - y11 - y12);
    int y = abs(y01 - y02) + abs(y11 - y12);
    return  (zx <= x && zy <= y);
}

void ToolHelper::preLoadSound(const char* filename) {
    std::string cmd = "open \"" + std::string(filename) + "\" alias snd";
    mciSendStringA(cmd.c_str(), nullptr, 0, nullptr);
}

void ToolHelper::playSound(const char* filename) {
    std::string cmd = "play snd from 0";
    mciSendStringA(cmd.c_str(), nullptr, 0, nullptr);
}