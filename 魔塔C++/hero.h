#ifndef __HERO_H__
#define __HERO_H__
#include<graphics.h>
#include<string>
#include<vector>
using namespace std;

class hero {
public:

    struct AttackBox {
        int x, y;       // 左上角位置
        int width, height; // 宽高
        bool active;    // 当前是否启用攻击判定
    };

    int x;
    int y;
    int hp;
    bool Lwalkkey;
    bool Rwalkkey;
    bool attackkey;
    bool jumpkey;

    bool attackL;
    bool attackR;

    int speed;
    int hurt;
    int hurt1;
    int fangyu;
    int tong;
    bool sleep;
    int sleeptime;
    AttackBox atkBox;

    vector<string> walk;
    vector<string> stand;
    vector<string> attack;

    vector<string> swalk;
    vector<string> sattack;

    vector<IMAGE> walk1;
    vector<IMAGE> stand1;
    vector<IMAGE> attack1;
    vector<IMAGE> jump;

    vector<IMAGE> walk2;
    vector<IMAGE> attack2;

public:
    hero();
    hero(int x1, int y1, int number1, int number2, int number3);

    void updatestand(int count);
    void updatewalk(int count);
    void updateattack(int count);
    void updatejump();
    void boolhero();
    void beHit(int attackPower);
    void freeze();
    ~hero() {}

};

#endif