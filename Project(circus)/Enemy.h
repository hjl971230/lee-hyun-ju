#pragma once
#include"Mecro.h"
#include"BitMap.h"

class Enemy
{
protected:
	POINT m_point;
	POINT m_halfpoint;
	int m_itype_code;
public:
	Enemy();
	virtual void Init(HDC, HINSTANCE) = 0;
	virtual void Move() = 0;
	virtual bool CollideCheck() = 0;
	void Update();
	virtual ~Enemy() = 0;
};

class Ring : public Enemy
{
private:
	BitMap RingImage[2][3];
public:
	Ring(HDC, HINSTANCE);
	~Ring();
	void Init(HDC, HINSTANCE);
	void Move();
	bool CollideCheck();
};

class SmallRing : public Enemy
{
private:
	BitMap RingImage[2][3];
public:
	SmallRing(HDC, HINSTANCE);
	~SmallRing();
	void Init(HDC, HINSTANCE);
	void Move();
	bool CollideCheck();
};

class Pot : public Enemy
{
private:
	BitMap potImage[2];
public:
	Pot(HDC, HINSTANCE);
	~Pot();
	void Init(HDC, HINSTANCE);
	void Move();
	bool CollideCheck();
};
