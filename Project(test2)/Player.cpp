#include "Player.h"

Player* Player::m_Player_this = NULL;

Player::Player()
{

}

Player::~Player()
{

}

void Player::setPoint(int x, int y)
{
	m_Point.x = x;
	m_Point.y = y;
}

void Player::move(vector<vector<int>> vecmap)
{
	char ch = getch();
	switch (ch)
	{
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case KEY_ENTER:
		break;
	case KEY_SPACE:
		break;
	default:
		break;
	}
}