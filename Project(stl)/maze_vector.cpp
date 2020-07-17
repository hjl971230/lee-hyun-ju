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

void Init(vector<vector<int>>& v) {
	/*int Width = (WIDTH * 2) + 10;
	int Height = HEIGHT + 10;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);*/

	v =
	{
		{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
		{WALL, ENTRY_START, CHARACTER, EMPTY, EMPTY, RANDOM_START + 1, WALL, WALL, EMPTY, EMPTY, RANDOM_START + 2, WALL},
		{WALL, EMPTY, CHARACTER2P, EMPTY, EXIT_START + 1, WALL, EMPTY, WALL, WALL, EMPTY, EMPTY, WALL},
		{WALL, WALL, WALL, WALL, WALL, EMPTY, WALL, EMPTY, EXIT_START + 3, ENTRY_START + 4, EMPTY, WALL},
		{WALL, EMPTY, RANDOM_START + 3, EMPTY, WALL, EMPTY, WALL, EMPTY, ENTRY_START + 1, EMPTY, EMPTY, WALL},
		{WALL, EMPTY, ENTRY_START + 3, EXIT_START + 5, WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL},
		{WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, KEY, EMPTY, WALL},
		{WALL, EMPTY, RANDOM_START + 4, EMPTY, WALL, RESET, WALL, ENTRY_START + 2, EMPTY, WALL, EMPTY, GAMEOVER},
		{WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EXIT_START + 4, EMPTY, EMPTY, EMPTY, WALL},
		{WALL, EMPTY, EXIT_START, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, WALL, RANDOM_START, WALL},
		{WALL, KEY, EMPTY, EMPTY, WALL, EMPTY, WALL, EMPTY, EMPTY, EXIT_START + 2, EMPTY, WALL},
		{WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
	};

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (v[y][x] == CHARACTER)
			{
				Character[X] = x;
				Character[Y] = y;
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] < ENTRY_START + POTAL_MAX)
			{
				Entry_Potal[v[y][x] - ENTRY_START][X] = x;
				Entry_Potal[v[y][x] - ENTRY_START][Y] = y;
			}
			else if (v[y][x] >= EXIT_START && v[y][x] < EXIT_START + POTAL_MAX)
			{
				Exit_Potal[v[y][x] - EXIT_START][X] = x;
				Exit_Potal[v[y][x] - EXIT_START][Y] = y;
			}
			else if (v[y][x] >= RANDOM_START && v[y][x] < RANDOM_START + POTAL_MAX)
			{
				Random_Potal[v[y][x] - RANDOM_START][X] = x;
				Random_Potal[v[y][x] - RANDOM_START][Y] = y;
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
				//ResetCharacter2p[X] = x;
				//ResetCharacter2p[Y] = y;
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] < ENTRY_START + POTAL_MAX)
			{
				Entry_Potal2p[v[y][x] - ENTRY_START][X] = x;
				Entry_Potal2p[v[y][x] - ENTRY_START][Y] = y;
				//ResetEntry_Potal2p[resetmap[y][x] - ENTRY_START][X] = x;
				//ResetEntry_Potal2p[resetmap[y][x] - ENTRY_START][Y] = y;
			}
			else if (v[y][x] >= EXIT_START && v[y][x] < EXIT_START + POTAL_MAX)
			{
				Exit_Potal2p[v[y][x] - EXIT_START][X] = x;
				Exit_Potal2p[v[y][x] - EXIT_START][Y] = y;
				//ResetExit_Potal2p[resetmap[y][x] - EXIT_START][X] = x;
				//ResetExit_Potal2p[resetmap[y][x] - EXIT_START][Y] = y;
			}
			else if (v[y][x] >= RANDOM_START && v[y][x] < RANDOM_START + POTAL_MAX)
			{
				Random_Potal2p[v[y][x] - RANDOM_START][X] = x;
				Random_Potal2p[v[y][x] - RANDOM_START][Y] = y;
				//ResetRandom_Potal2p[resetmap[y][x] - RANDOM_START][X] = x;
				//ResetRandom_Potal2p[resetmap[y][x] - RANDOM_START][Y] = y;
			}

		}
	}
}

