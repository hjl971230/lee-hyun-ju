#pragma once
#include"Mecro.h"

class Bitmap
{
protected:
	HDC MemDC;
	HBITMAP m_pBitMap;
	HBITMAP m_pBitOld;
	SIZE m_size;
public:
	Bitmap();
	void Init(HDC hdc, HINSTANCE hInst, int id);
	//void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);
	virtual ~Bitmap();
};

