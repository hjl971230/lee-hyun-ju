#include "ChessPiece.h"
Knight::Knight() { m_NumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::Knight(char ch) : ChessPiece(ch) { m_NumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::~Knight() {}
