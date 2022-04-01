#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <process.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SUBMIT 5
#define READYTOINPUT 6 // 입력을 기다리는 상태

// 전역변수
extern COORD pos; // X, Y값 구조체

typedef struct {
	int limitMinY; // 홈메뉴 최상단 y값 이 값을 통해 사용자가 맨 위에서 더 이동하려고 하는 상황 해결
	int limitMaxY; // 홈메뉴 최하단 y값 이 값을 통해 사용자가 맨 아래에서 더 이동하려고 하는 상황 해결
	bool isSubmit;
	int key;
}keyControl;

extern keyControl keyControlData;

/*
printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　# 1. 격리 생활관　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　                            　　　                                            　　　　　　　■\n");
	printf("■　                            　                                            　　　　　　　　　■\n");
	printf("■　　　　　　　 　　 　　 　　　    　   　 　   　　  　　  　    　　          　　　　　　　■\n");
	printf("■　                            　　　                            　　  　　  　　　　　　　　　■\n");
	printf("■　　　　　　　      　　　  　　  　　　    　　　　    　　　  　　  　　      　　　　　　　■\n");
	printf("■　              　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　                            　　　                            　　　                　　　　■\n");
	printf("■　                            　　　                                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■  >  Continue                                                                                 ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
*/