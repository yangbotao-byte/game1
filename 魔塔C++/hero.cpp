#define _CRT_SECURE_NO_WARNINGS 1
#include"hero.h"
#include"allinclude.h"
#include<windows.h>
#pragma comment(lib, "Msimg32.lib")
//
//hero::hero() {
//    x = 0;
//    y = 0;
//}

//第一个为静态  第二个为走路  第三个为攻击  
hero::hero(int x1, int y1, int number1, int number2, int number3) {
    x = x1;
    y = y1;
    speed = 10;
    hurt = 20; //普通伤害
    hurt1 = 9; // 魔法伤害
    fangyu = 10;
    tong = 0;
    hp = 100;

    attackL = false;
    attackR = false;

    stand1.resize(number1); // 初始化 stand 的大小
    attack1.resize(number3); // 初始化 attack 的大小
    walk1.resize(number2); // 初始化 walk 的大小
    walk2.resize(number2); // 初始化 walk2 的大小
    attack2.resize(number3); // 初始化 attack2 的大小
    jump.resize(4); // 初始化 attack2 的大小

    for (int i = 0; i < number1; i++) {
        char path[50];
        sprintf(path, "./hero/stand/frame_%d.png", i);
        //这里的尾插法会扩大stand/attack/walk的容器，这样就会导致数组越界
        stand.push_back(path);
        //printf("Loading: %s\n", path); // 在构造时打印路径
    }

    for (int i = 0; i < number2; ++i) {
        char path[50];
        sprintf(path, "./hero/walk/frame_%d.png", i);
        walk.push_back(path);
        //printf("Loading: %s\n", path); // 在构造时打印路径
    }

    for (int i = 0; i < number3; ++i) {
        char path[50];
        sprintf(path, "./hero/attack/frame_%d.png", i);
        attack.push_back(path);
        //printf("Loading: %s\n", path); // 在构造时打印路径
    }

    for (int i = 0; i < number2; ++i) {
        char path[50];
        sprintf(path, "./hero/Rwalk/frame_%d.png", i);
        swalk.push_back(path);
        //printf("Loading: %s\n", path); // 在构造时打印路径
    }

    for (int i = 0; i < number3; ++i) {
        char path[50];
        sprintf(path, "./hero/Lattack/frame_%d.png", i);
        sattack.push_back(path);
        //printf("Loading: %s\n", path); // 在构造时打印路径
    }

    for (int i = 0; i < 4; ++i) {
        char path[50];
        sprintf(path, "./hero/jump/frame_0%d.png", i);
        loadimage(&jump[i], path);
        //printf("Loading: %s\n", path); // 在构造时打印路径
    }
}


void hero::updatestand(int count) {
    putimagePNG2(x, y, &stand1[count]);
}

void hero::updatewalk(int count) {
    if (Rwalkkey) {
        count = count % walk1.size(); // 防止越界，确保换帧
        x += speed;
        putimagePNG2(x, y, &walk1[count]);
        //printf("Loading: %s\n", walk1[count]); // 在构造时打印路径
        /*char info[64];
        sprintf(info, "hero1.x = %.1f", x);
        outtextxy(500, 40, info);*/
        
    }
    
    else if (Lwalkkey) {
        count = count % walk2.size(); // 防止越界，确保换帧
        x -= speed;
        putimagePNG2(x, y, &walk2[count]);
        //printf("Loading: %s\n", walk2[count]); // 在构造时打印路径
        /*char info[64];
        sprintf(info, "hero1.x = %.1f", x);
        outtextxy(500, 50, info);*/
    }

}

void hero::updateattack(int count) {
    if (attackkey && attackR) {
        count = count % attack1.size(); // 防止越界，确保换帧
        putimagePNG2(x, y, &attack1[count]);
        printf("Loading: %s\n", attack1[count]); // 在构造时打印路径
    }
    else if (attackkey && attackL) {
        count = count % attack2.size(); // 防止越界，确保换帧
        putimagePNG2(x, y, &attack2[count]);
        printf("Loading: %s\n", attack2[count]); // 在构造时打印路径
    }

}

void hero::beHit(int attackPower) {
    hp = hp - attackPower;
}

void hero::boolhero() {
    int maxHp = 100;           // 假设最大血量为100
    int barWidth = 300;
    int barHeight = 15;

    int healthWidth = hp * barWidth / maxHp;
    int barX = 200, barY = 60;

    // 血条背景（灰色）
    setfillcolor(DARKGRAY);
    fillrectangle(barX, barY, barX + barWidth, barY + barHeight);

    // 当前血条（红色）
    setfillcolor(RED);
    fillrectangle(barX, barY, barX + healthWidth, barY + barHeight);

    // 受击框（用于调试）
    setlinecolor(GREEN);
    rectangle(barX, barY, barX + barWidth, barY + barHeight);
}

void hero::freeze(){
    sleep = true;
    sleeptime = 30;
}

//void hero::updatejump() {
//    if (jumpkey) {
//        for (int i = 0; i < 4; i++) {
//            putimagePNG2(x, y, &jump[i]);
//        if (i == 0 || i == 1) {
//            y += 40;
//            Sleep(10);
//        }
//        else if (i == 2 || i == 3) {
//            y -= 40;
//            Sleep(10);
//        }
//        }
//    }
//}