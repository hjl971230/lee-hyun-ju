#include "ChessPiece.h"
Bishop::Bishop() { m_NumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::Bishop(char ch) : ChessPiece(ch) { m_NumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::~Bishop() {}