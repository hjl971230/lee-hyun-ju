#include "ChessPiece.h"
King::King() { m_iNumCode = CHESSPIECE_NUM_KING; }
King::King(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_KING; }
King::~King() {}

void King::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
{

}

ChessPiece* King::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}