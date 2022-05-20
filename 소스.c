#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SUBMIT 5
#define READYTOINPUT 6 // 입력을 기다리는 상태

typedef struct {
	int limitMinY; // 홈메뉴 최상단 y값 이 값을 통해 사용자가 맨 위에서 더 이동하려고 하는 상황 해결
	int limitMaxY; // 홈메뉴 최하단 y값 이 값을 통해 사용자가 맨 아래에서 더 이동하려고 하는 상황 해결
	bool isSubmit; // 스페이스바가 눌렸는가
	int key; // 입력받은 키 값
}keyControl;

// 텍스트 연결리스트
typedef struct TextLinkedList {
	char* text;
	struct TextLinkedList* link;
}TextLinkedList;

//선택지 연결리스트
typedef struct SelectLinkedList {
	char* text;
	struct SelectLinkedList* link;
}SelectLinkedList;

//  트리
typedef struct TreeNode {
	struct TextLinkedList* thead;
	struct SelectLinkedList* shead;
	int maxindex;
	struct TreeNode* left, * right;
	struct TreeNode** dptr;		//선택지가 많아서 구조체포인터 배열 주소를 받는 이중포인터
}TreeNode;

//SelectLinkedList s1 = { "1번", 1, NULL, NULL };
TextLinkedList t17 = { "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", NULL };
TextLinkedList t16 = { "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", &t17 };
TextLinkedList t15 = { "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", &t16 };
TextLinkedList t14 = { "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", &t15 };
TextLinkedList t13 = { "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", &t14 };
TextLinkedList t12 = { "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n", &t13 };
TextLinkedList t11 = { "■　　　　　　　　　　　　　　　　　　　　　　　　　　Press any key to continue　　 　　　　　　■\n", &t12 };
TextLinkedList t10 = { "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n", &t11 };
TextLinkedList t9 = { "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n", &t10 };
TextLinkedList t8 = { "■　　　　　　　■■■　　　■　　■　　　■■　　　　■■　　　■　　■　　■■■　　　　　　　■\n", &t9 };
TextLinkedList t7 = { "■　　　　　　　■　　■　　■　　■　　　■■　　　■　　■　　■　　■　　■　　　　　　　　　■\n", &t8 };
TextLinkedList t6 = { "■　　　　　　　■　　■　　■■■■　　　■■　　　■　　■　　■　■■　　■■■　　　　　　　■\n",&t7 };
TextLinkedList t5 = { "■　　　　　　　■　　■　　■　　■　　■　　■　　■　　■　　■■　■　　■　　　　　　　　　■\n",&t6 };
TextLinkedList t4 = { "■　　　　　　　■■■　　　　■■　　　■　　■　　　■■　　　■　　■　　■■■　　　　　　　■\n", &t5 };
TextLinkedList t3 = { "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n", &t4 };
TextLinkedList t2 = { "■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n", &t3 };
TextLinkedList t1 = { "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", &t2 };
//TreeNode b = { &t1, &s1, 1, NULL, NULL };

// 변수 선언
// 전역변수
COORD pos = { 0, 0 }; // X, Y값 구조체
keyControl keyControlData;
keyControl keyControlData = { 0, 0, 0, 0 };

//노드 선언부
//격리 생활관
TreeNode f1;
TreeNode f21;
TreeNode f22;
TreeNode f31;
TreeNode f32;
TreeNode f33;
//동편
TreeNode e1;
TreeNode e21;
TreeNode e22;
TreeNode e31;
TreeNode e32;
TreeNode e33;
TreeNode e41;
TreeNode e42;
TreeNode e43;

//중앙복도
TreeNode c1;
TreeNode c21;
TreeNode c22;
TreeNode c31;
TreeNode c32;
TreeNode c41;
TreeNode c42;

//서편
TreeNode w1;
TreeNode w2;
TreeNode w31;
TreeNode w32;
TreeNode w41;
TreeNode w42;
TreeNode w43;
TreeNode w44;
TreeNode w51;
TreeNode w52;

//1층
TreeNode p1;
TreeNode p2;
TreeNode p31;
TreeNode p32;
TreeNode p41;
TreeNode p42;
TreeNode p43;
TreeNode p44;
TreeNode p51;
TreeNode p52;
TreeNode p53;
TreeNode p54;
TreeNode p61;
TreeNode p62;
TreeNode p63;
TreeNode p71;
TreeNode p72;
TreeNode p81;
TreeNode p91;
TreeNode p92;

//옥상
TreeNode r1;
TreeNode r2;
TreeNode r31;
TreeNode r32;
TreeNode r41;
TreeNode r42;
TreeNode r51;
TreeNode r52;

