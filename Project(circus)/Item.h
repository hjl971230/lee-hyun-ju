#pragma once
#include "BitMap.h"
class Item
{
protected:
	BitMap Cash;
	POINT m_point;
public:
	Item();
	~Item();
	inline void setx(int i) { m_point.x = i; }
	inline void sety(int i) { m_point.y = i; }
	inline int getx() { return m_point.x; }
	inline int gety() { return m_point.y; }
	inline POINT getPoint() { return m_point; }
	void Init(HDC, HINSTANCE);
	void Draw(HDC);
};

