#pragma once
#include"Block.h"

class GameManager
{
private:
	static GameManager* m_this;
	TCHAR m_timer[128];
	TCHAR m_minenumtext[128];
	int m_imin;
	int m_isec;
	POINT Lmouse;
	POINT Rmouse;
	BitMap m_BitMap;
	BitMap m_BG;
	int m_ilevel;
	int m_imapheight;
	int m_imapwidth;
	vector<vector<Block*>> m_vecmap;
	int m_itrapcount;
	int m_igametrapcount;
	bool m_btrapflag;
	bool m_bAllsearchflag;
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
	inline void setlevel(int i) { m_ilevel = i; }
	void Init(HDC, HINSTANCE);
	void Draw(HDC, HINSTANCE);
	void BGDraw();
	void TimeUpdate();
	void Lbutton_Click();
	void Rbutton_Click();
	void MouseReset();
	void MapInit(HDC, HINSTANCE);
	void MapDraw();
	void MapRelease();
	void LevelInit();
	void ChangeLevel(HINSTANCE);
	void trap_setrandom(int count);
	void trap_setcount(HINSTANCE);
	void DefaultCheck(int x, int y, int direction);
	void FinishCheck(HWND, HDC, HINSTANCE);
	bool ClearCheck();
};

