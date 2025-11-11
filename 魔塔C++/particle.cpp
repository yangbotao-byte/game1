#include "particle.h"
#include <cstdlib>

std::vector<Particle> fireParticles;
std::vector<Particle> iceParticles;

// 添加火焰粒子
void addFireParticle(int x, int y) {
    Particle p;
    p.x = (float)x + rand() % 10 - 5;
    p.y = (float)y + rand() % 5;
    p.dx = (float)(rand() % 100 - 50) / 100.0f;
    p.dy = -(float)(rand() % 30 + 10) / 100.0f;
    p.life = 40 + rand() % 10;
    p.color = RGB(255, 100 + rand() % 100, 0);
    fireParticles.push_back(p);
}

// 添加寒冰粒子
void addIceParticle(int x, int y) {
    Particle p;
    p.x = (float)x + rand() % 10 - 5;
    p.y = (float)y + rand() % 10 - 5;
    p.dx = (float)(rand() % 100 - 50) / 200.0f;
    p.dy = -(float)(rand() % 10) / 100.0f;
    p.life = 50 + rand() % 20;
    p.color = RGB(150 + rand() % 50, 200 + rand() % 55, 255);
    iceParticles.push_back(p);
}

// 更新并绘制所有粒子
void updateAndDrawParticles() {
    // 火焰粒子
    for (int i = 0; i < fireParticles.size(); ) {
        Particle& p = fireParticles[i];
        p.x += p.dx;
        p.y += p.dy;
        p.life--;
        setfillcolor(p.color);
        solidcircle((int)p.x, (int)p.y, 3);
        if (p.life <= 0)
            fireParticles.erase(fireParticles.begin() + i);
        else
            i++;
    }

    // 冰霜粒子
    for (int i = 0; i < iceParticles.size(); ) {
        Particle& p = iceParticles[i];
        p.x += p.dx;
        p.y += p.dy;
        p.life--;
        setfillcolor(p.color);
        solidcircle((int)p.x, (int)p.y, 2);
        if (p.life <= 0)
            iceParticles.erase(iceParticles.begin() + i);
        else
            i++;
    }
}
