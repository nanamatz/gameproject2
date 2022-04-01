#include "head.h"

int Home() {

	// 화면 좌표 지정
	keyControlData.limitMinY = 13;
	keyControlData.limitMaxY = 14;
	pos.X = 4; pos.Y = 13;

	// 화면 출력
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
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■  >  Game Start                                                                               ■\n");
	printf("■     Quit                                                                                     ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");


	while (!keyControlData.isSubmit) { // SUBMIT가 눌릴 때까지 while문 반복
		keyControlData.key = KeyIn(); // 어떤 입력이 들어오는지 확인
		KeyPrint(); // 메뉴에 있는 커서(>)의 위치를 옮겨줌
		Sleep(1);
	}
	keyControlData.isSubmit = FALSE; // isSubmit 상태로 변경

	if (pos.Y == 0) { // Game Start인 경우
		MainGame();
	}
	else if (pos.Y == 1) { // Language인 경우
		LanguageSelect();
	}
	else if (pos.Y == 2) { // Quit인 경우 게임 종료
		return 0;
	}
}