#include"allinclude.h"
IMAGE bg;

// 角色跳跃帧
static float jumpSpeed = 0.0f;
const float gravity = 1.2f;
const float initialJumpSpeed = -18.0f;
static Animation jumpAnim = { 0, 4, 0.5f, 0.0f, true }; // 4帧，每帧0.5秒

Enemy empty1(900,380);
vector<IMAGE> bin;

int level1(){
    init();
	loadimage(&bg, "./bg\\Background_8K.png");

    bin.resize(11);
    for (int i = 1; i <= 10; i++) {
        char path[50];
        sprintf(path, "./冰冻/%d.PNG", i);
        loadimage(&bin[i], path);
    }

    srand((unsigned int)time(0));

    DWORD lastTime = GetTickCount();
	while (1) {
        //时间的控制
        DWORD currentTime = GetTickCount();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        //检测
        keydetect();
        UIdetect();

		BeginBatchDraw();
		putimage(0, 0, &bg);
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
        empty1.update(hero1);
        if (empty1.alive == false) {
            return 1;
        }

        else if(hero1.hp == 0){
            return 2;
        }
        empty1.draw();
        updateAttackBox(hero1);
        updateAndDrawParticles();
        updateUI();
        hero1.boolhero();
		EndBatchDraw();
        Sleep(70);
	}
}