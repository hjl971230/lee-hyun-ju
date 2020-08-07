#pragma once
#include"mecro.h"
#include"BitMap.h"
struct Point
{
	int x;
	int y;
};

class Animal : public BitMap
{
private:
	int m_ibmpid;
	Point m_Point;
	TCHAR m_szName[128];
public:
	Animal();
	~Animal();
	inline void setbmpid(int i) { m_ibmpid = i; }
	inline int getbmpid() { return m_ibmpid; }
	inline void setPoint(int x, int y) { m_Point.x = x, m_Point.y = y; }
	inline Point getPoint() { return m_Point; }
	inline void setName(TCHAR name[]) { wsprintf(m_szName, name);}
	inline TCHAR* getName() { return m_szName; }
};

