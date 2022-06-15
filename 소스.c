#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SUBMIT 5
#define READYTOINPUT 6 // 입력을 기다리는 상태
#define SELECTSTARTPOS 21

//함수 선언부

char* itemList[16] = { "[칸막이 열쇠]","[부러진 대걸레]","[차갑게 식은 냉동 만두]","[옥상 열쇠]","[손전등]",
"[야채 건빵]" ,"[몽키 스패너]","[붕대]","[터보 라이터]","[손 소독제]","[총기함 키]","[주임원사실 열쇠]","[권총과 탄알집]","[K2 소총]","[노트북과 연결 포트]","[어딘가 중요해 보이는 열쇠]"};

int is_condi = 0; // 조건 노드인가
int is_leaf = 0; // 단말 노드인가
int is_true = 0; //조건이 참인가
int is_exp = 0; //탐색하는가
int is_item = 0;//아이템이 있는가
int is_back = 0; //동편으로 돌아왔는가
int is_kill = 0;//싸움이 일어났는가
int is_over = 0;//게임 오버인가
int is_ending = 0;//게임 엔딩인가

typedef const char element;


typedef struct {
	int limitMinY; // 홈메뉴 최상단 y값 이 값을 통해 사용자가 맨 위에서 더 이동하려고 하는 상황 해결
	int limitMaxY; // 홈메뉴 최하단 y값 이 값을 통해 사용자가 맨 아래에서 더 이동하려고 하는 상황 해결
	bool isSubmit; // 스페이스바가 눌렸는가
	int key; // 입력받은 키 값
}keyControl;

//인벤토리 연결 리스트
typedef struct ListNode {
	element* data;
	struct ListNode* prelink;
	struct ListNode* link;
} ListNode;

// 텍스트 연결리스트
typedef struct TextLinkedList {
	const char* text;
	struct TextLinkedList* link;
}TextLinkedList;

//선택지 연결리스트
typedef struct SelectLinkedList {
	const char* text;
	struct SelectLinkedList* link;
}SelectLinkedList;

//  트리
typedef struct TreeNode {
	struct TextLinkedList* thead;
	struct SelectLinkedList* shead;
	int maxindex;
	struct TreeNode* left, * right;
	struct TreeNode** dptr;		//선택지가 많아서 구조체포인터 배열 주소를 받는 이중포인터
	const char* current_pos;
}TreeNode;

typedef struct {
	int hp;
	int energy;
}Player;

Player p = { 5,10 };

// 변수 선언
// 전역변수
COORD pos = { 0, 0 }; // X, Y값 구조체
keyControl keyControlData = { 0, 0, 0, 0 };
//함수 선언부============================================================================================================================================
void gotoxy();
void print_frame();
void print_console(TreeNode* current);
int KeyIn(TreeNode* current, ListNode* inventory);
int KeyPrint();
int is_condition_node(TreeNode* current_node);
int is_leaf_node(TreeNode* current_node);
int is_explore(TreeNode* pre);
int checking_condition(TreeNode* current_node, ListNode* inventory);
ListNode* checking_inventory(TreeNode* current_node, ListNode* inventory);
TreeNode* next_node(int y, TreeNode* current_node);
TreeNode* checking_node(int y, TreeNode* current_node, ListNode* inventory);
ListNode* insert_last(ListNode* head, element* data);
ListNode* insert_first(ListNode* head, element* data);
ListNode* insert(ListNode* head, ListNode* pre, element* data);
void print_list(ListNode* head);
ListNode* deleted(ListNode* head, ListNode* removed);
int searching(ListNode* head, element* data);
ListNode* getdeleteNode(ListNode* head, element* data);
void init(ListNode* head);
void map_print();
//=============================================================노드 선언부=============================================================
TreeNode intro_;
TreeNode intro1;
TreeNode intro2;
TreeNode intro3;

TreeNode happy1;
TreeNode happy2;
TreeNode bad1;
TreeNode bad2;
TreeNode gameover;

//옥상 루트(r)

TreeNode r1;
TreeNode r2;
TreeNode r3;
TreeNode r31;
TreeNode r32;
TreeNode r4;
TreeNode r5;
TreeNode r6;
TreeNode r7;

//1층 루트(p)


TreeNode p1;//1층 로비
TreeNode p2;//인사과
TreeNode p21;
TreeNode p3;//군수과
TreeNode p31;
TreeNode p4;//대대장실
TreeNode p5;//지휘통제실
TreeNode p51;
TreeNode p52;//무기가 있을 경우
TreeNode p53; //좀비 처치 후 탐색 -->주임원사실 열쇠 획득
TreeNode p54;//무기가 없을 경우
TreeNode p6;//주임원사실
TreeNode p61;
TreeNode p62;
TreeNode p63;
TreeNode p64;
TreeNode p65;
TreeNode p66;
TreeNode password;
TreeNode password2;
TreeNode p69;
TreeNode p610;
TreeNode p7;//통신물자창고
TreeNode p71;
TreeNode p8;//총기함실
TreeNode p811;
TreeNode p81;
TreeNode p82;

//2층 서편 루트(w)

TreeNode w1;//서편 로비
TreeNode w2;//1-1반
TreeNode w21;
TreeNode w3;//1-2반
TreeNode w31;
TreeNode w4;//1-3반
TreeNode w41;
TreeNode w42;
TreeNode w43;
TreeNode w5;//2-1반
TreeNode w51;
TreeNode w6;//2-2반
TreeNode w61;
TreeNode w62;
TreeNode w63;
TreeNode w7;//2-3반
TreeNode w71;

//2층 중앙 복도(c)

TreeNode cr;
TreeNode c1;
TreeNode c2;
TreeNode c21;
TreeNode c22;
TreeNode c3;

//2층 동편 루트(e)

TreeNode er;
TreeNode e1;
TreeNode e2;
TreeNode e21;
TreeNode e3;
TreeNode e31;
TreeNode e4;
TreeNode e41;
//격리생활관 루트 (f)

TreeNode f1;
TreeNode f2;
TreeNode f3;
TreeNode f21;
TreeNode f31;
TreeNode f32;




//선택지 인트로
SelectLinkedList intro_s2 = { "종료",NULL };
SelectLinkedList intro_s1 = { "게임 시작",&intro_s2 };

//선택지 격리 생활관

SelectLinkedList f1_s2 = { "[2]칸막이 밖으로 나간다",NULL };
SelectLinkedList f1_s1 = { "[1]간부연구실로 간다",&f1_s2 };

//선택지 동편
SelectLinkedList e1_s4 = { "[4]중앙복도로 간다",NULL };
SelectLinkedList e1_s3 = { "[3]행정반으로 간다",&e1_s4 };
SelectLinkedList e1_s2 = { "[2]세탁실로 간다",&e1_s3 };
SelectLinkedList e1_s1 = { "[1]화장실로 간다",&e1_s2 };

//공용 선택지 fight, run

//선택지 중앙복도(처음x)
SelectLinkedList cr_s4 = { "[4]동편으로 이동한다" ,NULL };
SelectLinkedList cr_s3 = { "[3]옥상으로 이동한다",&cr_s4 };
SelectLinkedList cr_s2 = { "[2]1층으로 이동한다" ,&cr_s3 };
SelectLinkedList cr_s1 = { "[1]서편으로 이동한다",&cr_s2 };

SelectLinkedList c3_s2 = { "[2]1층으로 도망간다" ,NULL };
SelectLinkedList c3_s1 = { "[1]서편으로 도망간다",&c3_s2 };

SelectLinkedList c21_s4 = { "[4]동편으로 이동한다" ,NULL };
SelectLinkedList c21_s3 = { "[3]옥상으로 이동한다",&c21_s4 };
SelectLinkedList c21_s2 = { "[2]1층으로 이동한다" ,&c21_s3 };
SelectLinkedList c21_s1 = { "[1]서편으로 이동한다",&c21_s2 };

//선택지 서편
SelectLinkedList w1_s7 = { "[7]중앙복도로 간다",NULL };
SelectLinkedList w1_s6 = { "[6]2-3반으로 간다",&w1_s7 };
SelectLinkedList w1_s5 = { "[5]2-2반으로 간다",&w1_s6 };
SelectLinkedList w1_s4 = { "[4]2-1반으로 간다",&w1_s5 };
SelectLinkedList w1_s3 = { "[3]1-3반으로 간다",&w1_s4 };
SelectLinkedList w1_s2 = { "[2]1-2반으로 간다",&w1_s3 };
SelectLinkedList w1_s1 = { "[1]1-1반으로 간다",&w1_s2 };

//선택지 1층
SelectLinkedList p1_s8 = { "[8]중앙복도로 간다",NULL };
SelectLinkedList p1_s7 = { "[7]총기함 실로 간다",&p1_s8 };
SelectLinkedList p1_s6 = { "[6]통신물자 창고로 간다",&p1_s7 };
SelectLinkedList p1_s5 = { "[5]주임원사실로 간다",&p1_s6 };
SelectLinkedList p1_s4 = { "[4]지휘통제실로 간다",&p1_s5 };
SelectLinkedList p1_s3 = { "[3]대대장실로 간다",&p1_s4 };
SelectLinkedList p1_s2 = { "[2]군수과로 간다",&p1_s3 };
SelectLinkedList p1_s1 = { "[1]인사과로 간다",&p1_s2 };

SelectLinkedList p61_s2 = { "[2]건들지 않고 떠난다",NULL };
SelectLinkedList p61_s1 = { "[1]금고를 열어본다", &p61_s2 };

SelectLinkedList p66_s2 = { "[2]도망친다",NULL };
SelectLinkedList p66_s1 = { "[1]숨는다",&p66_s2 };

//선택지 옥상

SelectLinkedList r2_s2 = { "[2]2층 중앙복도로 내려간다",NULL };
SelectLinkedList r2_s1 = { "[1]통신망을 개통한다",&r2_s2 };


SelectLinkedList r31_s4 = { "[4]아아, 들리세요?? 저기요! 여보세요? 야 이 개새$끼야 받았으면 대답을 해!!",NULL };
SelectLinkedList r31_s3 = { "[3]어, 나 육군 참모총장인데 거기 당직 사령 좀 바꿔봐.",&r31_s4 };
SelectLinkedList r31_s2 = { "[2]여보세요??살려주세요!! 여기 사람이 있다구요!!!",&r31_s3 };
SelectLinkedList r31_s1 = { "[1]통신보안, 여기는 11사단 통신대대, 생존자 1명 대기중, 구조 바람.",&r31_s2 };


//선택지 공통
SelectLinkedList confirm = { "[확인]",NULL };
SelectLinkedList leave = { "[2]떠난다",NULL };
SelectLinkedList explore = { "[1]탐색한다",&leave };

SelectLinkedList run = { "[2]도망간다",NULL };
SelectLinkedList fight = { "[1]맞서 싸운다",&run };

