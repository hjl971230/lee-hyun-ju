#include "ChessPiece.h"
Knight::Knight() { m_iNumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::Knight(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::~Knight() {}


void Knight::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
{

}

ChessPiece* Knight::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}