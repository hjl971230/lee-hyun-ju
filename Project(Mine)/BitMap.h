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
	void Draw(HDC hdc, int x, int y, float scale_x = 1, float scale_y = 1);
	void CutDraw(HDC hdc, int x, int y, int size_x, int size_y, int start_x, int start_y, int end_x, int end_y);
	~BitMap();
	inline HDC& getMemDC() { return MemDC; }
	inline SIZE getsize() { return m_size; }
	inline void setsize(SIZE s) { m_size = s; }
};

