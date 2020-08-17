#pragma once
#include"BitMap.h"

class ChessPiece : public BitMap
{
protected:
	char m_chPlayerType;
	int m_NumCode;
public:
	ChessPiece();
	ChessPiece(char ch);
	~ChessPiece();
	void FileNameSetting();
};

class Pawn : public ChessPiece
{
private:
	
public:
	Pawn();
	Pawn(char ch);
	~Pawn();
};

class Knight : public ChessPiece
{
private:

public:
	Knight();
	Knight(char ch);
	~Knight();
};

class Bishop : public ChessPiece
{
private:

public:
	Bishop();
	Bishop(char ch);
	~Bishop();
};

class Rook : public ChessPiece
{
private:

public:
	Rook();
	Rook(char ch);
	~Rook();
};

class Queen : public ChessPiece
{
private:

public:
	Queen();
	Queen(char ch);
	~Queen();
};

class King : public ChessPiece
{
private:

public:
	King();
	King(char ch);
	~King();
};
