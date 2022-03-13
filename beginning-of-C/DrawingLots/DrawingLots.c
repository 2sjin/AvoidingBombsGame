#include <stdio.h>
#include <time.h> 
#include <windows.h> 

void print_item(int select);
int check_collection();

// 5������ īƮ�ٵ� �ִ�
// �ƹ� Ű�� ������ �������� ī��ٵ� �̾� 5���� ��� �����ϱ�!
// �ߺ� �߻� ����!

// īƮ�ٵ� ���� : �̸�, ����, �Ұ�, ��� 	
struct KARTBODY {
	char* name; // �̸� 
	int age; // ���� 
	char* character; // �Ұ� 
	int level;	 // ��� 
};

// ��ü īƮ�ٵ� ����Ʈ ���� 
struct KARTBODY item[5];

// ������� ������ īƮ�ٵ� 
int collection[5] = { 0, 0, 0, 0, 0 };        // 0 - �̺���, 1 - ���� 

// ī��ٵ� �̱� Ƚ�� 
int count = 0;

int main() {
	srand(time(NULL));

	// ================== īƮ�ٵ� ���� �Է� ===================

	item[0].name = "����";
	item[0].age = 3;
	item[0].character = "���� ���󰡴� �ְ��� ���ǵ�";
	item[0].level = 1;

	item[1].name = "ī����";
	item[1].age = 4;
	item[1].character = "ȥ���� ������";
	item[1].level = 2;

	item[2].name = "����";
	item[2].age = 5;
	item[2].character = "��� �׿� ���� ����";
	item[2].level = 3;

	item[3].name = "�Ķ��";
	item[3].age = 7;
	item[3].character = "���ο� ������ ����! Ʈ���� �����϶�";
	item[3].level = 4;

	item[4].name = "��Ƽ��";
	item[4].age = 8;
	item[4].character = "�������� �����ս��� �����϶�";
	item[4].level = 5;

	item[-1].name = "";
	item[-1].age = -1;
	item[-1].character = "";
	item[-1].level = -1;

	// =======================================================


	// ���� ���� 
	print_item(-1);
	int collect_all = check_collection(0);

	while (1) {
		printf("�αٵα�~! ��� īƮ�ٵ� ���ñ��?\n[Enter] Ű�� ������ Ȯ���ϼ���!");
		getchar();
		system("cls");

		int select = rand() % 5; // 0~4 ������ ���� ��ȯ
		print_item(select); // īƮ�ٵ� ���� ��� 
		collection[select] = 1; // īƮ�ٵ� ���� ���·� ó�� 
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

	printf(" �� īƮ�ٵ� ȹ�� ���� \n\n");
	printf("   - �̸� : %s\n", item[select].name);

	printf("   - ��ȣ : ");
	if (item[select].age != -1)
		printf("%03d", item[select].age);
	printf("\n");

	printf("   - �Ұ� : %s\n", item[select].character);

	printf("   - ��� : ");
	for (int i = 0; i < item[select].level; i++) {
		printf("%s", "��");
	}
}

int check_collection() {
	// 1. ���� ������ īƮ�ٵ� ��� ���
	// 2. ��� ��Ҵ��� ���θ� ��ȯ 
	int collect_all = 1;
	printf("\n\n\n\n �Ẹ�� ���� ������  \n\n");
	for (int i = 0; i < 5; i++) {
		// īƮ�ٵ� ���� X -> �� ���� ǥ�� 
		if (collection[i] == 0) {
			printf("%15s", "[      ]");
			collect_all = 0; // ��� ������ ���� 
		}
		// īƮ�ٵ� ���� O -> �̸� ǥ��
		else {
			printf("%15s", item[i].name);
		}
	}
	printf("\n\n ===============================================================================\n\n");

	if (collect_all) {
		printf("\n\n �����մϴ�! ��� īƮ�ٵ� �� ��Ҿ��. ����� ������ īƮ ���̴�!\n");
		printf("\n ( �̱� Ƚ�� : %d )\n\n\n", count);

	}


	return collect_all;
}
