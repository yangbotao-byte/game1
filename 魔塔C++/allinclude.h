#ifndef __ALLINCLUDE_H__
#define __ALLINCLUDE_H__
#define _CRT_SECURE_NO_WARNINGS 1

#define _WINDOW_WIDTH__ 1300
#define _WINDOW_LONG__  650

#include<graphics.h>
#include<iostream>
#include<conio.h>
#include<vector>
#include<string>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdlib>

//music
#include<Windows.h>

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include"hero.h"
#include"particle.h"
#include"Enemy.h"

using namespace std;
struct Animation {
    int currentFrame;     // 当前播放到哪一帧
    int frameCount;       // 总帧数
    float frameTime;      // 每帧播放的时间（秒）
    float elapsedTime;    // 当前帧已经累计播放了多久
    bool loop;            // 是否循环播放
};

struct AttackBox {
    int x, y;       // 左上角位置
    int width, height; // 宽高
    bool active;    // 当前是否启用攻击判定
};

/*游戏函数*/
extern int welcome();
extern int loading();
extern void mainwelcome();
extern void updatehero();
extern void keydetect();
extern void updateUI();
extern void init();
extern int UIdetect();
extern int mymap();
extern int level1();

//关卡门
extern void updatemen();
extern void updatemen1();

/*工具函数*/
extern void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
extern void putimagePNG2(int x, int y, IMAGE* picture);
extern void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);
extern void UpdateAnimation(Animation& anim, float deltaTime);
extern void updateAttackBox(hero& h);

extern hero hero1;
extern bool isJumping;
extern vector<IMAGE> bin;
extern Enemy empty1;

#endif

