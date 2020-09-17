#pragma once
#include"Player.h"
#include"EnemyManager.h"

class GameManager
{
private:
	static GameManager* m_this;
	BitMap m_BitMap;
	BitMap m_BG[4];
	BitMap m_Miter;
	int m_ibacksize;
	int m_idecosize;
	int m_inormalcount;
	int m_imitercount;
	int m_imiter;
	int m_imovemiter;
	bool m_bwinflag;
	bool m_bgameflag;
	TCHAR nowMiter[128];
	BitMap End;
	BitMap Icon;
	BitMap Star[3];
	int m_iNormal_ver;
	POINT mouse;
	RECT StartButton;
	RECT ExitButton;
public:
	static GameManager* GetInstance()
	{
		if (m_this == NULL)
			m_this = new GameManager;
		return m_this;
	}
	GameManager();
	~GameManager();
	inline bool getgameflag() { return m_bgameflag; }
	inline void setmouse(int x, int y) { mouse.x = x; mouse.y = y; }
	void GameInit(HDC, HINSTANCE);
	void GameDraw(HDC, HINSTANCE);
	void GameTitle(HDC, HINSTANCE);
	void BGDraw(HDC);
	void ScoreLifeDraw(HDC);
	void Update(HDC, HWND, HINSTANCE);
	void Win(HDC, HWND, HINSTANCE);
	void Die(HDC, HWND, HINSTANCE);
	void PlayGame();
	void KeyInput();
	void GameOver(HDC, HINSTANCE);
	bool finishcheck();
};

