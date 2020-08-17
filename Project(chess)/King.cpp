#include "ChessPiece.h"
King::King() { m_NumCode = CHESSPIECE_NUM_KING; }
King::King(char ch) : ChessPiece(ch) { m_NumCode = CHESSPIECE_NUM_KING; }
King::~King() {}