#include"allinclude.h"
IMAGE men[48];
IMAGE men1[113];


void updatemen() {
	for (int i = 0; i < 48; ++i) {
		char path[64];
		sprintf_s(path, "./set/kai/frame_%02d_delay-0.08s.png", i + 1); // 生成 frame_01 ~ frame_12
		loadimage(&men[i], path);
	}

	mciSendString("close ./music\\begin.mp3", 0, 0, 0);
	mciSendString("close ./music\\nu.mp3", NULL, 0, NULL);
	mciSendString("open ./music\\nu.mp3", 0, 0, 0);
	mciSendString("play ./music\\nu.mp3", 0, 0, 0);

	for (int i = 0; i < 49; i++) {
		putimage(50, 0, &men[i]);
		Sleep(100);
		cleardevice();
	}
}

void updatemen1() {
	for (int i = 0; i < 113; ++i) {
		char path[64];
		sprintf_s(path, "./set/kai_1/frame_%03d_delay-0.1s.png", i + 1); // 生成 frame_01 ~ frame_12
		loadimage(&men1[i], path);
	}

	mciSendString("close ./music\\begin.mp3", 0, 0, 0);
	mciSendString("close ./music\\long.mp3", NULL, 0, NULL);
	mciSendString("open ./music\\long.mp3", 0, 0, 0);
	mciSendString("play ./music\\long.mp3", 0, 0, 0);

	for (int i = 0; i < 113; i++) {
		putimage(320, 0, &men1[i]);
		Sleep(100);
		cleardevice();
	}
}