//====================================================텍스트========================================================================================================
//텍스트 인트로
TextLinkedList intro_t27 = { "밖으로 나가서 무슨 일인지 확인해봐야겠다.",NULL };
TextLinkedList intro_t26 = { "...???",&intro_t27 };
TextLinkedList intro_t25 = { "어디선가 조용한 아침의 평화를 깨는 날카로운 비명이 들렸다.",&intro_t26 };
TextLinkedList intro_t24 = { "[아아아ㅏ아아아아아ㅏ아아아ㅏㄱ악!]",&intro_t25 };
TextLinkedList intro_t23 = { "너무 무리하게 마셨나,,,",&intro_t24 };
TextLinkedList intro_t22 = { "잠귀가 예민해서 말년이 되도록 6시 30분에 눈이 안 떠진적이 없었다.",&intro_t23};
TextLinkedList intro_t21 = { "뭐지 여태까지 기상송을 못들은 적이 없는데,,,",&intro_t22 };
TextLinkedList intro_t20 = { "시계를 보니 시침은 이미 7을 넘어간지 오래다.",&intro_t21 };
TextLinkedList intro_t19 = { "평소보다 잠을 푹 잔 것같이 개운한 기분이다.",&intro_t20 };
TextLinkedList intro_t18 = { "몇 시간이나 지났을까,,,",&intro_t19 };

TextLinkedList intro_t17 = { "목을 축이고 다시 침대라고 하기 부끄러운 매트리스 위에 몸을 던졌다.",NULL };
TextLinkedList intro_t16 = { "에,,,에,,휴 개빠졌네 말세다 말세야,,벌컥 벌컥",&intro_t17 };
TextLinkedList intro_t15 = { "왠지 모르게 기괴한 느낌에 약간 오싹했다." ,&intro_t16 };
TextLinkedList intro_t14 = { "형체의 움직임은 느릿하면서도 껄렁대는 느낌이다.",&intro_t15 };
TextLinkedList intro_t13 = { "꼭두 새벽같은 시간에도 불침번은 잘 수가 없는 법." ,&intro_t14 };
TextLinkedList intro_t12 = { "반투명한 비닐막 바깥으로 사람의 형체가 보인다." ,&intro_t13 };
TextLinkedList intro_t11 = { "그저 반투명 비닐막 문으로 대충 막아놓은 것이지만,,,",&intro_t12 };
TextLinkedList intro_t10 = { "격리 구역은 칸막이로 외부로부터 단절되어있다.",&intro_t11 };
TextLinkedList intro_t9 = { "물을 마시려면 문 밖에 있는 정수기까지 가야한다.",&intro_t10 };
TextLinkedList intro_t8 = { "전날에 마신 술 때문에 갈증이 몹시 났기 때문에 잠에서 깬 것 같다.",&intro_t9 };
TextLinkedList intro_t7= { "복귀 첫 날은 항상 피곤하기 때문에 금방 잠이 들었던 것 같다.",&intro_t8 };

TextLinkedList intro_t6 = { "개꿀같은 1인 격리 생활로 꿀빨다가 전역이라니,,,기다려라 사회야..!",NULL };
TextLinkedList intro_t5 = { "게다가 코로나 시국에 휴가를 나갔다오면 격리를 당하니, 이 좋은 세상인가!",&intro_t6 };
TextLinkedList intro_t4 = { "불쌍한 놈들,,얼마나 뺑이를 치고 있을지 생각하면 입가에 미소가 저절로 나왔다.",&intro_t5 };
TextLinkedList intro_t3 = { "다행히도 말년에 극악무도한 KCTC훈련에서 벗어났기 때문에 후회는 없다.",&intro_t4 };
TextLinkedList intro_t2 = { "전역 전 말출(마지막 휴가)은 순식간이었다.",&intro_t3 };
TextLinkedList intro_t1 = { "2주 동안의 극락을 맛보고 다시 지옥으로 돌아왔다." ,&intro_t2};
//공통 텍스트
TextLinkedList no_item3 = { "더 이상 쓸만한 물건이 없는 것 같다.",NULL };
TextLinkedList no_item2 = { "...달그락 달그락...",&no_item3 };
TextLinkedList no_item1 = { "...뒤적 뒤적...",&no_item2 };

TextLinkedList no_zombie3 = { "더 이상 좀비는 없는 것 같다.",NULL };
TextLinkedList no_zombie2 = { "아무 인기척도 느껴지지 않는다.",&no_zombie3 };
TextLinkedList no_zombie1 = { "...매우 조용하다",&no_zombie2 };
//
//텍스트 격리생활관
TextLinkedList f1_t4 = { "옆에는 간부연구실이 보인다.",NULL };
TextLinkedList f1_t3 = { "복도 방향으로 칸막이가 막고있다.",&f1_t4 };
TextLinkedList f1_t2 = { "격리생활관 앞이다.",&f1_t3 };
TextLinkedList f1_t1 = { "[격리생활관 앞 복도]",&f1_t2 };

TextLinkedList f2_t5 = { "코로나 사태 이후 창고로 사용되는 것 같다.",NULL };
TextLinkedList f2_t4 = { "하지만 지금은 먼지만 쌓여있다.",&f2_t5 };
TextLinkedList f2_t3 = { "매우 비좁은 1인 격리실이지만 있을 건 다 있는 모양새다.",&f2_t4 };
TextLinkedList f2_t2 = { "간부연구실이다.",&f2_t3 };
TextLinkedList f2_t1 = { "[간부연구실]",&f2_t2 };

TextLinkedList f3_t1 = { "칸막이 문에 자물쇠가 걸려있는 것 같다.",NULL };

TextLinkedList f21_t1 = { "[칸막이 열쇠]를 발견했다.",NULL };

TextLinkedList f31_t4 = { "밖으로 나가자.",NULL };
TextLinkedList f31_t3 = { "오래된 나무끼리 마찰되는 소리와 함께 문이 힘없이 열렸다.",&f31_t4 };
TextLinkedList f31_t2 = { "[칸막이 열쇠]를 사용했다.",&f31_t3 };
TextLinkedList f31_t1 = { "철커덕!",&f31_t2 };

TextLinkedList f32_t2 = { "열쇠는 주변에서 찾을 수 있을 것 같다.",NULL };
TextLinkedList f32_t1 = { "[칸막이 열쇠]가 필요하다.",&f32_t2 };

//텍스트 동편
TextLinkedList er_t6 = { "필요한 것들을 찾을 수 있을 것 같다.",NULL };
TextLinkedList er_t5 = { "왼쪽에는 화장실과 세탁실이 있다.",&er_t6 };
TextLinkedList er_t4 = { "오른쪽에는 행정반이 보인다." ,&er_t5};
TextLinkedList er_t3 = { "지나올 때 좀비는 없었으니 안심해도 될 것 같다.",&er_t4 };
TextLinkedList er_t2 = { "분명 놓친게 있는 것 같다.",&er_t3 };
TextLinkedList er_t1 = { "[2층 동편]",&er_t2 };

TextLinkedList e1_t5 = { "오른쪽에는 화장실과 세탁실이 있다.",NULL };
TextLinkedList e1_t4 = { "왼쪽에는 행정반이 보인다.",&e1_t5 };
TextLinkedList e1_t3 = { "역광 때문에 어둡게 보이지만 정상은 아닌 것 같다.",&e1_t4 };
TextLinkedList e1_t2 = { "저 멀리 복도 중앙에 사람 형체들이 보인다.",&e1_t3 };
TextLinkedList e1_t1 = { "[2층 동편]",&e1_t2 };

TextLinkedList e2_t3 = { "몇일 동안 청소를 못한 모양이다",NULL };
TextLinkedList e2_t2 = { "퀴퀴한 냄새가 진동한다.",&e2_t3 };
TextLinkedList e2_t1 = { "[화장실]",&e2_t2 };

TextLinkedList e21_t2 = { "무기로 사용할 수 있을 것 같다.",NULL };
TextLinkedList e21_t1 = { "[부러진 대걸레]를 발견했다.",&e21_t2 };

TextLinkedList e3_t3 = { "창문 밖으로 좀비들이 돌아다니는 모습이 보인다.",NULL };
TextLinkedList e3_t2 = { "세탁기 위에 빨랫감이 그대로 쌓여있다.",&e3_t3 };
TextLinkedList e3_t1 = { "[세탁실]",&e3_t2 };

TextLinkedList e31_t1 = { "[차갑게 식은 냉동 만두]를 발견했다.",NULL };

TextLinkedList e4_t7 = { "불길한 예감이 든다...빨리 움직여야 할 것 같다.",NULL }; 
TextLinkedList e4_t6 = { "...예상 발원지인 홍천군부터 폭격 예정...",&e4_t7 };
TextLinkedList e4_t5 = { "...좀비 사태 대응하여 좀비와의 전쟁을 선포...",&e4_t6 };
TextLinkedList e4_t4 = { "...당국은 내일인 6월 14일부터 대대적인...",&e4_t5 };
TextLinkedList e4_t3 = { "어디선가 라디오 소리가 작게 들린다.",&e4_t4 };
TextLinkedList e4_t2 = { "아무 인기척도 느껴지지 않는다.",&e4_t3 };
TextLinkedList e4_t1 = { "[2중대 행정반]",&e4_t2 };

TextLinkedList e41_t2 = { "주기가 되어있지만 글씨가 번져서 잘 안보인다.'...상'",NULL };
TextLinkedList e41_t1 = { "[*상 열쇠]를 발견했다.",&e41_t2 };

//텍스트 중앙 복도
TextLinkedList c1_t7 = { "저쪽에서 먼저 나의 존재를 알아챈 것 같다.",NULL };
TextLinkedList c1_t6 = { "하지만 아는 척 할 수는 없을 것 같다.",&c1_t7 };
TextLinkedList c1_t5 = { "내 알동기 윤모..어쩌다 이렇게...",&c1_t6 };
TextLinkedList c1_t4 = { "설마 ㅅ서..성...윤모..?",&c1_t5 };
TextLinkedList c1_t3 = { "익숙한 얼굴이 보인다..",&c1_t4 };
TextLinkedList c1_t2 = { "복도 중앙에 좀비 무리가 있다.",&c1_t3 };
TextLinkedList c1_t1 = { "[2층 중앙 복도]",&c1_t2 };

TextLinkedList cr_t5 = { "어디선가 반복적인 기계음이 계속 들린다.",NULL };
TextLinkedList cr_t4 = { "우웅ㅡ우웅ㅡ우웅ㅡ우웅ㅡ",&cr_t5 };
TextLinkedList cr_t3 = { "이상한 소리만 제외하면 매우 고요하다.",&cr_t4 };
TextLinkedList cr_t2 = { "좀비는 더 이상 보이지 않는다.",&cr_t3 };
TextLinkedList cr_t1 = { "[2층 중앙 복도]",&cr_t2 };

TextLinkedList c3_t3 = { "아무튼 아니다.",NULL };
TextLinkedList c3_t2 = { "작전상 후퇴일뿐.",&c3_t3 };
TextLinkedList c3_t1 = { "이건 절대 도망치는게 아니다.",&c3_t2 };

TextLinkedList c2_t1 = { "윤모는 인간이었을 때도 나약했으니 충분히 승산이 있을 것 같다.",NULL };


