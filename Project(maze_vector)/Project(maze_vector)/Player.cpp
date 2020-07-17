#include "Player.h"

Player::Player()
{
	CharacterPoint.x = 0;
	CharacterPoint.y = 0;
	m_iLastObjectindex = 0;
}

Player::~Player()
{
}

bool Player::Move(vector<vector<int>>& v,  Point Exit_Potal[], bool &resetflag)
{
	char ch;
	ch = getch();
	system("cls");
	if ((ch == W) || (ch == A) || (ch == S) || (ch == D))
	{
		return PlayerMoveCheck(ch, v, Exit_Potal, resetflag);
	}
}

bool Player::PlayerMoveCheck(char ch, vector<vector<int>>& v, Point Exit_Potal[], bool &resetflag)
{
	v[CharacterPoint.y][CharacterPoint.x] = m_iLastObjectindex;
	switch (ch)
	{
	case A:
		if (v[CharacterPoint.y][CharacterPoint.x - 1] != WALL)
			CharacterPoint.x--;
		break;
	case D:
		if (v[CharacterPoint.y][CharacterPoint.x + 1] != WALL)
			CharacterPoint.x++;
		break;
	case W:
		if (v[CharacterPoint.y - 1][CharacterPoint.x] != WALL)
			CharacterPoint.y--;
		break;
	case S:
		if (v[CharacterPoint.y + 1][CharacterPoint.x] != WALL)
			CharacterPoint.y++;
		break;
	}
	return MovePlayer(v, Exit_Potal, resetflag);
}

bool Player::MovePlayer(vector<vector<int>>& v,  Point Exit_Potal[], bool &resetflag)
{
	bool tmp = MoveCheck(v, Exit_Potal, resetflag);
	m_iLastObjectindex = v[CharacterPoint.y][CharacterPoint.x];
	v[CharacterPoint.y][CharacterPoint.x] = CHARACTER;
	return tmp;
}

bool Player::MoveCheck(vector<vector<int>>& v,  Point Exit_Potal[], bool &resetflag)
{
	int index = v[CharacterPoint.y][CharacterPoint.x];
	int random = (rand() % 4);
	int deleterandom = (rand() % 9) + 1;
	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)
	{
		CharacterPoint.x = Exit_Potal[index - ENTRY_START].x;
		CharacterPoint.y = Exit_Potal[index - ENTRY_START].y;
	}
	if (index >= RANDOM_START && index < RANDOM_START + POTAL_MAX)
	{
		CharacterPoint.x = Exit_Potal[random].x;
		CharacterPoint.y = Exit_Potal[random].y;
	}
	if (index == KEY)
	{
		if (v[deleterandom][deleterandom] == WALL)
		{
			v[deleterandom][deleterandom] = EMPTY;
		}
	}
	if (index == RESET)
	{
		resetflag = true;
	}
	if (index == GAMECLEAR)
	{
		cout << "Game Clear";
		return false;
	}

	return true;
}