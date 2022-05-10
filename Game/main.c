#include <stdio.h>
#include <malloc.h>
#include "game.h"

int main(void)
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	init(head);
	char* itemList[15] = { "에너지바","칸막이 열쇠","야채맛 건빵","부러진 대걸레","붕대","라이터","손 소독제","총기함 열쇠","K2 소총","K5 권총","옥상 열쇠","전투 식량","빅팜 소시지","ACDC 변환 장치"};
	head = insert_last(head, itemList[0]);
	head = insert_last(head, itemList[1]);
	print_list(head);



	return 0;
}
