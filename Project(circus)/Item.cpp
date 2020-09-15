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
	Cash.Draw(hdc, 0, 0);
}