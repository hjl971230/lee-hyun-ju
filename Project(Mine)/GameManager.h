#pragma once
#include"Block.h"

class GameManager
{
private:
	static GameManager* m_this;
	TCHAR m_mintimer[128];
	TCHAR m_sectimer[128];
	TCHAR m_timer[128];
	int m_imin;
	int m_isec;
	POINT Lmouse;
	POINT Rmouse;
	BitMap m_BitMap;
	BitMap m_BG;
	int m_ilevel;
	vector<vector<Block>> m_vecmap;
public:
	inline static GameManager* GetInstance()
	{
		if (m_this == NULL) m_this = new GameManager;
		return m_this;
	}
	GameManager();
	~GameManager();
	inline void setLmousepoint(int x, int y) { Lmouse.x = x; Lmouse.y = y; }
	inline void setRmousepoint(int x, int y) { Rmouse.x = x; Rmouse.y = y; }
	void Init(HDC, HINSTANCE);
	void Draw(HDC, HINSTANCE);
	void TimeUpdate();
	void Click();
	void MouseReset();
	void MapInit(HDC, HINSTANCE);
};

