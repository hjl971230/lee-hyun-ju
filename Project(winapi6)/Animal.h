#pragma once
#include"Bitmap.h"
struct Point
{
	int x;
	int y;
};

class Animal : public Bitmap
{
private:
	int m_ibmpid;
	Point m_Point;
	TCHAR m_szName[128];
	bool m_bmatchflag;
	bool m_bClickflag;
	bool m_bcompleteflag;
public:
	Animal();
	~Animal();
	void Draw(HDC hdc);
	inline void setbmpid(int i) { m_ibmpid = i; }
	inline int getbmpid() { return m_ibmpid; }
	inline void setPoint(int x, int y) { m_Point.x = x, m_Point.y = y; }
	inline Point getPoint() { return m_Point; }
	inline void setName(TCHAR name[]) { wsprintf(m_szName, name); }
	inline TCHAR* getName() { return m_szName; }
	inline void setmatchflag(bool b) { m_bmatchflag = b; }
	inline bool getmatchflag() { return m_bmatchflag; }
	inline void setClickflag(bool b) { m_bClickflag = b; }
	inline bool getClickflag() { return m_bClickflag; }
	inline void setcompleteflag(bool b) { m_bcompleteflag = b; }
	inline bool getcompleteflag() { return m_bcompleteflag; }
};

