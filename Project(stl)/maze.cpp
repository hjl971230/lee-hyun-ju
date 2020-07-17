#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<iostream>
#include<vector>

using namespace std;
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
#define WALL 1//배열로 만든 맵중 벽은 1
#define EMPTY 0//공간은 0
#define Y 0//y축 이동
#define X 1//x축 이동
#define CHARACTER 2//캐릭터 시작 위치
#define CHARACTER2P 3//캐릭터 시작 위치
#define POTAL_MAX 6//포탈 갯수
#define ENTRY_START 10//입구 포탈의 시작 위치
#define EXIT_START 20//출구 포탈의 시작 위치
#define H 104//좌 방향키 입력값
#define K 107//우 방향키 입력값
#define U 117//상 방향키 입력값
#define J 106//하 방향키 입력값
#define WIDTH 12//가로
#define HEIGHT 12//세로
#define RANDOM_START 30//랜덤
#define W 119//2p 상하좌우
#define A 97
#define S 115
#define D 100
#define KEY 9
#define GAMEOVER 4
#define RESET 7
int v[HEIGHT][WIDTH]//map[12][12]
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,10,2,0,0,31,1,1,0,0,32,1},
	{1,0,3,0,21,1,0,1,1,0,0,1},
	{1,1,1,1,1,0,1,0,23,14,0,1},
	{1,0,33,0,1,0,1,0,11,0,0,1},
	{1,0,13,25,1,0,1,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,0,9,0,1},
	{1,0,34,0,1,7,1,12,0,1,0,4},
	{1,0,0,0,0,0,1,24,0,0,0,1},
	{1,0,20,0,1,0,1,0,0,1,30,1},
	{1,9,0,0,1,0,1,0,0,22,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};
int Character[2];//1p x,y
int Character2p[2];//2p x,y
int Entry_Potal[POTAL_MAX][2];//1p 입구포탈 좌표
int Exit_Potal[POTAL_MAX][2];//1p 출구포탈 좌표
int Random_Potal[POTAL_MAX][2];//1p 랜덤포탈 좌표
int Entry_Potal2p[POTAL_MAX][2];//2p 입구포탈 좌표
int Exit_Potal2p[POTAL_MAX][2];//2p 출구포탈 좌표
int Random_Potal2p[POTAL_MAX][2];//2p 랜덤포탈 좌표
int LastObjectindex = EMPTY;//1p 처음 이동하려는 위치 정보를 NULL로 저장
int LastObjectindex2p = EMPTY;//2p 처음 이동하려는 위치 정보를 NULL로 저장
int key[2];
int resetmap[HEIGHT][WIDTH]//map[12][12]
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,10,2,0,0,31,1,1,0,0,32,1},
	{1,0,3,0,21,1,0,1,1,0,0,1},
	{1,1,1,1,1,0,1,0,23,14,0,1},
	{1,0,33,0,1,0,1,0,11,0,0,1},
	{1,0,13,25,1,0,1,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,0,9,0,1},
	{1,0,34,0,1,7,1,12,0,1,0,4},
	{1,0,0,0,0,0,1,24,0,0,0,1},
	{1,0,20,0,1,0,1,0,0,1,30,1},
	{1,9,0,0,1,0,1,0,0,22,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};
