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
    // ��ȡ�ӳ�ʱ��
    int getDelay();

    // PNG͸����ͼ��غ���
    void putimagePNG(int x, int y, IMAGE* picture);
    void putimagePNG2(int x, int y, IMAGE* picture);
    void putimagePNG2(int x, int y, int widthLimit, IMAGE* picture);

    // ����Ѫ��
    void drawBloodBar(int x, int y, int width, int height, int border,
        COLORREF borderColor, COLORREF bgColor, COLORREF fgColor, float percent);

    // ��ײ��⣨�����ཻ��
    bool rectIntersect(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2);

    // ��Ч��غ���
    void preLoadSound(const char* filename);
    void playSound(const char* filename);

private:
    // ��̬��Ա�������ڼ�¼ʱ�䣨���ԭȫ�־�̬������
    static unsigned long long lastTime;
};