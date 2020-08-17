#include "ChessPiece.h"
Queen::Queen() { m_NumCode = CHESSPIECE_NUM_QUEEN; }
Queen::Queen(char ch) : ChessPiece(ch) { m_NumCode = CHESSPIECE_NUM_QUEEN; }
Queen::~Queen() {}