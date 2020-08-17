#include "BitMap.h"

BitMap::BitMap()
{
	wsprintf(m_szFileName, TEXT("block\0"));
}

//메모리 DC를 생성하고 그림 그릴 준비를 한다.
void BitMap::Init(HWND hWnd, int x, int y)
{
	HDC hdc = GetDC(hWnd);
	MemDC = CreateCompatibleDC(hdc);
	m_pBitMap = (HBITMAP)LoadImage(NULL, m_szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_pBitOld = (HBITMAP)SelectObject(MemDC, m_pBitMap);
	BITMAP BitMap_Info;
	//준비된 비트맵의 정보를 가져온다. – width, height
	GetObject(m_pBitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
	m_Point.x = x;
	m_Point.y = y;
}

void BitMap::Draw(HDC hdc)
{
	//그려준다.
	TransparentBlt(hdc, m_Point.x, m_Point.y, (m_size.cx) / 2, (m_size.cy) / 2, MemDC,
		0,0, (m_size.cx), (m_size.cy),
		RGB(255, 0, 255));
}

BitMap::~BitMap()
{
	//해제코드를 추가한다.
	SelectObject(MemDC, m_pBitOld);
	DeleteObject(m_pBitMap);
	DeleteDC(MemDC);
}