TextLinkedList c21_t6 = { "이제 다른 곳으로 이동해야 할 것 같다.",NULL };
TextLinkedList c21_t5 = { "더 이상 미동이 없다.",&c21_t6 };
TextLinkedList c21_t4 = { "[부러진 대걸레]를 잃었다.",&c21_t5 };
TextLinkedList c21_t3 = { "대걸레가 꽂힌 채로 쓰러졌다.",&c21_t4 };
TextLinkedList c21_t2 = { "[부러진 대걸레]로 숨통을 끊었다.",&c21_t3 };
TextLinkedList c21_t1 = { "윤모야 미안하다..하지만 어쩔 수 없었다.",&c21_t2 };

TextLinkedList c22_t4 = { "간신히 2층 서편으로 도망쳐 왔다.",NULL };
TextLinkedList c22_t3 = { "지금이라도 도망가야 할 것 같다.",&c22_t4 };
TextLinkedList c22_t2 = { "내가 알 던 윤모가 아니다.",&c22_t3 };
TextLinkedList c22_t1 = { "헉,,,헉,,,무기 없이는 무리인 것 같다.",&c22_t2 };

//텍스트 서편
TextLinkedList w1_t4 = { "어쩌면 다른 생존자가 있을 수도 있을 것 같다.",NULL };
TextLinkedList w1_t3 = { "쓸만한 물건들이 남아 있을지도 모른다.",&w1_t4 };
TextLinkedList w1_t2 = { "1소대와 2소대 생활관들이 보인다.",&w1_t3 };
TextLinkedList w1_t1 = { "[2층 서편]",&w1_t2 };

TextLinkedList w2_t3 = { "벽 군데군데 곰팡이가 피어있다.",NULL };
TextLinkedList w2_t2 = { "1 - 1반..복도 제일 끝 생활관이라 그런지 햇볕이 잘 들어오지 않는다.",&w2_t3 };
TextLinkedList w2_t1 = { "[1-1생활관]",&w2_t2 };

TextLinkedList w21_t1 = { "[손전등]을 발견했다.",NULL };

TextLinkedList w3_t3 = { "들어서자마자 꼬랑내 때문에 구역질이 난다.",NULL };
TextLinkedList w3_t2 = { "1-2반..항상 물만 묻히고 안씻는 이혜성 상병이 있던 곳이다.",&w3_t3 };
TextLinkedList w3_t1 = { "[1-2생활관]",&w3_t2 };

TextLinkedList w31_t1 = { "[야채 건빵] 한 봉지를 발견했다.",NULL };

TextLinkedList w4_t4 = { "좀비가 구석 한켠에 처박혀 앉아 있다.",NULL };
TextLinkedList w4_t3 = { "이상할 정도로 조용한 것이 좀비가 있는 것 같다.",&w4_t4 };
TextLinkedList w4_t2 = { "1 - 3반..항상 시끄러운 반이었지만 지금은 매우 조용하다.",&w4_t3 };
TextLinkedList w4_t1 = { "[1-3생활관]",&w4_t2 };

TextLinkedList w41_t4 = { "사시나무처럼 떨고 있다.",NULL };
TextLinkedList w41_t3 = { "좀비의 목을 힘껏 비틀어 제껴버렸다.",&w41_t4 };
TextLinkedList w41_t2 = { "푸드드득 우직 꾸엑!",&w41_t3 };
TextLinkedList w41_t1 = { "살...금...살...금...",&w41_t2 };

TextLinkedList w42_t3 = { "최대한 소리가 안나게 문을 닫고 나왔다.",NULL };
TextLinkedList w42_t2 = { "한이 많이 쌓인 좀비임이 분명하다.",&w42_t3 };
TextLinkedList w42_t1 = { "조용히 나가야겠다.",&w42_t2 };

TextLinkedList w43_t1 = { "[몽키 스패너]를 발견했다.",NULL };

TextLinkedList w5_t4 = { "하느님이 아니라 싸이버거를 굳게 믿었던 것 같다.",NULL };
TextLinkedList w5_t3 = { "아무리 둘러봐도 성경과 십자가는 안보인다.",&w5_t4 };
TextLinkedList w5_t2 = { "2 - 1반..기독교 신자가 유난히 많았던 반..",&w5_t3 };
TextLinkedList w5_t1 = { "[2-1생활관]",&w5_t2 };

TextLinkedList w51_t2 = { "부상이 생겼을 때 유용하게 사용할 수 있을 것이다.",NULL };
TextLinkedList w51_t1 = { "꾀병 환자의 [붕대]를 발견했다.",&w51_t2 };


TextLinkedList w6_t4 = { "문을 열자마자 숨어있던 좀비가 공격해온다!",NULL };
TextLinkedList w6_t3 = { "끼-----------이이이이이익--------------",&w6_t4 };
TextLinkedList w6_t2 = { "2-2반이라.....",&w6_t3 };
TextLinkedList w6_t1 = { "[2-2생활관]",&w6_t2 };

TextLinkedList w61_t3 = { "좀비가 멍청해서 그대로 벽에 머리를 박고 죽었다.",NULL };
TextLinkedList w61_t2 = { "반사신경으로 재빠르게 공격을 피했다.",&w61_t3 };
TextLinkedList w61_t1 = { "잘못하면 목을 내어주고 좀비로 진급할 뻔했다.",&w61_t2 };

TextLinkedList w62_t5 = { "경미한 부상을 입었다.",NULL };
TextLinkedList w62_t4 = { "더 이상 쫓아오지는 않는 것 같다.",&w62_t5 };
TextLinkedList w62_t3 = { "공격을 피하느라 벽에 몸을 부딛혔다.",&w62_t4 };
TextLinkedList w62_t2 = { "바로 문을 닫고 나왔다.",&w62_t3 };
TextLinkedList w62_t1 = { "잘못하면 목을 내어주고 좀비로 진급할 뻔했다.",&w62_t2 };

TextLinkedList w63_t1 = { "꼴초의 [터보 라이터]를 발견했다.",NULL };

TextLinkedList w7_t3 = { "항상 청결한 생활관이다.",NULL };
TextLinkedList w7_t2 = { "2-3반..알코올 냄새가 코를 뻥 뚫어주는 것 같다.",&w7_t3 };
TextLinkedList w7_t1 = { "[2-3생활관]",&w7_t2 };

TextLinkedList w71_t1 = { "[손 소독제]를 발견했다.",NULL };

//텍스트 1층--------------------------------------------------------------------------------------------------------------------

TextLinkedList p1_t4 = { "그 외에는 침묵이 가득하다." ,NULL };
TextLinkedList p1_t3 = { "아까부터 계속 미세한 기계음이 반복적으로 들린다..",&p1_t4 };
TextLinkedList p1_t2 = { "곳곳에 혈흔 자국들이 보인다.",&p1_t3 };
TextLinkedList p1_t1 = { "[1층 중앙 현관]",&p1_t2 };

TextLinkedList p2_t4 = { "어딘가에 [총기함 키]가 있을 것이다." ,NULL };
TextLinkedList p2_t3 = { "한켠에는 아직 개봉되지 않은 택배 상자들이 쌓여있다.",&p2_t4 };
TextLinkedList p2_t2 = { "인사과장이 1년 동안 결산하지 않은 부대 체육 리그 점수표가 정면에 보인다.",&p2_t3 };
TextLinkedList p2_t1 = { "[인사과]",&p2_t2 };

TextLinkedList p21_t1 = { "[총기함 키]를 발견했다." ,NULL };

TextLinkedList p3_t6 = { "[8월 10일,대대장님 생신★]" ,NULL };
TextLinkedList p3_t5 = { "옆에는 달력이 있다." ,&p3_t6 };
TextLinkedList p3_t4 = { "책상 위에 군수과장 아들내미 사진이 보인다." ,&p3_t5 };
TextLinkedList p3_t3 = { "지독한 사람이었다.",&p3_t4 };
TextLinkedList p3_t2 = { "대대장의 총애를 받던 군수과장이 있던 곳이다.",&p3_t3 };
TextLinkedList p3_t1 = { "[군수과]",&p3_t2 };

TextLinkedList p31_t5 = { "[어딘가 중요해 보이는 열쇠]를 발견했다." ,NULL };
TextLinkedList p31_t4 = { "도로록" ,&p31_t5 };
TextLinkedList p31_t3 = { "띵!" ,&p31_t4 };
TextLinkedList p31_t2 = { "달그락 달그락" ,&p31_t3 };
TextLinkedList p31_t1 = { "......." ,&p31_t2 };

TextLinkedList p4_t2 = { "문이 잠겨있다....[부재중]..." ,NULL };
TextLinkedList p4_t1 = { "[대대장실]" ,&p4_t2 };

TextLinkedList p5_t8 = { "갑자기 뒤에서 좀비 한 마리가 달려든다." ,NULL };
TextLinkedList p5_t7 = { "쿠당탕!" ,&p5_t8 };
TextLinkedList p5_t6 = { "내가 보이는 화면에 이상한 형체가 같이 있다." ,&p5_t7 };
TextLinkedList p5_t5 = { "그런데... 뭔가 이상하다." ,&p5_t6 };
TextLinkedList p5_t4 = { "옥상에는 좀비가 없는 것 같다." ,&p5_t5 };
TextLinkedList p5_t3 = { "CCTV 감시 화면 곳곳에 좀비들 모습이 보인다..",&p5_t4 };
TextLinkedList p5_t2 = { "항상 간부들이 북적거리던 곳이다.",&p5_t3};
TextLinkedList p5_t1 = { "[지휘 통제실]",&p5_t2 };

TextLinkedList p51_t1 = { "좀비가 매우 강력해보인다." ,NULL };

TextLinkedList p52_t4 = { "큰 부상을 입었다." ,NULL };
TextLinkedList p52_t3 = { "머리가 조금 찢어진 것 같다." ,&p52_t4 };
TextLinkedList p52_t2 = { "하마터면 엔딩도 보기전에 죽을 뻔했다." ,&p52_t3 };
TextLinkedList p52_t1 = { "간신히 제압했다." ,&p52_t2 };


TextLinkedList p53_t2 = { "주임원사실에 들어갈 수 있을 것이다." ,NULL };
TextLinkedList p53_t1 = { "좀비가 입고있던 전투복에서 [주임원사실 열쇠]를 발견했다." ,&p53_t2 };

TextLinkedList p54_t5 = { "쿨럭,," ,NULL };
TextLinkedList p54_t4 = { "어라..?점점 의식이 흐려진다." ,&p54_t5 };
TextLinkedList p54_t3 = { "지금이라도 도망쳐야 할 것 같다." ,&p54_t4 };
TextLinkedList p54_t2 = { "자세히 보니 주임원사님의 얼굴을 꼭 빼닮은 것 같다." ,&p54_t3 };
TextLinkedList p54_t1 = { "헉,,,헉,,,역시 맨손으로는 무리였다." ,&p54_t2 };

TextLinkedList p6_t1 = { "주임 원사실...[부재중]..." ,NULL };

