#include "Animal.h"

Animal::Animal()
{
	m_ibmpid = IDB_BITMAP11;
	m_Point.x = 0;
	m_Point.y = 0;
	m_bmatchflag = false;
	m_bClickflag = false;
	m_bcompleteflag = false;
	m_irandcount = MATCH;
}

Animal::~Animal()
{

}

void Animal::Draw(HDC hdc)
{
	StretchBlt(hdc, m_Point.x, m_Point.y, CARD_DRAW_SIZE_X, CARD_DRAW_SIZE_Y, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}