int ResetCharacter[2];//1p x,y
int ResetCharacter2p[2];//2p x,y
int ResetEntry_Potal[POTAL_MAX][2];//1p 입구포탈 좌표
int ResetExit_Potal[POTAL_MAX][2];//1p 출구포탈 좌표
int ResetRandom_Potal[POTAL_MAX][2];//1p 랜덤포탈 좌표
int ResetEntry_Potal2p[POTAL_MAX][2];//2p 입구포탈 좌표
int ResetExit_Potal2p[POTAL_MAX][2];//2p 출구포탈 좌표
int ResetRandom_Potal2p[POTAL_MAX][2];//2p 랜덤포탈 좌표
int ResetLastObjectindex = EMPTY;//1p 처음 이동하려는 위치 정보를 NULL로 저장
int ResetLastObjectindex2p = EMPTY;//2p 처음 이동하려는 위치 정보를 NULL로 저장
int Resetkey[2];
void Init();
void mapdraw();
void userbook();
void movecheck();
void movecheck2();
void move1p();
void Playermovecheck(char ch);
void move2p();
void Playermovecheck2p(char ch);
void move();
void Reseter();
void Reseter2();
void main()
{
	Init();
	srand(time(EMPTY));
	while (1)
	{
		mapdraw();
		userbook();
		move();
	}
}
void Init() {
	/*int Width = (WIDTH * 2) + 10;
	int Height = HEIGHT + 10;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);*/
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (v[y][x] == CHARACTER)
			{
				Character[X] = x;
				Character[Y] = y;
				ResetCharacter[X] = x;
				ResetCharacter[Y] = y;
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] < ENTRY_START + POTAL_MAX)
			{
				Entry_Potal[v[y][x] - ENTRY_START][X] = x;
				Entry_Potal[v[y][x] - ENTRY_START][Y] = y;
				ResetEntry_Potal[resetmap[y][x] - ENTRY_START][X] = x;
				ResetEntry_Potal[resetmap[y][x] - ENTRY_START][Y] = y;
			}
			else if (v[y][x] >= EXIT_START && v[y][x] < EXIT_START + POTAL_MAX)
			{
				Exit_Potal[v[y][x] - EXIT_START][X] = x;
				Exit_Potal[v[y][x] - EXIT_START][Y] = y;
				ResetExit_Potal[resetmap[y][x] - EXIT_START][X] = x;
				ResetExit_Potal[resetmap[y][x] - EXIT_START][Y] = y;
			}
			else if (v[y][x] >= RANDOM_START && v[y][x] < RANDOM_START + POTAL_MAX)
			{
				Random_Potal[v[y][x] - RANDOM_START][X] = x;
				Random_Potal[v[y][x] - RANDOM_START][Y] = y;
				ResetRandom_Potal[resetmap[y][x] - RANDOM_START][X] = x;
				ResetRandom_Potal[resetmap[y][x] - RANDOM_START][Y] = y;
			}

		}
	}
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (v[y][x] == CHARACTER2P)
			{
				Character2p[X] = x;
				Character2p[Y] = y;
				ResetCharacter2p[X] = x;
				ResetCharacter2p[Y] = y;
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] < ENTRY_START + POTAL_MAX)
			{
				Entry_Potal2p[v[y][x] - ENTRY_START][X] = x;
				Entry_Potal2p[v[y][x] - ENTRY_START][Y] = y;
				ResetEntry_Potal2p[resetmap[y][x] - ENTRY_START][X] = x;
				ResetEntry_Potal2p[resetmap[y][x] - ENTRY_START][Y] = y;
			}
			else if (v[y][x] >= EXIT_START && v[y][x] < EXIT_START + POTAL_MAX)
			{
				Exit_Potal2p[v[y][x] - EXIT_START][X] = x;
				Exit_Potal2p[v[y][x] - EXIT_START][Y] = y;
				ResetExit_Potal2p[resetmap[y][x] - EXIT_START][X] = x;
				ResetExit_Potal2p[resetmap[y][x] - EXIT_START][Y] = y;
			}
			else if (v[y][x] >= RANDOM_START && v[y][x] < RANDOM_START + POTAL_MAX)
			{
				Random_Potal2p[v[y][x] - RANDOM_START][X] = x;
				Random_Potal2p[v[y][x] - RANDOM_START][Y] = y;
				ResetRandom_Potal2p[resetmap[y][x] - RANDOM_START][X] = x;
				ResetRandom_Potal2p[resetmap[y][x] - RANDOM_START][Y] = y;
			}

		}
	}

}
void mapdraw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (v[y][x] == WALL)
			{
				printf("▩");
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] < ENTRY_START + POTAL_MAX)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (v[y][x] >= EXIT_START && v[y][x] < EXIT_START + POTAL_MAX)
			{
				YELLOW
					printf("●");
				ORIGINAL
			}
			else if (v[y][x] == GAMEOVER)
			{
				GRAY
					printf("◎");
				ORIGINAL
			}
			else if (v[y][x] == CHARACTER)
			{
				RED
					printf("♠");
				ORIGINAL
			}
			else if (v[y][x] == CHARACTER2P)
			{
				PUPPLE
					printf("♣");
				ORIGINAL
			}
			else if (v[y][x] >= RANDOM_START && v[y][x] < RANDOM_START + POTAL_MAX)
			{
				GREEN
					printf("●");
				ORIGINAL
			}
			else if (v[y][x] == KEY)
			{
				SKY_BLUE
					printf("★");
				ORIGINAL
			}
			else if (v[y][x] == RESET)
			{
				GOLD
					printf("★");
				ORIGINAL
			}
			else if (v[y][x] == EMPTY)
				printf("  ");
		}
		printf("\n");
	}
}
void userbook()
{
	printf("▩: 벽\n");

	BLUE
		printf("◎: 포탈 입구\t");
	ORIGINAL

		YELLOW
		printf("●: 포탈 출구\n");
	ORIGINAL

		RED
		printf("♠: 플레이어 1\t");
	ORIGINAL

		PUPPLE
		printf("♣: 플레이어 2\n");
	ORIGINAL

		GREEN
		printf("●: 랜덤 포탈\t");
	ORIGINAL

		SKY_BLUE
		printf("★: 랜덤 삭제\n");
	ORIGINAL

		GOLD
		printf("★: 초기화\n");
	ORIGINAL

}
void move()
{
	char ch;
	ch = getch();
	system("cls");
	if ((ch == U) || (ch == H) || (ch == J) || (ch == K))
	{
		Playermovecheck(ch);
	}
	else if ((ch == W) || (ch == A) || (ch == S) || (ch == D))
	{
		Playermovecheck2p(ch);
	}
}
void Playermovecheck(char ch)
{
	switch (ch)
	{
	case H:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y]][Character[X] - 1] != WALL) && (v[Character[Y]][Character[X] - 1] != CHARACTER2P))
			Character[X]--;
		move1p();

		break;
	case K:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y]][Character[X] + 1] != WALL) && (v[Character[Y]][Character[X] + 1] != CHARACTER2P))
			Character[X]++;
		move1p();
		break;
	case U:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y] - 1][Character[X]] != WALL) && (v[Character[Y] - 1][Character[X]] != CHARACTER2P))
			Character[Y]--;
		move1p();
		break;
	case J:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y] + 1][Character[X]] != WALL) && (v[Character[Y] + 1][Character[X]] != CHARACTER2P))
			Character[Y]++;
		move1p();
		break;
	}

}
void Playermovecheck2p(char ch)
{
	switch (ch)
	{
	case A:
		v[Character2p[Y]][Character2p[X]] = LastObjectindex2p;
		if ((v[Character2p[Y]][Character2p[X] - 1] != WALL) && (v[Character2p[Y]][Character2p[X] - 1] != CHARACTER))
			Character2p[X]--;
		move2p();
		break;
	case D:
		v[Character2p[Y]][Character2p[X]] = LastObjectindex2p;
		if ((v[Character2p[Y]][Character2p[X] + 1] != WALL) && (v[Character2p[Y]][Character2p[X] + 1] != CHARACTER))
			Character2p[X]++;
		move2p();
		break;
	case W:
		v[Character2p[Y]][Character2p[X]] = LastObjectindex2p;
		if ((v[Character2p[Y] - 1][Character2p[X]] != WALL) && (v[Character2p[Y] - 1][Character2p[X]] != CHARACTER))
			Character2p[Y]--;
		move2p();
		break;
	case S:
		v[Character2p[Y]][Character2p[X]] = LastObjectindex2p;
		if ((v[Character2p[Y] + 1][Character2p[X]] != WALL) && (v[Character2p[Y] + 1][Character2p[X]] != CHARACTER))
			Character2p[Y]++;
		move2p();
		break;
	}
}
void move1p()
{
	movecheck();
	LastObjectindex = v[Character[Y]][Character[X]];
	v[Character[Y]][Character[X]] = CHARACTER;
}
void move2p() {
	movecheck2();
	LastObjectindex2p = v[Character2p[Y]][Character2p[X]];
	v[Character2p[Y]][Character2p[X]] = CHARACTER2P;
}
void movecheck()
{
	int index = v[Character[Y]][Character[X]];

	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)
	{
		Character[X] = Exit_Potal[index - ENTRY_START][X];
		Character[Y] = Exit_Potal[index - ENTRY_START][Y];

	}
	if (index >= RANDOM_START && index < RANDOM_START + POTAL_MAX)
	{
		Character[X] = Exit_Potal[(rand() % 4) + 0][X];
		Character[Y] = Exit_Potal[(rand() % 4) + 0][Y];

	}
	if (index == KEY)
	{
		if (index != EMPTY)
		{
			v[rand() % 11][rand() % 11] = EMPTY;

		}
	}
	if (index == RESET) {
		Reseter();
	}
	if (index == GAMEOVER)
	{
		printf("Game Over");
		exit(0);
	}
}
void movecheck2()
{
	int index2 = v[Character2p[Y]][Character2p[X]];
	if (index2 >= ENTRY_START && index2 < ENTRY_START + POTAL_MAX)
	{
		Character2p[X] = Exit_Potal2p[index2 - ENTRY_START][X];
		Character2p[Y] = Exit_Potal2p[index2 - ENTRY_START][Y];

	}
	if (index2 >= RANDOM_START && index2 < RANDOM_START + POTAL_MAX)
	{
		Character2p[X] = Exit_Potal2p[(rand() % 4) + 0][X];
		Character2p[Y] = Exit_Potal2p[(rand() % 4) + 0][Y];

	}
	if (index2 == KEY)
	{
		if (index2 != EMPTY)
			v[rand() % 11][rand() % 11] = EMPTY;

	}
	if (index2 == RESET) {
		Reseter2();
	}
	if (index2 == GAMEOVER)
	{
		printf("Game Over");
		exit(0);
	}
}
void Reseter()
{
	Character[X] = ResetCharacter[X];
	Character[Y] = ResetCharacter[Y];
	LastObjectindex = ResetLastObjectindex;
	v[Character[Y]][Character[X]] = resetmap[ResetCharacter[Y]][ResetCharacter[X]];
	v[Character[Y]][Character[X]] = LastObjectindex;
	LastObjectindex = v[Character[Y]][Character[X]];
	v[Character[Y]][Character[X]] = CHARACTER;
	resetmap[ResetCharacter[Y]][ResetCharacter[X]] = ResetLastObjectindex;
	ResetLastObjectindex = resetmap[ResetCharacter[Y]][ResetCharacter[X]];
	resetmap[ResetCharacter[Y]][ResetCharacter[X]] = CHARACTER;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (resetmap[y][x] == CHARACTER)
			{
				resetmap[y][x] = EMPTY;
			}
			v[y][x] = resetmap[y][x];
		}
	}
}
void Reseter2()
{
	Character2p[X] = ResetCharacter2p[X];
	Character2p[Y] = ResetCharacter2p[Y];
	LastObjectindex2p = ResetLastObjectindex2p;
	v[Character2p[Y]][Character2p[X]] = resetmap[ResetCharacter2p[Y]][ResetCharacter2p[X]];
	v[Character2p[Y]][Character2p[X]] = LastObjectindex2p;
	LastObjectindex2p = v[Character2p[Y]][Character2p[X]];
	v[Character2p[Y]][Character2p[X]] = CHARACTER2P;
	resetmap[ResetCharacter2p[Y]][ResetCharacter2p[X]] = ResetLastObjectindex2p;
	ResetLastObjectindex2p = resetmap[ResetCharacter2p[Y]][ResetCharacter2p[X]];
	resetmap[ResetCharacter2p[Y]][ResetCharacter2p[X]] = CHARACTER2P;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (resetmap[y][x] == CHARACTER2P)
			{
				resetmap[y][x] = EMPTY;
			}

			v[y][x] = resetmap[y][x];
		}
	}
}