TextLinkedList p6__t2 = { "좀비의 여파로 더 이상 문이 열리지 않는다.",NULL }; //주임원사실 한바탕 소란이 끝나고 다시 갔을 때
TextLinkedList p6__t1 = { "철컥,,,,드르륵,,,탁,,쿵,,",&p6__t2 };

TextLinkedList p61_t7 = { "오오,,이것은 정말 영롱하다..!",NULL };
TextLinkedList p61_t6 = { "위엄있어 보이는 장검 진열대 사이로 [금고]가 보인다." ,&p61_t7 };
TextLinkedList p61_t5 = { "잡다한 용접 도구들이 눈에 띈다.",&p61_t6 };
TextLinkedList p61_t4 = { "안으로 들어갈 수록 커피 원두향이 진하게 난다." ,&p61_t5 };
TextLinkedList p61_t3 = { "좀비에게서 얻은 열쇠로 문이 열렸다." ,&p61_t4 };
TextLinkedList p61_t2 = { "달그락 슈루룩 철컥!" ,&p61_t3 };
TextLinkedList p61_t1 = { "[주임원사실]" ,&p61_t2 };

TextLinkedList p62_t3 = { "열쇠가 필요하다." ,NULL };
TextLinkedList p62_t2 = { "철컥 철컥 문이 잠겨있다." ,&p62_t3 };
TextLinkedList p62_t1 = { "[주임원사실]" ,&p62_t2 };


TextLinkedList p63_t2 = { "강철로 된 정육면체의 모양이 빛 한 줄기 빠져나올 수 없는 밀실을 연상시킨다." ,NULL };
TextLinkedList p63_t1 = { "빛이 바래서 표면에 광을 띄고 있다." ,&p63_t2 };

TextLinkedList p64_t5 = { "[권총과 탄알집]을 발견했다." ,NULL };
TextLinkedList p64_t4 = { "중요해보이는 기밀 문서들이 잔뜩 있다." ,&p64_t5 };
TextLinkedList p64_t3 = { "금고가 열렸다!!!" , &p64_t4 };
TextLinkedList p64_t2 = { "드륽 철컥!" , &p64_t3 };
TextLinkedList p64_t1 = { "..........." ,&p64_t2 };

TextLinkedList p66_t5 = { "빨리 도망치거나 숨어야 할 것 같다." ,NULL };
TextLinkedList p66_t4 = { "좀비들이 몰려오는 소리가 들린다." ,&p66_t5 };
TextLinkedList p66_t3 = { "갑자기 비상벨이 울린다." ,&p66_t4 };
TextLinkedList p66_t2 = { "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" ,&p66_t3 };
TextLinkedList p66_t1 = { "삐--용--삐--용--삐--용--삐--용-- " ,&p66_t2 };

TextLinkedList p65_t3 = { "열쇠가 필요하다." ,NULL };
TextLinkedList p65_t2 = { "아무 반응이 없다." ,&p65_t3 };
TextLinkedList p65_t1 = { "철커덕...철커덕..." ,&p65_t2 };


TextLinkedList p69_t8 = { "이제 밖으로 나가서 동태를 살펴봐야겠다." ,NULL };
TextLinkedList p69_t7 = { "휴 다행히 좀비 소리가 다시 멀어졌다." ,&p69_t8 };
TextLinkedList p69_t6 = { "쿵...쾅...쿵...쾅...쿵.........." ,&p69_t7 };
TextLinkedList p69_t5 = { "쿵쾅..쿵쾅..쿵..쿵..쿵...쾅...쾅...." ,&p69_t6 };
TextLinkedList p69_t4 = { "쿵쾅쿵쾅쿵쾅쿵쾅쿵쾅쿵쿵쾅쾅...." ,&p69_t5 };
TextLinkedList p69_t3 = { "숨을 참아도 심장 소리는 더 커지는 것 같다...." ,&p69_t4 };
TextLinkedList p69_t2 = { "좀비들의 발소리가 점점 가까워진다." ,&p69_t3 };
TextLinkedList p69_t1 = { "일단 락커에 몸을 숨겼다." ,&p69_t2 };

TextLinkedList p610_t6 = { "세상이 불그노르스름해졌다. 그를ㄹㄹㄹㄹ" ,NULL };
TextLinkedList p610_t5 = { "혈관을 타고 뜨거운 수증기가 발 끝부터 머리 끝까지 차오르는 느낌이 든다." ,&p610_t6 };
TextLinkedList p610_t4 = { "으드득으드득..으드득으드득....." ,&p610_t5 };
TextLinkedList p610_t3 = { "좀비들이 나의 앞을 가로막고 있다." ,&p610_t4 };
TextLinkedList p610_t2 = { "하지만 이미 늦었다.." ,&p610_t3 };
TextLinkedList p610_t1 = { "황급히 주임원사실 밖으로 뛰쳐나왔다." ,&p610_t2 };

TextLinkedList p7_t5 = { "외부와 연락하기 위해서 필요한 장비들을 가져가야 할 것 같다." ,NULL };
TextLinkedList p7_t4 = { "옥상에 있는 통신 장비와 연결할 수 있다." ,&p7_t5 };
TextLinkedList p7_t3 = { "통신망 개통에 필요한 유지 장비들이 있다." ,&p7_t4 };
TextLinkedList p7_t2 = { "먼지로 뒤덮여 있어서 공기가 매캐하다." ,&p7_t3 };
TextLinkedList p7_t1 = { "[통신 물자 창고]" ,&p7_t2 };

TextLinkedList p71_t2 = { "망개통에 필요한 물품은 다 챙긴 것 같다." ,NULL };
TextLinkedList p71_t1 = { "[노트북과 연결 포트]를 발견했다." ,&p71_t2 };

TextLinkedList p8_t3 = { "WD냄새와 쇳덩이 냄새들이 난다." ,NULL };
TextLinkedList p8_t2 = { "총기함실이다." ,&p8_t3 };
TextLinkedList p8_t1 = { "[총기함실]" ,&p8_t2 };

TextLinkedList p811_t1 = { "총기함은 굳게 잠겨있다." ,NULL };

TextLinkedList p81_t3 = { "[K2 소총]을 얻었다." ,NULL };
TextLinkedList p81_t2 = { "훈련 때문에 탄약은 없는 것 같다." ,&p81_t3 };
TextLinkedList p81_t1 = { "[총기함키]로 문을 열었다." ,&p81_t2 };

TextLinkedList p82_t3 = { "인사과에 가면 있을 것이다." ,NULL };
TextLinkedList p82_t2 = { "[총기함키]가 필요하다." ,&p82_t3 };
TextLinkedList p82_t1 = { "총기함이 잠겨있다." ,&p82_t2 };

//텍스트 옥상----------------------------------------------------------------------------------------------------------------------
TextLinkedList r1_t4 = { "[옥상 열쇠]가 필요할 것 같다.",NULL };
TextLinkedList r1_t3 = { "철컥, 철컥,",&r1_t4 };
TextLinkedList r1_t2 = { "[ 관계자 외 출입금지 ]",&r1_t3 };
TextLinkedList r1_t1 = { "옥상 문이 닫혀있다.",&r1_t2 };

TextLinkedList r2_t5 = { "우우웅...우우웅...(반복적인 기계음)",NULL };
TextLinkedList r2_t4 = { "통신망만 개통하면 외부와 연락이 가능할 것이다.",&r2_t5 };
TextLinkedList r2_t3 = { "다행히 통신 장비가 작동중인 것 같다.",&r2_t4 };
TextLinkedList r2_t2 = { "옥상에 설치된 안테나 통신 장치들이 반복적인 기계음을 내고 있다.",&r2_t3 };
TextLinkedList r2_t1 = { "[옥상]",&r2_t2 };

TextLinkedList r31_t6 = { "본부대 상병 김상명, 전화받았습니다~",NULL };
TextLinkedList r31_t5 = { "또로로로로로로...또로로로로로로...(신호 대기음) ",&r31_t6 };
TextLinkedList r31_t4 = { "[접속 상태: 양호 ]",&r31_t5 };
TextLinkedList r31_t3 = { "[...무선 통신 체계 접속중...]",&r31_t4 };
TextLinkedList r31_t2 = { "[...국방망 연결중...]",&r31_t3 };
TextLinkedList r31_t1 = { "[...이더넷 연결중...]",&r31_t2 };

TextLinkedList r32_t3 = { "우우웅...우우웅...(반복적인 기계음)",NULL };
TextLinkedList r32_t2 = { "통신망 개통을 위한 장비는 1층 [통신물자 창고]에 있을 것이다.",&r32_t3 };
TextLinkedList r32_t1 = { "역시 통신망 연결이 끊겨있다.",&r32_t2 };

TextLinkedList r3_t2 = { "혹시 연결되어 있을 수도..?",NULL };
TextLinkedList r3_t1 = { "통신망을 연결하려면 노트북과 연결 포트가 필요하다.",&r3_t2 };

TextLinkedList r4_t4 = { " 더 이상 신호가 잡히지 않는다.",NULL };
TextLinkedList r4_t3 = { "통신 장비 노드가 노후되어 연결이 불안정한 것 같다.",&r4_t4 };
TextLinkedList r4_t2 = { "연결이 끊어졌다..",&r4_t3 };
TextLinkedList r4_t1 = { "뚜...뚜...뚜...",&r4_t2 };

//텍스트 엔딩-----------------------------------------------------------------------------------------------------------------------
TextLinkedList h1_t13 = { "나는 살았다..",NULL };
TextLinkedList h1_t12 = { "구조 헬기다!",&h1_t13 };
TextLinkedList h1_t11 = { "눈을 떠보니 저 멀리 산 골짜기 위로 희망이 날아오고 있다.",&h1_t12 };
TextLinkedList h1_t10 = { "두두두두두두두두두두두두두두두두두두두두두두",&h1_t11 };
TextLinkedList h1_t9 = { ".....도도도도도도도도도도도두도두도두도두도두두두",&h1_t10 };
TextLinkedList h1_t8 = { "이제는 더 이상 본래 원주민의 모습은 온데 간데 없고 이방인이 주인 자리를 차지했다.",&h1_t9 };
TextLinkedList h1_t7 = { "처음에는 이방인이 열세했지만 시간이 갈 수록 원주민을 압도한다.",&h1_t8 };
TextLinkedList h1_t6 = { "자신의 영역을 침범하는 낯선 소음과 경쟁하듯 간섭을 이룬다.",&h1_t7 };
TextLinkedList h1_t5 = { "그리고 이제는 성가신 기계음의 반복적인 소음...",&h1_t6 };
TextLinkedList h1_t4 = { "여기에 존재하는 것은 나 자신과 좀비...",&h1_t5 };
TextLinkedList h1_t3 = { "산 기슭을 훑고 지나오는 바람은 머나먼 곳으로 떠나는 것 같다.",&h1_t4 };
TextLinkedList h1_t2 = { "점점 석양이 지고, 태양빛이 붉게 무르익어 간다.",&h1_t3 };
TextLinkedList h1_t1 = { "어느정도 시간이 흐른 것 같다.",&h1_t2 };

