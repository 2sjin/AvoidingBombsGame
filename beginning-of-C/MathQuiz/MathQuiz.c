#include<stdio.h>
#include<time.h>

int GetRandomNumber(int level) {
	return rand() % (level * 7) + 1;
}

void ShowQuestion(int level, int num1, int num2) {
	printf("\n\n\n************ %d 번째 퀴즈 ************\n", level);
	printf("\n\t     %d x %d = ?", num1, num2);
	printf("\n\n*************************************\n\n");
	printf("(종료하시려면 '-1'을 입력하세요.) \n");
	printf("■ 답 입력 ☞ ");

}

void success() {
	printf("\n 정답입니다!!! \n");
}


void fail() {
	printf("\n 틀렸지롱!!! \n");
}


int main() {

	// 문제가 5개가 있고
	// 각 문제마다 점점 어려운 수식 퀴즈가 출제 (랜덤) 

	// 맞히면 통과, 틀리면 실패 

	srand(time(NULL));	// 랜덤 함수 선언 
	int count = 0;		// count : 정답 횟수 
	int i;
	for (i = 1; i <= 5; i++) {   // 5번의 기회(i)가 끝날 때 까지 반복
		// X * Y = ?
		int num1 = GetRandomNumber(i);	//	num1 랜덤 
		int num2 = GetRandomNumber(i);	//	num2 랜덤 
		ShowQuestion(i, num1, num2);	//	문제 불러오기 

	// 비밀번호 입력 
		int answer = -1;				//	answer = 입력되는 답 
		scanf_s("%d", &answer);			//	답 입력 

	// -1 입력 시 프로그램 종료 
		if (answer == -1) {
			printf("프로그램을 종료합니다.\n");
			exit(0);
		}
		// 정답인 경우 
		else if (answer == num1 * num2) {
			success();
			count++;
		}
		// 오답인 경우 
		else {
			fail();
		}
	}


	// 기회 끝
	printf("당신은 5개 중 %d 개를 맞혔습니다.", count);

	return 0;
}

