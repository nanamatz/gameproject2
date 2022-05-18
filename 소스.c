#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
	char* text;
	struct TreeNode* left, * right;
}TreeNode;

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
TreeNode p1 = { "곳곳에 혈흔 자국들이 보인다. 아까부터 계속 미세한 기계음이 반복적으로 들린다. 그 외에는 침묵이 가득하다.",&p2,&c1 };
TreeNode p2 = { "문이 잠겨있다....[부재중]... ",&p31,&p32 };
TreeNode p31 = { "통신망 개통에 필요한 유지 장비들이 있다. 옥상에 있는 통신 장비와 연결할 수 있다. 노트북과 연결 포트를 발견했다.",&p41,&p42 };
TreeNode p32 = { "대대장의 총애를 받던 군수과장이 있던 곳이다. 팀장을 노리는 엘리트 부장같은 사람이었다. 책상 위에 군수과장 아들내미 사진이 보인다.옆에는 달력이 있다.[6월 24일,대대장님 생신★]",&p43,&p44 };
TreeNode p41 = { "주임원사실...",&p51,&p52 };
TreeNode p42 = { "인사과장이 1년 동안 결산하지 않은 부대 체육 리그 점수표가 정면에 보인다.한켠에는 아직 개봉되지 않은 택배 상자들이 쌓여있다.총기함키를 발견했다. ",NULL,&p1 };
TreeNode p43 = { "항상 간부들이 북적거리던 곳이다. CCTV 감시 화면 곳곳에 좀비들 모습이 보인다. 옥상에는 좀비가 없는 것 같다. 우당탕! 갑자기 뒤에서 좀비 한 마리가 달려든다.",&p53,&p1 };
TreeNode p44 = { "총기함실이다. WD냄새와 쇳덩이 냄새들이 난다. 총기함은 굳게 잠겨있다.",&p54,&p1 };
TreeNode p51 = { "좀비에게서 얻은 열쇠로 문이 열렸다. 안으로 들어갈 수록 커피 원두향이 진하게 난다. 잡다한 용접 도구들이 눈에 띈다.",&p61,&p1 };
TreeNode p52 = { "문이 잠겨있다. 열쇠가 필요하다.",NULL,&p1 };
TreeNode p53 = { "좀 강력해 보이는 좀비다.", &p62,&p63 };
TreeNode p54 = { "훈련 때문에 탄약은 없는 것 같다. 총기 한 자루를 얻었다.",NULL,&p1 };
TreeNode p61 = { "금고가 보인다.하지만 비밀번호로 잠겨있다.비밀번호:(_,_,_,_)",&p71,&p72 };
TreeNode p62 = { "좀비가 입고있던 전투복에서 열쇠를 얻었다. 무슨 열쇠인지는 모르겠다.",NULL,&p1 };
TreeNode p63 = { "맨손으로는 무리였다. 자세히 보니 주임원사님의 얼굴을 꼭 빼닮은 것 같다. 의식이 흐려진다. 게임오버",NULL,&gameover };//게임오버
TreeNode p71 = { "금고가 열렸다!!!중요해보이는 문서들이 있다.권총과 비상용 탄 8발을 발견했다.",NULL,&p1 };
TreeNode p72 = { "삐-비-익 이 비밀번호가 아닌 것 같다..",&p81,&p61 };
TreeNode p81 = { "삐--용--삐--용--삐--용--삐--용-- 갑자기 비상벨이 울린다. 좀비들이 몰려오는 소리가 들린다.",&p91,&p92 };
TreeNode p91 = { "일단 락커에 몸을 숨겼다. 좀비들의 발소리가 점점 가까워진다. 숨을 참아도 심장 소리는 더 커지는 것 같다....휴 다행히 좀비 소리가 다시 멀어졌다.",NULL,&p51 };
TreeNode p92 = { "황급히 주임원사실 밖으로 뛰쳐나왔다. 하지만 이미 늦었다. 좀비들이 나의 앞을 가로막고 있었다. 으드득으드득 나는 목부터 발까지 뜯겨나갔다.",NULL,&gameover };//게임오버로 가야함

