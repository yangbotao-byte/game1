#include"allinclude.h"
#include"hero.h"

void updateAttackBox(hero& h) {
    if (h.attackkey) {
        h.atkBox.active = true;
        h.atkBox.y = h.y + 260 +  20;  // 距离人物头部有个偏移

        //cout << "矩阵的y：" << h.atkBox.y << endl;

        if (h.attackR) {
            //500是人物图片的大小
            h.atkBox.x = h.x + 260 + 50; // 人物右侧
        }
        else if (h.attackL) {
            h.atkBox.x = h.x + 200 - 50;      // 人物左侧
        }

        h.atkBox.width = 70;
        h.atkBox.height = 100;
    }

     //cout << "矩阵的x：" << h.atkBox.x << endl;

    if (hero1.atkBox.active && h.attackkey) {
        setlinecolor(RED);
        rectangle(hero1.atkBox.x, hero1.atkBox.y,
            hero1.atkBox.x + hero1.atkBox.width,
            hero1.atkBox.y + hero1.atkBox.height);
    }

    else {
        h.atkBox.active = false;
    }
}