//선택지 격리생활관
SelectLinkedList f1_s1 = { "[1]간부연구실로 간다",&f1_s2 };
SelectLinkedList f1_s2 = { "[2]칸막이 밖으로 나간다",NULL };
//선택지 동편
SelectLinkedList e1_s1 = { "[1]화장실로 간다",&e1_s2 };
SelectLinkedList e1_s2 = { "[2]세탁실로 간다",&e1_s3 };
SelectLinkedList e1_s3 = { "[3]행정반으로 간다",&e1_s4 };
SelectLinkedList e1_s4 = { "[4]중앙복도로 간다",NULL };
//선택지 중앙복도(처음)
//공용 선택지 fight, run
//선택지 중앙복도(처음x)
SelectLinkedList c1_s1 = { "[1]동편으로 간다",&c1_s2 };
SelectLinkedList c1_s2 = { "[2]서편으로 간다",&c1_s3 };
SelectLinkedList c1_s3 = { "[3]1층으로 간다",&c1_s4 };
SelectLinkedList c1_s4 = { "[4]중앙복도로 간다",NULL };

SelectLinkedList cr_s1 = { "[1]서편으로 이동한다",&cr_s2 };
SelectLinkedList cr_s2 = { "[2]1층으로 이동한다" ,&cr_s3 };
SelectLinkedList cr_s3 = { "[3]옥상으로 이동한다",&cr_s4 };
SelectLinkedList cr_s4 = { "[4]동편으로 이동한다" ,NULL };

SelectLinkedList c2_s1 = { "[1]서편으로 도망간다",&cr_s2 };
SelectLinkedList c2_s2 = { "[2]1층으로 도망간다" ,NULL };

SelectLinkedList c31_s1 = { "[1]서편으로 이동한다",&c31_s2 };
SelectLinkedList c31_s2 = { "[2]1층으로 이동한다" ,&c31_s3 };
SelectLinkedList c31_s3 = { "[3]옥상으로 이동한다",&c31_s4 };
SelectLinkedList c31_s4 = { "[4]동편으로 이동한다" ,NULL };

//선택지 서편
SelectLinkedList w1_s1 = { "[1]1-1반으로 간다",&w1_s2 };
SelectLinkedList w1_s2 = { "[2]1-2반으로 간다",&w1_s3 };
SelectLinkedList w1_s3 = { "[3]1-3반으로 간다",&w1_s4 };
SelectLinkedList w1_s4 = { "[4]2-1반으로 간다",&w1_s5 };
SelectLinkedList w1_s5 = { "[5]2-2반으로 간다",&w1_s6 };
SelectLinkedList w1_s6 = { "[6]2-3반으로 간다",&w1_s7 };
SelectLinkedList w1_s7 = { "[7]중앙복도로 간다",NULL };

//선택지 1층
SelectLinkedList p1_s1 = { "[1]인사과로 간다",&p1_s2 };
SelectLinkedList p1_s2 = { "[2]군수과로 간다",&p1_s3 };
SelectLinkedList p1_s3 = { "[3]대대장실로 간다",&p1_s4 };
SelectLinkedList p1_s4 = { "[4]지휘통제실로 간다",&p1_s5 };
SelectLinkedList p1_s5 = { "[5]주임원사실로 간다",&p1_s6 };
SelectLinkedList p1_s6 = { "[6]통신물자 창고로 간다",&p1_s7 };
SelectLinkedList p1_s7 = { "[7]총기함 실로 간다",&p1_s8 };
SelectLinkedList p1_s8 = { "[8]중앙복도로 간다",NULL };
//선택지 옥상
SelectLinkedList r1_s1 = { "[1]통신망을 개통한다",&r1_s2 };
SelectLinkedList r1_s2 = { "[1]2층 중앙복도로 내려간다",NULL };


//선택지 공통
SelectLinkedList explore = { "1.탐색한다",&leave};
SelectLinkedList leave = { "2.떠난다",NULL };

SelectLinkedList fight = { "1.맞서 싸운다",&run };
SelectLinkedList run = { "2.도망간다",NULL };




//텍스트 격리생활관
TextLinkedList f1_t1 = { "격리생활관에서 나왔다.",&f1_t2 };
TextLinkedList f1_t2 = { "복도 방향으로 칸막이가 막고있다.",&f1_t3 };
TextLinkedList f1_t3 = { "옆에는 간부연구실이 보인다.",NULL };

TextLinkedList f2_t1 = { "간부연구실에 들어왔다.",&f2_t2 };
TextLinkedList f2_t2 = { "코로나 사태 이후로 창고로 사용되는 것 같다.",NULL };

TextLinkedList f3_t1 = { "칸막이 문에 자물쇠가 걸려있는 것 같다.",NULL };

TextLinkedList f21_t1 = { "칸막이 열쇠를 발견했다.",NULL };

TextLinkedList f31_t1 = { "칸막이가 열렸다.",&f31_t2 };
TextLinkedList f31_t2 = { "밖으로 나가자.",NULL };

