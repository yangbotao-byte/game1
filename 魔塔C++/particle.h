#pragma once
#include <vector>
#include <graphics.h>

struct Particle {
    float x, y;
    float dx, dy;
    int life;
    COLORREF color;
};

extern std::vector<Particle> fireParticles;
extern std::vector<Particle> iceParticles;

void addFireParticle(int x, int y);
void addIceParticle(int x, int y);
void updateAndDrawParticles();
