#include"Enemy.h"

SmallRing::SmallRing(HDC hdc, HINSTANCE hInst) : Ring(hdc, hInst)
{
	m_itype_code = ENEMY_CODE_SMALLRING;
	Init(hdc, hInst);
}

SmallRing::~SmallRing()
{

}

void SmallRing::Init(HDC hdc, HINSTANCE hInst)
{
	RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_ORIGIN].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_B].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_b.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_1][RING_IMAGE_TYPE_F].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_f.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_2][RING_IMAGE_TYPE_ORIGIN].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_2][RING_IMAGE_TYPE_B].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy1_b.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	RingImage[RING_IMAGE_2][RING_IMAGE_TYPE_F].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy1_f.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	SmallRingImage[RING_IMAGE_TYPE_ORIGIN].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_l.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	SmallRingImage[RING_IMAGE_TYPE_B].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_l_b.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	SmallRingImage[RING_IMAGE_TYPE_F].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_l_f.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}

void SmallRing::B_Draw(HDC hdc)
{
	SmallRingImage[RING_IMAGE_TYPE_B].Draw(hdc, m_point.x + m_iscroll_move, m_point.y);
}

void SmallRing::F_Draw(HDC hdc)
{
	SmallRingImage[RING_IMAGE_TYPE_F].Draw(hdc, m_point.x + ((SmallRingImage[RING_IMAGE_TYPE_ORIGIN].getsize().cx) / 2) + m_iscroll_move, m_point.y);
}

bool SmallRing::CollideCheck(RECT rt)
{
	RECT Intersect;
	collider = { m_point.x + m_iscroll_move,m_point.y,m_point.x + m_iscroll_move + SmallRingImage[RING_IMAGE_TYPE_ORIGIN].getsize().cx,m_point.y + SmallRingImage[RING_IMAGE_TYPE_ORIGIN].getsize().cy };
	RECT topcollider = { collider.left + 10, collider.top, collider.right - 10, collider.top + 10 };
	RECT bottomcollider = { collider.left + 10, collider.bottom - 10, collider.right - 10, collider.bottom };
	if (IntersectRect(&Intersect, &rt, &topcollider) || IntersectRect(&Intersect, &rt, &bottomcollider))
		return true;
	else if (IntersectRect(&Intersect, &rt, &collider) && (!IntersectRect(&Intersect, &rt, &topcollider) || !IntersectRect(&Intersect, &rt, &bottomcollider)))
	{
		if (!firstcollideflag)
		{
			Player::GetInstance()->setscore(Player::GetInstance()->getscore() + 200);
			firstcollideflag = true;
		}
		return false;
	}
	else return false;
}