TextLinkedList h2_t24 = { "또 군대 꿈을 꾸다니!",NULL };
TextLinkedList h2_t23 = { "잠에서 일어나니 등이 축축하게 젖어있다.",&h2_t24 };
TextLinkedList h2_t22 = { "코로나에 걸려서 온 몸에 열이 났던 것 같다.",&h2_t23 };
TextLinkedList h2_t21 = { "마치 내연 기관이 주체할 수 없을 속도로 펌프질하는 것처럼 과열 상태다.",&h2_t22 };
TextLinkedList h2_t20 = { "심장 박동이 온몸으로 느껴진다.",&h2_t21 };
TextLinkedList h2_t19 = { "흐어악!",&h2_t20 };
TextLinkedList h2_t18 = { "일종의 경련과 함께 눈이 떠졌다.",&h2_t19 };
TextLinkedList h2_t17 = { "쿠구구구구구구구구구구구 쿠구구구구구구구구구구구",&h2_t18 };
TextLinkedList h2_t16 = { "삐ㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣ",&h2_t17 };
TextLinkedList h2_t15 = { "그리고 내가 마지막으로 본 것은 눈 앞을 뒤 덮는 섬광이었다.",&h2_t16 };
TextLinkedList h2_t14 = { "내 머리 위로 굉음을 내며 지나갔다.",&h2_t15 };
TextLinkedList h2_t13 = { "부ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ왕ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ",&h2_t14 };
TextLinkedList h2_t12 = { "구하러 왔구나!",&h2_t13 };
TextLinkedList h2_t11 = { "눈을 떠보니 저 멀리 산 골짜기 위로 희망이 날아오고 있다.",&h2_t12 };
TextLinkedList h2_t10 = { "바바바바바ㅡ바바바바바ㅡ바바바바바ㅡ바바바바바",&h2_t11 };
TextLinkedList h2_t9 = { "브브브브브ㅡ브브브브브ㅡ브브브브브ㅡ브브브브브",&h2_t10 };
TextLinkedList h2_t8 = { "이제는 더 이상 본래 원주민의 모습은 온데 간데 없고 이방인이 주인 자리를 차지했다.",&h2_t9 };
TextLinkedList h2_t7 = { "처음에는 이방인이 열세했지만 시간이 갈 수록 원주민을 압도한다.",&h2_t8 };
TextLinkedList h2_t6 = { "자신의 영역을 침범하는 낯선 소음과 경쟁하듯 간섭을 이룬다.",&h2_t7 };
TextLinkedList h2_t5 = { "그리고 이제는 성가신 기계음의 반복적인 소음...",&h2_t6 };
TextLinkedList h2_t4 = { "여기에 존재하는 것은 나 자신과 좀비...",&h2_t5 };
TextLinkedList h2_t3 = { "산 기슭을 훑고 지나오는 바람은 머나먼 곳으로 떠나는 것 같다.",&h2_t4 };
TextLinkedList h2_t2 = { "점점 석양이 지고, 태양빛이 붉게 무르익어 간다.",&h2_t3 };
TextLinkedList h2_t1 = { "어느정도 시간이 흐른 것 같다.",&h2_t2 };

TextLinkedList b1_t16 = { "콰직!",NULL };
TextLinkedList b1_t15 = { "머리부터 자유 낙하를 했다.",&b1_t16 };
TextLinkedList b1_t14 = { "이럴때 옥상이라는 장점을 이용하면 되는 것을 깨달았다.",&b1_t15 };
TextLinkedList b1_t13 = { "하지만 이제는 문을 막아놓은 통신 장비조차 옮길 힘이 없다.",&b1_t14 };
TextLinkedList b1_t12 = { "차라리 좀비한테 먹히는게 더 의미있을 것 같다.",&b1_t13 };
TextLinkedList b1_t11 = { "의식은 점점 메말라가는 느낌이다.",&b1_t12 };
TextLinkedList b1_t10 = { "차라리 폭격을 당해서 시원한 불 비를 맞고 작렬하게 불타고 싶을 정도다.",&b1_t11 };
TextLinkedList b1_t9 = { "그렇다. 정말 빠져나갈 길이 없는 것이다.",&b1_t10 };
TextLinkedList b1_t8 = { "하지만 나 또한 마찬가지다.",&b1_t9 };
TextLinkedList b1_t7 = { "문은 통신장비들로 막아놔서 들어올 수는 없을 것이다.",&b1_t8 };
TextLinkedList b1_t6 = { "며칠이나 지났을까...좀비들이 옥상 문 앞까지 들랑거리는 소리가 들린다.",&b1_t7 };
TextLinkedList b1_t5 = { "그리고 이제는 성가신 기계음의 반복적인 소음...",&b1_t6 };
TextLinkedList b1_t4 = { "여기에 존재하는 것은 나 자신과 좀비...",&b1_t5 };
TextLinkedList b1_t3 = { "산 기슭을 훑고 지나오는 바람은 머나먼 곳으로 떠나는 것 같다.",&b1_t4 };
TextLinkedList b1_t2 = { "점점 석양이 지고, 태양빛이 붉게 무르익어 간다.",&b1_t3 };
TextLinkedList b1_t1 = { "어느정도 시간이 흐른 것 같다.",&b1_t2 };

TextLinkedList b2_t24 = { "이런..",NULL };
TextLinkedList b2_t23 = { "밑을 보니 잔해물을 이불로 덮고 자고있는 내 모습이 보인다.",&h2_t24 };
TextLinkedList b2_t22 = { "정말 그렇다.",&h2_t23 };
TextLinkedList b2_t21 = { "마치 영혼이라도 된 것처럼 자유로운 느낌이다.",&h2_t22 };
TextLinkedList b2_t20 = { "몸이 홀가분하고 새처럼 가벼워진 것 같다.",&h2_t21 };
TextLinkedList b2_t19 = { "흐어악!",&h2_t20 };
TextLinkedList b2_t18 = { "일종의 경련과 함께 눈이 떠졌다.",&h2_t19 };
TextLinkedList b2_t17 = { "쿠구구구구구구구구구구구 쿠구구구구구구구구구구구",&h2_t18 };
TextLinkedList b2_t16 = { "삐ㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣㅣ",&h2_t17 };
TextLinkedList b2_t15 = { "그리고 내가 마지막으로 본 것은 눈 앞을 뒤 덮는 섬광이었다.",&h2_t16 };
TextLinkedList b2_t14 = { "내 머리 위로 굉음을 내며 지나갔다.",&h2_t15 };
TextLinkedList b2_t13 = { "부ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ왕ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ",&h2_t14 };
TextLinkedList b2_t12 = { "구하러 왔구나!",&h2_t13 };
TextLinkedList b2_t11 = { "눈을 떠보니 저 멀리 산 골짜기 위로 희망이 날아오고 있다.",&h2_t12 };
TextLinkedList b2_t10 = { "바바바바바ㅡ바바바바바ㅡ바바바바바ㅡ바바바바바",&h2_t11 };
TextLinkedList b2_t9 = { "브브브브브ㅡ브브브브브ㅡ브브브브브ㅡ브브브브브",&h2_t10 };
TextLinkedList b2_t8 = { "이제는 더 이상 본래 원주민의 모습은 온데 간데 없고 이방인이 주인 자리를 차지했다.",&h2_t9 };
TextLinkedList b2_t7 = { "처음에는 이방인이 열세했지만 시간이 갈 수록 원주민을 압도한다.",&h2_t8 };
TextLinkedList b2_t6 = { "자신의 영역을 침범하는 낯선 소음과 경쟁하듯 간섭을 이룬다.",&h2_t7 };
TextLinkedList b2_t5 = { "그리고 이제는 성가신 기계음의 반복적인 소음...",&h2_t6 };
TextLinkedList b2_t4 = { "여기에 존재하는 것은 나 자신과 좀비...",&h2_t5 };
TextLinkedList b2_t3 = { "산 기슭을 훑고 지나오는 바람은 머나먼 곳으로 떠나는 것 같다.",&h2_t4 };
TextLinkedList b2_t2 = { "점점 석양이 지고, 태양빛이 붉게 무르익어 간다.",&h2_t3 };
TextLinkedList b2_t1 = { "어느정도 시간이 흐른 것 같다.",&h2_t2 };

TextLinkedList gameover_t1 = { "[게임 오버]",NULL };
TextLinkedList gameclear_t1 = { "[게임 클리어]",NULL };


//선택지의 수에 따라 링크를 저장한 구조체포인터 배열 생성
TreeNode* ending[2] = { &r6,&r7 }; //엔딩 선택지
TreeNode* pre[6] = { &p4,&p5,&p6,&p7,&p8,&cr };//
TreeNode* west[5] = { &w4,&w5,&w6,&w7,&cr };//
TreeNode* center[2] = { &r1,&er };//옥상과 동편 주소는 따로 저장
TreeNode* east[2] = { &e4,&c1 };//세탁실,행정반,중앙복도(첫번째)
TreeNode* east2[2] = { &e4,&cr };

//해피엔딩, 배드 엔딩, 게임오버 일단 오류 피하기 위해서 만들어놓음
TreeNode happy1 = { &h1_t1,NULL,0,NULL,NULL,NULL,NULL };
TreeNode happy2 = { &h2_t1,NULL,0,NULL,NULL,NULL,NULL };
TreeNode bad1 = { &b1_t1,NULL,0,NULL,NULL,NULL,NULL };
TreeNode bad2 = { &b2_t1,NULL,0,NULL,NULL,NULL,NULL };

TreeNode gameover = { NULL,&confirm,0,NULL,NULL,NULL,NULL };
//옥상 루트(r)

TreeNode r1 = { &r1_t1,&confirm,0,&r2,&cr,NULL,"[옥상]" };//옥상열쇠가 있는가
TreeNode r2 = { &r2_t1,&r2_s1,2,&r3,&cr,NULL,"[옥상]" };//1망개통 한다 2중앙복도로 내려간다
TreeNode r3 = { &r3_t1,&confirm,0,&r31,&r32,NULL,"[옥상]" }; //연결포트와 노트북이 있는가
TreeNode r31 = { &r31_t1,&r31_s1,4,&r4,&r5,ending,"[옥상]" };//연결포트와 노트북이 있는 경우
TreeNode r32 = { &r32_t1,&confirm,0,&r2,NULL,NULL,"[옥상]" };//연결포트와 노트북이 없는 경우
TreeNode r4 = { &r4_t1,&confirm,0,&bad1,&bad1,NULL,"[옥상]" };
TreeNode r5 = { &r4_t1,&confirm,0,&happy1,&happy1 ,NULL,"[옥상]" };
TreeNode r6 = { &r4_t1,&confirm,0,&bad2,&bad2,NULL,"[옥상]" };
TreeNode r7 = { &r4_t1,&confirm,0,&happy2,&happy2,NULL,"[옥상]" };

//1층 루트(p)


TreeNode p1 = { &p1_t1,&p1_s1,8,&p2,&p3,pre,"1층 중앙 현관" };//1층 중앙 현관

TreeNode p2 = { &p2_t1,&explore,2,&p21,&p1,NULL,"[인사과]" };//인사과
TreeNode p21 = { &p21_t1,&confirm,0,NULL,&p2,NULL,"[인사과]" };

