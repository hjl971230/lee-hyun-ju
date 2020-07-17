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
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//���� ����
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
#define WALL 1//�迭�� ���� ���� ���� 1
#define EMPTY 0//������ 0
#define Y 0//y�� �̵�
#define X 1//x�� �̵�
#define CHARACTER 2//ĳ���� ���� ��ġ
#define CHARACTER2P 3//ĳ���� ���� ��ġ
#define POTAL_MAX 6//��Ż ����
#define ENTRY_START 10//�Ա� ��Ż�� ���� ��ġ
#define EXIT_START 20//�ⱸ ��Ż�� ���� ��ġ
#define H 104//�� ����Ű �Է°�
#define K 107//�� ����Ű �Է°�
#define U 117//�� ����Ű �Է°�
#define J 106//�� ����Ű �Է°�
#define WIDTH 12//����
#define HEIGHT 12//����
#define RANDOM_START 30//����
#define W 119//2p �����¿�
#define A 97
#define S 115
#define D 100
#define KEY 9
#define GAMEOVER 4
#define RESET 7

int Character[2];//1p x,y
int Character2p[2];//2p x,y
int Entry_Potal[POTAL_MAX][2];//1p �Ա���Ż ��ǥ
int Exit_Potal[POTAL_MAX][2];//1p �ⱸ��Ż ��ǥ
int Random_Potal[POTAL_MAX][2];//1p ������Ż ��ǥ
int Entry_Potal2p[POTAL_MAX][2];//2p �Ա���Ż ��ǥ
int Exit_Potal2p[POTAL_MAX][2];//2p �ⱸ��Ż ��ǥ
int Random_Potal2p[POTAL_MAX][2];//2p ������Ż ��ǥ
int LastObjectindex = EMPTY;//1p ó�� �̵��Ϸ��� ��ġ ������ NULL�� ����
int LastObjectindex2p = EMPTY;//2p ó�� �̵��Ϸ��� ��ġ ������ NULL�� ����
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
				cout << "��";
			}
			else if (v[y][x] >= ENTRY_START && v[y][x] < ENTRY_START + POTAL_MAX)
			{
				BLUE
					cout << "��";
				ORIGINAL
			}
			else if (v[y][x] >= EXIT_START && v[y][x] < EXIT_START + POTAL_MAX)
			{
				YELLOW
					cout << "��";
				ORIGINAL
			}
			else if (v[y][x] == GAMEOVER)
			{
				GRAY
					cout << "��";
				ORIGINAL
			}
			else if (v[y][x] == CHARACTER)
			{
				RED
					cout << "��";
				ORIGINAL
			}
			else if (v[y][x] == CHARACTER2P)
			{
				PUPPLE
					cout << "��";
				ORIGINAL
			}
			else if (v[y][x] >= RANDOM_START && v[y][x] < RANDOM_START + POTAL_MAX)
			{
				GREEN
					cout << "��";
				ORIGINAL
			}
			else if (v[y][x] == KEY)
			{
				SKY_BLUE
					cout << "��";
				ORIGINAL
			}
			else if (v[y][x] == RESET)
			{
				GOLD
					cout << "��";
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
	cout << "��: ��" << endl;

	BLUE
		cout << "��: ��Ż �Ա� " << "\t";
	ORIGINAL

	YELLOW
		cout << "��: ��Ż �ⱸ" << endl;
	ORIGINAL

	RED
		cout << "��: �÷��̾� 1" << "\t";
	ORIGINAL

	PUPPLE
		cout << "��: �÷��̾� 2" << endl;
	ORIGINAL

	GREEN
		cout << "��: ���� ��Ż" << "\t";
	ORIGINAL

	SKY_BLUE
		cout << "��: ���� ����" << endl;
	ORIGINAL

	GOLD
		cout << "��: �ʱ�ȭ" << endl;
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
