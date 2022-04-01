#include "head.h"

void Page1() {
	// 화면 좌표 지정
	keyControlData.limitMinY = 13;
	keyControlData.limitMaxY = 13;
	pos.X = 4; pos.Y = 13;

	// 화면 출력
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　# 1. 격리 생활관　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　피곤한 주말 아침이다. 손목 시계를 보니 07시 30분.                             　　　　　　　■\n");
	printf("■　기상나팔도 못 듣고 푹 잤나보다.                                           　　　　　　　　　■\n");
	printf("■　　　　　　　 　　 　　 　　　    　   　 　   　　  　　  　    　　          　　　　　　　■\n");
	printf("■　세수를 하고 머리를 감고 침대에 앉아 다시 시계를 보니 8시 10분 　　  　　  　　　　　　　　　■\n");
	printf("■　　　　　　　      　　　  　　  　　　    　　　　    　　　  　　  　　      　　　　　　　■\n");
	printf("■　뭔가 이상하다.　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　지금 시간이면 핸드폰 보관함 키와 조식이 도착했어야 하는데 인기척이 느껴지지 읺는다. 　　　　■\n");
	printf("■　커텐을 걷고 밖을 둘러봤는데 이상하리만큼 조용하다.                         　　 　　　　　　■\n");
	printf("■　책상에 놓여진 무전기를 집고 침대에 앉아서 조심스레 무전을 보내본다, 　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■  >  Continue                                                                                 ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

	// KeyPrint 필요 X
	while (!keyControlData.isSubmit) { // SUBMIT가 눌릴 때까지 while문 반복
		keyControlData.key = KeyIn(); // 어떤 입력이 들어오는지 확인
		Sleep(1);
	}
	keyControlData.isSubmit = FALSE; // isSubmit 상태로 변경

	system("cls");
	// 화면 출력
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　# 1. 격리 생활관　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　이상하다. 아무 대답이 없다. 　　　                                            　　　　　　　■\n");
	printf("■　안되겠다. 밖으로 나가봐야겠다.                                            　　　　　　　　　■\n");
	printf("■　　　　　　　 　　 　　 　　　    　   　 　   　　  　　  　    　　          　　　　　　　■\n");
	printf("■　                            　　　                            　　  　　  　　　　　　　　　■\n");
	printf("■　　　　　　　      　　　  　　  　　　    　　　　    　　　  　　  　　      　　　　　　　■\n");
	printf("■　              　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　                            　　　                            　　　                　　　　■\n");
	printf("■　                            　　　                                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■  >  격리 생활관 밖으로 나간다.                                                               ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

	while (!keyControlData.isSubmit) { // SUBMIT가 눌릴 때까지 while문 반복
		keyControlData.key = KeyIn(); // 어떤 입력이 들어오는지 확인
		Sleep(1);
	}
	keyControlData.isSubmit = FALSE; // isSubmit 상태로 변경


	if (pos.Y == 0) { // Game Start인 경우
		
	}
}