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
	void Init(HDC hdc, HINSTANCE hInst, HBITMAP hBitMap);
	void Draw(HDC hdc, int x, int y);
	~BitMap();
	inline HDC& getMemDC() { return MemDC; }
	inline SIZE getsize() { return m_size; }
};

