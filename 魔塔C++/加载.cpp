#define _CRT_SECURE_NO_WARNINGS 1
#include"allinclude.h"

int loading() {
    // vector<string> resources;

    IMAGE loading001;
    IMAGE ProgressBar;

    // 创建进度条参数
    int barWidth = 1000;
    int barHeight = 10;
    int barX = 100;
    int barY = 550;
    loadimage(&loading001, "./loading\\loading_001.png");
    loadimage(&ProgressBar, "./loading\\programbar.png");
    int sizesum = (hero1.walk.size() + hero1.stand.size() + hero1.attack.size() + hero1.swalk.size());
    //cout为调试代码
    /*cout << hero1.stand.size() << endl;
    cout << hero1.walk.size() << endl;
    cout << hero1.attack.size() << endl;
    cout << sizesum << endl;*/

    if (hero1.stand.empty() || hero1.walk.empty() || hero1.attack.empty()) {
        cout << "Error: hero1 resources are not properly initialized!" << endl;
        return -1; // 返回错误状态
    }

    // 加载循环
    for (int i = 0; i < sizesum; i++) {
        //加载站立  跑步  攻击图片
        //后续增加攻击

        //cout << "Loading resource " << i << " of " << sizesum << endl;

        if (i < hero1.stand.size()) {
            //cout << "Loading stand image: " << hero1.stand[i] << endl;
            loadimage(&hero1.stand1[i], hero1.stand[i].c_str());
        }

        else if (i < hero1.walk.size() + hero1.stand.size()) {
            int walkIndex = i - hero1.stand.size();
            //cout << "Loading walk image: " << hero1.walk[walkIndex] << endl;
            loadimage(&hero1.walk1[walkIndex], hero1.walk[walkIndex].c_str());
            loadimage(&hero1.walk2[walkIndex], hero1.swalk[walkIndex].c_str());
        }

        else if (i < hero1.attack.size() + hero1.walk.size() + hero1.stand.size()) {
            int attackIndex = i - hero1.stand.size() - hero1.walk.size();
            //cout << "Loading attack image: " << hero1.attack[attackIndex] << endl;
            loadimage(&hero1.attack1[attackIndex], hero1.attack[attackIndex].c_str());
            loadimage(&hero1.attack2[attackIndex], hero1.sattack[attackIndex].c_str());
        }

        // 更新进度
        float progress = static_cast<float>(i + 1) / sizesum;

        // 绘制界面
        //清除，减少占用内存
        cleardevice();

        BeginBatchDraw();
        // 绘制背景
        setbkcolor(RGB(30, 30, 50));
        //cleardevice();
        putimagePNG2(300, 70, &loading001);

        // 绘制进度条背景
        setfillcolor(RGB(70, 70, 90));
        fillrectangle(barX, barY, barX + barWidth, barY + barHeight);

        // 绘制进度条前景
        setfillcolor(RGB(100, 200, 255));
        fillrectangle(barX, barY, barX + (int)(barWidth * progress), barY + barHeight);

        // 绘制边框
        setlinecolor(WHITE);
        rectangle(barX, barY, barX + barWidth, barY + barHeight);

        //修饰
        putimagePNG2(200, 500, &ProgressBar);

        // 显示进度文本
        char text[64];
        sprintf(text, _T("loading... %d picture"), progress * 100);
        settextcolor(WHITE);
        outtextxy(barX, barY - 40, text);
        // 显示提示文字
        settextstyle(25, 0, _T("黑体"));
        outtextxy(barX, barY + 50, "Please wait, loading game resources...");
        EndBatchDraw();

        FlushBatchDraw();
        Sleep(40);
    }

    // 加载完成提示
    outtextxy(920, 570, "Loading complete!");
    FlushBatchDraw();
    //Sleep(1000);

    EndBatchDraw();
    cleardevice();

    return 1; // 返回加载成功状态
}
