#include"allinclude.h"
static int counter;

void updatehero() {
	if (hero1.sleep == true) {
		hero1.sleeptime--;
		putimagePNG2(hero1.x + 150, hero1.y + 180, &bin[1]);
		if (hero1.sleeptime == 0) {
			hero1.sleep = false;
		}
	}

	else if (hero1.attackkey && isJumping == false) {
		hero1.updateattack(counter);
		counter++;
		cout << counter << endl;
		if (counter == 30) {
			empty1.beHit(20);
			counter = 0;
		}
		if ((GetAsyncKeyState('J') & 0x8000) == 0) {
			hero1.attackkey = false;
			counter = 0;
		}
	}
    else if (hero1.Lwalkkey && isJumping == false) {
		hero1.attackL = true;
		hero1.attackR = false;
		printf(">>>> updatehero: hero1.x = %d\n", hero1.x);
		hero1.updatewalk(counter);
		/*hero1.x -= hero1.speed;*/
		counter++;
		if ((GetAsyncKeyState('A') & 0x8000) == 0) {
			hero1.Lwalkkey = false;
			counter = 0;
		}
	}
	else if (hero1.Rwalkkey && isJumping == false) {
		hero1.attackL = false;
		hero1.attackR = true;
		printf(">>>> updatehero: hero1.x = %d\n", hero1.x);
		hero1.updatewalk(counter);
		/*hero1.x += hero1.speed;*/
		counter++;
		if ((GetAsyncKeyState('D') & 0x8000) == 0) {
			hero1.Rwalkkey = false;
			counter = 0;
		}
	}
	else if(hero1.jumpkey == false && isJumping == false){
		//防止行走或者攻击之后，帧数不对越界
		counter = counter % hero1.stand1.size();
		hero1.updatestand(counter);
		counter++;
		counter = counter % hero1.stand1.size();
	}
}

void keydetect() {
	hero1.Lwalkkey = (GetAsyncKeyState('A') & 0x8000) != 0;
	/*if (hero1.Lwalkkey) {
		cout << "启动左边行走模式" << endl;
	}*/
	hero1.Rwalkkey = (GetAsyncKeyState('D') & 0x8000) != 0;
	/*if (hero1.Rwalkkey) {
		cout << "启动右边行走模式" << endl;
	}*/
	hero1.attackkey = (GetAsyncKeyState('J') & 0x8000) != 0;
	/*counter = 0*/
	hero1.jumpkey = (GetAsyncKeyState('K') & 0x8000) != 0;
}