TextLinkedList f32_t1 = { "칸막이 열쇠가 필요하다.",&f32_t2 };
TextLinkedList f32_t2 = { "열쇠는 주변에서 찾을 수 있을 것 같다.",NULL };

//텍스트 동편
TextLinkedList e1_t1 = { "저 멀리 복도 중앙에 사람 형체들이 보인다.",&e1_t2 };
TextLinkedList e1_t2 = { "역광 때문에 어둡게 보이지만 정상은 아닌 것 같다.",&e1_t3 };
TextLinkedList e1_t3 = { "왼쪽에는 행정반이 보인다.",&e1_t4 };
TextLinkedList e1_t4 = { "오른쪽에는 화장실과 세탁실이 있다.",NULL };

TextLinkedList e2_t1 = { "퀴퀴한 냄새가 진동한다.",&e2_t2 };
TextLinkedList e2_t2 = { "몇일 동안 청소를 못한 모양이다",NULL };

TextLinkedList e21_t1 = { "부러진 대걸레 자루를 발견했다.",&e21_t2 };
TextLinkedList e21_t2 = { "무기로 사용할 수 있을 것 같다.",NULL };

TextLinkedList e3_t1 = { "세탁기 위에 빨랫감이 그대로 쌓여있다.",&e3_t1 };
TextLinkedList e3_t2 = { "창문 밖으로 좀비들이 돌아다니는 모습이 보인다.",NULL };

TextLinkedList e31_t1 = { "차갑게 식은 냉동 만두를 발견했다.",NULL };

TextLinkedList e4_t1 = { "아무 인기척도 느껴지지 않는다.",&e4_t2 };
TextLinkedList e4_t2 = { "어디선가 라디오 소리가 작게 들린다.",&e4_t3 };
TextLinkedList e4_t3 = { "...당국은 내일인 6월 14일부터 대대적인 좀비 사태 대응 포격 감행 결정...",&e4_t4 };
TextLinkedList e4_t4 = { "불길한 예감이 든다...빨리 움직여야 할 것 같다.",NULL };

TextLinkedList e41_t1 = { "열쇠를 발견했다.",&e41_t2 };
TextLinkedList e41_t2 = { "주기가 되어있지만 글씨가 번져서 잘 안보인다.'...상'",NULL };

//텍스트 중앙 복도
TextLinkedList c1_t1 = { "복도 중앙에 좀비 무리가 있다.",&c1_t2 };
TextLinkedList c1_t2 = { "익숙한 얼굴이 보인다..",&c1_t3 };
TextLinkedList c1_t3 = { "설마 ㅅ서..성...윤모..?",&c1_t4 };
TextLinkedList c1_t4 = { "내 알동기 윤모..어쩌다 이렇게...",&c1_t5 };
TextLinkedList c1_t5 = { "하지만 아는 척 할 수는 없을 것 같다.",&c1_t6 };
TextLinkedList c1_t6 = { "저쪽에서 먼저 나의 존재를 알아챈 것 같다.",NULL };

TextLinkedList cr_t1 = { "//2층 중앙 복도//",&cr_t2 };
TextLinkedList cr_t2 = { "좀비는 보이지 않는다.",&cr_t3 };
TextLinkedList cr_t3 = { "일정한 기계음이 조금 더 크게 들린다.",NULL };

TextLinkedList c2_t1 = { "이건 절대 도망치는게 아니다.",&c2_t2 };
TextLinkedList c2_t2 = { "작전상 후퇴일뿐.",&c2_t3 };
TextLinkedList c2_t3 = { "아무튼 아니다.",NULL };

TextLinkedList c3_t1 = { "윤모는 인간이었을 때도 나약했으니 충분히 승산이 있을 것 같다.",NULL };


TextLinkedList c31_t1 = { "윤모야 미안하다..하지만 어쩔 수 없었다.",&c31_t2 };
TextLinkedList c31_t2 = { "부러진 대걸레로 숨통을 끊었다.",&c31_t3 };
TextLinkedList c31_t3 = { "대걸레가 꽂힌 채로 쓰러졌다.",&c31_t4 };
TextLinkedList c31_t4 = { "더 이상 미동이 없다.",&c31_t5 };
TextLinkedList c31_t5 = { "이제 다른 곳으로 이동해야 할 것 같다.",NULL };

TextLinkedList c32_t1 = { "무기 없이는 무리인 것 같다.",&c32_t2 };
TextLinkedList c32_t2 = { "내가 알 던 윤모가 아니다.",&c32_t3 };
TextLinkedList c32_t3 = { "지금이라도 도망가야 할 것 같다.",NULL };

//텍스트 서편
TextLinkedList w1_t1 = { "1소대와 2소대 생활관들이 보인다.",&w1_t2 };
TextLinkedList w1_t2 = { "쓸만한 물건들이 남아 있을지도 모른다.",&w1_t3 };
TextLinkedList w1_t3 = { "어쩌면 다른 생존자가 있을 수도 있을 것 같다.",NULL };

