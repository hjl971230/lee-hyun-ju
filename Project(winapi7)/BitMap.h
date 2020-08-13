#pragma once
#include "Mecro.h"

class BitMap
{
protected:
	HDC MemDC;
	HBITMAP m_pBitMap;
	HBITMAP m_pBitOld;
	SIZE m_size;
public:
	BitMap();
	virtual void Init(HWND hWnd, HINSTANCE hInst) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual ~BitMap();
};

