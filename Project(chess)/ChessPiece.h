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
	virtual void MoveCalculate() = 0;
};

class Pawn : public ChessPiece
{
private:
	
public:
	Pawn();
	Pawn(char ch);
	~Pawn();
	void MoveCalculate();
};

class Knight : public ChessPiece
{
private:

public:
	Knight();
	Knight(char ch);
	~Knight();
	void MoveCalculate();
};

class Bishop : public ChessPiece
{
private:

public:
	Bishop();
	Bishop(char ch);
	~Bishop();
	void MoveCalculate();
};

class Rook : public ChessPiece
{
private:

public:
	Rook();
	Rook(char ch);
	~Rook();
	void MoveCalculate();
};

class Queen : public ChessPiece
{
private:

public:
	Queen();
	Queen(char ch);
	~Queen();
	void MoveCalculate();
};

class King : public ChessPiece
{
private:

public:
	King();
	King(char ch);
	~King();
	void MoveCalculate();
};
