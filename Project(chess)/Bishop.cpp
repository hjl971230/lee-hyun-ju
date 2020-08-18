#include "ChessPiece.h"
Bishop::Bishop() { m_iNumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::Bishop(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::~Bishop() {}

void Bishop::MoveCalculate()
{

}