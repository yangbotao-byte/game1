#ifndef __ENEMY_H__
#define __ENEMY_H__
#include<vector>
#include<graphics.h>
#include"hero.h"

class Enemy {
public:
    int x, y;
    int width, height;
    int hp;
    bool alive;

    // 移动与动画
    std::vector<IMAGE> walkFrames;
    std::vector<IMAGE> attackFrames;
    int currentFrame;
    bool isAttacking;

    // 受击区域
    RECT hurtBox;

    // 攻击参数
    int attackPower;
    int attackCooldown;
    int attackTimer;

    // 技能
    int skillCooldown;
    int skillTimer;

    // 冻结技能
    bool iceSkillActive;
    int freezeDuration;

    Enemy(int _x, int _y);

    void update(hero& player);
    void draw();
    void beHit(int damage);
    bool isHitBy(const RECT& atkBox);

private:
    void useFireSkill(hero& player);
    void useIceSkill(hero& player);
};

#endif
