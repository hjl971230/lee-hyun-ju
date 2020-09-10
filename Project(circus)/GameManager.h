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
	TCHAR nowMiter[128];
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
	void Update(HDC);
	void PlayGame();
	void KeyInput();
};

