#pragma once
#include"mecro.h"
#include"resource.h"

class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_pBitMap;
	HBITMAP m_pBitOld;
	SIZE m_size;
public:
	BitMap();
	virtual ~BitMap();
	void Init(HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);
};