TextLinkedList w2_t1 = { "1 - 1반..복도 제일 끝 생활관이라 그런지 햇볕이 잘 들어오지 않는다.",&w2_t2 };
TextLinkedList w2_t2 = { "벽 군데군데 곰팡이가 피어있다.",NULL };

TextLinkedList w21_t1 = { "[손전등]을 발견했다.",NULL };

TextLinkedList w3_t1 = { "1-2반..항상 물만 묻히고 안씻는 이혜성 상병이 있던 곳이다.",&w3_t2 };
TextLinkedList w3_t2 = { "들어서자마자 꼬랑내 때문에 구역질이 난다.",NULL };

TextLinkedList w31_t1 = { "[건빵 한 봉지]를 발견했다.",NULL };

TextLinkedList w4_t1 = { "1 - 3반..항상 시끄러운 반이었지만 지금은 매우 조용하다.",&w4_t2 };
TextLinkedList w4_t2 = { "이상할 정도로 조용한 것이 좀비가 있는 것 같다.",&w4_t3 };
TextLinkedList w4_t3 = { "좀비가 구석 한켠에 처박혀 앉아 있다.",NULL };

TextLinkedList w41_t1 = { "살...금...살...금...",&w4_t2 };
TextLinkedList w41_t2 = { "푸드드득 우직 꾸엑!",&w4_t3 };
TextLinkedList w41_t3 = { "좀비의 목을 힘껏 비틀어 제껴버렸다.",&w41_t4 };
TextLinkedList w41_t4 = { "사시나무처럼 떨고 있다.",NULL };

TextLinkedList w42_t1 = { "조용히 나가야겠다.",&w42_t2 };
TextLinkedList w42_t2 = { "한이 많이 쌓인 좀비임이 분명하다.",&w42_t3 };
TextLinkedList w42_t3 = { "최대한 소리가 안나게 문을 닫고 나왔다.",NULL };

TextLinkedList w43_t1 = { "[몽키 스패너]를 발견했다.",NULL };

TextLinkedList w5_t1 = { "2 - 1반..기독교 신자가 유난히 많았던 반..",&w5_t2 };
TextLinkedList w5_t2 = { "아무리 둘러봐도 성경과 십자가는 안보인다.",&w5_t3 };
TextLinkedList w5_t3 = { "하느님이 아니라 싸이버거를 굳게 믿었던 것 같다.",NULL };

TextLinkedList w51_t1 = { "꾀병 환자의 [붕대]를 발견했다.",&w51_t2 };
TextLinkedList w51_t2 = { "부상이 생겼을 때 유용하게 사용할 수 있을 것이다.",NULL };


TextLinkedList w6_t1 = { "2-2반이라.....",&w6_t2 };
TextLinkedList w6_t2 = { "끼-----------이이이이이익--------------",&w6_t3 };
TextLinkedList w6_t3 = { "문을 열자마자 숨어있던 좀비가 공격해온다!",NULL };

TextLinkedList w61_t1 = { "잘못하면 목을 내어주고 좀비로 진급할 뻔했다.",&w61_t2 };
TextLinkedList w61_t2 = { "반사신경으로 재빠르게 공격을 피했다.",&w61_t3 };
TextLinkedList w61_t3 = { "좀비가 멍청해서 그대로 벽에 머리를 박고 죽었다.",NULL };

TextLinkedList w62_t1 = { "잘못하면 목을 내어주고 좀비로 진급할 뻔했다.",&w62_t2 };
TextLinkedList w62_t2 = { "바로 문을 닫고 나왔다.",&w62_t3 };
TextLinkedList w62_t3 = { "공격을 피하느라 벽에 몸을 부딛혔다.",&w62_t4 };
TextLinkedList w62_t4 = { "더 이상 쫓아오지는 않는 것 같다.",&w62_t5 };
TextLinkedList w62_t5 = { "경미한 부상을 입었다.",NULL };

TextLinkedList w63_t1 = { "꼴초의 [터보 라이터]를 발견했다.",NULL };

TextLinkedList w7_t1 = { "2-3반..알코올 냄새가 코를 뻥 뚫어주는 것 같다.",&w4_t2 };
TextLinkedList w7_t2 = { "항상 청결한 생활관이다.",&w4_t3 };
TextLinkedList w7_t3 = { "하느님이 아니라 싸이버거를 굳게 믿었던 것 같다.",NULL };

TextLinkedList w71_t1 = { "[손 소독제]를 발견했다.",NULL };

//텍스트 1층

TextLinkedList p1_t1 = { "곳곳에 혈흔 자국들이 보인다.",&p1_t2 };
TextLinkedList p1_t2 = { "아까부터 계속 미세한 기계음이 반복적으로 들린다..",&p1_t3 };
TextLinkedList p1_t3 = { "그 외에는 침묵이 가득하다." ,NULL };

