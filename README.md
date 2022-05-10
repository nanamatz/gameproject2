# gameproject2#include 
<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

typedef struct ListNode { 
	element* data;
	struct ListNode* prelink;
	struct ListNode* link;
} ListNode;

ListNode* insert_last(ListNode* head, element* data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head->link == head || head->prelink == head) {
		head->link = node;
		head->prelink = node;
		node->link = head;
		node->prelink = head;
	}
	else {
		node->prelink = head->prelink;
		node->link = head;
		head->prelink->link = node;
		head->prelink = node;
	}
	return head;
}
ListNode* insert_first(ListNode* head, element* data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head->link == head || head->prelink == head) {
		node->link = head;
		node->prelink = head;
		head->link = node;
		head->prelink = node;

	}
	else {
		node->prelink = head;
		node->link = head->link;
		node->link->prelink = node;
		head->link = node;
	}
	return head;
}
ListNode* insert(ListNode* head, ListNode* pre, element* data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head->link == head || head->prelink == head || head==pre) {
		head = insert_first(head, data);
		return head;
	}
	else {
		node->prelink = pre;
		node->link = pre->link;
		pre->link->prelink = node;
		pre->link = node;
	}
	return head;
}
void print_list(ListNode* head)
{
	ListNode* p;
	int num = 1;
	if (head->prelink == head || head->link == head) return;
	p = head->link;
	printf("=================INVENTORY===================\n");
	do {

		printf("%d.%s", num,p->data);
		num++;
		p = p->link;
		printf("\n");
	} while (p != head);
	printf("=============================================\n");
}
ListNode* deleted(ListNode* head, ListNode* removed) {
	if (head == removed) return;
	else {
		removed->link->prelink = removed->prelink;
		removed->prelink->link = removed->link;
		free(removed);
	}
	return head;
}
//ListNode* getinsertNode(ListNode* head, element data) {
//	ListNode* temp = NULL;
//	if (head->link == head || head->prelink == head) {
//		return head;
//	}
//	for (ListNode* p = head->link; p != head; p = p->link) {
//		if (p->data < data) {
//			temp = p;
//		}
//	}
//	if (temp == NULL) {
//		return head;
//	}
//	return temp;
//}
ListNode* getdeleteNode(ListNode* head, element* data) {
	if (head->link == head || head->prelink == head) {
		printf("비어있습니다.\n");
		return;
	}
		ListNode* removed = NULL;
	for (ListNode* p = head->link; p != head; p = p->link) {
		if (!strcmp(p->data,data)) {
			removed = p;
			break;
		}
	}
	if (removed == NULL) {
		printf("해당 값이 없습니다.\n");
		return head;
	}
	return removed;
}
void init(ListNode* head) {
	head->link = head;
	head->prelink = head;
	head->data = '공백';
}
int main(void)
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	init(head);
	char* itemList[10] = { "나이프","야전삽","지뢰","전투식량","건빵","수통","탄알집","총","손전등","열쇠" };
	head = insert_last(head, itemList[0]);
	head = insert_first(head, itemList[6]);
	head = insert_last(head, itemList[5]);
	head = insert_last(head, itemList[2]);
	head = insert_last(head, itemList[8]);
	head = insert_last(head, itemList[9]);
	head = deleted(head, getdeleteNode(head,itemList[8]));
	print_list(head);

	return 0;
}
