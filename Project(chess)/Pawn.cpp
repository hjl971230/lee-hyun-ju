#include "ChessPiece.h"
Pawn::Pawn() { m_iNumCode = CHESSPIECE_NUM_PAWN; }
Pawn::Pawn(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_PAWN;}
Pawn::~Pawn() {}

void Pawn::MoveCalculate()
{
	BitMap* tmp = new BitMap;
	//������ ��Ʈ�� �����ֱ�
}