TextLinkedList p2_t1 = { "인사과장이 1년 동안 결산하지 않은 부대 체육 리그 점수표가 정면에 보인다.",&p2_t2 };
TextLinkedList p2_t2 = { "한켠에는 아직 개봉되지 않은 택배 상자들이 쌓여있다.",&p2_t3 };
TextLinkedList p2_t3 = { "어딘가에 총기함키가 있을 것이다." ,NULL };

TextLinkedList p21_t1 = { "[총기함키]를 발견했다." ,NULL };

TextLinkedList p3_t1 = { "대대장의 총애를 받던 군수과장이 있던 곳이다.",&p3_t2 };
TextLinkedList p3_t2 = { "지독한 사람이었다.",&p3_t3 };
TextLinkedList p3_t3 = { "책상 위에 군수과장 아들내미 사진이 보인다." ,&p3_t4 };
TextLinkedList p3_t4 = { "옆에는 달력이 있다." ,&p3_t5 };
TextLinkedList p3_t5 = { "[6월 24일,대대장님 생신★]" ,NULL };

TextLinkedList p31_t1 = { "쓸 만한 물건이 없는 것 같다." ,NULL };

TextLinkedList p4_t1 = { "문이 잠겨있다....[부재중]..." ,NULL };

TextLinkedList p5_t1 = { "항상 간부들이 북적거리던 곳이다.",&p5_t2 };
TextLinkedList p5_t2 = { "CCTV 감시 화면 곳곳에 좀비들 모습이 보인다..",&p5_t3 };
TextLinkedList p5_t3 = { "옥상에는 좀비가 없는 것 같다." ,&p5_t4 };
TextLinkedList p5_t4 = { "그런데... 뭔가 이상하다." ,&p5_t5 };
TextLinkedList p5_t5 = { "내가 보이는 화면에 이상한 형체가 같이 있다." ,&p5_t6 };
TextLinkedList p5_t6 = { "쿠당탕!" ,&p5_t7 };
TextLinkedList p5_t7 = { "갑자기 뒤에서 좀비 한 마리가 달려든다." ,NULL };

TextLinkedList p51_t1 = { "좀비가 매우 강력하다." ,&p51_t2 };
TextLinkedList p51_t2 = { "간신히 제압했다." ,&p51_t3 };
TextLinkedList p51_t3 = { "하마터면 엔딩도 보기전에 죽을 뻔했다." ,&p51_t4 };
TextLinkedList p51_t4 = { "머리가 조금 찢어진 것 같다." ,&p51_t5 };
TextLinkedList p51_t5 = { "큰 부상을 입었다." ,NULL };

TextLinkedList p52_t1 = { "맨손으로는 무리인 것 같다." ,&p52_t2 };
TextLinkedList p52_t2 = { "자세히 보니 주임원사님의 얼굴을 꼭 빼닮은 것 같다." ,&p52_t3 };
TextLinkedList p52_t3 = { "지금이라도 도망쳐야 할 것 같다." ,&p52_t4 };
TextLinkedList p52_t4 = { "어라..?점점 의식이 흐려진다." ,&p52_t5 };
TextLinkedList p52_t5 = { "게임오버" ,NULL };

TextLinkedList p53_t1 = { "좀비가 입고있던 전투복에서 [열쇠]를 발견했다." ,&p53_t2 };
TextLinkedList p53_t2 = { "무슨 열쇠인지는 모르겠다." ,NULL };

TextLinkedList p6_t1 = { "주임 원사실...[부재중]..." ,NULL };

TextLinkedList p61_t1 = { "철컥 철컥 문이 잠겨있다." ,&p61_t2 };
TextLinkedList p61_t2 = { "좀비에게서 얻은 열쇠로 문이 열렸다." ,&p61_t3 };
TextLinkedList p61_t3 = { "안으로 들어갈 수록 커피 원두향이 진하게 난다." ,&p61_t4 };
TextLinkedList p61_t4 = { "잡다한 용접 도구들이 눈에 띈다.",NULL };

TextLinkedList p62_t1 = { "철컥 철컥 문이 잠겨있다." ,&p62_t2 };
TextLinkedList p62_t2 = { "열쇠가 필요하다." ,NULL };

TextLinkedList p63_t1 = { "금고가 보인다." ,&p63_t2 };
TextLinkedList p63_t2 = { "하지만 비밀번호로 잠겨있다." ,&p63_t3 };
TextLinkedList p63_t3 = { "비밀번호 입력: [_][_][_][_]" ,NULL };

TextLinkedList p64_t1 = { "띠-띠-띠로리--" ,&p64_t2 };
TextLinkedList p64_t2 = { "금고가 열렸다!!!" , &p64_t3 };
TextLinkedList p64_t3 = { "중요해보이는 기밀 문서들이 잔뜩 있다." ,&p64_t4 };
TextLinkedList p64_t4 = { "[권총]과 [비상용 탄 8발]을 발견했다." ,NULL };

