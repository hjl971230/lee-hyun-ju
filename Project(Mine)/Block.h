#pragma once
#include"BitMap.h"
class Block
{
private:
	int m_iminecount;
	int m_ihideflag;
	POINT m_point;
	RECT collider;
	BitMap m_flag;
	BitMap m_mine;
	BitMap m_block;
	BitMap m_numbers;
public:
	Block();
	~Block();
	inline void setx(int i) { m_point.x = i; }
	inline void sety(int i) { m_point.y = i; }
	inline int getx() { return m_point.x; }
	inline int gety() { return m_point.y; }
	inline POINT getPoint() { return m_point; }
	inline BitMap getblock() { return m_block; }
	void Init(HDC, HINSTANCE);
	void numbersload(HDC, HINSTANCE);
	void Draw(HDC hdc, int x, int y, float scale_x = 1, float scale_y = 1);
};

