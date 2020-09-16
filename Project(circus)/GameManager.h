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
	bool winflag;
	TCHAR nowMiter[128];
	BitMap End;
	BitMap Icon;
	int m_iNormal_ver;
public:
	static GameManager* GetInstance()
	{
		if (m_this == NULL)
			m_this = new GameManager;
		return m_this;
	}
	GameManager();
	~GameManager();
	void GameInit(HDC, HINSTANCE);
	void GameDraw(HDC, HINSTANCE);
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

