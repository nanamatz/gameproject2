#include "head.h"

COORD pos = { 0,0 };
keyControl keyControlData = { 0, 0, 0, 0 };

int main() {

	system("mode con cols=100 lines=30"); // mode con:콘솔모드 cols:가로 lines:세로
	Intro();
	Home();
	return 0;
}