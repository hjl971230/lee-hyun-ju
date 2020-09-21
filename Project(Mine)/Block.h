#pragma once
#include"BitMap.h"
class Block
{
private:
	int m_iminecount;
	bool m_bhideflag;
	bool m_buseflag;
	POINT m_point;
	RECT collider;
	BitMap m_flag;
	BitMap m_mine;
	BitMap m_block;
	BitMap m_numbers[BLOCK_COUNT];
public:
	Block();
	~Block();
	inline void setx(int i) { m_point.x = i; }
	inline void sety(int i) { m_point.y = i; }
	inline int getx() { return m_point.x; }
	inline int gety() { return m_point.y; }
	inline POINT getPoint() { return m_point; }
	void Init(HDC, HINSTANCE);
	void numbersload(HDC, HINSTANCE);
};

