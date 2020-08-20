#include "ChessPiece.h"
Rook::Rook() { m_iNumCode = CHESSPIECE_NUM_ROOK; }
Rook::Rook(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_ROOK; }
Rook::~Rook() {}

void Rook::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)//가로/세로 끝까지 계산
{

}