TextLinkedList p65_t1 = { "삐-비-익" ,&p65_t2 };
TextLinkedList p65_t2 = { "이 비밀번호가 아닌 것 같다.." ,NULL };

TextLinkedList p67_t1 = { "삐--용--삐--용--삐--용--삐--용-- " ,&p67_t2 };
TextLinkedList p67_t2 = { "!!!갑자기 비상벨이 울린다." ,&p67_t3 };
TextLinkedList p67_t3 = { "좀비들이 몰려오는 소리가 들린다." ,NULL };

TextLinkedList p68_t1 = { "빨리 도망치거나 숨어야 할 것 같다." ,NULL };

TextLinkedList p69_t1 = { "일단 락커에 몸을 숨겼다." ,&p67_t2 };
TextLinkedList p69_t2 = { "좀비들의 발소리가 점점 가까워진다." ,&p67_t3 };
TextLinkedList p69_t3 = { "숨을 참아도 심장 소리는 더 커지는 것 같다...." ,&p69_t4 };
TextLinkedList p69_t4 = { "쿵쾅쿵쾅쿵쾅쿵쾅쿵쾅쿵쿵쾅쾅...." ,&p69_t5 };
TextLinkedList p69_t5 = { "쿵쾅..쿵쾅..쿵..쿵..쿵...쾅...쾅...." ,&p69_t6 };
TextLinkedList p69_t6 = { "쿵...쾅...쿵...쾅...쿵.........." ,&p69_t7 };
TextLinkedList p69_t7 = { "휴 다행히 좀비 소리가 다시 멀어졌다." ,NULL };

TextLinkedList p610_t1 = { "황급히 주임원사실 밖으로 뛰쳐나왔다." ,&p610_t2 };
TextLinkedList p610_t2 = { "하지만 이미 늦었다.." ,&p610_t3 };
TextLinkedList p610_t3 = { "좀비들이 나의 앞을 가로막고 있다." ,&p610_t4 };
TextLinkedList p610_t4 = { "으드득으드득..으드득으드득....." ,&p610_t5 };
TextLinkedList p610_t5 = { "나는 목부터 발까지 뜯겨나갔다." ,NULL };


TextLinkedList p7_t1 = { "먼지로 뒤덮여 있어서 공기가 매캐하다." ,&p7_t2 };
TextLinkedList p7_t2 = { "통신망 개통에 필요한 유지 장비들이 있다." ,&p7_t3 };
TextLinkedList p7_t3 = { "옥상에 있는 통신 장비와 연결할 수 있다." ,&p7_t4 };
TextLinkedList p7_t4 = { "외부와 연락하기 위해서 필요한 장비들을 가져가야 할 것 같다." ,NULL };

TextLinkedList p71_t1 = { "[노트북]과 [연결 포트]를 발견했다." ,&p71_t2 };
TextLinkedList p71_t2 = { "망개통에 필요한 물품은 다 챙긴 것 같다." ,NULL };

TextLinkedList p8_t1 = { "총기함실이다." ,&p8_t2 };
TextLinkedList p8_t2 = { "WD냄새와 쇳덩이 냄새들이 난다." ,&p8_t3 };
TextLinkedList p8_t3 = { "총기함은 굳게 잠겨있다." ,NULL };

TextLinkedList p81_t1 = { "총기함 열쇠로 문을 열었다." ,&p81_t2 };
TextLinkedList p81_t2 = { "훈련 때문에 탄약은 없는 것 같다." ,&p81_t3 };
TextLinkedList p81_t3 = { "[K2 소총]을 얻었다." ,NULL };

TextLinkedList p82_t1 = { "총기함이 잠겨있다." ,&p82_t2 };
TextLinkedList p82_t2 = { "총기함키가 필요하다." ,&p82_t3 };
TextLinkedList p82_t3 = { "인사과에 가면 있을 것이다." ,NULL };

//선택지의 수에 따라 링크를 저장한 구조체포인터 배열 생성

TreeNode* pre[7] = { &p2,&p3,&p4,&p5,&p6,&p7,&p8 };//인사과~총기함실
TreeNode* west[6] = { &w2,&w3,&w4,&w5,&w6,&w7 };//1-1~2-3반
TreeNode* center[2] = { &r1,&e1 };//옥상과 동편 주소는 따로 저장
TreeNode* east[3] = { &e3,&e4,&cr };//세탁실,행정반,중앙복도(첫번째x)

