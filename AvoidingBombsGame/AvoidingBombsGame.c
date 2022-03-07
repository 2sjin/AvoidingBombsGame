#define _CRT_SECURE_NO_WARNINGS

#define LEVEL_MAX 20		// �ִ� ����
#define ITEM_NUM 13		// ������ ������ 

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int map[44][22];	// ��ǥ�� ���� ���� ���� �迭 (0 = ���� ���� / 1 = ��)  

// �Լ� ���� 
void object(char style, int X0, int Y0, int X1, int Y1);
void gotoxy(int x, int y);
void cursor(int n);

int main() {
	srand(time(NULL)); // ���� �Լ� 
	SetConsoleTitle(TEXT("���۰���"));// ���� ǥ���� 
	system("mode con cols=66 lines=24");	// �ܼ�â ũ�� ���� 

	while (1) {
		// ���� ����
		int score = 0;	// ����
		int life = 1;	// �ܿ� ������ ���� 
		int rings = 0;  // �忩 �� ���� 
		int exp = -1;	// ���� �� ���� ���� ���̺� 
		int level = 1;			// �ʱ� ����(��ǳ��, ������ ����)

		// �ð� �ʱ�ȭ �� ���� ���� 
		clock_t start, end;
		double time;
		start = clock();

		// ���ΰ� �ʱ� ���� 
		int x = 20;	// ���ΰ� ���� X ��ǥ 
		int y = 10;	// ���ΰ� ���� Y ��ǥ 
		int dx = 20;	// ���ΰ� �̵� ��ǥ ���� X ��ǥ 
		int dy = 10;	// ���ΰ� �̵� ��ǥ ���� Y ��ǥ
		int look = 2;  // ���ΰ��� �ٶ󺸴� ����(0=��, 1=��, 2=��, 3=��) 

		// ��ǳ�� �ʱ� ����  
		int bomb_x[LEVEL_MAX * 2];	// ��ǳ�� ���� X ��ǥ �迭 
		int bomb_y[LEVEL_MAX * 2];	// ��ǳ�� ���� Y ��ǥ �迭
		int countdown = -1;	 // ��ǳ�� ���߱��� ���� �ð� 
		int damage = 0; // ��ǳ�� �ǰ� ���� 

		// ������ �ʱ� ����
		int item_x[LEVEL_MAX * 2];	// ������ ���� X ��ǥ �迭 
		int item_y[LEVEL_MAX * 2];	// ������ ���� Y ��ǥ �迭 	
		int item_code[ITEM_NUM];		// ������ ���� �ڵ�
		double item_time[ITEM_NUM];		// �����ۺ� ������ �ð�

		// ������ ��뿩��  
		int sensor = 0;			// ����: ���ٱ� ���� ǥ�� 
		int reverse = 0;		// ���� ���� �ݴ�� 
		int trap = 0;  			// �̵� �Ұ� 
		int star = 0;			// ���ٱ� ���� �鿪
		int hidden = 0;			// ��ǳ�� ����

		// �迭 �Լ� �ʱ�ȭ
		for (int i = 0; i < LEVEL_MAX * 2; i++) {
			bomb_x[i] = 0;
			bomb_y[i] = 0;
			item_x[i] = 0;
			item_y[i] = 0;
		}
		for (int i = 0; i < ITEM_NUM; i++) {
			item_code[i] = 0;
			item_time[i] = 0;
		}

		// �ʱ� �� �±� 0 ���� ���� 
		object('0', 0, 0, 42, 21);

		// �ݺ� ó�� 
		while (1) {
			// Ŀ�� ����� 
			cursor(0);

			// �ð� ���� 
			end = clock();
			time = (double)(end - start) / CLK_TCK;

			// ���� ��
			if (level >= LEVEL_MAX && exp >= level) {
				level = LEVEL_MAX;
				exp = level - 1;
			}
			else if (exp >= level) {
				level++;
				exp = 0;
			}

			// ���� ���� ǥ��
			printf("\033[0;36m");
			gotoxy(46, 1);	printf("< ��ǳ�� ���ϱ� >");
			printf("\033[1;33m");
			gotoxy(46, 4);	printf("STAGE");
			gotoxy(46, 6);	printf("SCORE");
			gotoxy(46, 7);	printf("TIME");
			gotoxy(46, 8); printf("LIFE");
			gotoxy(46, 9); printf("RINGS");
			printf("\033[0m");

			gotoxy(54, 4);	printf("%d - %d", level, exp + 1);
			gotoxy(54, 6);	printf("%d", score);
			gotoxy(54, 7);	printf("%.0f", time);

			// ������ ǥ�� 
			gotoxy(54, 8); printf("\033[1;31m");
			switch (life) {
			case 0: printf(""); break;
			case 1: printf("��"); break;
			case 2: printf("����"); break;
			case 3: printf("������"); break;
			}
			printf("\033[0m");

			// �� ǥ�� 
			gotoxy(54, 9); printf("\033[0;33m");
			switch (rings) {
			case 0: printf(""); break;
			case 1: printf("��"); break;
			case 2: printf("�ݡ�"); break;
			case 3: printf("�ݡݡ�"); break;
			case 4: printf("�ݡݡݡ�"); break;
			case 5: printf("�ݡݡݡݡ�"); break;
			}
			printf("\033[0m");

			// ���� ī��Ʈ�ٿ� ǥ�� (������ ���) 
			//gotoxy(46, 20);	printf("COUNTDOWN\t%d", countdown);	 	

			// ������, �� �ִ�ġ ����
			if (life > 3)	life = 3;
			if (rings > 5)	rings = 5;

			// �׵θ� ���� 
			object('f', 0, 0, 42, 0);		// �׵θ�(��) 
			object('f', 0, 21, 42, 21);		// �׵θ�(��) 
			object('f', 0, 0, 0, 21);		// �׵θ�(��) 
			object('f', 42, 0, 42, 21);		// �׵θ�(��) 

			// �����ۺ� ���� �ڵ� ���� 
			int i_dv = 4;	// DeVil
			int i_hd = 6;	// HiDden
			int i_tr = 7;	// TRap
			int i_st = 11;	// STar
			int i_mt = 12;	// MaTrix 


			// ������ ���� (���� ����)					
			for (int i = 0; i <= level; i++) {
				switch (item_code[i]) {
				case 0: gotoxy(item_x[i], item_y[i]); break;
				case 1: gotoxy(item_x[i], item_y[i]); printf("\033[0;33m��\033[0m"); break;		// �� 
				case 2: gotoxy(item_x[i], item_y[i]); printf("\033[0;33m��\033[0m"); break;		// �� 
				case 3: gotoxy(item_x[i], item_y[i]); printf("\033[0;32m��\033[0m"); break;		// �ʷϾǸ� 
				case 4: gotoxy(item_x[i], item_y[i]); printf("\033[0;35m��\033[0m"); break;		// ����Ǹ� 					
				case 5: gotoxy(item_x[i], item_y[i]); printf("\033[0;31m��\033[0m"); break;		// ȭ�� 
				case 6: gotoxy(item_x[i], item_y[i]); printf("\033[0;34m��\033[0m"); break;		// ���� ��ǳ��						
				case 7: gotoxy(item_x[i], item_y[i]); printf("\033[0;33m��\033[0m"); break;		// �� 
				case 8: gotoxy(item_x[i], item_y[i]); printf("\033[0;32m��\033[0m"); break;		// �ʷϾǸ� 
				case 9: gotoxy(item_x[i], item_y[i]); printf("\033[0;35m��\033[0m"); break;		// ����Ǹ� 
				case 10: gotoxy(item_x[i], item_y[i]); printf("\033[1;31m��\033[0m"); break;	// ��Ʈ 
				case 11: gotoxy(item_x[i], item_y[i]); printf("\033[1;33m��\033[0m"); break;	// ��(����)
				case 12: gotoxy(item_x[i], item_y[i]); printf("\033[0;31m��\033[0m"); break;	// ȭ�� 
				case 13: gotoxy(item_x[i], item_y[i]); printf("\033[1;32m01\033[0m"); break;	// ��Ʈ����(����)  
				}
			}

			// ������ ��� �� (ȿ�� ����) 
			for (int i = 0; i < ITEM_NUM; i++) {
				if (x == item_x[i] && y == item_y[i]) {
					switch (item_code[i]) {
					case 0: break;
					case 1: rings++; item_code[i] = 0; break;										// �� +1 
					case 2: rings++; item_code[i] = 0; break;										// �� +1 
					case 3:	rings = 0; item_code[i] = 0; break;										// �� =0
					case 4:	reverse = 1; item_code[i] = 0; item_time[i_dv] = time + 7; break;		// ���� ���� �ݴ��
					case 5: countdown = 7; item_code[i] = 0; break;									// ��ǳ�� ��� ���� 
					case 6:	hidden = 1; item_code[i] = 0; item_time[i_hd] = time + 4; break;		// ��ǳ�� ����ȭ 
					case 7: trap = 1; item_code[i] = 0; item_time[i_tr] = time + 1; break;			// �̵� �Ұ� 
					case 8:	rings = 0; item_code[i] = 0; break;										// �� =0
					case 9:	reverse = 1; item_code[i] = 0; item_time[i_dv] = time + 7; break;		// ���� ���� �ݴ��
					case 10: life++; item_code[i] = 0; break;										// ������ +1 
					case 11: star = 1; item_code[i] = 0; item_time[i_st] = time + 3; break;			// ���� �ð� ���ٱ� �鿪 
					case 12: countdown = 7; item_code[i] = 0; break;								// ��ǳ�� ��� ���� 
					case 13: sensor = 1; item_code[i] = 0; item_time[i_mt] = time + 4; break;		// ���ٱ� ���� ǥ�� 
					}
				}
			}

			// ������ �ܿ��ð� ǥ��	
			if (item_time[i_dv] - time > 0) { gotoxy(46, 11);	printf("\033[0;35m��\033[0m");	gotoxy(47, 12);	printf("%.0f", item_time[i_dv] - time); }
			if (item_time[i_st] - time > 0) { gotoxy(48, 11);	printf("\033[1;33m��\033[0m");	gotoxy(49, 12);	printf("%.0f", item_time[i_st] - time); }
			if (item_time[i_mt] - time > 0) { gotoxy(50, 11);	printf("\033[1;32m01\033[0m");	gotoxy(51, 12);	printf("%.0f", item_time[i_mt] - time); }
			if (item_time[i_hd] - time > 0) { gotoxy(52, 11);	printf("\033[0;34m��\033[0m");	gotoxy(53, 12);	printf("%.0f", item_time[i_hd] - time); }

			// ���ӽð� ���� �� ������ ���� 
			if (trap == 1 && time >= item_time[i_tr]) trap = 0;
			if (reverse == 1 && time >= item_time[i_dv]) reverse = 0;
			if (star == 1 && time >= item_time[i_st]) star = 0;
			if (sensor == 1 && time >= item_time[i_mt]) sensor = 0;
			if (hidden == 1 && time >= item_time[i_hd]) hidden = 0;

			// ������ - ���ٱ� ���� ǥ��
			for (int i = 0; i < level + 2; i++) {
				if (sensor == 1 && time < item_time[i_mt]) {
					object('r', bomb_x[i], 1, bomb_x[i], 20);
					object('r', 2, bomb_y[i], 40, bomb_y[i]);
				}
			}

			for (int i = 0; i < level + 2; i++) {
				// ��ǳ�� ����	
				if (countdown <= 50) {
					switch (hidden) {
					case 0: object('b', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]); break;	// �Ϲ� ��ǳ�� 
					case 1: object('h', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]); break;	// ���� ��ǳ�� 
					}

				}

				// ���ٱ� ����(��ǳ�� ����) 
				if (countdown <= 5) {
					object('s', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]);
					object('s', bomb_x[i], 1, bomb_x[i], 20);
					object('s', 2, bomb_y[i], 40, bomb_y[i]);
				}

				// ���� ȹ��
				if (countdown == 5) {
					score = score + level;
				}


				if (countdown <= -1) {
					// ���ٱ� ���� 
					object('0', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]);
					object('0', bomb_x[i], 1, bomb_x[i], 20);
					object('0', 2, bomb_y[i], 40, bomb_y[i]);
					// ������ ���� ���� ����
					if (level <= 2)
						item_code[i] = rand() % 2 + 1;	 		// 2���������� ������ ���� ������  
					else if (rings >= 5)
						item_code[i] = rand() % ITEM_NUM + 3;	// �� 5�� �̻� : ��� ������ 
					else
						item_code[i] = rand() % 7 + 1;			// �� 4�� ����: �Ϻ� ������ 
				}
			}

			// ��ǳ��, ������ ��ġ ���� ���� 
			if (countdown <= -1) {
				for (int i = 0; i < LEVEL_MAX * 2; i++) {
					bomb_x[i] = rand() % 20 * 2 + 2;	// ��ǳ�� ���� ��ġ X 
					bomb_y[i] = rand() % 20 + 1;		// ��ǳ�� ���� ��ġ Y
					item_x[i] = rand() % 20 * 2 + 2;	// ������ ���� ��ġ X 
					item_y[i] = rand() % 20 + 1;		// ������ ���� ��ġ Y
				}
			}

			// ������ 0: ���� ���� 
			if (life <= 0) break;			// ������ 0 

			// ��ǳ�� �ǰ� ����		
			if (map[x][y] == 2 && star == 0 && damage == 0) {
				damage++;
				trap++;
				life--;
				rings = 0;
			}

			// ī��Ʈ �ٿ� �ʱ�ȭ 
			if (countdown <= -1) {
				if (damage >= 1) {
					damage = 0;
					trap = 0;
				}
				exp++;	// ����ġ ���� 
				countdown = 60;
			}

			// ���ΰ� �ݴ� �������� ����(�Ǹ�) 
			if (reverse == 1 && time < item_time[i_dv]) {
				if (_kbhit()) {
					char key_in = _getch();
					if (key_in == 'W' || key_in == 'w') { dy++; look = 2; }	// �� 
					if (key_in == 'A' || key_in == 'a') { dx += 2; look = 3; }	// �� 
					if (key_in == 'S' || key_in == 's') { dy--; look = 0; }	// ��				
					if (key_in == 'D' || key_in == 'd') { dx -= 2; look = 1; }	// �� 
				}
			}
			// ���ΰ� ���� �Ұ� ����
			else if (trap == 1) {}
			// ���ΰ� ���� ����(����) 
			else {
				if (_kbhit()) {
					char key_in = _getch();
					if (key_in == 'W' || key_in == 'w') { dy--; look = 0; }	// �� 
					if (key_in == 'A' || key_in == 'a') { dx -= 2; look = 1; }	// �� 
					if (key_in == 'S' || key_in == 's') { dy++; look = 2; }	// ��				
					if (key_in == 'D' || key_in == 'd') { dx += 2; look = 3; }	// �� 
				}
			}

			// ���ΰ� �̵� ��ǥ ������ ���� �ִ��� Ȯ�� 		
			if (map[dx][dy] == 1) {
				dx = x;
				dy = y;
			}

			// ���ΰ��� �̵� ��ǥ �������� �̵� 
			x = dx;
			y = dy;

			// ���ΰ� ���
			gotoxy(x, y);
			// ���ڻ� ���� ���� 
			if (star == 1) printf("\033[1;33m");
			else if (damage == 1) printf("\033[1;36m");
			else if (reverse == 1) printf("\033[0;35m");
			else if (sensor == 1) printf("\033[0;32m");
			else printf("\033[0;31m");

			switch (look) {
			case 0: printf("��"); break;
			case 1: printf("��"); break;
			case 2: printf("��"); break;
			case 3: printf("��"); break;
			}
			printf("\033[0m");	// ���ڻ� ���� ���� 

		// ȭ�� ���� 
			countdown--;
			Sleep(50);
			system("cls");
		}

		// GAME OVER
		gotoxy(12, 8);
		printf("\033[1;33m");	// ���ڻ� ���� ���� 
		printf("- �ǣ��ͣ� �ϣ֣ţ� -\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("\033[0m");	// ���ڻ� ���� ���� 
		Sleep(1500);
		_getch();
		continue;
	}
}


