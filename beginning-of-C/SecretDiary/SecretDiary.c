#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// ��й�ȣ�� �Է� �޾Ƽ�
// �´� ���? ��� �ϱ⸦ �о�ͼ� �����ְ�, ��� �ۼ��ϵ��� �մϴ�.
// Ʋ�� ���? ��� �޽����� ǥ���ϰ� �����մϴ�. 

#define MAX 10000

int main() {
	// fgets, fputs Ȱ��
	char line[MAX]; // ���Ͽ��� �ҷ��� ������ ������ ���� 
	char contents[MAX]; // �ϱ��忡 �Է��� ���� 
	char password[20]; // ��й�ȣ �Է�
	char c; // ��й�ȣ �Է��� �� Ű�� Ȯ�ο�(����ŷ) 

	printf("'����ϱ�'�� ���� ���� ȯ���մϴ�\n");


PW:		// ��й�ȣ �Է�
	printf("��й�ȣ�� �Է��ϼ��� : ");

	int i = 0;
	while (1) {
		c = getch();
		if (c == 13) { // 13 : Enter -> ��й�ȣ �Է� ���� 
			password[i] = '\0';
			break;
		}
		else if (c == 8) {  // 8 : Backspace -> ����� ����� �ȵǹǷ� ��� �Է� ���� 
			i--;
		}

		else {	// ��й�ȣ �Է� �� 
			// printf("%c", c);   // �����ڿ� 
			printf("*");
			password[i] = c;
		}
		i++;

	}

	// ��й�ȣ : qwer
	printf("\n\n === ��й�ȣ Ȯ�� ��... === \n\n");
	if (strcmp(password, "qwer") == 0) {
		printf(" === ��й�ȣ Ȯ�� �Ϸ� === \n\n");
		char* filename = "secretdiary.txt";
		FILE* file = fopen(filename, "a+b");
		// ������ ������ ����, ������ ������ ���� �߰� 

		if (file == NULL) {
			printf("���� ���� ����\n");
			return 1;
		}

		while (fgets(line, MAX, file) != NULL) {
			printf("%s", line);
		}

		printf("\n\n ������ ��� �ۼ��ϼ��� ! �����Ͻ÷��� '/end' �� �Է��ϼ��� \n\n");

		while (1) {
			scanf("%[^\n]", contents); // �� ��(\n)�� ������ �� ���� �о�帲(�� ���徿)
			getchar(); // Enter �Է� (\n) Flush ó��

			if (strcmp(contents, "/END") == 0 || strcmp(contents, "/end") == 0 || strcmp(contents, "/End") == 0) {
				printf("����ϱ� �Է��� �����մϴ�.\n\n");
				break;
			}
			fputs(contents, file);
			fputs("\n", file); // Enter �� ������ ���� ó�� �Ͽ����Ƿ� ���Ƿ� �߰�
		}
		fclose(file);
	}
	else { 	// ��й�ȣ Ʋ�� ��� 
		printf(" === ��й�ȣ�� Ʋ�Ƚ��ϴ�. === \n\n ");
		goto PW;	// ��й�ȣ �Է� �κ����� �̵� 
	}

	return 0;
}
