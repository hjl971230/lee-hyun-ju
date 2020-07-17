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

bool Player::Move(vector<vector<int>>& v, Point Exit_Potal[])
{
	char ch;
	ch = getch();
	system("cls");
	if ((ch == W) || (ch == A) || (ch == S) || (ch == D))
	{
		return PlayerMoveCheck(ch, v, Exit_Potal);
	}
}

bool Player::PlayerMoveCheck(char ch, vector<vector<int>>& v, Point Exit_Potal[])
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
	return MovePlayer(v, Exit_Potal);
}

bool Player::MovePlayer(vector<vector<int>>& v, Point Exit_Potal[])
{
	bool tmp = MoveCheck(v, Exit_Potal);
	m_iLastObjectindex = v[CharacterPoint.y][CharacterPoint.x];
	v[CharacterPoint.y][CharacterPoint.x] = CHARACTER;
	return tmp;
}

bool Player::MoveCheck(vector<vector<int>>& v, Point Exit_Potal[])
{
	int index = v[CharacterPoint.y][CharacterPoint.x];

	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)
	{
		CharacterPoint.x = Exit_Potal[index - ENTRY_START].x;
		CharacterPoint.y = Exit_Potal[index - ENTRY_START].y;
	}
	if (index >= RANDOM_START && index < RANDOM_START + POTAL_MAX)
	{
		CharacterPoint.x = Exit_Potal[(rand() % 4) + 0].x;
		CharacterPoint.y = Exit_Potal[(rand() % 4) + 0].y;
	}
	if (index == KEY)
	{
		if (index == WALL)
		{
			v[rand() % 9 + 1][rand() % 9 + 1] = EMPTY;
		}
	}
	if (index == GAMECLEAR)
	{
		cout << "Game Clear";
		return false;
	}

	return true;
}