#include "ChessPiece.h"
Pawn::Pawn() { m_NumCode = CHESSPIECE_NUM_PAWN; }
Pawn::Pawn(char ch) : ChessPiece(ch) { m_NumCode = CHESSPIECE_NUM_PAWN;}
Pawn::~Pawn() {}