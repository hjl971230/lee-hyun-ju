#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, HINSTANCE hInst, HBITMAP hBitMap)
{
	MemDC = CreateCompatibleDC(hdc);
	m_pBitMap = hBitMap;
	m_pBitOld = (HBITMAP)SelectObject(MemDC, m_pBitMap);
	BITMAP BitMap_Info;
	//준비된 비트맵의 정보를 가져온다. – width, height
	GetObject(m_pBitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y, float scale_x, float scale_y)
{
	//그려준다.
	//StretchBlt(hdc, x, y, m_size.cx * spX, m_size.cy * spY, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
	TransparentBlt(hdc, x, y, m_size.cx * scale_x, m_size.cy * scale_y, MemDC, 0, 0, m_size.cx, m_size.cy, RGB(0, 0, 0));
}

void BitMap::CutDraw(HDC hdc, int x, int y, int size_x, int size_y, int start_x, int start_y, int end_x, int end_y)
{
	TransparentBlt(hdc, x, y, size_x, size_y, MemDC, start_x, start_y, end_x, end_y, RGB(0, 0, 0));
}

BitMap::~BitMap()
{
	//해제코드를 추가한다.
	SelectObject(MemDC, m_pBitOld);
	DeleteObject(m_pBitMap);
	DeleteDC(MemDC);
}