#include "Item.h"

Item::Item()
{

}

Item::~Item()
{

}

void Item::Init(HDC hdc, HINSTANCE hInst)
{
	Cash.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\cash.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}

void Item::Draw(HDC hdc)
{
	Cash.Draw(hdc, m_point.x, m_point.y);
}

bool Item::CollideCheck(RECT rt)
{
	RECT Intersect;
	RECT collider = { m_point.x,m_point.y,m_point.x + Cash.getsize().cx,m_point.y + Cash.getsize().cy };
	if (IntersectRect(&Intersect, &rt, &collider))
		return true;
	else return false;
}