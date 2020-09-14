#pragma once
#include"Mecro.h"
#include"BitMap.h"

class Enemy
{
protected:
	POINT m_point;
	POINT m_halfpoint;
public:
	Enemy();
	virtual void Init() = 0;
	virtual void Move() = 0;
	virtual ~Enemy() = 0;
};

class Ring : public Enemy
{
private:
	vector<vector<BitMap>> RingImage;
public:
	Ring(HDC, HINSTANCE);
	~Ring();
	void Init();
	void Move();
};

class SmallRing : public Enemy
{
private:
	vector<vector<BitMap>> RingImage;
public:
	SmallRing(HDC, HINSTANCE);
	~SmallRing();
	void Init();
	void Move();
};

class Pot : public Enemy
{
private:
	BitMap potImage[2];
public:
	Pot(HDC, HINSTANCE);
	~Pot();
	void Init();
	void Move();
};
