#include "ChessPiece.h"

ChessPiece::ChessPiece() {}
ChessPiece::ChessPiece(char ch) : m_chPlayerType(ch) { }
ChessPiece::~ChessPiece(){}

void ChessPiece::FileNameSetting()
{
	sprintf(m_szFileName, "block_%c_0%d.bmp", m_chPlayerType, m_iNumCode);
}