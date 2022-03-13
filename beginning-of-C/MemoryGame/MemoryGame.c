#include <stdio.h>
#include <time.h>
#include <windows.h>

int card_num[20];	// ī���� ���� 
int card_turn[20];	// ī�� ������ ���� : ī�� ������ �� ���̸� 0, ���̸� 1 
char* answer[20];	// ���� ��� 
int count; 	// Ŭ������� �õ� Ƚ�� 

void show();
void press_any_key();

int main() {
	//  ī�� ��ȣ, ī�� ������ ���� �ʱ�ȭ 
	for (int i = 0; i < 20; i++) {
		card_num[i] = i;		// ī���ȣ �ʱ�ȭ(0~19) 
		card_turn[i] = 0;		// ī�� ������ ���� �ʱ�ȭ(0 = ī���ȣ ǥ��, 1 = ���� ������ ī�� ����, 2 = ���� ī�� ����)	
	}

	// ī�忡 ���� ���� ��� 
	char* list[10];
	list[0] = "�귣��";
	list[1] = "����";
	list[2] = "�ֽ�";
	list[3] = "��������";
	list[4] = "�߽���";
	list[5] = "������Ʈ";
	list[6] = "���̹�";
	list[7] = "�����Ƴ�";
	list[8] = "���̰�";
	list[9] = "����";

	// �������� ī�� ����
	srand(time(NULL));
	int check[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // ���� ī�尡 �� �� �ִ��� üũ 
	for (int i = 0; i < 20; i++) {
		int random = rand() % 10;
		if (check[random] < 2) {		// ���� ī�尡 2�� �������� ���� �� 
			answer[i] = list[random]; 	// �� ī�忡 ����Ʈ �ۼ� 
			check[random] += 1;
		}
		else {
			i--;
		}
	}

	// ���� �̸����� (ġƮ ���) 
	printf("\n===============================================================\n\n");
	for (int i = 0; i < 20; i++) {
		printf("%10s ", answer[i]);
		if (i % 5 == 4) {
			printf("\n");
		}
	}
	printf("\n===============================================================\n\n");
	printf(" ( �����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . . )\n");
	getch();
	system("cls");

	while (1) {
		show(); // ���� ī���� ��Ȳ ǥ�� 

		// ī�� ��ȣ�� �Է��Ͽ� ī�� ������ 
		int input_1;
		int input_2;
		printf(" ������ ī���� ��ȣ�� �Է��Ͻÿ�.\n");
		printf(" ( 1 ~ 20 ������ ���ڸ� �Է�)\n\n");

		printf(" �� ù ��° ī��: ");
		scanf_s("%d", &input_1);
		if (input_1 < 1 || 20 < input_1) {
			printf("\n �Է� ������ ������ϴ�. (1 ~ 20) \n");
			press_any_key();
			continue;
		}
		else if (card_turn[input_1 - 1] == 2) {
			printf("\n �̹� Ȯ�ε� ī���Դϴ�. \n");
			press_any_key();
			continue;
		}

		// ī�� 1���� �������� ��
		else {
			card_turn[input_1 - 1] += 1;
			system("cls");
			show();
		}

		printf(" ������ ī���� ��ȣ�� �Է��Ͻÿ�.\n");
		printf(" ( 1 ~ 20 ������ ���ڸ� �Է�)\n\n");
		printf(" �� ù ��° ī��: %d\n", input_1);
		printf(" �� �� ��° ī��: ");
		scanf_s("%d", &input_2);
		if (input_2 < 1 || 20 < input_2) {
			printf("\n �Է� ������ ������ϴ�. (1 ~ 20) \n");
			press_any_key();
			continue;
		}
		else if (card_turn[input_2 - 1] == 2) {
			printf("\n �̹� Ȯ�ε� ī���Դϴ�. \n");
			card_turn[input_1 - 1] -= 1;
			press_any_key();
			continue;
		}



		// ī�� �ΰ� ���Ͽ� ���� ���� Ȯ�� 
		if (input_1 - 1 == input_2 - 1) {
			printf("\n ���� �ٸ� �� ���� ī�带 ����ּ���.\n");
		}
		else {

			card_turn[input_2 - 1] += 1;
			system("cls");
			show();
			if (answer[input_1 - 1] == answer[input_2 - 1]) {
				printf(" ����!!!\n");
				card_turn[input_1 - 1] += 1;
				card_turn[input_2 - 1] += 1;
				count++;
			}
			else {
				printf(" ����...\n");
				card_turn[input_1 - 1] -= 1;
				card_turn[input_2 - 1] -= 1;
				count++;
			}
		}
		press_any_key();


		// �� ���� ī�尡 ������ �ִ��� Ȯ�� 
		int all_clear = 0;
		for (int i = 0; i < 20; i++) {
			if (card_turn[i] >= 1) {
				all_clear += 1;
			}
		}

		// ��� ī�带 ���������� Ŭ����!! 		
		if (all_clear == 20) {
			break;	// �������� Ż�� 
		}

	}

	// Ŭ���� ��Ʈ �� ���� 
	printf("\n===============================================================\n\n");
	for (int i = 0; i < 20; i++) {
		printf("%10s ", answer[i]);
		if (i % 5 == 4) {
			printf("\n");
		}
	}
	printf("\n===============================================================\n\n");
	printf("\n=================================================\n");
	printf("\n �����մϴ�!! ��� ī�带 ã�ҽ��ϴ�!!!\n");
	printf("\n ( �õ� Ƚ�� : %d ȸ ) \n", count);
	printf("\n=================================================\n");



	return 0;
}




// ���� ī���� ��Ȳ ǥ��
void show() {
	printf("\n===============================================================\n\n");
	for (int i = 0; i < 20; i++) {
		if (card_turn[i] >= 1) {
			printf("%10s ", answer[i]);	//	(1 = ���� ������ ī�� ����, 2 = ���� ī�� ����)	
			if (i % 5 == 4) {
				printf("\n");
			}
		}
		else {
			printf("%10d ", card_num[i] + 1);	// (0 = ī���ȣ ǥ��)	
			if (i % 5 == 4) {
				printf("\n");
			}
		}
	}
	printf("\n===============================================================\n\n");
}


// PRESS ANY KEY
void press_any_key() {
	printf("\n\n ( ����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . . )\n");
	getch();
	system("cls");
}

