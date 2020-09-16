#include "Enemy.h"

Pot::Pot(HDC hdc, HINSTANCE hInst)
{
	m_itype_code = ENEMY_CODE_POT;
	Init(hdc, hInst);
}

Pot::~Pot()
{

}

void Pot::Init(HDC hdc, HINSTANCE hInst)
{
	potImage[POT_IMAGE_1].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\front.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	potImage[POT_IMAGE_2].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\front2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}

void Pot::Draw(HDC hdc)
{
	if (m_simagenum != POT_IMAGE_1) m_simagenum = POT_IMAGE_1;
	else m_simagenum = POT_IMAGE_2;
	potImage[m_simagenum].Draw(hdc, m_point.x + m_iscroll_move, m_point.y);
}

void Pot::Move()
{
	
}

void Pot::B_Draw(HDC hdc)
{
	
}

void Pot::F_Draw(HDC hdc)
{
	
}

bool Pot::CollideCheck(RECT rt)
{
	RECT Intersect;
	collider = { m_point.x + m_iscroll_move,m_point.y,m_point.x + m_iscroll_move + potImage[POT_IMAGE_1].getsize().cx,m_point.y + potImage[POT_IMAGE_1].getsize().cy };
	if (IntersectRect(&Intersect, &rt, &collider))
		return true;
	else return false;
}