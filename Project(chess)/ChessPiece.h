#pragma once
#include"BitMap.h"

class ChessPiece : public BitMap
{
protected:
	char m_chPlayerType;
	int m_iNumCode;
public:
	ChessPiece();
	ChessPiece(char ch);
	~ChessPiece();
	void FileNameSetting();
	virtual void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec) = 0;
	void CalculateDraw(HWND hWnd, TCHAR FileName[128], int x, int y);
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
};

class Knight : public ChessPiece
{
private:

public:
	Knight();
	Knight(char ch);
	~Knight();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
};

class Bishop : public ChessPiece
{
private:

public:
	Bishop();
	Bishop(char ch);
	~Bishop();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
};

class Rook : public ChessPiece
{
private:

public:
	Rook();
	Rook(char ch);
	~Rook();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
};

class Queen : public ChessPiece
{
private:

public:
	Queen();
	Queen(char ch);
	~Queen();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
};

class King : public ChessPiece
{
private:

public:
	King();
	King(char ch);
	~King();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
};
