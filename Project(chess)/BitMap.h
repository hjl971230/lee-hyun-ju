#pragma once
#include "Mecro.h"

class BitMap
{
protected:
	HDC MemDC;
	HBITMAP m_pBitMap;
	HBITMAP m_pBitOld;
	SIZE m_size;
	TCHAR m_szFileName[128];
	POINT m_Point;
public:
	BitMap();
	virtual void Init(HWND hWnd, int x, int y);
	virtual void Draw(HDC hdc);
	virtual void colorDraw(HDC hdc,int r,int g, int b);
	virtual ~BitMap();
	inline void setFileName(char* sz) { wsprintf(m_szFileName, TEXT(sz)); }
	inline SIZE getsize() { return m_size; }
	inline POINT getPoint() { return m_Point; }
};