//해피엔딩, 배드 엔딩, 게임오버 일단 오류 피하기 위해서 만들어놓음
TreeNode happy = { "어느정도 시간이 흐른 것 같다. 반복적인 기계음에 어디선가 저 멀리서부터 낯선 소음 하나가 간섭을 이룬다. 낯선 소리가 기계음을 압도하며 다가온다. 산자락 너머로 구조헬기가 보인다. 살았다.",NULL,NULL };
TreeNode bad = { "어느정도 시간이 흐른 것 같다.반복적인 기계음에 어디선가 저 멀리서부터 낯선 소음 하나가 간섭을 이룬다. 낯선 소리가 기계음을 압도하며 다가온다. 다수의 헬기가 보인다. 갑자기 굉음과 함께 엄청난 섬광이 눈을 태운다. 진공의 정적만 흐르고 있다. 작은 미사일 하나로 내 발밑에 있는 모든 것을 날려버리기 충분했다.",NULL,NULL };
TreeNode gameover = { "게임오버",NULL,NULL };

//옥상 루트(r)
TreeNode r1 = { "옥상 문이 닫혀있다. '관계자 외 출입 금지' 철컥, 철컥, 열쇠가 필요할 것 같다.",&r2,&c1 };
TreeNode r2 = { "옥상에 설치된 안테나 통신 장치들이 반복적인 기계음을 내고 있다. 다행히 통신 장비가 작동중인 것 같다. 통신망만 개통하면 외부와 연락이 가능할 것이다.",&r31,&r32 };
TreeNode r31 = { " ...이더넷 연결중...국방망 연결중..통신망이 연결 되었다! 신호가 잡힌 것 같다..빨리 구조 요청을 해야한다.",&r41,&r42 };
TreeNode r32 = { "역시 통신망 연결이 끊겨있다. 통신망 개통을 위한 [노트북]과 [연결 포트]는 1층 [통신물자 창고]에 있을 것이다.",NULL,&c1 };
TreeNode r41 = { "신호가 끊겼다.통신 장비 노드가 노후되어 연결이 불안정한 것 같다. 더 이상 신호가 잡히지 않는다.",&happy,&r51 };
TreeNode r42 = { "신호가 끊겼다.통신 장비 노드가 노후되어 연결이 불안정한 것 같다. 더 이상 신호가 잡히지 않는다.",&bad,&r52 };
TreeNode r51 = { "신호가 끊겼다.통신 장비 노드가 노후되어 연결이 불안정한 것 같다. 더 이상 신호가 잡히지 않는다.",&happy,NULL };
TreeNode r52 = { "신호가 끊겼다.통신 장비 노드가 노후되어 연결이 불안정한 것 같다. 더 이상 신호가 잡히지 않는다.",&bad,NULL };
//1층 루트(p)

SelectLinkedList p68_s1 = { "[1]숨는다",&p68_s2 };
SelectLinkedList p68_s2 = { "[2]도망친다",NULL };

TreeNode p1 = { &p1_t1,&p1_s1,8,NULL,&cr,pre };//1층 로비
TreeNode p2 = { &p2_t1,&explore,2,&p21,&p1,NULL };//인사과
TreeNode p21 = { &p21_t1,NULL,0,NULL,&p1,NULL };
TreeNode p3 = { &p3_t1,&explore,2,&p31,&p1,NULL };//군수과
TreeNode p31 = { &p31_t1,NULL,0,NULL,&p1,NULL };
TreeNode p4 = { &p4_t1,NULL,0,NULL,&p1,NULL };//대대장실
TreeNode p5 = { &p5_t1,&fight,2,&p51,&p52, NULL };//지휘통제실
TreeNode p51 = { &p51_t1,&explore,2,&p53,&p1, NULL };
TreeNode p52 = { &p52_t1,NULL,0,NULL,&gameover, NULL };
TreeNode p53 = { &p53_t1,NULL,0,NULL,&p1, NULL };
TreeNode p6 = { &p6_t1,NULL,0,&p61,&p62,NULL };//주임원사실
TreeNode p61 = { &p61_t1,&explore,2,&p63,&p1,NULL };
TreeNode p62 = { &p62_t1,NULL,0,NULL,&p1,NULL };
TreeNode p63 = { &p63_t1,NULL,0,&p64,&p65,NULL };
TreeNode p64 = { &p64_t1,NULL,0,NULL,&p1,NULL };
TreeNode p65 = { &p65_t1,NULL,0,&p64,&p66,NULL };
TreeNode p66 = { &p65_t1,NULL,0,&p64,&p67,NULL };
TreeNode p67 = { &p67_t1,NULL,0,&p64,&p68,NULL };
TreeNode p68 = { &p68_t1,&p68_s1,2,&p69,&p610,NULL };
TreeNode p69 = { &p69_t1,&explore,2,&p63,&p1,NULL };
TreeNode p610 = { &p610_t1,NULL,0,NULL,&gameover,NULL };
TreeNode p7 = {&p7_t1,&explore,2,&p71,&p1,NULL };//통신물자창고
TreeNode p71= { &p71_t1,NULL,0,NULL,&p1,NULL };
TreeNode p8 = { &p8_t1,&explore,2,&p81,&p82,NULL };//총기함실
TreeNode p81 = { &p81_t1,NULL,0,NULL,&p1,NULL };
TreeNode p82 = { &p82_t1,NULL,0,NULL,&p1,NULL };

