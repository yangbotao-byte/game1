#include "allinclude.h"

// 原有图片
IMAGE UIAF;
IMAGE UIWM;
IMAGE UIBAG;
IMAGE BAG;
IMAGE UICHUAN[12];

// GIF 拆帧相关
const int GIF_FRAME_COUNT = 12; // 实际帧数（从 frame_01 到 frame_12）
const int GIF_FRAME_DELAY = 100; // 每帧时间 ms
IMAGE gifFrames[GIF_FRAME_COUNT]; // 注意：下标从 0 开始存储，但播放时从 1 开始
int currentGifFrame = 1; // 初始从 1 开始播放
DWORD lastGifFrameTime = 0;

// 函数声明
void UI_BAG();
int UIdetect();

void init() {
    loadimage(&UIAF, "./UI\\UI_Avatar_frame.png");
    loadimage(&UIWM, "./UI\\TO.png");
    loadimage(&UIBAG, "./set\\bag.png");
    loadimage(&BAG, "./set\\bagset.png");

    for (int i = 0; i < 12; i++) {
        char path[64];
        sprintf_s(path, "./UI/chuan/frame%d.png", i);
        loadimage(&UICHUAN[i], path);
    }

    // 加载 GIF 拆帧 PNG 图片（下标从 0 到 11，但播放时从下标 1 开始）
    for (int i = 0; i < GIF_FRAME_COUNT; ++i) {
        char path[64];
        sprintf_s(path, "./set/hero/frame_%02d_delay-0.1s.png", i + 1); // 生成 frame_01 ~ frame_12
        loadimage(&gifFrames[i], path);
    }
}

void updateUI() {
    static int currentChuanFrame = 0;      // 当前传送阵动画帧
    static DWORD lastChuanFrameTime = 0;  // 上次更新时间戳

    DWORD now = GetTickCount();
    if (now - lastChuanFrameTime >= GIF_FRAME_DELAY) { // 用同样的帧延迟
        currentChuanFrame++;
        if (currentChuanFrame >= 12) currentChuanFrame = 0;
        lastChuanFrameTime = now;
    }

    // 头像和头像框
    putimagePNG2(103, 8, &UIWM);
    putimagePNG2(0, 0, &UIAF);

    // 图标
    putimagePNG2(0, 120, &UIBAG);

    putimagePNG2(1050, 480, &UICHUAN[currentChuanFrame]);

    settextcolor(RGB(180, 180, 180));
    settextstyle(15, 0, _T("黑体"));
    outtextxy(0, 120 + UIBAG.getheight(), "Please Press 1.");
}


int UIdetect() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == '1') {
            cleardevice();
            UI_BAG();
        }
        if (ch == '2') {
            return 10; // 返回主菜单指令
        }
    }
    return 0;
}

void UI_BAG() {
    lastGifFrameTime = GetTickCount(); // 初始化动画时间

    while (1) {
        int key = UIdetect();
        if (key == 10) {
            cleardevice();
            break; // 返回上一级
        }

        DWORD now = GetTickCount();

        // 播放动画（从 gifFrames[1] 到 gifFrames[GIF_FRAME_COUNT - 1]）
        if (now - lastGifFrameTime >= GIF_FRAME_DELAY) {
            currentGifFrame++;
            if (currentGifFrame >= GIF_FRAME_COUNT) {
                currentGifFrame = 1; // 回到第1帧，跳过下标为0的帧
            }
            lastGifFrameTime = now;
        }

        BeginBatchDraw();

        // 背景
        putimage(0, 0, &BAG);

        // 显示当前帧（从 gifFrames[1] 起）
        putimage(170, 250, &gifFrames[currentGifFrame]);

        //// 调试
        //settextcolor(WHITE);
        //settextstyle(20, 0, _T("黑体"));
        //char info[32];
        //sprintf_s(info, "Frame: %d", currentGifFrame);
        //outtextxy(10, 10, info);

        //属性的显示
        settextcolor(WHITE);
        settextstyle(15, 0, _T("黑体"));
        char info[32];
        sprintf_s(info, "角色的基本属性:");
        outtextxy(600, 200, info);

        char Text[64];

        //伤害
        int hurt = hero1.hurt;
        sprintf_s(Text, "攻击力: %d", hurt);
        outtextxy(600, 220, Text);

        //速度
        int speed = hero1.speed;
        sprintf_s(Text, "速度值: %d", speed);
        outtextxy(600, 240, Text);

        //防御
        int fangyu = hero1.fangyu;
        sprintf_s(Text, "防御力: %d", fangyu);
        outtextxy(600, 260, Text);

        //法伤
        int fa = hero1.hurt1;
        sprintf_s(Text, "法伤值: %d", fa);
        outtextxy(600, 280, Text);

        //通关
        int tong = hero1.tong;
        sprintf_s(Text, "通关数 % d", tong);
        outtextxy(600, 340, Text);


        EndBatchDraw();

        Sleep(10); // 减少 CPU 占用
    }
}
