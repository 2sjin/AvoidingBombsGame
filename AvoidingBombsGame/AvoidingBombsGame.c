#define _CRT_SECURE_NO_WARNINGS

#define LEVEL_MAX 20		// 최대 레벨
#define ITEM_NUM 13		// 아이템 가짓수 

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int map[44][22];	// 좌표별 통행 가능 여부 배열 (0 = 통행 가능 / 1 = 벽)  

// 함수 선언 
void object(char style, int X0, int Y0, int X1, int Y1);
void gotoxy(int x, int y);
void cursor(int n);

int main() {
	srand(time(NULL)); // 랜덤 함수 
	SetConsoleTitle(TEXT("자작게임"));// 제목 표시줄 
	system("mode con cols=66 lines=24");	// 콘솔창 크기 조절 

	while (1) {
		// 게임 정보
		int score = 0;	// 점수
		int life = 1;	// 잔여 라이프 개수 
		int rings = 0;  // 장여 링 개수 
		int exp = -1;	// 레벨 업 까지 남은 웨이브 
		int level = 1;			// 초기 레벨(물풍선, 아이템 개수)

		// 시간 초기화 및 측정 시작 
		clock_t start, end;
		double time;
		start = clock();

		// 주인공 초기 정보 
		int x = 20;	// 주인공 현재 X 좌표 
		int y = 10;	// 주인공 현재 Y 좌표 
		int dx = 20;	// 주인공 이동 목표 지점 X 좌표 
		int dy = 10;	// 주인공 이동 목표 지점 Y 좌표
		int look = 2;  // 주인공이 바라보는 방향(0=상, 1=좌, 2=하, 3=우) 

		// 물풍선 초기 정보  
		int bomb_x[LEVEL_MAX * 2];	// 물풍선 생성 X 좌표 배열 
		int bomb_y[LEVEL_MAX * 2];	// 물풍선 생성 Y 좌표 배열
		int countdown = -1;	 // 물풍선 폭발까지 남은 시간 
		int damage = 0; // 물풍선 피격 판정 

		// 아이템 초기 정보
		int item_x[LEVEL_MAX * 2];	// 아이템 생성 X 좌표 배열 
		int item_y[LEVEL_MAX * 2];	// 아이템 생성 Y 좌표 배열 	
		int item_code[ITEM_NUM];		// 아이템 종류 코드
		double item_time[ITEM_NUM];		// 아이템별 끝나는 시간

		// 아이템 사용여부  
		int sensor = 0;			// 센서: 물줄기 범위 표시 
		int reverse = 0;		// 조작 방향 반대로 
		int trap = 0;  			// 이동 불가 
		int star = 0;			// 물줄기 피해 면역
		int hidden = 0;			// 물풍선 투명

		// 배열 함수 초기화
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

		// 초기 맵 태그 0 으로 설정 
		object('0', 0, 0, 42, 21);

		// 반복 처리 
		while (1) {
			// 커서 숨기기 
			cursor(0);

			// 시간 갱신 
			end = clock();
			time = (double)(end - start) / CLK_TCK;

			// 레벨 업
			if (level >= LEVEL_MAX && exp >= level) {
				level = LEVEL_MAX;
				exp = level - 1;
			}
			else if (exp >= level) {
				level++;
				exp = 0;
			}

			// 게임 정보 표시
			printf("\033[0;36m");
			gotoxy(46, 1);	printf("< 물풍선 피하기 >");
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

			// 라이프 표시 
			gotoxy(54, 8); printf("\033[1;31m");
			switch (life) {
			case 0: printf(""); break;
			case 1: printf("♥"); break;
			case 2: printf("♥♥"); break;
			case 3: printf("♥♥♥"); break;
			}
			printf("\033[0m");

			// 링 표시 
			gotoxy(54, 9); printf("\033[0;33m");
			switch (rings) {
			case 0: printf(""); break;
			case 1: printf("◎"); break;
			case 2: printf("◎◎"); break;
			case 3: printf("◎◎◎"); break;
			case 4: printf("◎◎◎◎"); break;
			case 5: printf("◎◎◎◎◎"); break;
			}
			printf("\033[0m");

			// 폭발 카운트다운 표시 (개발자 모드) 
			//gotoxy(46, 20);	printf("COUNTDOWN\t%d", countdown);	 	

			// 라이프, 링 최대치 설정
			if (life > 3)	life = 3;
			if (rings > 5)	rings = 5;

			// 테두리 생성 
			object('f', 0, 0, 42, 0);		// 테두리(상) 
			object('f', 0, 21, 42, 21);		// 테두리(하) 
			object('f', 0, 0, 0, 21);		// 테두리(좌) 
			object('f', 42, 0, 42, 21);		// 테두리(우) 

			// 아이템별 고유 코드 저장 
			int i_dv = 4;	// DeVil
			int i_hd = 6;	// HiDden
			int i_tr = 7;	// TRap
			int i_st = 11;	// STar
			int i_mt = 12;	// MaTrix 


			// 아이템 생성 (외형 설정)					
			for (int i = 0; i <= level; i++) {
				switch (item_code[i]) {
				case 0: gotoxy(item_x[i], item_y[i]); break;
				case 1: gotoxy(item_x[i], item_y[i]); printf("\033[0;33m◎\033[0m"); break;		// 링 
				case 2: gotoxy(item_x[i], item_y[i]); printf("\033[0;33m◎\033[0m"); break;		// 링 
				case 3: gotoxy(item_x[i], item_y[i]); printf("\033[0;32m黑\033[0m"); break;		// 초록악마 
				case 4: gotoxy(item_x[i], item_y[i]); printf("\033[0;35m黑\033[0m"); break;		// 보라악마 					
				case 5: gotoxy(item_x[i], item_y[i]); printf("\033[0;31m↗\033[0m"); break;		// 화살 
				case 6: gotoxy(item_x[i], item_y[i]); printf("\033[0;34m◐\033[0m"); break;		// 투명 물풍선						
				case 7: gotoxy(item_x[i], item_y[i]); printf("\033[0;33m♨\033[0m"); break;		// 덫 
				case 8: gotoxy(item_x[i], item_y[i]); printf("\033[0;32m黑\033[0m"); break;		// 초록악마 
				case 9: gotoxy(item_x[i], item_y[i]); printf("\033[0;35m黑\033[0m"); break;		// 보라악마 
				case 10: gotoxy(item_x[i], item_y[i]); printf("\033[1;31m♥\033[0m"); break;	// 하트 
				case 11: gotoxy(item_x[i], item_y[i]); printf("\033[1;33m★\033[0m"); break;	// 별(무적)
				case 12: gotoxy(item_x[i], item_y[i]); printf("\033[0;31m↗\033[0m"); break;	// 화살 
				case 13: gotoxy(item_x[i], item_y[i]); printf("\033[1;32m01\033[0m"); break;	// 매트릭스(센서)  
				}
			}

			// 아이템 사용 시 (효과 설정) 
			for (int i = 0; i < ITEM_NUM; i++) {
				if (x == item_x[i] && y == item_y[i]) {
					switch (item_code[i]) {
					case 0: break;
					case 1: rings++; item_code[i] = 0; break;										// 링 +1 
					case 2: rings++; item_code[i] = 0; break;										// 링 +1 
					case 3:	rings = 0; item_code[i] = 0; break;										// 링 =0
					case 4:	reverse = 1; item_code[i] = 0; item_time[i_dv] = time + 7; break;		// 조작 방향 반대로
					case 5: countdown = 7; item_code[i] = 0; break;									// 물풍선 즉시 폭발 
					case 6:	hidden = 1; item_code[i] = 0; item_time[i_hd] = time + 4; break;		// 물풍선 투명화 
					case 7: trap = 1; item_code[i] = 0; item_time[i_tr] = time + 1; break;			// 이동 불가 
					case 8:	rings = 0; item_code[i] = 0; break;										// 링 =0
					case 9:	reverse = 1; item_code[i] = 0; item_time[i_dv] = time + 7; break;		// 조작 방향 반대로
					case 10: life++; item_code[i] = 0; break;										// 라이프 +1 
					case 11: star = 1; item_code[i] = 0; item_time[i_st] = time + 3; break;			// 일정 시간 물줄기 면역 
					case 12: countdown = 7; item_code[i] = 0; break;								// 물풍선 즉시 폭발 
					case 13: sensor = 1; item_code[i] = 0; item_time[i_mt] = time + 4; break;		// 물줄기 범위 표시 
					}
				}
			}

			// 아이템 잔여시간 표시	
			if (item_time[i_dv] - time > 0) { gotoxy(46, 11);	printf("\033[0;35m黑\033[0m");	gotoxy(47, 12);	printf("%.0f", item_time[i_dv] - time); }
			if (item_time[i_st] - time > 0) { gotoxy(48, 11);	printf("\033[1;33m★\033[0m");	gotoxy(49, 12);	printf("%.0f", item_time[i_st] - time); }
			if (item_time[i_mt] - time > 0) { gotoxy(50, 11);	printf("\033[1;32m01\033[0m");	gotoxy(51, 12);	printf("%.0f", item_time[i_mt] - time); }
			if (item_time[i_hd] - time > 0) { gotoxy(52, 11);	printf("\033[0;34m◐\033[0m");	gotoxy(53, 12);	printf("%.0f", item_time[i_hd] - time); }

			// 지속시간 종료 시 아이템 해제 
			if (trap == 1 && time >= item_time[i_tr]) trap = 0;
			if (reverse == 1 && time >= item_time[i_dv]) reverse = 0;
			if (star == 1 && time >= item_time[i_st]) star = 0;
			if (sensor == 1 && time >= item_time[i_mt]) sensor = 0;
			if (hidden == 1 && time >= item_time[i_hd]) hidden = 0;

			// 아이템 - 물줄기 범위 표시
			for (int i = 0; i < level + 2; i++) {
				if (sensor == 1 && time < item_time[i_mt]) {
					object('r', bomb_x[i], 1, bomb_x[i], 20);
					object('r', 2, bomb_y[i], 40, bomb_y[i]);
				}
			}

			for (int i = 0; i < level + 2; i++) {
				// 물풍선 생성	
				if (countdown <= 50) {
					switch (hidden) {
					case 0: object('b', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]); break;	// 일반 물풍선 
					case 1: object('h', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]); break;	// 투명 물풍선 
					}

				}

				// 물줄기 생성(물풍선 폭발) 
				if (countdown <= 5) {
					object('s', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]);
					object('s', bomb_x[i], 1, bomb_x[i], 20);
					object('s', 2, bomb_y[i], 40, bomb_y[i]);
				}

				// 점수 획득
				if (countdown == 5) {
					score = score + level;
				}


				if (countdown <= -1) {
					// 물줄기 제거 
					object('0', bomb_x[i], bomb_y[i], bomb_x[i], bomb_y[i]);
					object('0', bomb_x[i], 1, bomb_x[i], 20);
					object('0', 2, bomb_y[i], 40, bomb_y[i]);
					// 아이템 종류 랜덤 설정
					if (level <= 2)
						item_code[i] = rand() % 2 + 1;	 		// 2레벨까지는 무조건 링만 나오게  
					else if (rings >= 5)
						item_code[i] = rand() % ITEM_NUM + 3;	// 링 5개 이상 : 모든 아이템 
					else
						item_code[i] = rand() % 7 + 1;			// 링 4개 이하: 일부 아이템 
				}
			}

			// 물풍선, 아이템 위치 랜덤 설정 
			if (countdown <= -1) {
				for (int i = 0; i < LEVEL_MAX * 2; i++) {
					bomb_x[i] = rand() % 20 * 2 + 2;	// 물풍선 생성 위치 X 
					bomb_y[i] = rand() % 20 + 1;		// 물풍선 생성 위치 Y
					item_x[i] = rand() % 20 * 2 + 2;	// 아이템 생성 위치 X 
					item_y[i] = rand() % 20 + 1;		// 아이템 생성 위치 Y
				}
			}

			// 라이프 0: 게임 오버 
			if (life <= 0) break;			// 라이프 0 

			// 물풍선 피격 판정		
			if (map[x][y] == 2 && star == 0 && damage == 0) {
				damage++;
				trap++;
				life--;
				rings = 0;
			}

			// 카운트 다운 초기화 
			if (countdown <= -1) {
				if (damage >= 1) {
					damage = 0;
					trap = 0;
				}
				exp++;	// 경험치 증가 
				countdown = 60;
			}

			// 주인공 반대 방향으로 조작(악마) 
			if (reverse == 1 && time < item_time[i_dv]) {
				if (_kbhit()) {
					char key_in = _getch();
					if (key_in == 'W' || key_in == 'w') { dy++; look = 2; }	// 상 
					if (key_in == 'A' || key_in == 'a') { dx += 2; look = 3; }	// 좌 
					if (key_in == 'S' || key_in == 's') { dy--; look = 0; }	// 하				
					if (key_in == 'D' || key_in == 'd') { dx -= 2; look = 1; }	// 우 
				}
			}
			// 주인공 조작 불가 상태
			else if (trap == 1) {}
			// 주인공 정상 조작(평상시) 
			else {
				if (_kbhit()) {
					char key_in = _getch();
					if (key_in == 'W' || key_in == 'w') { dy--; look = 0; }	// 상 
					if (key_in == 'A' || key_in == 'a') { dx -= 2; look = 1; }	// 좌 
					if (key_in == 'S' || key_in == 's') { dy++; look = 2; }	// 하				
					if (key_in == 'D' || key_in == 'd') { dx += 2; look = 3; }	// 우 
				}
			}

			// 주인공 이동 목표 지점에 벽이 있는지 확인 		
			if (map[dx][dy] == 1) {
				dx = x;
				dy = y;
			}

			// 주인공이 이동 목표 지점으로 이동 
			x = dx;
			y = dy;

			// 주인공 출력
			gotoxy(x, y);
			// 글자색 적용 시작 
			if (star == 1) printf("\033[1;33m");
			else if (damage == 1) printf("\033[1;36m");
			else if (reverse == 1) printf("\033[0;35m");
			else if (sensor == 1) printf("\033[0;32m");
			else printf("\033[0;31m");

			switch (look) {
			case 0: printf("▲"); break;
			case 1: printf("◀"); break;
			case 2: printf("▼"); break;
			case 3: printf("▶"); break;
			}
			printf("\033[0m");	// 글자색 적용 종료 

		// 화면 갱신 
			countdown--;
			Sleep(50);
			system("cls");
		}

		// GAME OVER
		gotoxy(12, 8);
		printf("\033[1;33m");	// 글자색 적용 시작 
		printf("- ＧＡＭＥ ＯＶＥＲ -\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("\033[0m");	// 글자색 적용 종료 
		Sleep(1500);
		_getch();
		continue;
	}
}


// 오브젝트 생성(출력 스타일, 시작X, 시작Y, 끝X, 끝Y) 
void object(char style, int X0, int Y0, int X1, int Y1) {
	for (int i = X0; i <= X1; i += 2) {
		for (int j = Y0; j <= Y1; j++) {
			gotoxy(i, j);
			switch (style) {
			case '0': map[i][j] = 0; break;					// 0 (통행 가능) 
			case 'w': map[i][j] = 1; printf("□"); break; 	// wall(벽) 
			case 'f': map[i][j] = 1; printf("\033[1;30m■\033[0m"); break; 	// frame(테두리) 
			case 'b': map[i][j] = 1; printf("\033[1;36m●\033[0m"); break; 	// bomb(물풍선) 
			case 'h': map[i][j] = 1; printf("\033[0;30m●\033[0m"); break; 	// hidden_bomb(투명 물풍선) 
			case 's': map[i][j] = 2; printf("\033[1;36m▩\033[0m"); break; 	// stream(물줄기) 
			case 'r': map[i][j] = 0; printf("\033[1;32m□\033[0m"); break; 	// range(물줄기 범위 표시)
			}
		}
	}
}

// gotoxy 함수 
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 커서 숨기기 함수 
void cursor(int n) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

