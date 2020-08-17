#include "ChessPiece.h"
Rook::Rook() { m_NumCode = CHESSPIECE_NUM_ROOK; }
Rook::Rook(char ch) : ChessPiece(ch) { m_NumCode = CHESSPIECE_NUM_ROOK; }
Rook::~Rook() {}