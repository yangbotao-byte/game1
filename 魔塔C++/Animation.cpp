#include"allinclude.h"

// 更新动画函数
void UpdateAnimation(Animation& anim, float deltaTime) {
    anim.elapsedTime += deltaTime;
    if (anim.elapsedTime >= anim.frameTime) {
        anim.currentFrame++;
        anim.elapsedTime = 0;
        if (anim.currentFrame >= anim.frameCount) {
            anim.currentFrame = anim.loop ? 0 : anim.frameCount - 1;
        }
    }
}

