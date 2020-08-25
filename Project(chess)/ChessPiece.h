#pragma once
#include"BitMap.h"

class ChessPiece : public BitMap
{
protected:
	char m_chPlayerType;
	int m_iNumCode;
	bool m_bClickflag;
	bool m_bPromotionflag;
	bool m_bfirstmoveflag;
	bool m_bcheckedflag;
public:
	ChessPiece();
	ChessPiece(char ch);
	~ChessPiece();
	void FileNameSetting();
	virtual void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec) = 0;
	virtual void Check(HWND hWnd, vector<vector<ChessPiece*>>& vec) = 0;
	virtual ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag) = 0;
	void CalculateDraw(HWND hWnd, TCHAR FileName[128], int x, int y, bool flag);
	ChessPiece* movefunc(int change_x, int change_y,
		vector<vector<ChessPiece*>>& vec, int index_x, int index_y, int change_index_x, int change_index_y, bool& flag);
	inline char getPlayerType() { return m_chPlayerType; }
	inline void setClickflag(bool b) { m_bClickflag = b; }
	inline bool getClickflag() { return m_bClickflag; }
	inline int getNumCode() { return m_iNumCode; }
	inline bool getpromotionflag() { return m_bPromotionflag; }
	inline void setfirstmoveflag(bool b) { m_bfirstmoveflag = b; }
	inline bool getfirstmoveflag() { return m_bfirstmoveflag; }
	inline void setcheckedflag(bool b) { m_bcheckedflag = b; }
	inline bool getcheckedflag() { return m_bcheckedflag; }
	int Promotion(HWND hWnd, vector<vector<ChessPiece*>> vec);
	bool CheckMatecheck(vector<vector<ChessPiece*>> vec);
	bool RookCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y);
	bool BishopCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y);
	bool KnightCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y);
	bool PawnCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y);
};

class Pawn : public ChessPiece
{
private:
	
public:
	Pawn();
	Pawn(char ch);
	~Pawn();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag);
	void Check(HWND hWnd, vector<vector<ChessPiece*>>& vec);
};

class Knight : public ChessPiece
{
private:

public:
	Knight();
	Knight(char ch);
	~Knight();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag);
	void Check(HWND hWnd, vector<vector<ChessPiece*>>& vec);
};

class Bishop : public ChessPiece
{
private:

public:
	Bishop();
	Bishop(char ch);
	~Bishop();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag);
	void Check(HWND hWnd, vector<vector<ChessPiece*>>& vec);
};

class Rook : public ChessPiece
{
private:

public:
	Rook();
	Rook(char ch);
	~Rook();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag);
	void Check(HWND hWnd, vector<vector<ChessPiece*>>& vec);
};

class Queen : public ChessPiece
{
private:

public:
	Queen();
	Queen(char ch);
	~Queen();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag);
	void Check(HWND hWnd, vector<vector<ChessPiece*>>& vec);
};

class King : public ChessPiece
{
private:

public:
	King();
	King(char ch);
	~King();
	void MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec);
	ChessPiece* Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag);
	void Check(HWND hWnd, vector<vector<ChessPiece*>>& vec);
};