//2층 서편 루트(w)
TreeNode w1 = { "1소대와 2소대 생활관들이 보인다. 쓸만한 물건들이 남아 있을지도 모른다. 어쩌면 다른 생존자가 있을 수도 있을 것 같다.",&w2,&c1 };
TreeNode w2 = { "",&w31,&w32 };
TreeNode w31 = { "1-1반..복도 제일 끝 생활관이라 그런지 햇볕이 잘 들어오지 않는다. 벽 군데군데 곰팡이가 피어있다. 손전등을 발견했다.",&w41,&w42 };
TreeNode w32 = { "2-1반..기독교 신자가 유난히 많았던 2-1반..아무리 찾아도 성경과 십자가는 안보인다. 싸이버거를 굳게 믿었던 것 같다.",&w43,&w44 };
TreeNode w41 = { "1-2반..항상 물만 묻히고 안씻는 이혜성 상병이 있던 곳이다. 들어서자마자 꼬랑내 때문에 구역질이 난다.",NULL,&w1 };
TreeNode w42 = { "1-3반..항상 시끄러운 반이었지만 지금은 매우 조용하다. 이상할 정도로 조용한 것이 좀비가 있는 것 같다. 좀비가 구석 한켠에 처박혀 앉아 있다. ",&w51,&w1 };
TreeNode w43 = { "2-2반이라..문을 열자마자 숨어있던 좀비가 공격해온다.",&w52,&w1 };
TreeNode w44 = { "2-3반..알코올 냄새가 코를 찌른다. 항상 청결한 생활관이다. 손 소독제를 발견했다.",NULL,&w1 };
TreeNode w51 = { "잘못하면 목을 내어주고 좀비로 진급할 뻔했다. 좀비 목을 꺾어버렸다. 꾀병 부리던 병사의 붕대를 발견했다.",NULL,&w1 };
TreeNode w52 = { "좀비를 처리하는 과정에서 경미한 부상을 입었다. 다행히 출혈은 없는 것 같다. 꼴초의 터보 라이터를 발견했다.",NULL,&w1 };

//2층 중앙 복도(c)
TreeNode c1 = { "복도 중앙에 좀비 무리가 있다. 익숙한 얼굴이 보인다. 내 알동기 윤모..어쩌다 이렇게...하지만 아는 척 할 수는 없을 것 같다.저쪽에서 먼저 나의 존재를 알아챈 것 같다.",&c21,&c22 };
TreeNode c21 = { "이건 도망치는게 아니다. 작전상 후퇴일뿐.",&c31,&e1 };
TreeNode c22 = { "윤모는 인간이었을 때도 나약했으니 충분히 승산이 있을 것 같다.",&c32,&w1 };
TreeNode c31 = { "어디로 도망갈까?",&w1,&p1 };
TreeNode c32 = { "윤모야 미안하다..하지만 어쩔 수 없었다. 부러진 대걸레로 숨통을 끊었다. 대걸레가 꽂힌 채로 쓰러졌다. 더 이상 미동이 없다. 이제 다른 곳으로 이동해야 할 것 같다.",&c41,&c42 };
TreeNode c41 = { "어디로 이동할까?",&w1,&e1 };
TreeNode c42 = { "어디로 이동할까?",&p1,&r1 };

//2층 동편 루트(e)
TreeNode e1 = { "저 멀리 복도 중앙에 사람 형체들이 보인다. 역광 때문에 어둡게 보이지만 정상은 아닌 것 같다. 왼쪽에는 행정반이 보인다. 오른쪽에는 화장실과 세탁실이 있다.",&e21, &e22 };
TreeNode e21 = { "어디로 갈까?",&e31,&e32 };
TreeNode e22 = { " 어디로 갈까?",&e33,&c1 };
TreeNode e31 = { "퀴퀴한 냄새가 진동한다. 몇일 동안 청소를 못한 모양이다.",&e41,&e1 };
TreeNode e32 = { "세탁기 위에 빨랫감이 그대로 쌓여있다. 창문 밖으로 좀비들이 돌아다니는 모습이 보인다.",&e42,&e1 };
TreeNode e33 = { "아무 인기척도 느껴지지 않는다. 어디선가 라디오 소리가 작게 들린다. '...당국은 내일인 6월 14일부터 대대적인 좀비 사태 대응 포격 감행 결정...",&e43,&e1 };
TreeNode e41 = { "부러진 대걸레 자루를 발견했다. 무기로 사용할 수 있을 것 같다.",NULL,&e1 };
TreeNode e42 = { "차갑게 식은 냉동 만두를 발견했다.",NULL,&e1 };
TreeNode e43 = { "열쇠를 발견했다. 주기가 되어있지만 글씨가 번져서 잘 안보인다.'...상'",NULL,&e1 };
//격리생활관 루트 (f)
TreeNode f1 = { "격리생활관에서 나왔다. 앞에는 칸막이가 막고있다. 옆에는 간부연구실이 보인다.",&f21,&f22 };
TreeNode f21 = { "간부연구실에 들어왔다. 코로나 사태 이후로 창고로 사용되는 것 같다.",&f31,&f1 };
TreeNode f22 = { "칸막이 문에 자물쇠가 걸려있는 것 같다.",&f32,&f33 };
TreeNode f31 = { "칸막이 열쇠를 발견했다.",NULL,&f21 };
TreeNode f32 = { "칸막이가 열렸다. 밖으로 나가자",&e1,NULL };
TreeNode f33 = { "열쇠가 필요하다. 열쇠는 주변에서 찾을 수 있을 것 같다.",NULL,&f1 };
//헤더 루트
TreeNode* root = &f1;
TreeNode* preroot;
int main(void) {
	char temp;
	do {

		printf("%s", root->text);
		temp = getchar();
		switch (temp) {
		case '1':
			preroot = root;
			root = root->left;
			break;
		case '2':
			preroot = root;
			root = root->right;
			break;
		}
		if (root == NULL) {
			root = preroot->right;
		}
	} while (1);
	
	return 0;
}