// ������Ʈ ����(��� ��Ÿ��, ����X, ����Y, ��X, ��Y) 
void object(char style, int X0, int Y0, int X1, int Y1) {
	for (int i = X0; i <= X1; i += 2) {
		for (int j = Y0; j <= Y1; j++) {
			gotoxy(i, j);
			switch (style) {
			case '0': map[i][j] = 0; break;					// 0 (���� ����) 
			case 'w': map[i][j] = 1; printf("��"); break; 	// wall(��) 
			case 'f': map[i][j] = 1; printf("\033[1;30m��\033[0m"); break; 	// frame(�׵θ�) 
			case 'b': map[i][j] = 1; printf("\033[1;36m��\033[0m"); break; 	// bomb(��ǳ��) 
			case 'h': map[i][j] = 1; printf("\033[0;30m��\033[0m"); break; 	// hidden_bomb(���� ��ǳ��) 
			case 's': map[i][j] = 2; printf("\033[1;36m��\033[0m"); break; 	// stream(���ٱ�) 
			case 'r': map[i][j] = 0; printf("\033[1;32m��\033[0m"); break; 	// range(���ٱ� ���� ǥ��)
			}
		}
	}
}

// gotoxy �Լ� 
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Ŀ�� ����� �Լ� 
void cursor(int n) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

