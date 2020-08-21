#pragma once
#include"Player.h"
#include"ChessPiece.h"

class GameManager
{
private:
	static GameManager* m_this;
	vector<vector<BitMap>> m_map;
	vector<vector<ChessPiece*>> m_vecChessPieces;
	vector<ChessPiece*> m_vecPiecesCemetery[PLAYERSIZE];
	bool m_bClickflag;
	bool m_bmoveflag;
	char m_chturn;
	ChessPiece* m_SelectPiece;
	int m_iblackdeathcount;
	int m_iwhitedeathcount;
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
	void ChessPieceInit(HWND hWnd);
	void ChessPieceNumSetting(int& num, int player, int count);
	void ChessPieceRelease();
	void ChessPieceDraw(HDC hdc);
	ChessPiece* ChessPieceFactory(HWND hWnd, int num, int x, int y, int player);
	bool SelectPiece(HWND hWnd, int x, int y);
	bool MovePiece(HWND hWnd, int x, int y);
	void CalculateDraw(HWND hWnd);
	inline ChessPiece* getSelectPiece() { return m_SelectPiece; }
	void PiecesCemeteryinit();
	void GotoCemetery(ChessPiece*);
};

