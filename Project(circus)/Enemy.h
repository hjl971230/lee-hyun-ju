#pragma once
#include"Mecro.h"
#include"BitMap.h"

class Enemy
{
protected:
	int m_ix;
	int m_iy;
public:
	Enemy();
	virtual void Move() = 0;
	virtual ~Enemy();
};

class Ring : public Enemy
{
private:
public:
	Ring();
	~Ring();
};

class SmallRing : public Enemy
{
private:
public:
	SmallRing();
	~SmallRing();
};

class Pot : public Enemy
{
private:
public:
	Pot();
	~Pot();
};
