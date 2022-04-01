#include "head.h"


// 현재 pos.X, posY로 콘솔 위치지정
void gotoxy() { 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  // 콘솔 위치지정
}

// 키보드에서 입력받은 값 반환
int KeyIn() { 
	char temp = _getch(); // 키 입력받기
	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') {
		keyControlData.isSubmit = TRUE;
		return READYTOINPUT;
	}
	
	return READYTOINPUT;
}

// 키보드에서 입력받은 값을 토대로 화면에 출력
int KeyPrint() { 
		switch (keyControlData.key)
		{
		case UP:
		{
			if (pos.Y > keyControlData.limitMinY)
			{
				gotoxy();
				printf(" ");
				pos.Y--;
				gotoxy();
				printf(">");
			}
			return keyControlData.key;
		}
		case DOWN:
		{
			if (pos.Y < keyControlData.limitMaxY)
			{
				gotoxy();
				printf(" ");
				pos.Y++;
				gotoxy();
				printf(">");
			}
			return keyControlData.key;
		}
		case SUBMIT: {
			return keyControlData.key;
		}
		default :
			return keyControlData.key;
		}
}

