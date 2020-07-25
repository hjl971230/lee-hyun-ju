#include "Player.h"

Player* Player::m_Player_this = NULL;

Player::Player()
{
	m_stricon = "¢Á";
}

Player::~Player()
{

}

void Player::setPoint(int x, int y)
{
	m_Point.x = x;
	m_Point.y = y;
}

void Player::move(char ch, int Width, int Height)
{
	switch (ch)
	{
	case KEY_UP:
		if (m_Point.y - 1 > 0)
			m_Point.y--;
		break;
	case KEY_DOWN:
		if (m_Point.y + 1 < Height - 1)
			m_Point.y++;
		break;
	case KEY_LEFT:
		if (m_Point.x - 1 > 0)
			m_Point.x--;
		break;
	case KEY_RIGHT:
		if (m_Point.x + 1 < Width - 1)
			m_Point.x++;
		break;
	}
}