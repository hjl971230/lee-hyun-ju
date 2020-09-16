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
	SmallRingImage[RING_IMAGE_TYPE_ORIGIN].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_l.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	SmallRingImage[RING_IMAGE_TYPE_B].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_l_b.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	SmallRingImage[RING_IMAGE_TYPE_F].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Enemy\\enemy_l_f.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	cash.Init(hdc, hInst);
	cash.Draw(hdc);
}