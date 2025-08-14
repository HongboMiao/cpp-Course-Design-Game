#include "background.h"
#include "tools.h"  

Background::Background() {
 
    for (int i = 0; i < 3; i++) {
        bgX[i] = 0;
    }

 
    bgSpeed[0] = 8; 
    bgSpeed[1] = 8;   
    bgSpeed[2] = 16; 
}

void Background::load() {
    char name[64];

    for (int i = 0; i < 3; i++) {
        sprintf_s(name, "res/bg%03d.png", i + 1);  
        loadimage(&bgImages[i], name);            
    }
}

void Background::update() {
   
    for (int i = 0; i < 3; i++) {
        bgX[i] -= bgSpeed[i];

        
        if (bgX[i] < -WIN_WIDTH) {
            bgX[i] = 0;
        }
    }
}

void Background::render() {
    ToolHelper tool;
    tool.putimagePNG2(bgX[0], 0, &bgImages[0]);

    tool.putimagePNG2(bgX[1], 119, &bgImages[1]);

    tool.putimagePNG2(bgX[2], 330, &bgImages[2]);
}