void mapdraw(vector<vector<int>> v)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (v[y][x] == WALL)
			{
				cout << "▩";
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] < ENTRY_START + POTAL_MAX)
			{
				BLUE
					cout << "◎";
				ORIGINAL
			}
			else if (v[y][x] >= EXIT_START && v[y][x] < EXIT_START + POTAL_MAX)
			{
				YELLOW
					cout << "●";
				ORIGINAL
			}
			else if (v[y][x] == GAMEOVER)
			{
				GRAY
					cout << "◎";
				ORIGINAL
			}
			else if (v[y][x] == CHARACTER)
			{
				RED
					cout << "♠";
				ORIGINAL
			}
			else if (v[y][x] == CHARACTER2P)
			{
				PUPPLE
					cout << "♣";
				ORIGINAL
			}
			else if (v[y][x] >= RANDOM_START && v[y][x] < RANDOM_START + POTAL_MAX)
			{
				GREEN
					cout << "●";
				ORIGINAL
			}
			else if (v[y][x] == KEY)
			{
				SKY_BLUE
					cout << "★";
				ORIGINAL
			}
			else if (v[y][x] == RESET)
			{
				GOLD
					cout << "★";
				ORIGINAL
			}
			else if (v[y][x] == EMPTY)
				cout << "  ";
		}
		cout << endl;
	}
}

void userbook()
{
	cout << "▩: 벽" << endl;

	BLUE
		cout << "◎: 포탈 입구 " << "\t";
	ORIGINAL

	YELLOW
		cout << "●: 포탈 출구" << endl;
	ORIGINAL

	RED
		cout << "♠: 플레이어 1" << "\t";
	ORIGINAL

	PUPPLE
		cout << "♣: 플레이어 2" << endl;
	ORIGINAL

	GREEN
		cout << "●: 랜덤 포탈" << "\t";
	ORIGINAL

	SKY_BLUE
		cout << "★: 랜덤 삭제" << endl;
	ORIGINAL

	GOLD
		cout << "★: 초기화" << endl;
	ORIGINAL

}

void movecheck(vector<vector<int>>& v)
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
	if (index == GAMEOVER)
	{
		cout << "Game Over";
		exit(0);
	}
}

void move1p(vector<vector<int>>& v)
{
	movecheck(v);
	LastObjectindex = v[Character[Y]][Character[X]];
	v[Character[Y]][Character[X]] = CHARACTER;
}

void Playermovecheck(char ch, vector<vector<int>>& v)
{
	switch (ch)
	{
	case H:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y]][Character[X] - 1] != WALL) && (v[Character[Y]][Character[X] - 1] != CHARACTER2P))
			Character[X]--;
		move1p(v);
		break;
	case K:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y]][Character[X] + 1] != WALL) && (v[Character[Y]][Character[X] + 1] != CHARACTER2P))
			Character[X]++;
		move1p(v);
		break;
	case U:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y] - 1][Character[X]] != WALL) && (v[Character[Y] - 1][Character[X]] != CHARACTER2P))
			Character[Y]--;
		move1p(v);
		break;
	case J:
		v[Character[Y]][Character[X]] = LastObjectindex;
		if ((v[Character[Y] + 1][Character[X]] != WALL) && (v[Character[Y] + 1][Character[X]] != CHARACTER2P))
			Character[Y]++;
		move1p(v);
		break;
	}

}

void move(vector<vector<int>>& v)
{
	char ch;
	ch = getch();
	system("cls");
	if ((ch == U) || (ch == H) || (ch == J) || (ch == K))
	{
		Playermovecheck(ch, v);
	}
	else if ((ch == W) || (ch == A) || (ch == S) || (ch == D))
	{
		Playermovecheck(ch, v);
	}
}

void main()
{
	vector<vector<int>> map(12, vector<int>(12));
	map.reserve(12);
	Init(map);
	vector<vector<int>> resetmap(map);
	srand(time(NULL));

	while (1)
	{
		mapdraw(map);
		userbook();
		move(map);
	}
}
