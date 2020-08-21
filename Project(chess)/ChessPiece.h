#pragma once
#include"BitMap.h"

class ChessPiece : public BitMap
{
protected:
	char m_chPlayerType;
	int m_iNumCode;
	bool m_bClickflag;
public:
	ChessPiece();
	ChessPiece(char ch);
	~ChessPiece();
	void FileNameSetting();
	virtual void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec) = 0;
	virtual ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag) = 0;
	void CalculateDraw(HWND hWnd, TCHAR FileName[128], int x, int y, bool flag);
	inline char getPlayerType() { return m_chPlayerType; }
	inline void setClickflag(bool b) { m_bClickflag = b; }
	inline bool getClickflag() { return m_bClickflag; }
};

class Pawn : public ChessPiece
{
private:
	bool m_bfirstmoveflag;
public:
	Pawn();
	Pawn(char ch);
	~Pawn();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag);
};

class Knight : public ChessPiece
{
private:

public:
	Knight();
	Knight(char ch);
	~Knight();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag);
};

class Bishop : public ChessPiece
{
private:

public:
	Bishop();
	Bishop(char ch);
	~Bishop();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag);
};

class Rook : public ChessPiece
{
private:

public:
	Rook();
	Rook(char ch);
	~Rook();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag);
};

class Queen : public ChessPiece
{
private:

public:
	Queen();
	Queen(char ch);
	~Queen();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag);
};

class King : public ChessPiece
{
private:

public:
	King();
	King(char ch);
	~King();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag);
};
