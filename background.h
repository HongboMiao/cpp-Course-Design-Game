#pragma once
#include <graphics.h>

// ���ڳߴ糣���������main.cpp����һ�£�
#define WIN_WIDTH 1012
#define WIN_HEIGHT 618

class Background {
public:
    Background();
    ~Background() = default;

    void load();       // �������㱳��ͼƬ
    void update();     // ���±�������״̬
    void render();     // ��Ⱦ���㱳��

private:
    IMAGE bgImages[3]; // �洢���㱳��ͼƬ
    int bgX[3];        // ÿ�㱳����X����
    int bgSpeed[3];    // ÿ�㱳���Ĺ����ٶ�
};
