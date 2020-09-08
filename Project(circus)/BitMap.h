#pragma once
#include "Mecro.h"

class BitMap
{
protected:
	HDC MemDC[OBJECT_MAX];
	HBITMAP m_pBitMap[OBJECT_MAX];
	HBITMAP m_pBitOld[OBJECT_MAX];
	SIZE m_size;
public:
	BitMap();
	virtual void Init(HDC hdc, HINSTANCE hInst);
	virtual void Draw(HDC hdc);
	virtual ~BitMap();
};

