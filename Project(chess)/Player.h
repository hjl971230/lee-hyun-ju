#pragma once
#include"BitMap.h"
#include "ChessPiece.h"

class Player : public BitMap
{
private:
	char m_chPlayerType;
	vector<ChessPiece*> m_vecChessPieces;
public:
	Player();
	~Player();
	inline void setPlayerType(char ch) { m_chPlayerType = ch; }
	void ChessPieceInit(HWND hWnd, int x, int y, int player);
	void ChessPieceNumSetting(int& num, int player, int count);
	void ChessPieceRelease();
	void ChessPieceDraw(HDC hdc);
	ChessPiece* ChessPieceFactory(HWND hWnd, int num, int x, int y);
};

