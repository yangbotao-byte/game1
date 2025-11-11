#define _CRT_SECURE_NO_WARNINGS 1
#include "Enemy.h"
#include"allinclude.h"

Enemy::Enemy(int _x, int _y) {
    walkFrames.resize(7);
    attackFrames.resize(7);

    for (int i = 0; i < 7; i++) {
        char path[50];
        sprintf(path, "./e_m_001/run_2/action/000%d.png", i);
        loadimage(&walkFrames[i], path);
    }
    for (int i = 0; i < 7; i++) {
        char path[50];
        sprintf(path, "./e_m_001/attack_2/action/000%d.png", i);
        loadimage(&attackFrames[i], path);
    }

    x = _x;
    y = _y;
    width = walkFrames[1].getwidth();
    height = walkFrames[1].getheight();
    hp = 100;
    alive = true;
    currentFrame = 0;

    attackPower = 10;
    attackCooldown = 60;
    attackTimer = 0;
    isAttacking = false;

    skillCooldown = 300;
    skillTimer = 0;

    freezeDuration = 0;
    iceSkillActive = false;

    hurtBox = { x, y, x + width, y + height };
}

void Enemy::update(hero& player) {
    if (!alive) return;

    int playerX = player.x + 180;
    int playerY = player.y + 210;

    int centerX = x + width / 2;
    int dx = playerX - centerX;
    float dist = sqrt(dx * dx);

    if (dist > 5 && freezeDuration == 0) {
        x += (int)(dx / dist * 2.5);
    }

    // 攻击逻辑
    if (dist < 60) {
        if (attackTimer == 0) {
            isAttacking = true;
            attackTimer = attackCooldown;
            player.beHit(attackPower);
            cout << "敌人攻击玩家，造成 " << attackPower << " 点伤害" << endl;
        }
    }
    else {
        isAttacking = false;
    }

    if (attackTimer > 0) attackTimer--;

    // 技能逻辑
    if (skillTimer <= 0) {
        if (rand() % 2 == 0)
            useFireSkill(player);
        else
            useIceSkill(player);

        skillTimer = skillCooldown;
    }
    else {
        skillTimer--;
    }

    if (freezeDuration > 0) freezeDuration--;

    hurtBox = { x, y, x + width, y + height };
}

void Enemy::draw() {
    if (!alive) return;

    if (!isAttacking) {
        putimagePNG2(x, y, &walkFrames[currentFrame]);
    }
    else {
        putimagePNG2(x, y, &attackFrames[currentFrame]);
    }

    currentFrame = (currentFrame + 1) % walkFrames.size();

    // 血条
    int maxHp = 100;           // 假设最大血量为100
    int barWidth = 100;
    int barHeight = 10;

    int healthWidth = hp * barWidth / maxHp;
    cout << "hp : " << hp << endl;
    int barX = 1100, barY = 30;

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

void Enemy::beHit(int damage) {
    cout << "Enemy::beHit 被调用，伤害 = " << damage << endl;
    hp -= damage;
    if (hp <= 0) {
        alive = false;
        cout << "敌人被击败！" << endl;
    }
}

bool Enemy::isHitBy(const RECT& atkBox) {
    if (!alive) return false;
    RECT intersect;
    return IntersectRect(&intersect, &hurtBox, &atkBox);
}

// ======== 技能实现 ========

void Enemy::useFireSkill(hero& player) {
    cout << "敌人释放火焰技能！" << endl;
    for (int i = 0; i < 30; i++) {
        addFireParticle(player.x + 240, player.y + 320 - rand() % 20); // 火焰从脚底冒出
    }
    player.beHit(15);
}

void Enemy::useIceSkill(hero& player) {
    cout << "敌人释放寒冰技能！" << endl;
    for (int i = 0; i < 20; i++) {
        addIceParticle(player.x + 240, player.y + 320 - rand() % 20); // 冰雾粒子
    }
    player.freeze(); // 冻结1秒（假设你有这个函数）
}
