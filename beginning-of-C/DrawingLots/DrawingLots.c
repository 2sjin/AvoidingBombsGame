#include <stdio.h>
#include <time.h> 
#include <windows.h> 

void print_item(int select);
int check_collection();

// 5종류의 카트바디가 있다
// 아무 키나 눌러서 랜덤으로 카드바디를 뽑아 5종류 모두 수집하기!
// 중복 발생 가능!

// 카트바디 정보 : 이름, 시즌, 소개, 등급 	
struct KARTBODY {
	char* name; // 이름 
	int age; // 시즌 
	char* character; // 소개 
	int level;	 // 등급 
};

// 전체 카트바디 리스트 생성 
struct KARTBODY item[5];

// 현재까지 보유한 카트바디 
int collection[5] = { 0, 0, 0, 0, 0 };        // 0 - 미보유, 1 - 보유 

// 카드바디 뽑기 횟수 
int count = 0;

int main() {
	srand(time(NULL));

	// ================== 카트바디 정보 입력 ===================

	item[0].name = "백기사";
	item[0].age = 3;
	item[0].character = "빛을 따라가는 최고의 스피드";
	item[0].level = 1;

	item[1].name = "카오스";
	item[1].age = 4;
	item[1].character = "혼돈의 지배자";
	item[1].level = 2;

	item[2].name = "흑기사";
	item[2].age = 5;
	item[2].character = "쾌걸 네오 밤의 군주";
	item[2].level = 3;

	item[3].name = "파라곤";
	item[3].age = 7;
	item[3].character = "새로운 강자의 등장! 트랙을 지배하라";
	item[3].level = 4;

	item[4].name = "멘티스";
	item[4].age = 8;
	item[4].character = "무결점의 퍼포먼스를 경험하라";
	item[4].level = 5;

	item[-1].name = "";
	item[-1].age = -1;
	item[-1].character = "";
	item[-1].level = -1;

	// =======================================================


	// 게임 시작 
	print_item(-1);
	int collect_all = check_collection(0);

	while (1) {
		printf("두근두근~! 어느 카트바디가 나올까요?\n[Enter] 키를 눌러서 확인하세요!");
		getchar();
		system("cls");

		int select = rand() % 5; // 0~4 사이의 숫자 반환
		print_item(select); // 카트바디 정보 출력 
		collection[select] = 1; // 카트바디 뽑은 상태로 처리 
		count++;

		int collect_all = check_collection();
		if (collect_all == 1) {
			break;
		}

	}


	return 0;
}


void print_item(int select) {
	printf("\n\n ===============================================================================\n\n");

	printf(" ■ 카트바디 획득 정보 \n\n");
	printf("   - 이름 : %s\n", item[select].name);

	printf("   - 번호 : ");
	if (item[select].age != -1)
		printf("%03d", item[select].age);
	printf("\n");

	printf("   - 소개 : %s\n", item[select].character);

	printf("   - 등급 : ");
	for (int i = 0; i < item[select].level; i++) {
		printf("%s", "★");
	}
}

int check_collection() {
	// 1. 현재 보유한 카트바디 목록 출력
	// 2. 모두 모았는지 여부를 반환 
	int collect_all = 1;
	printf("\n\n\n\n ■보유 중인 아이템  \n\n");
	for (int i = 0; i < 5; i++) {
		// 카트바디 수집 X -> 빈 상자 표시 
		if (collection[i] == 0) {
			printf("%15s", "[      ]");
			collect_all = 0; // 모두 모으지 못함 
		}
		// 카트바디 수집 O -> 이름 표시
		else {
			printf("%15s", item[i].name);
		}
	}
	printf("\n\n ===============================================================================\n\n");

	if (collect_all) {
		printf("\n\n 축하합니다! 모든 카트바디를 다 모았어요. 당신은 진정한 카트 라이더!\n");
		printf("\n ( 뽑기 횟수 : %d )\n\n\n", count);

	}


	return collect_all;
}
