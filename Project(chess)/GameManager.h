#pragma once
#include"Player.h"
#include"ChessPiece.h"

class GameManager
{
private:
	static GameManager* m_this;
	vector<vector<BitMap>> m_map;
	vector<vector<ChessPiece*>> m_vecChessPieces;
	//vector<Player> m_Playervec;
public:
	static inline GameManager* GetInstance()
	{
		if (m_this == NULL) m_this = new GameManager;
		return m_this;
	}
	GameManager();
	~GameManager();
	void GameInit(HWND hWnd);
	void MapInit(HWND hWnd);
	void MapRelease();
	void MapDraw(HDC hdc);
    //void PlayerInit(HWND hWnd);
	//void PieceDraw(HDC hdc);
	void ChessPieceInit(HWND hWnd);
	void ChessPieceNumSetting(int& num, int player, int count);
	void ChessPieceRelease();
	void ChessPieceDraw(HDC hdc);
	ChessPiece* ChessPieceFactory(HWND hWnd, int num, int x, int y, int player);
};