TreeNode p3 = { &p3_t1,&explore,2,&p31,&p1,NULL, "[군수과]" };//군수과
TreeNode p31 = { &p31_t1,&confirm,0,NULL,&p3,NULL, "[군수과]" };

TreeNode p4 = { &p4_t1,&confirm,0,NULL,&p1,NULL,"[1층 중앙 현관]" };//대대장실

TreeNode p5 = { &p5_t1,&fight,2,&p51,&p1, NULL,"[지휘통제실]" };//지휘통제실
TreeNode p51 = { &p51_t1,&confirm,0,&p52,&p54, NULL,"[지휘통제실]" };//무기가 있을 경우  #임시로 right 주소 p52로 바꿈
TreeNode p52 = { &p52_t1,&explore,2,&p53,&p1, NULL,"[지휘통제실]" };//좀비 처치 후 탐색
TreeNode p53 = { &p53_t1,&confirm,0,NULL,&p52, NULL,"[지휘통제실]" }; //-- > 주임원사실 열쇠 획득
TreeNode p54 = { &p54_t1,&confirm,0,NULL,&gameover, NULL,"[지휘통제실]" };//무기가 없을 경우
TreeNode p55 = { &p53_t1,&confirm,0,NULL,&p1,NULL };//도망갔다가 다시 와서 탐색했을 시

TreeNode p6 = { &p6_t1,&confirm,0,&p61,&p62,NULL,"[주임원사실]" };//주임원사실
TreeNode p61 = { &p61_t1,&p61_s1,2,&p63,&p1,NULL,"[주임원사실]" };//열쇠 있을시
TreeNode p62 = { &p62_t1,&confirm,0,&p1,NULL,NULL,"[주임원사실]" };//열쇠 없을시
TreeNode p63 = { &p63_t1,&confirm,0,&p64,&p65,NULL,"[주임원사실]" };
TreeNode p64 = { &p64_t1,&confirm,0,&p66,NULL,NULL,"[주임원사실]" };//금고 열쇠 있을시 권총과 탄알집
TreeNode p65 = { &p65_t1,&confirm,0,&p61,NULL,NULL,"[주임원사실]" };//금고 열쇠 없을시 뒤로
TreeNode p66 = { &p66_t1,&p66_s1,2,&p69,&p610,NULL,"[주임원사실]" };
TreeNode p69 = { &p69_t1,&confirm,0,NULL,&p1,NULL,"[주임원사실]" };//숨었을 때
TreeNode p610 = { &p610_t1,&confirm,0,NULL,&gameover,NULL,"[주임원사실]" };//도망쳤을 때 게임 오버
TreeNode p6_ = { &p6__t1,&confirm,0,NULL,&p1,NULL,"[1층 중앙 현관]" };

TreeNode p7 = { &p7_t1,&explore,2,&p71,&p1,NULL,"[통신물자창고]" };//통신물자창고
TreeNode p71 = { &p71_t1,&confirm,0,NULL,&p7,NULL,"[통신물자창고]" };

TreeNode p8 = { &p8_t1,&explore,2,&p811,&p1,NULL, "[총기함실]" };//총기함실
TreeNode p811 = { &p811_t1,&confirm,0,&p81,&p82,NULL, "[총기함실]" };
TreeNode p81 = { &p81_t1,&confirm,0,&p8,NULL,NULL, "[총기함실]" };//열쇠가 있을 시
TreeNode p82 = { &p82_t1,&confirm,0,&p8,NULL,NULL, "[총기함실]" };//열쇠가 없을 시

//2층 서편 루트(w)

TreeNode w1 = { &w1_t1,&w1_s1,7 ,&w2,&w3,west,"[2층 서편 복도]" };//서편 로비
TreeNode w2 = { &w2_t1,&explore,2,&w21,&w1,NULL,"[1-1반]" };//1-1반
TreeNode w21 = { &w21_t1,&confirm,0,NULL,&w2,NULL,"[1-1반]" }; // 손전등
TreeNode w3 = { &w3_t1,&explore,2,&w31,&w1,NULL,"[1-2반]" };//1-2반
TreeNode w31 = { &w31_t1,&confirm,0,NULL,&w3,NULL,"[1-2반]" }; // 야채 건빵
TreeNode w4 = { &w4_t1,&fight,2,&w41,&w42,NULL,"[1-3반]" };//1-3반
TreeNode w41 = { &w41_t1,&explore,2,&w43,&w1,NULL,"[1-3반]" };
TreeNode w42 = { &w42_t1,&confirm,0,NULL,&w1,NULL,"[1-3반]" };
TreeNode w43 = { &w43_t1,&confirm,0,NULL,&w41,NULL,"[1-3반]" }; // 몽키 스패너
TreeNode w5 = { &w5_t1,&explore,2 ,&w51,&w1,NULL,"[2-1반]" };//2-1반
TreeNode w51 = { &w51_t1,&confirm,0,NULL,&w5,NULL,"[2-1반]" }; // 터보 라이터
TreeNode w6 = { &w6_t1,&fight,2 ,&w61,&w62,NULL,"[2-2반]" };//2-2반
TreeNode w61 = { &w61_t1,&explore,2 ,&w63,&w1,NULL,"[2-2반]" };
TreeNode w62 = { &w62_t1,&confirm,0,NULL,&w1,NULL,"[2-2반]" };
TreeNode w63 = { &w63_t1,&confirm,0,NULL,&w61,NULL,"[2-2반]" }; // 붕대
TreeNode w7 = { &w7_t1,&explore,2 ,&w71,&w1,NULL,"[2-3반]" };//2-3반
TreeNode w71 = { &w71_t1,&confirm,0,NULL,&w7,NULL,"[2-3반]" }; // 손소독제

//2층 중앙 복도(c)


TreeNode cr = { &cr_t1,&cr_s1,4,&w1,&p1,center,"[2층 중앙 복도]" }; //두 번째 방문부터 중앙복도의 텍스트와 선택지가 바뀜
TreeNode c1 = { &c1_t1,&fight,2,&c2,&c3,NULL,"[2층 중앙 복도]" }; // 첫 번째 방문 중앙복도 노드
TreeNode c2 = { &c2_t1,&confirm,0,&c21,&c22,NULL,"[2층 중앙 복도]" };
TreeNode c21 = { &c21_t1,&c21_s1,4,&w1,&p1,center,"[2층 중앙 복도]" }; //서편으로 갈시 왼쪽 링크, 1층으로 갈시 오른쪽 링크, 옥상으로 갈 시 center[0],동편으로 갈 시 center[1]
TreeNode c22 = { &c22_t1,&confirm,0,&w1,&w1,NULL,"[2층 중앙 복도]" };
TreeNode c3 = { &c3_t1,&c3_s1,2,&w1,&p1,NULL,"[2층 중앙 복도]" };

//2층 동편 루트(e)

TreeNode er = { &er_t1,&e1_s1,4,&e2,&e3,east2,"[2층 동편 복도]" };//동편으로 돌아왔을 때 노드
TreeNode e1 = { &e1_t1,&e1_s1,4,&e2,&e3,east ,"[2층 동편 복도]" };
TreeNode e2 = { &e2_t1,&explore,2,&e21,&e1,NULL,"[화장실]" };//화장실
TreeNode e21 = { &e21_t1,&confirm,0,NULL,&e2,NULL,"[화장실]" };
TreeNode e3 = { &e3_t1,&explore,2,&e31,&e1,NULL,"[세탁실]" };//세탁실
TreeNode e31 = { &e31_t1,&confirm,0,NULL,&e3,NULL,"[세탁실]" };
TreeNode e4 = { &e4_t1,&explore,2,&e41,&e1,NULL,"[행정반]" };//행정반
TreeNode e41 = { &e41_t1,&confirm,0,NULL,&e4,NULL,"[행정반]" };
//격리생활관 루트 (f)

TreeNode f1 = { &f1_t1,&f1_s1,2,&f2,&f3 ,NULL,"[격리 생활관 앞]" }; //간부연구실로 간다 밖으로 나간다
TreeNode f2 = { &f2_t1,&explore,2,&f21,&f1 ,NULL,"[간부연구실]" };//탐색한다 떠난다
TreeNode f3 = { &f3_t1,&confirm, 0, &f31,&f32 ,NULL,"[간부연구실]" };//조건 노드(열쇠가 있는지 없는지)
TreeNode f21 = { &f21_t1,&confirm,0,NULL,&f2,NULL,"[간부연구실]" };//열쇠 발견하는 탐색 노드
TreeNode f31 = { &f31_t1,&confirm,0,&e1,&e1,NULL,"[격리 생활관 앞]" };//열쇠가 있을 시 동편으로 이동하는 단말 노드
TreeNode f32 = { &f32_t1,&confirm,0,&f1,&f1,NULL,"[격리 생활관 앞]" };//열쇠가 없을 시 격리생활관 앞으로 이동하는 단말노드

//헤더 루트
TreeNode* root = &f1;

