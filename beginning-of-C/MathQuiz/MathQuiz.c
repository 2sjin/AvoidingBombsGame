#include<stdio.h>
#include<time.h>

int GetRandomNumber(int level) {
	return rand() % (level * 7) + 1;
}

void ShowQuestion(int level, int num1, int num2) {
	printf("\n\n\n************ %d ��° ���� ************\n", level);
	printf("\n\t     %d x %d = ?", num1, num2);
	printf("\n\n*************************************\n\n");
	printf("(�����Ͻ÷��� '-1'�� �Է��ϼ���.) \n");
	printf("�� �� �Է� �� ");

}

void success() {
	printf("\n �����Դϴ�!!! \n");
}


void fail() {
	printf("\n Ʋ������!!! \n");
}


int main() {

	// ������ 5���� �ְ�
	// �� �������� ���� ����� ���� ��� ���� (����) 

	// ������ ���, Ʋ���� ���� 

	srand(time(NULL));	// ���� �Լ� ���� 
	int count = 0;		// count : ���� Ƚ�� 
	int i;
	for (i = 1; i <= 5; i++) {   // 5���� ��ȸ(i)�� ���� �� ���� �ݺ�
		// X * Y = ?
		int num1 = GetRandomNumber(i);	//	num1 ���� 
		int num2 = GetRandomNumber(i);	//	num2 ���� 
		ShowQuestion(i, num1, num2);	//	���� �ҷ����� 

	// ��й�ȣ �Է� 
		int answer = -1;				//	answer = �ԷµǴ� �� 
		scanf_s("%d", &answer);			//	�� �Է� 

	// -1 �Է� �� ���α׷� ���� 
		if (answer == -1) {
			printf("���α׷��� �����մϴ�.\n");
			exit(0);
		}
		// ������ ��� 
		else if (answer == num1 * num2) {
			success();
			count++;
		}
		// ������ ��� 
		else {
			fail();
		}
	}


	// ��ȸ ��
	printf("����� 5�� �� %d ���� �������ϴ�.", count);

	return 0;
}

