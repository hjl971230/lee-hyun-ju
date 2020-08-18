#include "ChessPiece.h"
Queen::Queen() { m_iNumCode = CHESSPIECE_NUM_QUEEN; }
Queen::Queen(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_QUEEN; }
Queen::~Queen() {}

void Queen::MoveCalculate()
{

}