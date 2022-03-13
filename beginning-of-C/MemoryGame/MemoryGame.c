#include <stdio.h>
#include <time.h>
#include <windows.h>

int card_num[20];	// 카드의 숫자 
int card_turn[20];	// 카드 뒤집힘 여부 : 카드 내용이 안 보이면 0, 보이면 1 
char* answer[20];	// 정답 목록 
int count; 	// 클리어까지 시도 횟수 

void show();
void press_any_key();

int main() {
	//  카드 번호, 카드 뒤집힘 여부 초기화 
	for (int i = 0; i < 20; i++) {
		card_num[i] = i;		// 카드번호 초기화(0~19) 
		card_turn[i] = 0;		// 카드 뒤집힘 여부 초기화(0 = 카드번호 표시, 1 = 현재 뒤집은 카드 내용, 2 = 정답 카드 내용)	
	}

	// 카드에 들어가는 내용 목록 
	char* list[10];
	list[0] = "브랜드";
	list[1] = "나미";
	list[2] = "애쉬";
	list[3] = "볼리베어";
	list[4] = "야스오";
	list[5] = "말파이트";
	list[6] = "아이번";
	list[7] = "오리아나";
	list[8] = "베이가";
	list[9] = "럭스";

	// 무작위로 카드 섞기
	srand(time(NULL));
	int check[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 같은 카드가 몇 개 있는지 체크 
	for (int i = 0; i < 20; i++) {
		int random = rand() % 10;
		if (check[random] < 2) {		// 같은 카드가 2개 놓여있지 않을 때 
			answer[i] = list[random]; 	// 빈 카드에 리스트 작성 
			check[random] += 1;
		}
		else {
			i--;
		}
	}

	// 정답 미리보기 (치트 기능) 
	printf("\n===============================================================\n\n");
	for (int i = 0; i < 20; i++) {
		printf("%10s ", answer[i]);
		if (i % 5 == 4) {
			printf("\n");
		}
	}
	printf("\n===============================================================\n\n");
	printf(" ( 시작하려면 아무 키나 누르십시오 . . . )\n");
	getch();
	system("cls");

	while (1) {
		show(); // 현재 카드의 상황 표시 

		// 카드 번호를 입력하여 카드 뒤집기 
		int input_1;
		int input_2;
		printf(" 뒤집을 카드의 번호를 입력하시오.\n");
		printf(" ( 1 ~ 20 사이의 숫자만 입력)\n\n");

		printf(" ① 첫 번째 카드: ");
		scanf_s("%d", &input_1);
		if (input_1 < 1 || 20 < input_1) {
			printf("\n 입력 범위를 벗어났습니다. (1 ~ 20) \n");
			press_any_key();
			continue;
		}
		else if (card_turn[input_1 - 1] == 2) {
			printf("\n 이미 확인된 카드입니다. \n");
			press_any_key();
			continue;
		}

		// 카드 1개만 뒤집었을 때
		else {
			card_turn[input_1 - 1] += 1;
			system("cls");
			show();
		}

		printf(" 뒤집을 카드의 번호를 입력하시오.\n");
		printf(" ( 1 ~ 20 사이의 숫자만 입력)\n\n");
		printf(" ① 첫 번째 카드: %d\n", input_1);
		printf(" ② 두 번째 카드: ");
		scanf_s("%d", &input_2);
		if (input_2 < 1 || 20 < input_2) {
			printf("\n 입력 범위를 벗어났습니다. (1 ~ 20) \n");
			press_any_key();
			continue;
		}
		else if (card_turn[input_2 - 1] == 2) {
			printf("\n 이미 확인된 카드입니다. \n");
			card_turn[input_1 - 1] -= 1;
			press_any_key();
			continue;
		}



		// 카드 두개 비교하여 정답 여부 확인 
		if (input_1 - 1 == input_2 - 1) {
			printf("\n 서로 다른 두 개의 카드를 골라주세요.\n");
		}
		else {

			card_turn[input_2 - 1] += 1;
			system("cls");
			show();
			if (answer[input_1 - 1] == answer[input_2 - 1]) {
				printf(" 성공!!!\n");
				card_turn[input_1 - 1] += 1;
				card_turn[input_2 - 1] += 1;
				count++;
			}
			else {
				printf(" 실패...\n");
				card_turn[input_1 - 1] -= 1;
				card_turn[input_2 - 1] -= 1;
				count++;
			}
		}
		press_any_key();


		// 몇 개의 카드가 뒤집혀 있는지 확인 
		int all_clear = 0;
		for (int i = 0; i < 20; i++) {
			if (card_turn[i] >= 1) {
				all_clear += 1;
			}
		}

		// 모든 카드를 뒤집었으면 클리어!! 		
		if (all_clear == 20) {
			break;	// 루프에서 탈출 
		}

	}

	// 클리어 멘트 후 종료 
	printf("\n===============================================================\n\n");
	for (int i = 0; i < 20; i++) {
		printf("%10s ", answer[i]);
		if (i % 5 == 4) {
			printf("\n");
		}
	}
	printf("\n===============================================================\n\n");
	printf("\n=================================================\n");
	printf("\n 축하합니다!! 모든 카드를 찾았습니다!!!\n");
	printf("\n ( 시도 횟수 : %d 회 ) \n", count);
	printf("\n=================================================\n");



	return 0;
}




// 현재 카드의 상황 표시
void show() {
	printf("\n===============================================================\n\n");
	for (int i = 0; i < 20; i++) {
		if (card_turn[i] >= 1) {
			printf("%10s ", answer[i]);	//	(1 = 현재 뒤집은 카드 내용, 2 = 정답 카드 내용)	
			if (i % 5 == 4) {
				printf("\n");
			}
		}
		else {
			printf("%10d ", card_num[i] + 1);	// (0 = 카드번호 표시)	
			if (i % 5 == 4) {
				printf("\n");
			}
		}
	}
	printf("\n===============================================================\n\n");
}


// PRESS ANY KEY
void press_any_key() {
	printf("\n\n ( 계속하려면 아무 키나 누르십시오 . . . )\n");
	getch();
	system("cls");
}

