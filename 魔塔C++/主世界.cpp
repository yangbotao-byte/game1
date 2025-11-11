#include "allinclude.h"
#include <vector>
#include <random>
#include <cmath>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

struct Raindrop {
    float x, y;
    float speedY;
    float speedX;
};

struct Splash {
    float x, y;
    int life;
};

// 闪电控制变量
int lightningTimer = 0;
bool isLightning = false;
int lightningDuration = 0;

const int RAIN_NUM = 200;
vector<Raindrop> raindrops;
vector<Splash> splashes;

// 动画实例
static Animation jumpAnim = { 0, 4, 0.5f, 0.0f, true }; // 4帧，每帧0.5秒

void updateBG(IMAGE world[]);
void updateRain();
void updateSplash();
void updateLightning();

bool isJumping = false;
float jumpSpeed = 0.0f;
const float gravity = 1.2f;
const float initialJumpSpeed = -18.0f;

void mainwelcome() {
    init();

    IMAGE world1[3];
    char image[200];
    for (int i = 0; i < 3; i++) {
        sprintf(image, "./bg\\Background_layer0%d.png", i);
        loadimage(&world1[i], image);
    }

    // 初始化雨滴
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> xDist(0, 1300);
    uniform_real_distribution<float> yDist(-600, 0);
    uniform_real_distribution<float> speedDistY(6.0f, 12.0f);
    uniform_real_distribution<float> speedDistX(-2.0f, 2.0f);

    for (int i = 0; i < RAIN_NUM; ++i) {
        raindrops.push_back({ xDist(gen), yDist(gen), speedDistY(gen), speedDistX(gen) });
    }

    // 游戏主循环
    DWORD lastTime = GetTickCount();
    while (1) {
        // 计算帧时间差
        DWORD currentTime = GetTickCount();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        keydetect();
        UIdetect();

        BeginBatchDraw();
        updateBG(world1);
        updateRain();
        updateSplash();
        updateLightning();

        // 跳跃控制
        if (hero1.jumpkey && !isJumping) {
            isJumping = true;
            jumpSpeed = initialJumpSpeed;
            jumpAnim.currentFrame = 0; // 重置动画
            jumpAnim.elapsedTime = 0;
        }

        // 跳跃更新
        if (isJumping) {
            hero1.y += jumpSpeed;
            jumpSpeed += gravity;

            // 更新跳跃动画
            UpdateAnimation(jumpAnim, deltaTime);
            putimagePNG2(hero1.x, hero1.y, &hero1.jump[jumpAnim.currentFrame]);

            // 落地检测
            if (hero1.y >= 170) {
                hero1.y = 170;
                isJumping = false;
                hero1.jumpkey = false;
                jumpSpeed = 0;
            }
        }
        else {
            // 非跳跃状态更新角色
            updatehero();
        }

        updateUI();
        EndBatchDraw();
        Sleep(35);
        bool key = (GetAsyncKeyState('W') & 0x8000) != 0;
        if (hero1.x > 810 && hero1.x < 910 && key == true) {
            break;
        }
        cleardevice();
    }
}

void updateBG(IMAGE world[]) {
    putimagePNG2(0, 0, &world[2]);
    putimagePNG2(0, 100, &world[1]);
    putimagePNG2(0, 0, &world[0]);
}

void updateRain() {
    for (auto& drop : raindrops) {
        drop.x += drop.speedX;
        drop.y += drop.speedY;

        setlinecolor(RGB(180, 180, 255));
        line(drop.x, drop.y, drop.x - drop.speedX * 1.5f, drop.y - drop.speedY * 1.5f);

        if (drop.y > 580) {
            splashes.push_back({ drop.x, 580, 10 });
            drop.y = -10;
            drop.x = rand() % 1300;
            drop.speedY = 6.0f + rand() % 6;
            drop.speedX = -2.0f + rand() % 5;
        }
    }
}

void updateSplash() {
    for (int i = 0; i < splashes.size(); i++) {
        setlinecolor(RGB(150, 150, 255));
        circle(splashes[i].x, splashes[i].y, 3 + (10 - splashes[i].life));

        splashes[i].life--;
        if (splashes[i].life <= 0) {
            splashes.erase(splashes.begin() + i);
            i--;
        }
    }
}

void updateLightning() {
    if (isLightning) {
        setlinecolor(WHITE);
        int startX = rand() % 1200 + 50;
        int y = 0;
        while (y < 600) {
            int nextX = startX + (rand() % 41 - 20);
            int nextY = y + rand() % 40 + 20;
            line(startX, y, nextX, nextY);
            startX = nextX;
            y = nextY;
        }

        lightningDuration--;
        if (lightningDuration <= 0) {
            isLightning = false;
            lightningTimer = rand() % 200 + 10;
        }
    }
    else {
        lightningTimer--;
        if (lightningTimer <= 0) {
            isLightning = true;
            lightningDuration = 3;
            //一定要提前关闭，要不然window会引起冲突导致音乐播放不了
            mciSendString("close ./music\\111.mp3", NULL, 0, NULL);
            mciSendString("open ./music\\111.mp3", 0, 0, 0);
            mciSendString("play ./music\\111.mp3", 0, 0, 0);

        }
    }
}
