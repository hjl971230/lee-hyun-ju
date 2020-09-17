#pragma once
#include"Player.h"

class Enemy
{
protected:
	POINT m_point;
	POINT m_halfpoint;
	int m_itype_code;
	int m_iscroll_move;
	RECT collider;
	short m_simagenum;
	bool firstcollideflag;
public:
	Enemy();
	inline void setx(int i) { m_point.x = i; }
	inline void sety(int i) { m_point.y = i; }
	inline int getx() { return m_point.x; }
	inline int gety() { return m_point.y; }
	inline POINT getPoint() { return m_point; }
	inline int gettype_code() { return m_itype_code; }
	inline void setscroll_move(int i) { m_iscroll_move = i; }
	virtual void Init(HDC, HINSTANCE) = 0;
	virtual void Move() = 0;
	virtual void Draw(HDC) = 0;
	virtual void B_Draw(HDC) = 0;
	virtual void F_Draw(HDC) = 0;
	virtual bool CollideCheck(RECT) = 0;
	virtual ~Enemy() = 0;
};

class Ring : public Enemy
{
protected:
	BitMap RingImage[2][3];
public:
	Ring(HDC, HINSTANCE);
	virtual ~Ring();
	virtual void Init(HDC, HINSTANCE);
	void Move();
	void Draw(HDC);
	virtual void B_Draw(HDC);
	virtual void F_Draw(HDC);
	virtual bool CollideCheck(RECT);
};

class SmallRing : public Ring
{
private:
	BitMap SmallRingImage[3];
public:
	SmallRing(HDC, HINSTANCE);
	~SmallRing();
	void Init(HDC, HINSTANCE);
	void B_Draw(HDC);
	void F_Draw(HDC);
	bool CollideCheck(RECT);
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
	void Draw(HDC);
	void B_Draw(HDC);
	void F_Draw(HDC);
	bool CollideCheck(RECT);
};
