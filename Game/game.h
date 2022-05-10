typedef char element;

typedef struct ListNode {
	element* data;
	struct ListNode* prelink;
	struct ListNode* link;
} ListNode;

ListNode* insert_last(ListNode* head, element* data);

void print_list(ListNode* head);

ListNode* deleted(ListNode* head, ListNode* removed);

ListNode* getdeleteNode(ListNode* head, element* data);

void init(ListNode* head);




