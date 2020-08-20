#include "ChessPiece.h"

ChessPiece::ChessPiece() {}
ChessPiece::ChessPiece(char ch) : m_chPlayerType(ch) { m_bClickflag = false; }
ChessPiece::~ChessPiece(){}

void ChessPiece::FileNameSetting()
{
	sprintf(m_szFileName, "block_%c_0%d.bmp", m_chPlayerType, m_iNumCode);
}

void ChessPiece::CalculateDraw(HWND hWnd, TCHAR FileName[128], int x, int y, bool flag)
{
	BitMap* tmp = NULL;
	tmp = new BitMap;
	tmp->setFileName(FileName);
	tmp->Init(hWnd, x, y);
	if(flag) 
		tmp->Draw(GetDC(hWnd));
	else
	{
		if(m_chPlayerType == BLACK) tmp->colorDraw(GetDC(hWnd), 255, 255, 255);
		else tmp->colorDraw(GetDC(hWnd), 0, 0, 0);
	}
		
	delete tmp;
}