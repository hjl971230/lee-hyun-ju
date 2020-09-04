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
	virtual void Init(HDC hdc, HINSTANCE hInst) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual ~BitMap();
};

