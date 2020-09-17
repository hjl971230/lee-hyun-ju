#include "Enemy.h"

Ring::Ring(HDC hdc, HINSTANCE hInst)
{
	m_itype_code = ENEMY_CODE_RING;
	Init(hdc, hInst);
}

Ring::~Ring()
{

}

void Ring::Init(HDC hdc, HINSTANCE hInst)
{
	RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_ORIGIN].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_B].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_b.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_F].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_f.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_2][RING_IMAGE_TYPE_ORIGIN].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_2][RING_IMAGE_TYPE_B].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy1_b.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_2][RING_IMAGE_TYPE_F].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy1_f.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}

void Ring::Move()
{
	m_point.x -= 5;
	if (m_point.x <= 0) m_point.x = 7000;
}

void Ring::Draw(HDC hdc)
{
	if (m_simagenum != RING_IMAGE_1) m_simagenum = RING_IMAGE_1;
	else m_simagenum = RING_IMAGE_2;
	RingImage[m_simagenum][RING_IMAGE_TYPE_ORIGIN].Draw(hdc, m_point.x + m_iscroll_move, m_point.y);
}

void Ring::B_Draw(HDC hdc)
{
	RingImage[m_simagenum][RING_IMAGE_TYPE_B].Draw(hdc, m_point.x + m_iscroll_move, m_point.y);
}

void Ring::F_Draw(HDC hdc)
{
	if (m_simagenum != RING_IMAGE_1) m_simagenum = RING_IMAGE_1;
	else m_simagenum = RING_IMAGE_2;
	RingImage[m_simagenum][RING_IMAGE_TYPE_F].Draw(hdc, m_point.x + ((RingImage[m_simagenum][RING_IMAGE_TYPE_ORIGIN].getsize().cx) / 2) + m_iscroll_move, m_point.y);
}

bool Ring::CollideCheck(RECT rt)
{
	RECT Intersect;
	collider = { m_point.x + m_iscroll_move,m_point.y,m_point.x + m_iscroll_move + RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_ORIGIN].getsize().cx,m_point.y + RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_ORIGIN].getsize().cy };
	RECT topcollider = { collider.left + 20, collider.top, collider.right - 20, collider.top + 20 };
	RECT bottomcollider = { collider.left + 20, collider.bottom - 20, collider.right - 20, collider.bottom };
	if (IntersectRect(&Intersect, &rt, &topcollider) || IntersectRect(&Intersect, &rt, &bottomcollider))
		return true;
	else if (IntersectRect(&Intersect, &rt, &collider) && (!IntersectRect(&Intersect, &rt, &topcollider) || !IntersectRect(&Intersect, &rt, &bottomcollider)))
	{
		if (!firstcollideflag)
		{
			Player::GetInstance()->setscore(Player::GetInstance()->getscore() + 100);
			firstcollideflag = true;
		}
		return false;
	}
	else return false;
}