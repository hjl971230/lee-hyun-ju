#include "ChessPiece.h"

ChessPiece::ChessPiece() {}
ChessPiece::ChessPiece(char ch) : m_chPlayerType(ch) { }
ChessPiece::~ChessPiece(){}

void ChessPiece::FileNameSetting()
{
	sprintf(m_szFileName, "block_%c_0%d.bmp", m_chPlayerType, m_iNumCode);
}

void ChessPiece::CalculateDraw(HWND hWnd, TCHAR FileName[128], int x, int y)
{
	BitMap* tmp = NULL;
	tmp = new BitMap;
	tmp->setFileName(FileName);
	tmp->Init(hWnd, x, y);
	tmp->Draw(GetDC(hWnd));
	delete tmp;
}