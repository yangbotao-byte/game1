#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>
#include"allinclude.h"
using namespace std;

// 星空粒子结构
struct Star {
    float x, y;
    float speed;
    float brightness;
};

//实现彩色文字
// 区间划分
// 0-59°: 红主导
// 60-119°: 绿主导
// 120-179°: 绿蓝过渡
// 180-239°: 蓝主导
// 240-299°: 蓝红过渡
// 300-359°: 红主导
//COLORREF 是 Windows API 中定义的一种 32 位无符号整型（DWORD），用于表示 RGB 颜色值

// HSV转RGB函数
COLORREF HSVtoRGB(int h, float s, float v) {
    float r, g, b;
    int i = h / 60;
    float f = h / 60.0f - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    switch (i % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
    }
    int a;

    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}

//星空例子初始化
//生成随机种子，根据我上面设置的范围来进行生成随机数字塞入到容器里面
vector<Star> initStars(int count) {
    vector<Star> stars;
    //这种组合是现代 C++ 推荐的标准随机数生成方式，取代了传统的 rand() 和 srand()
    random_device rd; //生成随机数字种子
    mt19937 gen(rd());//初始化随机数字种子
    //规定随机数字的值
    uniform_real_distribution<float> xDist(0, 1300);
    uniform_real_distribution<float> yDist(0, 600);
    uniform_real_distribution<float> speedDist(0.5, 2.0);
    uniform_real_distribution<float> brightDist(200, 400);

    for (int i = 0; i < count; ++i) {
        stars.push_back({ xDist(gen), yDist(gen), speedDist(gen), brightDist(gen) });
    }
    return stars;
}

// 更新和绘制星空
void updateStars(vector<Star>& stars) {
    for (auto& star : stars) {
        star.y += star.speed;
        if (star.y > _WINDOW_LONG__) {
            star.y = 0;
            star.x = rand() % _WINDOW_WIDTH__;
        }
        //putpixel 是一个在多种图形库中常见的函数，用于在指定坐标位置绘制一个像素点
        //虽然它不是C++标准库的一部分，但在许多图形编程环境中都能找到类似的实现
        setfillcolor(RGB((int)star.brightness, (int)star.brightness, (int)star.brightness));
        fillcircle((int)star.x, (int)star.y, 2 + (int)(star.speed * 0.9)); // 半径随速度增大
    }
}

// 获取文本宽度
int GetTextWidth(const char* text, int fontSize, const char* fontName = "黑体") {
    LOGFONT f;
    gettextstyle(&f);
    int oldSize = f.lfHeight;
    f.lfHeight = fontSize;
    strcpy_s(f.lfFaceName, fontName);
    settextstyle(&f);
    int width = textwidth(text);
    f.lfHeight = oldSize;
    settextstyle(&f);
    return width;
}

