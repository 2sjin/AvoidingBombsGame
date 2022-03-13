#include<stdio.h>
#include<time.h>

int main() {

	// 공의 무게 설정하기

	srand(time(NULL));

	int ball[6] = { 2,2,2,2,2,2 };	// 6개의 공(무게:2)

	int answer;
	answer = rand() % 6;		// 6개 중 무게 조절할 공 1개 선정 

	int weight;
	weight = rand() % 2;	// 가볍게 or 무겹게 
	if (weight == 0) {
		ball[answer] = 1;		// 가볍게 
	}
	else if (weight == 1) {
		ball[answer] = 3;		// 무겁게 
	}
	else {
		printf("\n알 수 없는 오류가 발생하였습니다.\n");
		exit(0);
	}



	// 저울로 공의 무게 측정(3번의 측정 기회) 

	printf("\n================================================================ \n\n");
	printf("여기 6개의 공이 있습니다. \n");
	printf("5개는 무게가 같지만, 단 1개만 무게가 다른 공이 섞여있습니다. \n");
	printf("가벼운지, 무거운지는 모릅니다. \n");
	printf("여기 있는 저울을 세 번만 사용해서 무게가 다른 돌을 맞춰보세요! \n");
	printf("\n================================================================ \n\n\n");

	printf("시작하시려면 [Enter] 키를 눌러주세요.\n\n\n");
	getchar();



	for (int chance = 1; chance <= 3; chance++) {

		// 입력

		printf("\n\n[ %d / 3 ] 번째 측정을 시작합니다. \n", chance);

		int input = 0;	// 입력 값 
		int left = 0;	// 왼쪽 저울 무게 
		int right = 0;	// 오른쪽 저울 무게 

		for (int i = 0; i <= 5; i++) {
			printf("\n %d 번째 공을 저울의 어느 쪽에 올려놓겠습니까? \n", i + 1);
			printf("   [ 1 ] 왼쪽    [ 2 ] 오른쪽    [3] 올려놓지 않는다\n");
			printf(" ■ 숫자만 입력( 1 ~ 3 ) >> ");
			scanf_s("%d", &input);

			if (input == 1) {
				left += ball[i];
			}
			else if (input == 2) {
				right += ball[i];
			}
			else if (input == 3) {
			}
			else {
				printf("입력 범위를 벗어났습니다. \n");
				i--;
			}
		}


		// 측정 결과

		printf("\n================================================================ \n");
		printf("\n[ %d / 3 ] 번째 측정 결과\n\n", chance);

		if (left > right) {
			printf("\n 저울이 왼쪽으로 기울었습니다. \n");
		}
		else if (left < right) {
			printf("\n 저울이 오른쪽으로 기울었습니다. \n");
		}
		else if (left == right) {
			printf("\n 저울이 평형을 유지하고 있습니다. \n");
		}
		else {
			printf("\n알 수 없는 오류가 발생하였습니다.\n");
			exit(0);
		}

	}

	printf("\n================================================================ \n\n\n");



	// 정답 입력 
	int input_answer;
	printf("\n\n 어느 공이 무게가 다른 공일까요?\n\n");
	printf("   [ 1 ] 1번째 공    [ 2 ] 2번째 공    [ 3 ] 3번째 공\n");
	printf("   [ 4 ] 4번째 공    [ 5 ] 5번째 공    [ 6 ] 6번째 공\n");
	printf("\n ■ 숫자만 입력( 1 ~ 6 ) >> ");
	scanf_s("%d", &input_answer);

	printf("\n================================================================ \n");

	if (input_answer == answer + 1) {
		printf("\n\n 정답입니다!! \n ...쉬웠었나요? \n\n");
	}
	else {
		printf("\n\n 틀렸군요.. 정답은 %d 번째 공이었습니다. \n\n", answer);
	}

	printf("\n================================================================ \n\n\n");


	return 0;
}