TreeNode intro_ = { NULL,&intro_s1,2,&intro1,NULL,NULL };
TreeNode intro1 = {&intro_t1,&confirm,0,&intro2,NULL,NULL};
TreeNode intro2 = { &intro_t7,&confirm,0,&intro3,NULL,NULL };
TreeNode intro3 = { &intro_t18,&confirm,0,NULL,NULL,NULL };
TreeNode* it = &intro_;
// 현재 pos.X, posY로 콘솔 위치지정
void gotoxy() {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  // 콘솔 위치지정
}
void print_frame_intro() {
	system("cls");
	Sleep(10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　■■■　　　　■■　　　■　　■　　　■■　　　■　　■　　■■■　　　　　　　■\n");
	printf("■　　　　　　　■　　■　　■　　■　　■　　■　　■　　■　　■■　■　　■　　　　　　　　　■\n");
	printf("■　　　　　　　■　　■　　■■■■　　　■■　　　■　　■　　■　■■　　■■■　　　　　　　■\n");
	printf("■　　　　　　　■　　■　　■　　■　　　■■　　　■　　■　　■　　■　　■　　　　　　　　　■\n");
	printf("■　　　　　　　■■■　　　■　　■　　　■■　　　　■■　　　■　　■　　■■■　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■  　　　　　　　                                                                              ■\n");
	printf("■     　　                                                                                     ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}
void print_frame() {
	system("cls");
	Sleep(10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■  　　　　　　　                                                                              ■\n");
	printf("■     　　                                                                                     ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}
void print_frame_outtro() {
	system("cls");
	Sleep(10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■                                                                                              ■\n");
	printf("■  　　　　　　　                                                                              ■\n");
	printf("■     　　                                                                                     ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}
void print_frame_gameover() {
	system("cls");
	Sleep(10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■   ■■■■　　  ■　　　■　　　　■ ■■■■■    ■■■　 ■　　　■ ■■■■■ ■■■■　 ■\n");
	printf("■ ■　　　　　  ■  ■　　■■ 　 ■■ ■　　　　  ■　　  ■  ■　　■  ■　　　　 ■　　 ■　■\n");
	printf("■ ■　■■■　 ■■■■　 ■　■■　■ ■■■■■  ■　　　■ 　■　■　 ■■■■■ ■■■■　 ■\n");
	printf("■ ■　　　■  ■　　  ■　■　　　　■ ■　　　　  ■　　  ■ 　 ■■　  ■　　　　 ■　　 ■　■\n");
	printf("■ 　■■■　 ■　　　  ■ ■　　　　■ ■■■■■    ■■■　 　　■　   ■■■■■ ■　　　■ ■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　                         　　 　　　　　　■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■  　　　　　　　                                                                              ■\n");
	printf("■           　　                                                                               ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}
void print_console(TreeNode* current) {
	pos.X = 36;
	pos.Y = 10;
	print_frame();
	gotoxy();
	printf("Press Any Key to Continue");
	getchar();
	print_frame();
	pos.X = 4;
	pos.Y = 2;
	for (TextLinkedList* current_text = current->thead; current_text != NULL; current_text = current_text->link) {
		gotoxy();
		printf("%s", current_text->text);
		//getchar();
		pos.Y++;
	}

	pos.Y = SELECTSTARTPOS;
	for (SelectLinkedList* current_select = current->shead; current_select != NULL; current_select = current_select->link) {
		gotoxy();
		printf("  %s", current_select->text);
		pos.Y++;
	}
	keyControlData.limitMinY = SELECTSTARTPOS;
	keyControlData.limitMaxY = SELECTSTARTPOS + current->maxindex - 1;
	pos.Y = SELECTSTARTPOS;

	gotoxy();
	printf(">");
}
void map_print(TreeNode* current) {
	system("cls");
	Sleep(10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　 옥상 　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■　■■■■■■■■■■■■■■■■■■■■　▲▲▲　■■■■■■■■■■■■■■■■■■■■  ■\n");
	printf("■　■　　　　　■　　　　　■　　  　　■　　　　　　　■　　　  　■　　　　  ■　  　　　■　■\n");
	printf("■　■　 1-1　　■　 1-2　　■　 1-3　　■　　　　　　　■　화장실　■　세탁실　■격리생활관■　■\n");
	printf("■　■　　　　　■　　　　　■　　  　　■　　　　　　　■　　　　　■　　　　  ■　　　　　■　■\n");
	printf("■  ■■■■■▲■■■■■▲■■■■■▲■　　　　　　　■▲■■■■■▲■■■■■▲■■■■■  ■\n");
	printf("■　■　　　　　　2층 서편　　　　　　　　 2층 중앙 복도　  　2층 동편　　　칸막이　　　　　■　■\n");
	printf("■　■■■■■▼■■■■■▼■■■■■▼■　　　　　　　■▼■■■■■■■■■■■▼■■■■■  ■\n");
	printf("■　■　　　　　■　　　　　■　　　  　■　　　　　　　■　　  　　　　　  ■　　　　　　　■　■\n");
	printf("■　■　 2-1　　■　 2-2　　■　 2-3  　■　　　　　　  ■ 　2중대 행정반 　■　간부연구실　■　■\n");
	printf("■　■　　　　　■　　　　　■　　　  　■　　　　　　　■  　　　　　　　  ■　　　　　　　■　■\n");
	printf("■  ■■■■■■■■■■■■■■■■■■■■　　　　　■■■■■■■■■■■■■■■■■■■■  ■\n");
	printf("■　■　　　　　　　　　■　　　　  　　■　　　　　　　■　　　  　　　　■　  　　  　　　■　■\n");
	printf("■　■　　총기함실　　　■　　인사과　　■　　　　　　　■　　군수과　　　■　통신물자창고　■　■\n");
	printf("■　■　　　　　　　　　■　　　　  　　■　　　　　　　■　　　　　　　　■　  　　　　　　■　■\n");
	printf("■  ■■■■■■■■■▲■■■■■■■▲■　　　　　　　■▲■■■■■■■■▲■■■■■■■■  ■\n");
	printf("■　■　　　　　　　　　　　　　　　　　　 1층 중앙 복도　  　　　　　　　　　　　　　　　　■　■\n");
	printf("■　■■■■■■■■■■■■■■■■■▼■　　　　　　　■▼■■■■■■■■▼■■■■■■■■  ■\n");
	printf("■　■　　　　　　　　　　　　　　　  　■　　　　　　　■　　  　　　　　■　　　　　　　　■　■\n");
	printf("■　■ 　　　　　지휘 통제실　　　　　　■　　　　　　  ■　주임 원사실 　■　　대대장실　　■　■\n");
	printf("■　■　　　　　　　　　　　　　　　  　■　　　　　　　■  　　　　　　　■　　　　　　　　■　■\n");
	printf("■  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■  ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■                                                                                              ■\n");
	printf("■                                                                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	pos.X = 4;
	pos.Y = 26;
	gotoxy();
	printf("현재 위치 : %s  >[확인]", current->current_pos);

}
// 키보드에서 입력받은 값 반환
int KeyIn(TreeNode* current,ListNode* inventory) {

	int key = _getch(); // 키 입력받기
	if (key == 224) {
		key = _getch();
		switch (key) {
		case 72:
			return UP;
			break;
		case 75:
			return LEFT;
			break;
		case 77:
			return RIGHT;
			break;
		case 80:
			return DOWN;
			break;
		}
	}
	else if (key == ' '|| key == 13) {
		keyControlData.isSubmit = TRUE;
		return READYTOINPUT;
	}
	else if (key == 73 || key == 105) {
		print_frame();
		print_list(inventory);
		getchar();
		print_console(current);
	}
	else if (key == 77 || key == 109) {
		map_print(current);
		getchar();
		print_console(current);
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
	default:
		return keyControlData.key;
	}
}
//인벤토리 연결리스트 함수
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
void use_item(ListNode* current,ListNode* inventory) {
	if (current->data == itemList[2]) {
		pos.Y = SELECTSTARTPOS;
		gotoxy();
		printf("%s를 먹고 기력이 증가했다.", current->data);
		pos.Y++;
		p.energy++;
		inventory = deleted(inventory, getdeleteNode(inventory, current->data));
	}
	else if (current->data == itemList[5]) {
		pos.Y = SELECTSTARTPOS;
		gotoxy();
		printf("%s를 먹고 기력이 증가했다.", current->data);
		pos.Y++;
		p.energy++;
		inventory = deleted(inventory, getdeleteNode(inventory, current->data));
	}
	else if (current->data == itemList[7]) {
		pos.Y = SELECTSTARTPOS;
		gotoxy();
		if (p.hp < 5) {
			printf("%s를 사용했다.", current->data);
			pos.Y++;
			gotoxy();
			printf("체력이 1만큼 회복되었다.");
			p.hp++;
			pos.Y++;
			inventory = deleted(inventory, getdeleteNode(inventory, current->data));
		}
		else {
			printf("나중에 부상을 당했을 때 사용하는 게 좋을 것 같다.");
			pos.Y++;
		}
	}
	else {
		pos.Y = SELECTSTARTPOS;
		gotoxy();
		printf("지금 %s를 사용할 수 없다.", current->data);
		pos.Y++;
	}
	gotoxy();
	printf("[확인]");
}
void print_list(ListNode* head)
{
	ListNode* current;
	ListNode* p;
	int key;
	pos.X = 16;
	pos.Y = 2;
	gotoxy();
	printf("***도움말: 아이템 사용: [enter]       인벤토리 닫기: [Q] + [enter]**");
	pos.X = 10;
	pos.Y = 5;
	gotoxy();
	if (head->prelink == head || head->link == head)
	{

		printf("=================INVENTORY===================");
		pos.Y++;
		pos.Y++;

		gotoxy();
		printf("비어있음");
		pos.Y++;
		pos.Y++;

		gotoxy();
		printf("=============================================");
		return;
	}


	current = head->link;
	p = head->link;
	printf("=================INVENTORY===================");
	pos.Y++;
	pos.Y++;
	do {
		gotoxy();
		if (current == p) {
			printf(">>%s",  p->data);
		}
		else {
			printf("  %s", p->data);
		}
		pos.Y++;
		p = p->link;
	} while (p != head);
	pos.Y++;
	gotoxy();
	printf("=============================================");
	do {

		pos.Y = 6;
		 key = _getch(); // 키 입력받기
		if (key == 224) {
			key = _getch();
			switch (key) {
				case 72:
					current = current->prelink;
					if (current == head) {
					current = current->prelink;
					}
					break;
				case 80:
					current = current->link;
					if (current == head) {
					current = current->link;
					}
					break;
				}			
			}

		do {
			gotoxy();
			if (current == p) {
				printf(">>%s", p->data);
				}
			else {
				printf("  %s", p->data);
				}

			pos.Y++;
			p = p->link;

		} while (p != head);

	 //key = _getch();
	if (key == ' ' || key == 13) {
		use_item(current,head);
		return;
	}
	if (key == 113 || key == 81) {
		pos.Y = SELECTSTARTPOS;
		gotoxy();
		printf("[닫기]");
		return;
	}
} while (1);
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
int searching(ListNode* head, element* data) {       //아이템 있는지 검사
	for (ListNode* p = head->link; p != head; p = p->link) {
		if (!strcmp(p->data, data)) {
			return 1;
		}
	}
	return 0;
}
ListNode* getdeleteNode(ListNode* head, element* data) {
	if (head->link == head || head->prelink == head) {
		printf("비어있습니다.\n");
		return head;
	}
	ListNode* removed = NULL;
	for (ListNode* p = head->link; p != head; p = p->link) {
		if (!strcmp(p->data, data)) {
			removed = p;
			break;
		}
	}
	if (removed == NULL) {
		printf("값을 찾지 못했습니다.\n");
		return head;
	}
	return removed;
}
void init(ListNode* head) {
	head->link = head;
	head->prelink = head;
	head->data = "";
}

int is_condition_node(TreeNode* current_node) { //조건 노드 검사 함수
	if (current_node->maxindex == 0 && (current_node->left != NULL && current_node->right != NULL)) {//선택지가 없고 왼쪽 링크는 NULL이 아닌경우 
		return 1;
	}
	else {
		return 0;
	}
}
int is_leaf_node(TreeNode* current_node) {//단말 노드 검사 함수
	if (current_node->maxindex == 0 && (current_node->left == NULL || current_node->right ==NULL)) {//선택지 없고 왼쪽 링크 비어있으면 단말
		return 1;
	}
	else {
		return 0;
	}
}
int is_fight(TreeNode* pre) {//전투 노드 검사 함수
	if (pre->shead == &fight) {
		return 1;
	}
	return 0;
}
int is_explore(TreeNode* pre) {//탐색 노드 검사 함수
	if (pre->shead == &explore) {
		return 1;
	}
	else
		return 0;
}
void is_east_return(TreeNode* current) {//동편 돌아가기 검사 함수
	if (current == &er) {
		TreeNode* temp = &e1;
		temp->thead = current->thead;
		temp->dptr = east2;
	}
}
int is_gameover(TreeNode* current) {//게임 오버 검사 함수
	return p.hp <0 || current->right== &gameover;
}
int is_game_ending(TreeNode* current) {//게임 엔딩 검사 함수
	if (current->left == &happy1 || current->left == &happy2 || current->left == &bad1 || current->left == &bad2)
		return 1;
	else return 0;
}
int checking_condition(TreeNode* current_node,ListNode* inventory) { 

	if (current_node == &f3) {//격리생활관 칸막이 열쇠 조건
		is_item = searching(inventory, itemList[0]);
		if (is_item) {
			inventory = deleted(inventory, getdeleteNode(inventory,itemList[0])); // 아이템 사용 후 삭제
			return 1; // 조건 참 반환
		}
		else {
			return 0; // 조건 거짓 반환
		}
	}
	else if (current_node == &c2 ) {//중앙복도(첫번째),지휘통제실: 무기가 있으면 참 없으면 거짓
		is_item = searching(inventory, itemList[1]);
		if (is_item) {
			inventory = deleted(inventory, getdeleteNode(inventory, itemList[1]));
			return 1;
		}
		else {
			return 0;
		}
		
	}
	else if (current_node == &p51) {//무기가 있으면 참, 없으면 거짓
		if (searching(inventory, itemList[1]) || searching(inventory, itemList[6]) || searching(inventory, itemList[12]) || searching(inventory, itemList[13])) {
			return 1;
		}
	
		else {
			return 0; // 조건 거짓 반환
		}
	}
	else if (current_node == &p6) {
		is_item = searching(inventory, itemList[11]);
		if (is_item) {//주임 원사실 열쇠 삭제x

			return 1; // 조건 참 반환
		}
		else {
			return 0; // 조건 거짓 반환
		}
	}

	else if (current_node == &p63) {
		is_item = searching(inventory, itemList[15]);
		if (is_item) { //금고 열쇠
			inventory = deleted(inventory, getdeleteNode(inventory, itemList[15]));
			return 1; // 조건 참 반환
		}
		else {
			return 0; // 조건 거짓 반환
		}
	}
	else if (current_node == &p69) {
		p6 = p6_;
		return 1;
	}
	else if (current_node == &p811) {
		is_item = searching(inventory, itemList[10]);
		if (is_item) { //총기함키 삭제 x

			return 1; // 조건 참 반환
		}
		else {
			return 0; // 조건 거짓 반환
		}
	}
	else if (current_node == &r1) {
		is_item = searching(inventory, itemList[3]);
		if (is_item) { // 옥상 열쇠는 사용해도 삭제하지 않음
			return 1; // 조건 참 반환
		}
		else {
			return 0; // 조건 거짓 반환
		}
	}
	else if (current_node == &r3) {
		is_item = searching(inventory, itemList[14]);
		if (is_item) {
			inventory = deleted(inventory, getdeleteNode(inventory, itemList[14])); // 아이템 사용 후 삭제
			return 1; // 조건 참 반환
		}
		else {
			return 0; // 조건 거짓 반환
		}
	}
}
ListNode* checking_inventory(TreeNode* current_node, ListNode* inventory) { 
	if (current_node == &f21) {// 칸막이 열쇠
		is_item = searching(inventory, itemList[0]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[0]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &e21) { //부러진 대걸레
		is_item = searching(inventory, itemList[1]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[1]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &e31) { // 차갑게 식은 냉동 만두
		is_item = searching(inventory, itemList[2]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[2]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &e41) { // 옥상 열쇠
		is_item = searching(inventory, itemList[3]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[3]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &w21) { // 손전등
		is_item = searching(inventory, itemList[4]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[4]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &w31) { // 야채 건빵
		is_item = searching(inventory, itemList[5]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[5]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &w43) { //몽키 스패너
		is_item = searching(inventory, itemList[6]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[6]);
			current_node->thead = &no_item1;
			current_node->right->thead = &no_zombie1;
		}
	}
	else if (current_node == &w51) { // 붕대 
		is_item = searching(inventory, itemList[7]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[7]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &w63) { // 터보 라이터
		is_item = searching(inventory, itemList[8]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[8]);
			current_node->thead = &no_item1;
			current_node->right->thead = &no_zombie1;

		}
	}
	else if (current_node == &w71) { // 손 소독제
		is_item = searching(inventory, itemList[9]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[9]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &p21) { // 총기함 키
		is_item = searching(inventory, itemList[10]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[10]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &p31) { // 금고 열쇠
		is_item = searching(inventory, itemList[15]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[15]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &p53) { //주임원사실 열쇠
		is_item = searching(inventory, itemList[11]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[11]);
			current_node->thead = &no_item1;
			p55.thead = &no_item1;
		}
	}
	else if (current_node == &p55) { //주임원사실 열쇠
		is_item = searching(inventory, itemList[11]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[11]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &p64) { //권총과 탄알집
		is_item = searching(inventory, itemList[12]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[12]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &p71) {//노트북과 연결 포트
		is_item = searching(inventory, itemList[14]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[14]);
			current_node->thead = &no_item1;
		}
	}
	else if (current_node == &p81) { //k2 소총
		is_item = searching(inventory, itemList[13]);
		if (!is_item && current_node->thead != &no_item1) {
			inventory = insert_last(inventory, itemList[13]);
			current_node->thead = &no_item1;
		}
	}
	return inventory;
}
void checking_fight(TreeNode* current_node) {
	if (current_node == &w4) {
		current_node->shead = &explore;
		current_node->thead->link = &no_zombie1;
		current_node->right = &w1;
		current_node->left = &w43;
	}
	else if (current_node == &w6) {
		current_node->shead = &explore;
		current_node->thead->link = &no_zombie1;
		current_node->right = &w1;
		current_node->left = &w63;
	}
	
	else if (current_node == &p5) {
		current_node->shead = &explore;
		current_node->thead->link = &no_zombie1;
		current_node->right = &p1;
		current_node->left = &p55;
	}
}
void checking_fight2(TreeNode* current_node) {
	if (current_node == &w62) {
		p.hp -= 2;
	}
	else if (current_node == &p52) {
		p.hp -= 3;
	}
}
TreeNode* next_node(int y, TreeNode* current_node) {
	switch (y) {
		case SELECTSTARTPOS:
			return current_node->left;
		case SELECTSTARTPOS + 1:
			return current_node->right;
		case SELECTSTARTPOS + 2:
			return current_node->dptr[0];
		case SELECTSTARTPOS + 3:
			return current_node->dptr[1];
		case SELECTSTARTPOS + 4:
			return current_node->dptr[2];
		case SELECTSTARTPOS + 5:
			return current_node->dptr[3];
		case SELECTSTARTPOS + 6:
			return current_node->dptr[4];
		case SELECTSTARTPOS + 7:
			return current_node->dptr[5];
	}
}
void intro(TreeNode* current) {
	print_frame_intro();

	while (current != NULL) {
		pos.X = 4;
		pos.Y = 2;
		if (current !=it ) {
			print_frame();
		}
		for (TextLinkedList* current_text = current->thead; current_text != NULL; current_text = current_text->link) {
			gotoxy();
			printf("%s", current_text->text);
			getchar();
			pos.Y++;
		}

		pos.Y = SELECTSTARTPOS;
		for (SelectLinkedList* current_select = current->shead; current_select != NULL; current_select = current_select->link) {
			gotoxy();
			printf("  %s", current_select->text);
			pos.Y++;
		}
		keyControlData.limitMinY = SELECTSTARTPOS;
		keyControlData.limitMaxY = SELECTSTARTPOS + current->maxindex - 1;
		pos.Y = SELECTSTARTPOS;

		gotoxy();
		printf(">");

		while (!keyControlData.isSubmit) {
			keyControlData.key = KeyIn(current, NULL);
			KeyPrint();
			Sleep(1);
		}
		if (pos.Y == 22) {
			exit(1);
		}
		current = next_node(pos.Y, current);

		keyControlData.isSubmit = FALSE;
	}

}
void outtro(TreeNode* current) {
	print_frame();
	while (current != NULL) {
		pos.X = 4;
		pos.Y = 2;
		if (current->left == NULL) {
			print_frame_outtro();
		}
		for (TextLinkedList* current_text = current->thead; current_text != NULL; current_text = current_text->link) {
			gotoxy();
			printf("%s", current_text->text);
			getchar();
			pos.Y++;
		}
		pos.Y = SELECTSTARTPOS;
		for (SelectLinkedList* current_select = current->shead; current_select != NULL; current_select = current_select->link) {
			gotoxy();
			printf("  %s", current_select->text);
			pos.Y++;
		}
		keyControlData.limitMinY = SELECTSTARTPOS;
		keyControlData.limitMaxY = SELECTSTARTPOS + current->maxindex - 1;
		pos.Y = SELECTSTARTPOS;

		gotoxy();
		printf(">");

		while (!keyControlData.isSubmit) {
			keyControlData.key = KeyIn(current, NULL);
			KeyPrint();
			Sleep(1);
		}
		if (pos.Y == 22) {
			exit(1);
		}
		current = next_node(pos.Y, current);

		keyControlData.isSubmit = FALSE;
	}

}
int main() {
	TreeNode* current = root;
	TreeNode* pre;
	TreeNode* it_ = it;
	ListNode* inventory = (ListNode*)malloc(sizeof(ListNode));


	init(inventory);
	system("mode con cols=100 lines=35"); // mode con:콘솔모드 cols:가로 lines:세로

	intro(it_);

	while (current!=NULL ) {
		// 만약 TreeNode가 Null이라면 while문 종료
		print_console(current);

		while (!keyControlData.isSubmit) {
			keyControlData.key = KeyIn(current,inventory);
			KeyPrint();
			Sleep(1);
		}
		is_exp = is_explore(current);
		is_kill = is_fight(current);


		pre = current;

		inventory = checking_inventory(current, inventory);
		
		current = next_node(pos.Y, current);

		is_ending = is_game_ending(current);
		if (is_ending) {
			outtro(current);
			break;
		}
		is_over = is_gameover(current);
		is_leaf = is_leaf_node(current);
		is_condi = is_condition_node(current);
		is_east_return(current);
		checking_fight2(current);

		if (!is_leaf /*&& !is_condi */&& is_kill) {
			checking_fight(pre);
			is_kill = 0;
		}
		if (is_leaf) {
			print_console(current);
			getchar();
			if (is_exp) {
				inventory = checking_inventory(current, inventory);
				is_exp = 0;
			}
			current = current->right;
			is_leaf = 0;
		}
		if (is_condi) {
			is_true = checking_condition(current, inventory);
			if (is_true) {
				print_console(current);
				getchar();
				current = current->left;
				is_over = is_gameover(current);
				if (is_over) {
					print_console(current);
					getchar();
					break;
				}
				is_true = 0;
			}
			else {
				print_console(current);
				getchar();

				current = current->right;
				is_over = is_gameover(current);
				if (is_over) {
					print_console(current);
					getchar();
					break;
				}
			}
		}

		keyControlData.isSubmit = FALSE;
	}

	if (is_over) {
		print_frame_gameover();
		getchar();
		system("cls");
		return 0;
	}

	return 0;
}