int welcome() {

    vector<Star> stars = initStars(150);

    vector<string> menuItems = {
        "Game Begin",
        "Option",
        "Introduce",
        "Exit Game"
    };

    int selectedIndex = 0;

    const int menuItemHeight = 60;
    const int menuTotalHeight = menuItems.size() * menuItemHeight;
    const int menuStartY = (600 - menuTotalHeight) / 2;

    // 火焰粒子结构体
    struct FireParticle {
        float x, y;
        float speedY;
        int lifetime;
        int age;
    };

    vector<FireParticle> fireParticles;

    // 初始化随机生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> fireXDist(0, 1300);         // 火焰横坐标分布
    uniform_real_distribution<float> fireSpeedDist(1.0f, 3.0f);  // 火焰上升速度分布
    uniform_int_distribution<int> fireLifeDist(30, 60);          // 火焰粒子寿命分布

    // 主循环
    while (true) {
        BeginBatchDraw();
        cleardevice();
        updateStars(stars); // 更新并绘制星空背景

        // 生成新的火焰粒子
        for (int i = 0; i < 8; ++i) {
            fireParticles.push_back({
                fireXDist(gen),   // 起始 X 坐标
                650,              // 起始 Y 坐标，靠近窗口底部
                fireSpeedDist(gen),  // 上升速度
                fireLifeDist(gen),   // 粒子生命周期
                0                   // 初始年龄
                });
        }

        // 更新并绘制火焰粒子
        for (auto it = fireParticles.begin(); it != fireParticles.end();) {
            it->y -= it->speedY;  // 上升
            it->age++;            // 增加年龄

            float progress = (float)it->age / it->lifetime;

            // 从黄色（40度）逐渐变为红色（0度），再趋近黑色（v减小）
            int hue = (int)(40 - 40 * progress);
            if (hue < 0) hue = 0;
            COLORREF color = HSVtoRGB(hue, 1.0f, 1.0f - progress * 0.5f);

            setfillcolor(color);
            fillcircle((int)it->x, (int)it->y, 3);  // 粒子绘制为小圆点

            // 如果超出寿命则删除该粒子
            if (it->age >= it->lifetime)
                it = fireParticles.erase(it);
            else
                ++it;
        }

        // 动态标题
        static float titleOffset = 0;
        titleOffset += 0.04f;
        int titleY = 50 + (int)(6 * sin(titleOffset));

        settextcolor(WHITE);
        settextstyle(48, 0, _T("黑体"));
        const char* title = "诅咒之刃";
        int titleWidth = GetTextWidth(title, 48, "黑体");
        outtextxy((1300 - titleWidth) / 2, titleY, _T(title));

        // 绘制菜单项
        for (int i = 0; i < menuItems.size(); i++) {
            int itemY = menuStartY + i * menuItemHeight;

            if (i == selectedIndex) {
                static int hue = 0;
                hue = (hue + 2) % 360;
                COLORREF color = HSVtoRGB(hue, 1, 1);
                settextcolor(color);
                settextstyle(36, 0, _T("黑体"));

                // 动态小圆点（呼吸效果）
                int pulseSize = 6 + (int)(2 * sin(GetTickCount() / 200.0));
                setfillcolor(HSVtoRGB((hue + 180) % 360, 1, 1));
                fillcircle(600 - 100, itemY + 20, pulseSize);
            }
            else {
                settextcolor(RGB(180, 180, 180));
                settextstyle(32, 0, _T("黑体"));
            }

            int textWidth = GetTextWidth(menuItems[i].c_str(), 32, "黑体");
            int centerX = (1300 - textWidth) / 2;
            outtextxy(centerX, itemY, menuItems[i].c_str());
        }

        // 输入处理
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 0 || ch == -32) {
                ch = _getch();
                switch (ch) {
                case 72: // ↑
                    selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
                    break;
                case 80: // ↓
                    selectedIndex = (selectedIndex + 1) % menuItems.size();
                    break;
                }
            }
            else if (ch == 13) { // 处理普通回车
                if (selectedIndex == 0) {
                    return 1;
                }
                else if (selectedIndex == 1) {
                    return 2;
                }
                else if (selectedIndex == 2) {
                    MessageBox(GetHWnd(), _T("暴雨中的悬崖上，雷恩用黎明使者支撑着身体，剑刃插进黑龙阿斯卡隆的心脏。龙血喷溅在他脸上时，他听到了恶魔般的低语：以血为契，你将永远渴望我的力量...\n三年后，被龙血诅咒侵蚀的雷恩来到遗忘神庙。每走一步，左脸的龙鳞纹路就灼烧一次——诅咒正在将他变成怪物。\n龙晶石能净化诅咒，老巫师临死前的话回荡耳边，但它会唤醒更可怕的东西...\n神庙深处，紫水晶般的龙晶石悬浮在祭坛上。当雷恩触碰它的瞬间，整个神庙开始崩塌，远处传来此起彼伏的龙啸——沉睡的龙族苏醒了。\n雷恩握紧散发红光的龙晶石，发现自己的右手已经变成龙爪。诅咒没有消失，而是与晶石达成了诡异的平衡。此刻，东方的天空被火光照亮，那是王城的方向...\n（游戏从这里开始：您将扮演半龙化的雷恩，带着会说话的黎明使者剑，在全面爆发的龙灾中寻找真相。每次使用龙晶石力量都会加速变异，但不用就会死在巨龙爪下..."), _T("游戏故事内容:"), MB_OK);
                }
                else if (selectedIndex == 3) {
                    EndBatchDraw();
                    return 3;
                }
            }
        }

        FlushBatchDraw();

        // 控制帧率 ~60FPS
        Sleep(16);
    }

    return 0;
}
