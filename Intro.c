#include "head.h"

/* 
unsigned _stdcall thread_isInput(bool *p_input) {
	while(*p_input == TRUE) // input이 들어올 때까지 반복
		*p_input = _kbhit();
	return; // input이 들어왔다면 종료
}

void intro() {
	bool input = 0;

	_beginthereadex(NULL, 0, thread_isInput, &input, 0, NULL);

	while (input == 0) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("                                        ");
		printf("Press any key to continue");

		input = _kbhit();
		Sleep(300);
		system("cls");

		printf("Day\n");
		printf("Press         to continue");

		input = _kbhit();
		Sleep(300);
		system("cls");
	}

	_getch(); // 입력 버퍼 비우기
}
*/ 
// 첫 코드 > 입력이 들어왔을 때 즉시 홈 화면으로 이동되지 않는 문제가 발생해서 쓰레드를 사용하기로 결정

void Intro() {
	bool input = 0;

	while (input == 0) {
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　■■■　　　　■■　　　■　　■　　　■■　　　■　　■　　■■■　　　　　　　■\n");
		printf("■　　　　　　　■　　■　　■　　■　　■　　■　　■　　■　　■■　■　　■　　　　　　　　　■\n");
		printf("■　　　　　　　■　　■　　■■■■　　　■■　　　■　　■　　■　■■　　■■■　　　　　　　■\n");
		printf("■　　　　　　　■　　■　　■　　■　　　■■　　　■　　■　　■　　■　　■　　　　　　　　　■\n");
		printf("■　　　　　　　■■■　　　■　　■　　　■■　　　　■■　　　■　　■　　■■■　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　Press any key to continue　　 　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		input = _kbhit(); 
		Sleep(300);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　■■■　　　　■■　　　■　　■　　　■■　　　■　　■　　■■■　　　　　　　■\n");
		printf("■　　　　　　　■　　■　　■　　■　　■　　■　　■　　■　　■■　■　　■　　　　　　　　　■\n");
		printf("■　　　　　　　■　　■　　■■■■　　　■■　　　■　　■　　■　■■　　■■■　　　　　　　■\n");
		printf("■　　　　　　　■　　■　　■　　■　　　■■　　　■　　■　　■　　■　　■　　　　　　　　　■\n");
		printf("■　　　　　　　■■■　　　■　　■　　　■■　　　　■■　　　■　　■　　■■■　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　Press 　  key to continue　　 　　　　　　■\n");
		printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

		input = _kbhit();
		Sleep(300);
		system("cls");
	}

	_getch(); // 입력 버퍼 비우기
}