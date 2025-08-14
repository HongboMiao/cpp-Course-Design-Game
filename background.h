#pragma once
#include <graphics.h>

// 窗口尺寸常量（与你的main.cpp保持一致）
#define WIN_WIDTH 1012
#define WIN_HEIGHT 618

class Background {
public:
    Background();
    ~Background() = default;

    void load();       // 加载三层背景图片
    void update();     // 更新背景滚动状态
    void render();     // 渲染三层背景

private:
    IMAGE bgImages[3]; // 存储三层背景图片
    int bgX[3];        // 每层背景的X坐标
    int bgSpeed[3];    // 每层背景的滚动速度
};