//2층 서편 루트(w)
 
TreeNode w1 = {&w1_t1,&w1_s1,7 ,NULL,&cr,west};//서편 로비
TreeNode w2 = { &w2_t1,&explore,2,&w21,&w1,NULL };//1-1반
TreeNode w21 = { &w21_t1,NULL,0,NULL,&w1,NULL };
TreeNode w3 = { &w3_t1,&explore,2,&w31,&w1,NULL };//1-2반
TreeNode w31 = { &w31_t1,NULL,0,NULL,&w1,NULL };
TreeNode w4 = { &w4_t1,&fight,2,&w41,&w42,NULL };//1-3반
TreeNode w41 = { &w41_t1,&explore,2,&w43,&w1,NULL };
TreeNode w42 = { &w42_t1,NULL,0,NULL,&w1,NULL };
TreeNode w43 = { &w43_t1,NULL,0,NULL,&w1,NULL };
TreeNode w5 = {&w5_t1,&explore,2 ,&w51,&w1,NULL };//2-1반
TreeNode w51 = { &w51_t1,NULL,0,NULL,&w1,NULL };
TreeNode w6 = { &w6_t1,&fight,2 ,&w61,&w1,NULL };//2-2반
TreeNode w61 = { &w61_t1,&explore,2 ,NULL,&w1,NULL };
TreeNode w62 = { &w62_t1,NULL,0,NULL,&w1,NULL };
TreeNode w63 = { &w63_t1,NULL,0,NULL,&w1,NULL };
TreeNode w7 = {&w7_t1,&explore,2 ,&w71,&w1,NULL };//2-3반
TreeNode w71 = { &w71_t1,NULL,0,NULL,&w1,NULL };

//2층 중앙 복도(c)

TreeNode cr = { &cr_t1,&cr_s1,3,NULL,NULL,center }; //두 번째 방문부터 중앙복도의 텍스트와 선택지가 바뀜
TreeNode c1 = { &c1_t1,&fight,2,&c2,&c3,NULL }; // 첫 번째 방문 중앙복도 노드
TreeNode c2 = { &c2_t1,&c2_s1,2,&w1,&p1,NULL };
TreeNode c3 = { &c3_t1,NULL,0,&c31,&c32,NULL };
TreeNode c31 = { &c31_t1,&c31_s1,4,&w1,&p1,center }; //서편으로 갈시 왼쪽 링크, 1층으로 갈시 오른쪽 링크, 옥상으로 갈 시 center[0],동편으로 갈 시 center[1]
TreeNode c32 = { &c32_t1,NULL,0,NULL,&w1,NULL };

//2층 동편 루트(e)


TreeNode e1 = { &e1_t1,&e1_s1,4,&e2,&c1,east};//화장실로 간다 왼쪽 링크, 중앙복도(첫번째)로 간다 오른쪽 링크,
//세탁실로 간다 east[0],행정반으로 간다 east[1],중앙복도(첫번째x)로 간다 east[2]
TreeNode e2 = { &e2_t1,&explore,2,&e21,&e1,NULL };//화장실
TreeNode e21 = { &e21_t1,NULL,0,NULL,&e2,NULL };
TreeNode e3 = { &e3_t1,&explore,2,&e31,&e1,NULL };//세탁실
TreeNode e31 = { &e31_t1,NULL,0,NULL,&e3,NULL };
TreeNode e4 = {&e4_t1,&explore,2,&e41,&e1,NULL };//행정반
TreeNode e41 = { &e41_t1,NULL,0,NULL,&e4,NULL };
//격리생활관 루트 (f)

TreeNode f1 = { &f1_t1,&f1_s1,2,&f2,&f3 ,NULL};
TreeNode f2 = { &f2_t1,&explore,2,&f21,&f1 ,NULL};
TreeNode f3 = { &f3_t1,NULL, 0, &f32,&f33 ,NULL};
TreeNode f21 = { &f21_t1,NULL,0,NULL,&f1,NULL };
TreeNode f31 = { &f31_t1,NULL,0,&e1,NULL,NULL };
TreeNode f32 = { &f32_t1,NULL,0,NULL,&f1,NULL };

//헤더 루트
TreeNode* root = &f1;
TreeNode* preroot;

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
	default:
		return keyControlData.key;
	}
}

int GameController() {

}

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
		GameController();
	}
	else if (pos.Y == 1) { // Quit인 경우 게임 종료
		return 0;
	}
}

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

void print_console() {
	for (TextLinkedList* p = b.thead; p != NULL; p = p->link) {
		printf("%s", p->text);
	}
}
int main() {

	system("mode con cols=100 lines=30"); // mode con:콘솔모드 cols:가로 lines:세로
	Intro();
	Home();

	print_console();
	return 0;
}
